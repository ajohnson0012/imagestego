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
    //secret.get(ch);
    
    
    /*double blueT [stego.cols][stego.rows];
    double greenT [stego.cols][stego.rows];
    double redT [stego.cols][stego.rows];*/
    
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
    
    double blueT [8][8];
    double greenT [8][8];
    double redT [8][8];
    
    std::cout << ch << std::endl;
    int pos = 7;
    int eof = 0;
    
    std::cout << int(stego.at<cv::Vec3b>(5,5)[0]) << std::endl;
    
    // vector<vector<double> > blueT(stego.cols,vector<double>(stego.rows,0));      
    for(int i=0;i<stego.cols;i+=8) {
      for(int j=0;j<stego.rows;j+=8) {
        for(int u=0;u<8;u++) {
          for(int v=0;v<8;v++) {
            double bluesum = 0;
            double greensum = 0;
            double redsum = 0;
            for(int x=0;x<8;x++) {
              // double bluepsum = 0;
              // double greenpsum = 0;
              // double redpsum = 0;
              for(int y=0;y<8;y++) {
                bluesum+=stego.at<cv::Vec3b>(j+y,i+x)[0]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
                greensum+=stego.at<cv::Vec3b>(j+y,i+x)[1]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
                redsum+=stego.at<cv::Vec3b>(j+y,i+x)[2]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
              }
              // bluesum+=bluepsum;
              // greensum+=greenpsum;
              // redsum+=redpsum;
            }
            blueF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*bluesum)/QT[u][v]);
            if((blueF[i+u][j+v]!=1)&&(blueF[i+u][j+v]!=0)) {
              // std::cout << blueF[0][2] << "as" <<  std::endl;
              if(pos>0) {
                // std::cout << blueF[i+u][j+v] << std::endl;
                // std::cout << (int(blueF[i+u][j+v])%2) << std::endl;
                // std::cout << (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2)) << std::endl;
                // std::cout << ch << std::endl;
                // std::cout << (ch%2) << std::endl;
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << " " << std::flush;
                std::cout << "[" << (i+u) << "," << (j+v) << "]: " << blueF[i+u][j+v] << std::endl;
                // stego.at<cv::Vec3b>(j+v,i+u)[0] = (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2))+(ch%2);
                blueF[i+u][j+v] = (blueF[i+u][j+v]-(abs(int(blueF[i+u][j+v])%2)))+(ch%2);
                std::cout << "[" << (i+u) << "," << (j+v) << "]: " << blueF[i+u][j+v] << std::endl;
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << std::endl;
                ch = ch>>1;
                pos--;
                // if((pos==0)&&(eof==1)) goto fin;
              }
              else {
                ch = nextChar(secret);
                pos = 7;
                if(ch==0) eof = 1;//goto fin;
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << " " << std::flush;
                blueF[i+u][j+v] = (blueF[i+u][j+v]-(abs(int(blueF[i+u][j+v])%2)))+(ch%2);
                // stego.at<cv::Vec3b>(j+v,i+u)[0] = (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2))+(ch%2);
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << std::endl;
                std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
                ch = ch>>1;
                pos--;
              }
            }
            blueF[i+u][j+v] = blueF[i+u][j+v]*QT[u][v];
            greenF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*greensum)/QT[u][v]);
            if((greenF[i+u][j+v]!=1)&&(greenF[i+u][j+v]!=0)) {
              if(pos>0) {
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << " " << std::flush;
                // stego.at<cv::Vec3b>(j+v,i+u)[1] = (greenF[i+u][j+v]-(int(greenF[i+u][j+v])%2))+(ch%2);
                greenF[i+u][j+v] = (greenF[i+u][j+v]-(abs(int(greenF[i+u][j+v])%2)))+(ch%2);
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << std::endl;
                // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
                ch = ch>>1;
                pos--;
                // if((pos==0)&&(eof==1)) goto fin;
              }
              else {
                ch = nextChar(secret);
                pos = 7;
                if(ch==0) eof = 1;
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << " " << std::flush;
                // stego.at<cv::Vec3b>(j+v,i+u)[1] = (greenF[i+u][j+v]-(int(greenF[i+u][j+v])%2))+(ch%2);
                greenF[i+u][j+v] = (greenF[i+u][j+v]-(abs(int(greenF[i+u][j+v])%2)))+(ch%2);
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << std::endl;
                // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
                ch = ch>>1;
                pos--;
              }
            }
            greenF[i+u][j+v] = greenF[i+u][j+v]*QT[u][v];
            redF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*redsum)/QT[u][v]);
            if((redF[i+u][j+v]!=1)&&(redF[i+u][j+v]!=0)) {
              if(pos>0) {
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << " " << std::flush;
                // stego.at<cv::Vec3b>(j+v,i+u)[2] = (redF[i+u][j+v]-(int(redF[i+u][j+v])%2))+(ch%2);
                redF[i+u][j+v] = (redF[i+u][j+v]-(abs(int(redF[i+u][j+v])%2)))+(ch%2);
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << std::endl;
                // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
                ch = ch>>1;
                pos--;
                // if((pos==0)&&(eof==1)) goto fin;
              }
              else {
                ch = nextChar(secret);
                pos = 7;
                if(ch==0) eof = 1;
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << " " << std::flush;
                // stego.at<cv::Vec3b>(j+v,i+u)[2] = (redF[i+u][j+v]-(int(redF[i+u][j+v])%2))+(ch%2);
                redF[i+u][j+v] = (redF[i+u][j+v]-(abs(int(redF[i+u][j+v])%2)))+(ch%2);
                // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << std::endl;
                // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
                ch = ch>>1;
                pos--;
              }
            }
            redF[i+u][j+v] = redF[i+u][j+v]*QT[u][v];
            // stego.at<cv::Vec3b>(j+v,i+u)[0] = blueF[i+u][j+v];
            // stego.at<cv::Vec3b>(j+v,i+u)[1] = greenF[i+u][j+v];
            // stego.at<cv::Vec3b>(j+v,i+u)[2] = redF[i+u][j+v];
          }
        }
        // for(int x=0;x<8;x++) {
        //   std::cout << "{" << std::flush;
        //   for(int y=0;y<7;y++) {
        //     std::cout << blueF[i+x][j+y] << "," << std::flush;
        //     blueF[i+x][j+y] *= QT[x][y];
        //   }
        //   std::cout << blueF[i+x][j+7] << "}" << std::endl;
        //   blueF[i+x][j+7] *= QT[x][7];
        // }
        // for(int x=0;x<8;x++) {
        //   std::cout << "{" << std::flush;
        //   for(int y=0;y<7;y++) {
        //     std::cout << blueF[i+x][j+y] << "," << std::flush;
        //   }
        //   std::cout << blueF[i+x][j+7] << "}" << std::endl;
        // }
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
            stego.at<cv::Vec3b>(j+y,i+x)[0] = round(bluesum);
            stego.at<cv::Vec3b>(j+y,i+x)[1] = round(greensum);
            stego.at<cv::Vec3b>(j+y,i+x)[2] = round(redsum);
            
          }
        }
        if((pos==0)&&(eof==1)) goto end;
      }
    }
    
    end:for(int i=0;i<8;i++) {
      std::cout << "{" << std::flush;
      for(int j=0;j<7;j++) {
        std::cout << int(stego.at<cv::Vec3b>(j,i)[0]) << "," << std::flush;
      }
      std::cout << int(stego.at<cv::Vec3b>(7,i)[0]) << "}" << std::endl;
    }
    for(int i=0;i<8;i++) {
      std::cout << "{" << std::flush;
      for(int j=0;j<7;j++) {
        std::cout << int(stego.at<cv::Vec3b>(j,i)[1]) << "," << std::flush;
      }
      std::cout << int(stego.at<cv::Vec3b>(7,i)[1]) << "}" << std::endl;
    }
    for(int i=0;i<8;i++) {
      std::cout << "{" << std::flush;
      for(int j=0;j<7;j++) {
        std::cout << int(stego.at<cv::Vec3b>(j,i)[2]) << "," << std::flush;
      }
      std::cout << int(stego.at<cv::Vec3b>(7,i)[2]) << "}" << std::endl;
    }
    
       
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
