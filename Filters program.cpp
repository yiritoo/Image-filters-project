#include <iostream>
#include "Image_Class.h"
using namespace std;

int main() {
    string filename;
    cout << "Enter the file name of a colored image: ";
    cin >> filename;
    cout << "Choose a filter for the image: \n";
    int pick;
    cout << "1- Inverse colors filter\n";
    cout << "2- Rotate image\n";
    cout << "0- Exit program\n";
    cin >> pick;

    if (pick == 1){

        Image image(filename);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                for (int k = 0; k < 3; ++k) {
                    image(i,j,k) = 255 - image(i, j, k);
                }
            }
        }
        cout << "Enter a new image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";

        cin >> filename;
        image.saveImage(filename);
        return 0;
    }

    else if (pick == 2){
        int rotatepick;
        cout << "How much would u like to rotate your image?\n";
        cout << "1- 90°\n";
        cout << "2- 180°\n";
        cout << "3- 270°\n";
        cin >> rotatepick;

        if (rotatepick == 1){
            
            Image image(filename);
            Image newImage(image.height, image.width);

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        newImage(image.height - 1 - j, i, k) = image(i, j, k);
                    }
                }
            }

            cout << "Please enter the filename to store the rotated image (with extension .jpg, .bmp, .png, .tga): ";
            cin >> filename;
            newImage.saveImage(filename);
        }

        else if (rotatepick == 2){
            Image image(filename);
            Image newImage(image.width, image.height);

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        newImage(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                    }
                }
            }

            cout << "Please enter the filename to store the rotated image (with extension .jpg, .bmp, .png, .tga): ";
            cin >> filename;
            newImage.saveImage(filename);
        }

        else if (rotatepick == 3){
            Image image(filename);
            Image newImage(image.height, image.width);

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        newImage(j, image.width - 1 - i, k) = image(i, j, k);
                    }
                }
            }

            cout << "Please enter the filename to store the rotated image (with extension .jpg, .bmp, .png, .tga): ";
            cin >> filename;
            newImage.saveImage(filename);
        }
        
        cout << "Rotated image saved as " << filename << endl;
        return 0;
    }
    
    else if (pick == 0){
        return 0;
    }
}