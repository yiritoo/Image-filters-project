#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

void resizingimage (Image& image, Image& resizedImage, const int& a, const int& b) {
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
}

int main() {
    int a, b;
    string filename;
    cout << "Please enter a image name:\n";
    cin >> filename;
    cout << "Please enter the dimensions of resized image:\n";

    while (!(cin >> a >> b) || a <= 0 || b <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter the dimensions of resized image:\n";
    }

    Image image(filename);
    Image resizedImage(a, b);
    resizingimage(image, resizedImage, a, b);
    cout << "Please enter a image name to store new image and specify (with extension .jpg, .bmp, .png, .tga):\n";
    cin >> filename;
    resizedImage.saveImage(filename);
    return 0;
}