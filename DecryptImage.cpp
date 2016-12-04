#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DecryptImage.out <Image_Path>\n");
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
    //char ch;
    //char END_OF_FILE = '#';
    //secret.get(ch);
    //std::cout << stego.rows << std::endl;
    //std::cout << stego.cols << std::endl;
    int xPixel = 0;
    int yPixel = 0;
    int charVal = -1;
    while(charVal != 0) {
      //std::cout << stego.at<cv::Vec3b>(xPixel,yPixel)[0] << " " << stego.at<cv::Vec3b>(xPixel,yPixel)[1] << " " << stego.at<cv::Vec3b>(xPixel,yPixel)[2] << std::endl;
      int blue = stego.at<cv::Vec3b>(xPixel,yPixel)[0] % 8;
      int green = stego.at<cv::Vec3b>(xPixel,yPixel)[1] % 8;
      int red = stego.at<cv::Vec3b>(xPixel,yPixel)[2] % 4;
      charVal = (blue << 5) + (green << 2) + red;
      std::cout << blue << " " << green << " " << red << std::endl;
      std::cout << charVal << std::endl;
      if (charVal == 32) {
        output << "" << std::endl;
      }
      else {
        output << char(charVal) << std::flush;
      }
      xPixel++;
      if (xPixel>=stego.rows) {
        xPixel = 0;
        yPixel++;
      }
    }
    /*while (!secret.eof()) {
      //std::cout << ch << std::endl;
      std::cout << int(ch) << std::endl;
      
      int blue = int(ch) >> 5;
      int green = (int(ch) - (blue << 5)) >> 3;
      int red = int(ch) % 4;
      stego.at<cv::Vec3b>(xPixel,yPixel)[0] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[0] >> 3) << 3) + blue;
      stego.at<cv::Vec3b>(xPixel,yPixel)[1] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[1] >> 3) << 3) + green;
      stego.at<cv::Vec3b>(xPixel,yPixel)[2] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[2] >> 2) << 2) + red;      
      xPixel++;
      if (xPixel>=stego.rows) {
        xPixel = 0;
        yPixel++;
      }
      secret.get(ch);
    }*/
    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", stego);
    //imwrite("stego.png", stego);

    //waitKey(0);

    return 0;
}
