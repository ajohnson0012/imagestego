/**
 *
 *    This program decodes an image that was created by the EncryptImageDCT.cpp
 *    This program also operates in the frequency domain.
 *    Author: Alex Johnson
 *
**/


#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace cv;

/* Function that is necessary for the DCT */
double alpha(int val) {
  if (val == 0)
    return 1/(sqrt(2));
  return 1;
}

/* Print character to output file */
int nextChar(std::ofstream &output, int charVal) {
  /* If the character is the NULL character, then stop encoding */
  if(charVal==0) return 0;
  else {
    char ch = char(charVal);
    output << ch << std::flush;
    return 1;
  }
}

int main(int argc, char** argv )
{
    /* Check to make sure the correct amount of arguments have been supplied */
    if ( argc != 2 )
    {
        printf("usage: DecryptImageDCT <Image_Path>\n");
        return -1;
    }
    /* Read in the original image which we will use to encode secret */
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
    output.open("outputDCT.txt", std::fstream::out);
    /* Declare 3 two-dimensional arrays to use for intermediate calculations */
    double **blueF = new double*[stego.cols];
    double **greenF = new double*[stego.cols];
    double **redF = new double*[stego.cols];
    for(int i=0;i<stego.cols;i++) {
      blueF[i] = new double[stego.rows];
      greenF[i] = new double[stego.rows];
      redF[i] = new double[stego.rows];
    }
    /* Initialize Quantization Table */
    double QT[8][8] = {
      {16,11,10,16,24,40,51,61},
      {12,12,14,19,26,58,60,55},
      {14,13,16,24,40,57,69,56},
      {14,17,22,29,51,87,80,62},
      {18,22,37,56,68,109,103,77},
      {24,35,55,64,81,104,113,92},
      {49,64,78,87,103,121,120,101},
      {72,92,95,98,112,100,103,99},
    };
    /* Initialize variables for later use */
    int ch = 0;
    int pos = 0;
    /* Break up the image into 8x8 blocks, and decode until we hit the NULL character */   
    for(int i=0;i<stego.cols;i+=8) {
      for(int j=0;j<stego.rows;j+=8) {
        /* Convert each block into the DCT domain */
        for(int u=0;u<8;u++) {
          for(int v=0;v<8;v++) {
            double bluesum = 0;
            double greensum = 0;
            double redsum = 0;
            for(int x=0;x<8;x++) {
              for(int y=0;y<8;y++) {
                bluesum+=stego.at<cv::Vec3b>(j+y,i+x)[0]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
                greensum+=stego.at<cv::Vec3b>(j+y,i+x)[1]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
                redsum+=stego.at<cv::Vec3b>(j+y,i+x)[2]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
              }
            }
            /* Quantize each block */
            blueF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*bluesum)/QT[u][v]);
            /* If the coefficient is not 0 or 1, get LSB from that coefficient */
            if((blueF[i+u][j+v]!=1)&&(blueF[i+u][j+v]!=0)) {
              if(pos<7) {
                ch += (abs(int(blueF[i+u][j+v])%2))<<pos;
                pos++;
              }
              /* If we have a full character, print it to output file */
              else {
                if(nextChar(output, ch)==0) goto fin;
                pos = ch = 0;
                ch += (abs(int(blueF[i+u][j+v])%2))<<pos;
                pos++;
              }
            }
            /* Same as blue pixel values, but for green */
            greenF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*greensum)/QT[u][v]);
            if((greenF[i+u][j+v]!=1)&&(greenF[i+u][j+v]!=0)) {
              if(pos<7) {
                ch += (abs(int(greenF[i+u][j+v])%2))<<pos;
                pos++;
              }
              else {
                if(nextChar(output, ch)==0) goto fin;
                pos = ch = 0;
                ch += (abs(int(greenF[i+u][j+v])%2))<<pos;
                pos++;
              }
            }
            /* Same as blue pixel values, but for red */
            redF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*redsum)/QT[u][v]);
            if((redF[i+u][j+v]!=1)&&(redF[i+u][j+v]!=0)) {
              if(pos<7) {
                ch += (abs(int(redF[i+u][j+v])%2))<<pos;
                pos++;
              }
              else {
                if(nextChar(output, ch)==0) goto fin;
                pos = ch = 0;
                ch += (abs(int(redF[i+u][j+v])%2))<<pos;
                pos++;
              }
            }
          }
        }
      }
    }
    /* Close output file */
    fin:output.close();
    /* Free all previously allocated space */
    for (int i=stego.cols;i>0;) {
      delete[] redF[--i];
      delete[] greenF[i];
      delete[] blueF[i];
    }
    delete[] redF;
    delete[] greenF;
    delete[] blueF;

    return 0;
}
