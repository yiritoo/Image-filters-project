#include "Image_Class.h"
using namespace std;

void sunlight (Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            unsigned char& red = image(x, y, 0);
            unsigned char& green = image(x, y, 1);
            unsigned char& blue = image(x, y, 2);

    red = min(red + 25, 255);
    green = min(green + 25, 255);
    blue = max(blue - 25, 0);
        }
    }
}

int main() {
    string filename;
    cout << "Please enter the name of the image to filter in sunlight:";
    cin >> filename;
    Image image(filename);
    sunlight(image);
    cout << "Please enter a filename to store the new black & white image (with extension .jpg, .bmp, .png, .tga):";
    cin >> filename;
    image.saveImage(filename);
    return 0;
}
