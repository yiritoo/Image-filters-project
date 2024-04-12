#include "Image_Class.h"
using namespace std;

void sunlight (Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            unsigned char& r = image(x, y, 0);
            unsigned char& g = image(x, y, 1);
            unsigned char& b = image(x, y, 2);

    r = min(r + 25, 255);
    g = min(g + 25, 255);
    b = max(b - 25, 0);
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