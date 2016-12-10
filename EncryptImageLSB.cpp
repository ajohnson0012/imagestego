#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 3 )
    {
        printf("usage: EncryptImageLSB.out <Image_Path> <Secret_File_Path>\n");
        return -1;
    }

    Mat image, stego;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    image.copyTo(stego);
    std::ifstream secret;
    secret.open(argv[2], std::fstream::in);
    char ch;
    char END_OF_FILE = '#';
    secret.get(ch);
    //std::cout << stego.rows << std::endl;
    //std::cout << stego.cols << std::endl;
    int xPixel = 0;
    int yPixel = 0;
    while (!secret.eof()) {
      //std::cout << ch << std::endl;
      std::cout << int(ch) << std::endl;
      
      int blue = int(ch) >> 5;
      int green = (int(ch) - (blue << 5)) >> 2;
      int red = int(ch) % 4;
      int nblue = stego.at<cv::Vec3b>(xPixel,yPixel)[0] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[0] >> 3) << 3) + blue;
      int ngreen = stego.at<cv::Vec3b>(xPixel,yPixel)[1] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[1] >> 3) << 3) + green;
      int nred = stego.at<cv::Vec3b>(xPixel,yPixel)[2] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[2] >> 2) << 2) + red;      
      std::cout << blue << " " << green << " " << red << std::endl;
      xPixel++;
      if (xPixel>=stego.rows) {
        xPixel = 0;
        yPixel++;
      }
      secret.get(ch);
    }
    stego.at<cv::Vec3b>(xPixel,yPixel)[0] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[0] >> 3) << 3);
    stego.at<cv::Vec3b>(xPixel,yPixel)[1] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[1] >> 3) << 3);
    stego.at<cv::Vec3b>(xPixel,yPixel)[2] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[2] >> 2) << 2);     
    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", stego);
    imwrite("stego.png", stego);
    secret.close();

    //waitKey(0);

    return 0;
}
