/**
 *
 *    This program decodes the secret message from the steganographic image that comes from EncryptImageLSB.cpp
 *    This program also works in the spatial domain of image steganography.
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
    if ( argc != 2 )
    {
        printf("usage: DecryptImageLSB.out <Image_Path>\n");
        return -1;
    }
    /* Read in the image and store in a matrix variable */
    Mat stego;
    stego = imread( argv[1], 1 );
    /* Check to make sure that the image file actually contains an image */
    if ( !stego.data )
    {
        printf("No image data \n");
        return -1;
    }
    /* Open file to print the output/secret message to. */ 
    std::ofstream output;
    output.open("output.txt", std::fstream::out);
    /* Initialize all variables */
    int xPixel = 0;
    int yPixel = 0;
    int charVal = -1;
    /* While the NULL character has not been decoded, keep decoding the image */
    while(charVal != 0) {
      /* Each character's binary form consists of the 3 LSB of the blue pixel value, 3 LSB of green, 2 LSB of red */
      int blue = stego.at<cv::Vec3b>(xPixel,yPixel)[0] % 8;
      int green = stego.at<cv::Vec3b>(xPixel,yPixel)[1] % 8;
      int red = stego.at<cv::Vec3b>(xPixel,yPixel)[2] % 4;
      charVal = (blue << 5) + (green << 2) + red;
      output << char(charVal) << std::flush;      // Output each character into the output file
      xPixel++;
      /* If we reach the bottom of a column, go to the top of the next column */
      if (xPixel>=stego.rows) {
        xPixel = 0;
        yPixel++;
      }
    }
    output.close();
    return 0;
}
