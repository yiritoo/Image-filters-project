// Yassen elsayed Kamal - 20230471 - Inverted colors filter - Rotate image filter - Blur image filter - Image frame filter - Infrared Filter
// Abdullah Ahmed - 20230224 - Grayscale filter - Darken and lighten filters - Purple filter - Merge images - Edge detection filter
// Marwan Khaled - 20230383 - Flip image filter - Sunlight filter - Resize Filter - Black and white filter - Crop filter
// https://drive.google.com/drive/u/0/folders/1keBVDo1Z1SmInZrtIQo4SipA1jOb6u36 (System diagram for the Program)
// https://github.com/yiritoo/Image-filters-project

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <limits>
#include "Image_Class.h"
using namespace std;

// Function for saving image
void Saveimage(Image& image, string& filename){

    cout << "1- Replace existing image\n";
    cout << "2- Save Image in a new file\n";
    cout << "3- Close\n";
    int choice;
    cin >> choice;

    if (choice == 1){// Saving in Same File
        image.saveImage(filename);
    }
    else if (choice == 2){ // Saving in New File
        cout << "Enter a new name to store new image: ";
        cin >> filename;

        while (true){
            try {
                image.saveImage(filename);
                break;
            }
            catch(invalid_argument) {
                cout <<  "Enter the file name with correct extension: ";
                cin >> filename ;
            }
        }
    }
    else if (choice == 3){
        cout << "Terminating program";
        exit(0);
    }
}

// Function for loading images
void loadimage(Image& image, string& filename){
    ifstream file;
    while (true) {
        try {
            cout << "Enter the file name of a colored image: ";
            cin >> filename;

            // Trying to open file to check if it exists
            file.open(filename);

            if (!file.is_open()) {
                throw runtime_error("Please enter a valid file name with correct extension");
            }
            break;

        } catch (const runtime_error &e) {
            cerr << e.what() << endl;
        }
    }
    file.close();
    image.loadNewImage(filename);
}

void inverseColors(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

void rotateImage(Image& image, int rotatepick) {
    Image newImage;
    if (rotatepick == 1) {
        Image newImage(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    newImage(image.height - 1 - j, i, k) = image(i, j, k);
                }
            }
        }
        image = newImage;
        
    } else if (rotatepick == 2) {
        Image newImage(image.width, image.height);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    newImage(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                }
            }
        }
        image = newImage;

    } else if (rotatepick == 3) {
        Image newImage(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    newImage(j, image.width - 1 - i, k) = image(i, j, k);
                }
            }
        }
        image = newImage;
    }
}

void flipImage(Image& image, const string& choose) {
    if (choose == "1") { // Horizontal Flip
        for (int i = 0; i < image.width / 2; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    // Flip pixels from right to left.
                    swap(image.getPixel(i, j, k), image.getPixel(image.width - i - 1, j, k));
                }
            }
        }
    } else if (choose == "2") { // Vertical Flip
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height / 2; j++) {
                for (int k = 0; k < 3; k++) {
                    // Flip pixels from up to down.
                    swap(image.getPixel(i, j, k), image.getPixel(i, image.height - j - 1, k));
                }
            }
        }
    }
}

void grayscale(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0; // Initialize average value
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }
            avg /= 3; // Calculate average
            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

void darkenLighten(Image& image, const string& colour) {
    if (colour == "Darken" || colour == "darken") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    int result = image(i, j, k) * 0.5;
                    if (result < 0) {
                        image(i, j, k) = 0;
                    } else
                        image(i, j, k) = result;
                }
            }
        }
    }
    else if (colour == "Lighten" || colour == "lighten") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    int result = image(i, j, k) * 1.5;
                    if (result > 255) {
                        image(i, j, k) = 255;
                    } else
                        image(i, j, k) = result;
                }
            }
        }
    }
}

void Infrared(Image& image) {
    const double minopacity = 0.1;
    const double maxopacity = 0.8;
    const unsigned char mincolor[] = {255, 35, 35};
    const unsigned char maxcolor[] = {255, 35, 35};

    // Convert to grayscale
    grayscale(image);

    // invert colors
    inverseColors(image);

    // Apply opacity and color mapping
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned char intensity = image(i, j, 0);
            double opacity = maxopacity + (minopacity - maxopacity) * (intensity / 255.0);
            unsigned char color[3];
            for (int k = 0; k < 3; ++k) {
                color[k] = mincolor[k] + (maxcolor[k] - mincolor[k]) * (intensity / 255.0);
            }
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = (1 - opacity) * image(i, j, k) + opacity * color[k];
            }
        }
    }

    // Lighten the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int result = image(i, j, k) * 1.5;
                if (result > 255) {
                    image(i, j, k) = 255;
                } else
                    image(i, j, k) = result;
            }
        }
    }
}

void blurImage(Image& image) {
    // Calculate the average dimension of the image
    int averageDimension = (image.width + image.height) / 2;
    const int maxDimension = 3000;
    
    // Calculate the blur radius using the average dimension
    int radius = (averageDimension * 20) / maxDimension;

    // Create a new image with the same dimensions as original
    Image blurredImage(image.width, image.height);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            // Initialize variables to store total color values of pixels and count
            int totalR = 0, totalG = 0, totalB = 0 , count = 0;

            // Iterate around the current pixel to calculate the average color
            for (int checkX = -radius; checkX <= radius; ++checkX) {
                for (int checkY = -radius; checkY <= radius; ++checkY) {
                    int x = i + checkX;
                    int y = j + checkY;

                    // Make sure the neighboring pixels are within the image bounds
                    if (x >= 0 && x < image.width && y >= 0 && y < image.height) {
                        // Accumulate the color values
                        totalR += image(x, y, 0);
                        totalG += image(x, y, 1);
                        totalB += image(x, y, 2);
                        count++;
                    }
                }
            }

            // Calculate the average color for the current pixel
            blurredImage(i, j, 0) = totalR / count;
            blurredImage(i, j, 1) = totalG / count;
            blurredImage(i, j, 2) = totalB / count;
        }
    }
    image = blurredImage;
}

void Frame(Image& image){

    // Choose suitable frame size
    const int smallerDimension = min(image.width, image.height);
    int frameSize = smallerDimension / 50;
    int colorchoice;
    int frameR, frameG, frameB;

    cout << "Select a main frame color: \n";
    cout << "1- Red\n";
    cout << "2- Blue\n";
    cout << "3- Green\n";
    cout << "4- White\n";
    cout << "5- Black\n";
    cin >> colorchoice;

    switch (colorchoice){
        case 1:
            frameR = 255;
            frameG = 0;
            frameB = 0;
            break;
        case 2:
            frameR = 0;
            frameG = 0;
            frameB = 255;
            break;
        case 3:
            frameR = 0;
            frameG = 255;
            frameB = 0;
            break;
        case 4:
            frameR = 255;
            frameG = 255;
            frameB = 255;
            break;
        case 5:
            frameR = 0;
            frameG = 0;
            frameB = 0;
            break;
        default:
            cout << "Invalid choice, please select a valid choice\n";
            cout << "1- Red\n";
            cout << "2- Blue\n";
            cout << "3- Green\n";
            cout << "4- White\n";
            cout << "5- Black\n";
            cin >> colorchoice;
    }

    int frameaccentpick;
    int frameaccentR, frameaccentG, frameaccentB;
    cout << "Select a secondary color for the frame: \n";
    cout << "1- Red\n";
    cout << "2- Blue\n";
    cout << "3- Green\n";
    cout << "4- White\n";
    cout << "5- Black\n";
    cin >> frameaccentpick;

    switch (frameaccentpick){
        case 1:
            frameaccentR = 255;
            frameaccentG = 0;
            frameaccentB = 0;
            break;
        case 2:
            frameaccentR = 0;
            frameaccentG = 0;
            frameaccentB = 255;
            break;
        case 3:
            frameaccentR = 0;
            frameaccentG = 255;
            frameaccentB = 0;
            break;
        case 4:
            frameaccentR = 255;
            frameaccentG = 255;
            frameaccentB = 255;
            break;
        case 5:
            frameaccentR = 0;
            frameaccentG = 0;
            frameaccentB = 0;
            break;
        default:
            cout << "Invalid choice, please select a valid choice\n";
            cout << "1- Red\n";
            cout << "2- Blue\n";
            cout << "3- Green\n";
            cout << "4- White\n";
            cout << "5- Black\n";
            cin >> frameaccentpick;
    }

    int framepick;
    cout << "Choose the type of frame you want: \n";
    cout << "1- Simple\n";
    cout << "2- Fancy\n";
    cin >> framepick;

    int cornerRadius;

    switch (framepick){
        case 1:
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    if (i < frameSize || i >= image.width - frameSize || j < frameSize || j >= image.height - frameSize) {
                        // Draw inner part of the frame
                        if (i < frameSize - 20 || i >= image.width - frameSize + 20 || j < frameSize - 20 || j >= image.height - frameSize + 20) {
                            image(i, j, 0) = frameR;
                            image(i, j, 1) = frameG;
                            image(i, j, 2) = frameB;
                        } 
                        // Draw outer part of the frame
                        else {
                            image(i, j, 0) = frameaccentR;
                            image(i, j, 1) = frameaccentG;
                            image(i, j, 2) = frameaccentB;
                        }
                    }
                }
            }
            break;

        case 2:
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    // Draw the first outer frame
                    if ((i < frameSize || i >= image.width - frameSize || j < frameSize || j >= image.height - frameSize) &&
                        !(i < frameSize - 20 || i >= image.width - frameSize + 20 || j < frameSize - 20 || j >= image.height - frameSize + 20)) {
                        image(i, j, 0) = frameaccentR;
                        image(i, j, 1) = frameaccentG;
                        image(i, j, 2) = frameaccentB;
                    }
                    // Draw the second outer frame
                    else if ((i < frameSize - 20 || i >= image.width - frameSize + 20 || j < frameSize - 20 || j >= image.height - frameSize + 20) &&
                            !(i < frameSize - 40 || i >= image.width - frameSize + 40 || j < frameSize - 40 || j >= image.height - frameSize + 40)) {
                        image(i, j, 0) = frameaccentR;
                        image(i, j, 1) = frameaccentG;
                        image(i, j, 2) = frameaccentB;
                    }
                    // Draw the inner part of the frame
                    else if (i < frameSize + 20 || i >= image.width - frameSize + 20 || j < frameSize + 20 || j >= image.height - frameSize + 20) {
                        image(i, j, 0) = frameR;
                        image(i, j, 1) = frameG;
                        image(i, j, 2) = frameB;
                    }
                }
            }

            // Add diagonal lines
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    // Draw the lines
                    if ((i + j) % 20 == 0) {
                        image(i, j, 0) = frameaccentR;
                        image(i, j, 1) = frameaccentG;
                        image(i, j, 2) = frameaccentB;
                    }
                }
            }

            // Add small circles at the corners
            cornerRadius = 50;
            for (int i = 0; i < cornerRadius; ++i) {
                for (int j = 0; j < cornerRadius; ++j) {
                    if (i * i + j * j <= cornerRadius * cornerRadius) {
                        // Top-left corner
                        image(i, j, 0) = frameaccentR;
                        image(i, j, 1) = frameaccentG;
                        image(i, j, 2) = frameaccentB;
                        
                        // Top-right corner
                        image(image.width - i - 1, j, 0) = frameaccentR;
                        image(image.width - i - 1, j, 1) = frameaccentG;
                        image(image.width - i - 1, j, 2) = frameaccentB;
                        
                        // Bottom-left corner
                        image(i, image.height - j - 1, 0) = frameaccentR;
                        image(i, image.height - j - 1, 1) = frameaccentG;
                        image(i, image.height - j - 1, 2) = frameaccentB;
                        
                        // Bottom-right corner
                        image(image.width - i - 1, image.height - j - 1, 0) = frameaccentR;
                        image(image.width - i - 1, image.height - j - 1, 1) = frameaccentG;
                        image(image.width - i - 1, image.height - j - 1, 2) = frameaccentB;
                    }
                }
            }
            break;
            
        default:
            cout << "Invalid choice, please select a valid choice\n";
            cout << "1- Simple\n";
            cout << "2- Fancy\n";
            cin >> framepick;
            break;
    }
}

void Merge(Image& image, string& filename2){
    cout << "Please enter Image 2 To Merge with Image 1:\n";
    cin >> filename2;
    Image image2(filename2);
    if ((image.width == image2.width) && (image.height == image2.height)) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }
    }
    else {
        cout << "1- Resize to the Biggest common height and width then merge\n";
        cout << "2- Merge common area between smallest height and width\n";
        int num;
        cin >> num;
        switch (num) {
            case 1: {
                Image image2(filename2);
                int a = max(image.width, image2.width);
                int b = max(image.height, image2.height);
                Image resizedImage(a, b);
                double ratioX = double(image.width) / a;
                double ratioY = double(image.height) / b;

                for (int i = 0; i < a; i++) {
                    for (int j = 0; j < b; j++) {
                        int X = round(i * ratioX);
                        int Y = round(j * ratioY);

                        X = min(max(X, 0), image.width - 1);
                        Y = min(max(Y, 0), image.height - 1);

                        for (int k = 0; k < image.channels; k++) {
                            resizedImage.setPixel(i, j, k, image.getPixel(X, Y, k));
                        }
                    }
                }
                resizedImage.saveImage("test.jpg");
                image.loadNewImage("test.jpg");
                Image resizedImage2(a, b);
                double ratio2X = double(image2.width) / a;
                double ratio2Y = double(image2.height) / b;

                for (int i = 0; i < a; i++) {
                    for (int j = 0; j < b; j++) {
                        int X = round(i * ratio2X);
                        int Y = round(j * ratio2Y);

                        X = min(max(X, 0), image2.width - 1);
                        Y = min(max(Y, 0), image2.height - 1);

                        for (int k = 0; k < image2.channels; k++) {
                            resizedImage2.setPixel(i, j, k, image2.getPixel(X, Y, k));
                        }
                    }
                }
                resizedImage2.saveImage("test.jpg");
                image2.loadNewImage("test.jpg");
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            image(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                        }
                    }
                }
                break;
            }
            case 2: {
                Image image2(filename2);
                int width, height;
                width = min(image.width, image2.width);
                height = min(image.height, image2.height);
                Image image3(width, height);
                for (int i = 0; i < width; ++i) {
                    for (int j = 0; j < height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            unsigned int result = (image(i, j, k) + image2(i, j, k)) / 2;
                            image3(i, j, k) = result;
                        }
                    }
                }
                image = image3;
                break;
            }
        }
    }
}

void Purple(Image& image){

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int green = image(i,j,1);
            unsigned int newGreen = green * 0.7;
            image(i,j,1) = newGreen;
        }
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int result = image(i, j, k) * 1.25;
                if (result > 255) {
                    image(i, j, k) = 255;
                } else
                    image(i, j, k) = result;
            }
        }
    }
}

void Sunlight(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int Blue = image(i,j,2);
            unsigned int newBlue = Blue * 0.7;
            image(i,j,2) = newBlue;
        }
    }
}

void blackandwhite (Image& image) {
    int mean = 127;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = 0;
                if (avg < mean)
                    image(i, j, k) = 0;
                else
                    image(i, j, k) = 255;
            }
        }
    }
}

void Resize(Image& image){
    int a, b;
    cout << "Please enter the dimensions of resized image:\n";
    while (!(cin >> a >> b) || a <= 0 || b <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter the dimensions of resized image:\n";
    }
    
    Image resizedImage(a, b);

    double ratioX = double(image.width) / a;
    double ratioY = double(image.height) / b;

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            int X = round(i * ratioX);
            int Y = round(j * ratioY);

            X = min(max(X, 0), image.width - 1);
            Y = min(max(Y, 0), image.height - 1);

            for (int k = 0; k < 3; k++) {
                resizedImage.setPixel(i, j, k, image.getPixel(X, Y, k));
            }
        }
    }
    image = resizedImage;
}

void Crop (Image& image){
    int w, h, x, y;
    cout << "Please enter the dimensions of the cropped image:\n";

    while (!(cin >> w >> h) || w <= 0 || h <= 0) {
        // Check for invalid inputs
        cin.clear();    // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid inputs. Please enter the dimensions of the cropped image:\n";
    }

    cout << "Please enter the starting and ending point:\n";

    while (!(cin >> x >> y) || x < 0 || y < 0 || x + w > image.width || y + h > image.height) {
        // Check validate inputs
        cin.clear();    // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid inputs. Please enter the starting point:\n";
    }
    Image croppedImage(w, h);

    for (int i = 0; i < w; i++) {  // Copy pixels from original image to cropped image
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < 3; k++) {
                croppedImage.setPixel(i, j, k, image.getPixel(x + i, y + j, k));
            }
        }
    }   
    image = croppedImage;
}

void DetectEdges(Image& image) {

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    int array_x[3][3] = {{-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1}};
    int array_y[3][3] = {{-1, -2, -1},
                         {0,  0,  0},
                         {1,  2,  1}};
    Image edges(image.width, image.height);
    for (int x = 1; x < image.width - 1; ++x) {
        for (int y = 1; y < image.height - 1; ++y) {
            int x_edges = 0;
            int y_edges = 0;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    x_edges = x_edges + array_x[j + 1][i + 1] * image(x + i, y + j, 0);
                    y_edges = y_edges + array_y[j + 1][i + 1] * image(x + i, y + j, 0);
                }
            }
            double result = sqrt(x_edges * x_edges + y_edges * y_edges);
            if(result>127.5){
                result = 0;
            }
            else{
                result = 255;
            }
            for (int c = 0; c < 3; ++c) {
                edges(x, y, c) = result;
            }
        }
    }
    for (int x = 0; x < image.width; ++x) {
        for (int y = 0; y < image.height; ++y) {
            for (int c = 0; c < 3; ++c) {
                image(x, y, c) = edges(x, y, c);
            }
        }
    }
}

int main() {
    Image image;
    string filename;
    while (true) {
        cout << "\n『•• Welcome To The Image Filtering Program ••』\n";
        int pick;
        cout << "\n 1- Load image | 2- Save image\n\n 3- Inverse colors filter | 4- Rotate image\n\n 5- Flip image | 6- Grayscale filter\n\n 7- Darken/lighten image | 8- Infrared Filter\n\n 9- Blur image | 10- Image Frame\n\n 11- Merge | 12- Purple filter\n\n 13- Sunlight filter | 14- Black/White filter\n\n 15- Resize image | 16- Crop image\n\n 17- Detect Edges | 0- Exit program\n\n";
        while (true) {
            if (cin >> pick && pick >= 0 && pick <= 17) {
                break;
            } 
            else {
                cout << "Invalid input. Please enter a number between 0 and 17: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if (pick == 1){
            loadimage(image, filename);
        }

        else if (pick == 2){
            Saveimage(image, filename);
        }

        else if (pick == 3) {
            inverseColors(image);
        }

        else if (pick == 4) {
            int rotatepick;
            cout << "How much would you like to rotate your image?\n";
            cout << "1- 90°\n";
            cout << "2- 180°\n";
            cout << "3- 270°\n";
            cin >> rotatepick;

            while ((rotatepick != 1) && (rotatepick != 2) && (rotatepick != 3)) { // A loop that makes the user choose a valid choice
                cout << "Invalid choice. Please choose the amount of image rotation: \n";
                cout << "1- 90°\n";
                cout << "2- 180°\n";
                cout << "3- 270°\n";
                cin >> rotatepick;
            }
            rotateImage(image, rotatepick);
        }

        else if (pick == 5) {
            string choose;
            cout << "Please choose the type of image flipping: \n1) Horizontal \n2) Vertical\n";
            cin >> choose;
            while ((choose != "1") && (choose != "2")) { // A loop that makes the user choose a valid choice
                cout << "Invalid choice. Please choose the type of image flipping: \n1) Horizontal \n2) Vertical\n";
                cin >> choose;
            }
            flipImage(image, choose);
        }

        else if (pick == 6) {
            grayscale(image);
        }

        else if (pick == 7) {
            string colour;
            cout << "To choose type Darken or Lighten: \n";
            cin >> colour;
            while ((colour != "darken") && (colour != "lighten") && (colour != "Lighten") && (colour != "Darken")){
                cout << "Invalid choice. Please type either Darken or Lighten: \n";
                cin >> colour;
            }
            darkenLighten(image, colour);
        }

        else if (pick == 8){
            Infrared(image);
        }

        else if (pick == 9){
            blurImage(image);
        }

        else if (pick == 10) {
            Frame(image);
        }

        else if (pick == 11){
            string filename2;
            Merge(image, filename2);
        }

        else if (pick == 12){
            Purple(image);
        }

        else if (pick == 13){
            Sunlight(image);
        }

        else if (pick == 14){
            blackandwhite(image);
        }

        else if (pick == 15){
            Resize(image);
        }

        else if (pick == 16){
            Crop(image);
        }

        else if (pick == 17){
            DetectEdges(image);
        }

        else if (pick == 0) {
            cout << "Exiting the program...";
            break;
        }
    }
return 0;
}