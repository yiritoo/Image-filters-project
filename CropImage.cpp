#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

void cropimage (Image& image, Image& croppedImage, const int& x, const int& y, const int& w, const int& h) {
        for (int i = 0; i < w; i++) {  // Copy pixels from original image to cropped image
            for (int j = 0; j < h; j++) {
                for (int k = 0; k < image.channels; k++) {
                    croppedImage.setPixel(i, j, k, image.getPixel(x + i, y + j, k));
                }
            }
        }
}

int main() {
    int w, h, x, y;
    string filename;
    cout << "Please enter an image name:\n";
    cin >> filename;
    cout << "Please enter the dimensions of the cropped image:\n";
    Image image(filename);

    while (!(cin >> w >> h) || w <= 0 || h <= 0) {
        // Check for invalid inputs
        cin.clear();    // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid inputs. Please enter the dimensions of the cropped image:\n";
    }

    cout << "Please enter the starting point:\n";

    while (!(cin >> x >> y) || x < 0 || y < 0 || x + w > image.width || y + h > image.height) {
        // Check validate inputs
        cin.clear();    // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid inputs. Please enter the starting point:\n";
    }

    Image croppedImage(w, h);  // Create a new image for the cropped region

    cropimage(image, croppedImage, x, y, w, h);
    cout << "Please enter a new image name to store the cropped image (with extension .jpg, .bmp, .png, .tga):\n";
    cin >> filename;
    croppedImage.saveImage(filename);
    return 0;
}