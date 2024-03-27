// Yassen elsayed Kamal - 20230471 - Inverted colors filter & Rotate image filter
// Abdullah Ahmed - 20230224 - Grayscale - Darken and lighten filters
// Marwan Khaled - 20230383 - Flip image

#include <iostream>
#include "Image_Class.h"
using namespace std;

void inverseColors(Image& image, const string& filename) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    image.saveImage(filename);
}

void rotateImage(Image& image, const string& filename, int rotatepick) {
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
        newImage.saveImage(filename);
        
    } else if (rotatepick == 2) {
        Image newImage(image.width, image.height);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    newImage(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                }
            }
        }
        newImage.saveImage(filename);

    } else if (rotatepick == 3) {
        Image newImage(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    newImage(j, image.width - 1 - i, k) = image(i, j, k);
                }
            }
        }
        newImage.saveImage(filename);
    }
}

void flipImage(Image& image, const string& filename, const string& choose) {
    if (choose == "1") { // Horizontal Flip
        for (int i = 0; i < image.width / 2; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    // Flip pixels from right to left.
                    swap(image.getPixel(i, j, k), image.getPixel(image.width - i - 1, j, k));
                }
            }
        }
    } else if (choose == "2") { // Vertical Flip
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height / 2; j++) {
                for (int k = 0; k < image.channels; k++) {
                    // Flip pixels from up to down.
                    swap(image.getPixel(i, j, k), image.getPixel(i, image.height - j - 1, k));
                }
            }
        }
    }
    image.saveImage(filename);
}

void grayscale(Image& image, const string& filename) {
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
    image.saveImage(filename);
}

void darkenLighten(Image& image, const string& filename, const string& colour) {
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
    image.saveImage(filename);
}

int main() {
    string filename;
    cout << "Enter the file name of a colored image: ";
    cin >> filename;
    while (true) {
        cout << "Choose a filter for the image: \n";
        Image image(filename);
        int pick;
        cout << "1- Inverse colors filter\n";
        cout << "2- Rotate image\n";
        cout << "3- Flip image\n";
        cout << "4- Grayscale filter\n";
        cout << "5- Darken and lighten image\n";
        cout << "0- Exit program\n";
        cin >> pick;

        if (pick == 1) {
            string newFilename;
            cout << "Enter a new image name to store new image\n";
            cout << "and specify extension .jpg, .bmp, .png, .tga: ";
            cin >> newFilename;
             inverseColors(image, newFilename);
        }

        else if (pick == 2) {
            int rotatepick;
            cout << "How much would you like to rotate your image?\n";
            cout << "1- 90°\n";
            cout << "2- 180°\n";
            cout << "3- 270°\n";
            cin >> rotatepick;

            while ((rotatepick != 1) && (rotatepick != 2) && (rotatepick != 3)) { // A loop that makes the user choose a valid choice.
                cout << "Invalid choice. Please choose the amount of image rotation: \n";
                cout << "1- 90°\n";
                cout << "2- 180°\n";
                cout << "3- 270°\n";
                cin >> rotatepick;
            }

            string newFilename;
            cout << "Please enter the filename to store the rotated image (with extension .jpg, .bmp, .png, .tga): ";
            cin >> newFilename;
            rotateImage(image, newFilename, rotatepick);
            cout << "Rotated image saved as " << newFilename << endl;
        }

        else if (pick == 3) {
            string choose;
            cout << "Please choose the type of image flipping: \n1) Horizontal \n2) Vertical\n";
            cin >> choose;
            while ((choose != "1") && (choose != "2")) { // A loop that makes the user choose a valid choice.
                cout << "Invalid choice. Please choose the type of image flipping: \n1) Horizontal \n2) Vertical\n";
                cin >> choose;
            }

            string newFilename;
            cout << "Please enter the image name to store the new image and specify the extension (.jpg, .bmp, .png, .tga): ";
            cin >> newFilename;
            flipImage(image, newFilename, choose);
        }

        else if (pick == 4) {
            string newFilename;
            cout << "Please Enter image name to store new image\n";
            cout << "choose file .jpg, .bmp, .png, .tga: ";
            cin >> newFilename;
            grayscale(image, newFilename);
        }

        else if (pick == 5) {
            string colour, newFilename;
            cout << "To choose type Darken or Lighten: " << endl;
            cin >> colour;
            cout << "Please Enter Image Name To Store New Image And (with extension .jpg, .bmp, .png, .tga): ";
            cin >> newFilename;
            darkenLighten(image, newFilename, colour);
        }

        else if (pick == 0) {
            break;
        }
    }

    return 0;
}
