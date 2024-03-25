
#include <iostream>
# include "Image_Class.h"
using namespace std;

int main() {
    string filename;
    cout << "Please Enter image name to turn to gray scale: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

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

    cout << "please Enter image name to store new image\n";
    cout << "choose file .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);


    return 0;
}
