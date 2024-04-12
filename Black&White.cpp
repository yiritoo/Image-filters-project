#include "Image_Class.h"

using namespace std;

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

int main() {
    string filename;
    cout << "Please enter the name of the image to filter in black & white:";
    cin >> filename;
    Image image(filename);
    blackandwhite(image);
    cout << "Please enter a filename to store the new black & white image (with extension .jpg, .bmp, .png, .tga):";
    cin >> filename;
    image.saveImage(filename);
    return 0;
}
