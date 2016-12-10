#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace cv;

double alpha(int val) {
  if (val == 0)
    return 1/(sqrt(2));
  return 1;
}

int nextChar(std::ofstream &output, int charVal) {
  if(charVal==0) return 0;
  else {
    char ch = char(charVal);
    std::cout << charVal << " = " << ch << std::endl;
    output << ch << std::flush;
    return 1;
  }
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DecryptImageDCT <Image_Path>\n");
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
    output.open("outputDCT.txt", std::fstream::out);
    
    double **blueF = new double*[stego.cols];
    double **greenF = new double*[stego.cols];
    double **redF = new double*[stego.cols];
    for(int i=0;i<stego.cols;i++) {
      blueF[i] = new double[stego.rows];
      greenF[i] = new double[stego.rows];
      redF[i] = new double[stego.rows];
    }
    
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
    
    int ch = 0;
    int pos = 0;
    
    for(int i=0;i<8;i++) {
      std::cout << "{" << std::flush;
      for(int j=0;j<7;j++) {
        std::cout << int(stego.at<cv::Vec3b>(j,i)[0]) << "," << std::flush;
      }
      std::cout << int(stego.at<cv::Vec3b>(7,i)[0]) << "}" << std::endl;
    }
    
    for(int i=0;i<stego.cols;i+=8) {
      for(int j=0;j<stego.rows;j+=8) {
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
            blueF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*bluesum)/QT[u][v]);
            if((blueF[i+u][j+v]!=1)&&(blueF[i+u][j+v]!=0)) {
              std::cout << "[" << (i+u) << "," << (j+v) << "] "  << "blue " << int(blueF[i+u][j+v]) << std::endl;
              if(pos<7) {
                ch += (abs(int(blueF[i+u][j+v])%2))<<pos;
                std::cout << ch << " " << pos << std::endl;
                pos++;
              }
              else {
                if(nextChar(output, ch)==0) goto fin;
                pos = ch = 0;
                ch += (abs(int(blueF[i+u][j+v])%2))<<pos;
                std::cout << "[" << (i+u) << "," << (j+v) << "] " << ch << " " << pos << std::endl;
                pos++;
              }
            }
            greenF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*greensum)/QT[u][v]);
            if((greenF[i+u][j+v]!=1)&&(greenF[i+u][j+v]!=0)) {
              std::cout << "green " << greenF[i+u][j+v] << std::endl;
              if(pos<7) {
                ch += (abs(int(greenF[i+u][j+v])%2))<<pos;
                std::cout << "[" << (i+u) << "," << (j+v) << "] " << ch << " " << pos << std::endl;
                pos++;
              }
              else {
                if(nextChar(output, ch)==0) goto fin;
                pos = ch = 0;
                ch += (abs(int(greenF[i+u][j+v])%2))<<pos;
                std::cout << "[" << (i+u) << "," << (j+v) << "] " << ch << " " << pos << std::endl;
                pos++;
              }
            }
            redF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*redsum)/QT[u][v]);
            if((redF[i+u][j+v]!=1)&&(redF[i+u][j+v]!=0)) {
              std::cout << "red " << redF[i+u][j+v] << std::endl;
              if(pos<7) {
                ch += (abs(int(redF[i+u][j+v])%2))<<pos;
                std::cout << "[" << (i+u) << "," << (j+v) << "] " << ch << " " << pos << std::endl;
                pos++;
              }
              else {
                if(nextChar(output, ch)==0) goto fin;
                pos = ch = 0;
                ch += (abs(int(redF[i+u][j+v])%2))<<pos;
                std::cout << "[" << (i+u) << "," << (j+v) << "] " << ch << " " << pos << std::endl;
                pos++;
              }
            }
          }
        }
      }
    }
    
    fin:output.close();
    
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
