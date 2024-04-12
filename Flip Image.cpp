#include "Image_Class.h"
using namespace std;

void flipImage(Image& image, const string& choose) {
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
}

int main() {
    string filename;
    string choose;
    cout << "Please enter the image name to flip:";
    cin >> filename;
    cin.ignore();
    Image image(filename);
    cout << "Please choose the type of image flipping: \n1) Horizontal \n2) Vertical\n";
    getline(cin, choose);

    while ((choose != "1") && (choose != "2")) { // A loop that make user to choose a valid choice.
        cout << "Invalid choice. Please choose the type of image flipping: \n1) Horizontal \n2) Vertical\n";
        getline(cin, choose);
    }

    flipImage(image, choose);

    cout << "Please enter the image name to store the new image and specify the extension (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    image.saveImage(filename);
    return 0;
}
