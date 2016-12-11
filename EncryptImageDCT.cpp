/**
 *
 *    This program uses a DCT (Direct Cosine Transform) to encode a secret message in an image.
 *    This form of image steganography is referred to as the frequency domain.
 *    Author: Alex Johnson
 *
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

/* Get the next character from the secret file to encode in the image */
int nextChar(std::ifstream &secret) {
  char ch;
  if(secret.eof()) return 0;
  secret.get(ch);
  return int(ch);
}

int main(int argc, char** argv )
{
    /* Check to make sure the correct amount of arguments have been supplied */
    if ( argc != 3 )
    {
        printf("usage: EncryptImageDCT.out <Image_Path> <Secret_File_Path>\n");
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
    /* Open secret file with secret message which we will encode in the image */
    image.copyTo(stego);
    std::ifstream secret;
    secret.open(argv[2], std::fstream::in);
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
    /* Get first character to encode, and initialize other variables */
    int ch = nextChar(secret);
    int pos = 7;
    int eof = 0;
    /* Break up the image into 8x8 blocks, and encode until there is nothing left in the secret file */    
    for(int i=0;i<stego.cols;i+=8) {
      for(int j=0;j<stego.rows;j+=8) {
        /* Convert each 8x8 block to the DCT domain */
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
            /* Quantize each block (same for red and green) */
            blueF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*bluesum)/QT[u][v]);
            /* If quantized coefficient is not 1 or 0, replace LSB with next LSB of secret messsage */
            if((blueF[i+u][j+v]!=1)&&(blueF[i+u][j+v]!=0)) {
              if(pos>0) {
                blueF[i+u][j+v] = (blueF[i+u][j+v]-(abs(int(blueF[i+u][j+v])%2)))+(ch%2);
                ch = ch>>1;
                pos--;
              }
              /* Get next character if current character is already encoded */
              else {
                ch = nextChar(secret);
                pos = 7;
                if(ch==0) eof = 1;
                blueF[i+u][j+v] = (blueF[i+u][j+v]-(abs(int(blueF[i+u][j+v])%2)))+(ch%2);
                ch = ch>>1;
                pos--;
              }
            }
            blueF[i+u][j+v] = blueF[i+u][j+v]*QT[u][v];     // convert back to DCT domain (inverse-quantize)
            /* Same as with blue pixel values, but for green */
            greenF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*greensum)/QT[u][v]);
            if((greenF[i+u][j+v]!=1)&&(greenF[i+u][j+v]!=0)) {
              if(pos>0) {
                greenF[i+u][j+v] = (greenF[i+u][j+v]-(abs(int(greenF[i+u][j+v])%2)))+(ch%2);
                ch = ch>>1;
                pos--;
              }
              else {
                ch = nextChar(secret);
                pos = 7;
                if(ch==0) eof = 1;
                greenF[i+u][j+v] = (greenF[i+u][j+v]-(abs(int(greenF[i+u][j+v])%2)))+(ch%2);
                ch = ch>>1;
                pos--;
              }
            }
            greenF[i+u][j+v] = greenF[i+u][j+v]*QT[u][v];
            /* Same as with blue pixel values, but for red */
            redF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*redsum)/QT[u][v]);
            if((redF[i+u][j+v]!=1)&&(redF[i+u][j+v]!=0)) {
              if(pos>0) {
                redF[i+u][j+v] = (redF[i+u][j+v]-(abs(int(redF[i+u][j+v])%2)))+(ch%2);
                ch = ch>>1;
                pos--;
              }
              else {
                ch = nextChar(secret);
                pos = 7;
                if(ch==0) eof = 1;
                redF[i+u][j+v] = (redF[i+u][j+v]-(abs(int(redF[i+u][j+v])%2)))+(ch%2);
                ch = ch>>1;
                pos--;
              }
            }
            redF[i+u][j+v] = redF[i+u][j+v]*QT[u][v];
          }
        }
        /* Convert each block back to the spatial domain */
        fin:for(int x=0;x<8;x++) {
          for(int y=0;y<8;y++) {
            double bluesum = 0;
            double greensum = 0;
            double redsum = 0;
            for(int u=0;u<8;u++) {
              for(int v=0;v<8;v++) {
                bluesum += alpha(u)*alpha(v)*blueF[i+u][j+v]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
                greensum += alpha(u)*alpha(v)*greenF[i+u][j+v]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
                redsum += alpha(u)*alpha(v)*redF[i+u][j+v]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
              }
            }
            bluesum *= 0.25;
            greensum *=0.25;
            redsum *= 0.25;
            /* Ensure that overflow does not mess with image and encoding */
            if(bluesum>255) bluesum=255;
            if(greensum>255) greensum=255;
            if(redsum>255) redsum=255;
            if(bluesum<0) bluesum=0;
            if(greensum<0) greensum=0;
            if(redsum<0) redsum=0;
            /* Put new values into the stego image */
            stego.at<cv::Vec3b>(j+y,i+x)[0] = round(bluesum);
            stego.at<cv::Vec3b>(j+y,i+x)[1] = round(greensum);
            stego.at<cv::Vec3b>(j+y,i+x)[2] = round(redsum);
            
          }
        }
        if((pos==0)&&(eof==1)) goto end;      // If nothing else to encode, go to end
      }
    }
    /* Write image into stego.png file */
    end:imwrite("stego.png", stego);
    secret.close();
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
