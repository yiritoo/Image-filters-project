#include "Image_Class.h"
#include <iostream>
using namespace std;
int main() {
    string file_name1;
    string file_name2;
    cout << "Please Enter Image_1 To Merge with Image_2:\n";
    getline(cin, file_name1);
    cout << "Please Enter Image_2 To Merge with Image_1:\n";
    getline(cin, file_name2);
    Image image1(file_name1);
    Image image2(file_name2);
    if ((image1.width == image2.width) && (image1.height == image2.height)) {
        for (int i = 0; i < image1.width; ++i) {
            for (int j = 0; j < image1.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image1(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }
        string file_name3;
        cout << "Please Enter Image name To Store New Image";
        cout << " and specify extension (.jpg, .bmp, .png, .tga):";
        getline(cin, file_name3);
        image1.saveImage(file_name3);
    }
    else {
        cout << " choose one options from the  two options:\n";
        cout << "(1)-resize both images to the biggest height and the biggest width and then merge.\n";
        cout << "(2)-the other option is to merge the common area of the smaller width and the smaller height.\n";
        int num;
        cin >> num;
        switch (num) {
            case 1: {
                Image image1(file_name1);
                Image image2(file_name2);
                int a = max(image1.width, image2.width);
                int b = max(image1.height, image2.height);
                Image resizedImage(a, b);
                double ratioX = double(image1.width) / a;
                double ratioY = double(image1.height) / b;

                for (int i = 0; i < a; i++) {
                    for (int j = 0; j < b; j++) {
                        int X = round(i * ratioX);
                        int Y = round(j * ratioY);

                        X = min(max(X, 0), image1.width - 1);
                        Y = min(max(Y, 0), image1.height - 1);

                        for (int k = 0; k < image1.channels; k++) {
                            resizedImage.setPixel(i, j, k, image1.getPixel(X, Y, k));
                        }
                    }
                }
                resizedImage.saveImage("test.jpg");
                image1.loadNewImage("test.jpg");
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
                for (int i = 0; i < image1.width; ++i) {
                    for (int j = 0; j < image1.height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            image1(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                        }
                    }
                }
                string file_name3;
                cout << "Please Enter Image name To Store New Image";
                cout << " and specify extension (.jpg, .bmp, .png, .tga):";
                cin.ignore();
                getline(cin, file_name3);
                image1.saveImage(file_name3);
                break;
            }
            case 2: {
                Image image1(file_name1);
                Image image2(file_name2);
                int width, height;
                width = min(image1.width, image2.width);
                height = min(image1.height, image2.height);
                Image image3(width, height);
                for (int i = 0; i < width; ++i) {
                    for (int j = 0; j < height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            unsigned int result = (image1(i, j, k) + image2(i, j, k)) / 2;
                            image3(i, j, k) = result;
                        }
                    }
                }
                string file_name3;
                cout << "Please Enter Image name To Store New Image";
                cout << " and specify extension (.jpg, .bmp, .png, .tga):";
                cin.ignore();
                getline(cin, file_name3);
                image3.saveImage(file_name3);
                break;
            }
        }
    }
}
