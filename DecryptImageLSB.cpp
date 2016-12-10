#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DecryptImageLSB.out <Image_Path>\n");
        return -1;
    }

    Mat stego;
    stego = imread( argv[1], 1 );

    if ( !stego.data )
    {
        printf("No image data \n");
        return -1;
    }
    std::ofstream output;
    output.open("output.txt", std::fstream::out);
    int xPixel = 0;
    int yPixel = 0;
    int charVal = -1;
    while(charVal != 0) {
      int blue = stego.at<cv::Vec3b>(xPixel,yPixel)[0] % 8;
      int green = stego.at<cv::Vec3b>(xPixel,yPixel)[1] % 8;
      int red = stego.at<cv::Vec3b>(xPixel,yPixel)[2] % 4;
      charVal = (blue << 5) + (green << 2) + red;
      std::cout << blue << " " << green << " " << red << std::endl;
      std::cout << charVal << std::endl;
        output << char(charVal) << std::flush;
      xPixel++;
      if (xPixel>=stego.rows) {
        xPixel = 0;
        yPixel++;
      }
    }
    output.close();

    return 0;
}
