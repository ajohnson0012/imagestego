/**
 *
 *    This Program uses LSB substitution to hide a secret message in a .png image.
 *    This is a form of steganography that is referred to as the "spatial domain."
 *    Author: Alex Johnson
 *
 *
**/ 


#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

using namespace cv;

int main(int argc, char** argv )
{
    /* Check to make sure the correct amount of arguments have been supplied */
    if ( argc != 3 )
    {
        printf("usage: EncryptImageLSB.out <Image_Path> <Secret_File_Path>\n");
        return -1;
    }
    /* Read in the original image which we will use to encode secret */
    Mat image, stego;
    image = imread( argv[1], 1 );
    /* Check to make sure that the image file actually contains an image */
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    /* Open the secret data file to read from, and initialize variables */
    image.copyTo(stego);
    std::ifstream secret;
    secret.open(argv[2], std::fstream::in);
    char ch;
    secret.get(ch);
    int xPixel = 0;
    int yPixel = 0;
    /* While there are more characters in the secret file, get the next one to encode in the image */
    while (!secret.eof()) {
      /* Offset the character bits to get them ready for least significant bit substitution */
      int blue = int(ch) >> 5;
      int green = (int(ch) - (blue << 5)) >> 2;
      int red = int(ch) % 4;
      /* Substitute first three bits of character into 3 LSB of blue pixel value, 3 for green, and 2 for red */
      int nblue = stego.at<cv::Vec3b>(xPixel,yPixel)[0] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[0] >> 3) << 3) + blue;
      int ngreen = stego.at<cv::Vec3b>(xPixel,yPixel)[1] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[1] >> 3) << 3) + green;
      int nred = stego.at<cv::Vec3b>(xPixel,yPixel)[2] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[2] >> 2) << 2) + red;      
      xPixel++;
      if (xPixel>=stego.rows) {     // if at bottom of column, go to top of next column
        xPixel = 0;
        yPixel++;
      }
      secret.get(ch);     // get next character
    }
    /* Encode the NULL character so decoder knows when message is over */
    stego.at<cv::Vec3b>(xPixel,yPixel)[0] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[0] >> 3) << 3);
    stego.at<cv::Vec3b>(xPixel,yPixel)[1] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[1] >> 3) << 3);
    stego.at<cv::Vec3b>(xPixel,yPixel)[2] = ((stego.at<cv::Vec3b>(xPixel,yPixel)[2] >> 2) << 2);
    /* Save stego image into image file */
    imwrite("stego.png", stego);
    secret.close();
    return 0;
}
