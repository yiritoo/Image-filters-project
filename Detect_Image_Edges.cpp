#include "Image_Class.h"
#include<iostream>
using namespace std;
void Image_Edges() {
    string filename;
    cout << "Please Enter Image name To Detect Image Edges:\n";
    cin >> filename;
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    int array_x[3][3] = {{-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1}};
    int array_y[3][3] = {{-1, -2, -1},
                         {0,  0,  0},
                         {1,  2,  1}};
    Image edges(image.width, image.height);
    for (int x = 1; x < image.width - 1; ++x) {
        for (int y = 1; y < image.height - 1; ++y) {
            int x_edges = 0;
            int y_edges = 0;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    x_edges = x_edges + array_x[j + 1][i + 1] * image(x + i, y + j, 0);
                    y_edges = y_edges + array_y[j + 1][i + 1] * image(x + i, y + j, 0);
                }
            }
            double result = sqrt(x_edges * x_edges + y_edges * y_edges);
            if(result>127.5){
                result = 0;
            }
            else{
                result = 255;
            }
            for (int c = 0; c < 3; ++c) {
                edges(x, y, c) = result;
            }
        }
    }
    for (int x = 0; x < image.width; ++x) {
        for (int y = 0; y < image.height; ++y) {
            for (int c = 0; c < 3; ++c) {
                image(x, y, c) = edges(x, y, c);
            }
        }
    }
    cout << "please Enter image name to store new image";
    cout << " and specify extension .jpg, .bmp, .png, .tga:\n";

    cin >> filename;
    image.saveImage(filename);
}
int main(){
    Image_Edges();
}

