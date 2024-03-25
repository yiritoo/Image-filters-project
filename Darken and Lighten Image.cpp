#include <iostream>
#include "Image_Class.h"
using namespace std;

int main() {
    string File_Name;
    cout<<"Please Enter Image Name To Turn To Darken and Lighten Image: "<<endl;
    cin>>File_Name;
    Image image(File_Name);
    string colour;
    cout<<"Choose Image Darken OR Lighten: "<<endl;
    cin>>colour;
    if(colour=="Darken"||colour=="darken") {
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
    if(colour=="Lighten"||colour=="lighten") {
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
    string File_Name2;
    cout<<"Please Enter Image Name To Store New Image And (with extension .jpg, .bmp, .png, .tga): ";
    cin>>File_Name2;
    image.saveImage(File_Name2);
    return 0;
}