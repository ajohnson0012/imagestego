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

int nextChar(std::ifstream &secret) {
  char ch;
  if(secret.eof()) return 0;
  secret.get(ch);
  std::cout << ch << " " << int(ch) << std::endl;
  return int(ch);
}

int main(int argc, char** argv )
{
    if ( argc != 3 )
    {
        printf("usage: EncryptImageDCT.out <Image_Path> <Secret_File_Path>\n");
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
    
    int ch = nextChar(secret);
    
    int sset = 8;
    
    std::cout << "{" << std::endl;
    for(int i=0;i<8;i++) {
      std::cout << "{" << std::flush;
      for(int j=0;j<7;j++) {
        std::cout << int(stego.at<cv::Vec3b>(j+sset,i)[0]) << "," << std::flush;
      }
      std::cout << int(stego.at<cv::Vec3b>(7+sset,i)[0]) << "}" << std::endl;
    }
    
    std::cout << "}" << std::endl;
    
    double blueT [8][8];
    double greenT [8][8];
    double redT [8][8];
    
    std::cout << ch << std::endl;
    int pos = 7;
    int eof = 0;
    
    std::cout << int(stego.at<cv::Vec3b>(5,5)[0]) << std::endl;
    
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
              if(pos>0) {
                blueF[i+u][j+v] = (blueF[i+u][j+v]-(abs(int(blueF[i+u][j+v])%2)))+(ch%2);
                ch = ch>>1;
                pos--;
              }
              else {
                ch = nextChar(secret);
                pos = 7;
                if(ch==0) eof = 1;
                blueF[i+u][j+v] = (blueF[i+u][j+v]-(abs(int(blueF[i+u][j+v])%2)))+(ch%2);
                std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
                ch = ch>>1;
                pos--;
              }
            }
            blueF[i+u][j+v] = blueF[i+u][j+v]*QT[u][v];
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
            if(bluesum>255) bluesum=255;
            if(greensum>255) greensum=255;
            if(redsum>255) redsum=255;
            if(bluesum<0) bluesum=0;
            if(greensum<0) greensum=0;
            if(redsum<0) redsum=0;
            stego.at<cv::Vec3b>(j+y,i+x)[0] = round(bluesum);
            stego.at<cv::Vec3b>(j+y,i+x)[1] = round(greensum);
            stego.at<cv::Vec3b>(j+y,i+x)[2] = round(redsum);
            
          }
        }
        if((pos==0)&&(eof==1)) goto end;
      }
    }
    
    end:int set = 8;
       
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", stego);
    imwrite("stego.png", stego);

    waitKey(0);
    
    secret.close();
    
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
