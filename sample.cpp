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
    
    // double **blueF = new double*[stego.cols];
    // double **greenF = new double*[stego.cols];
    // double **redF = new double*[stego.cols];
    // for(int i=0;i<stego.cols;i++) {
    //   blueF[i] = new double[stego.rows];
    //   greenF[i] = new double[stego.rows];
    //   redF[i] = new double[stego.rows];
    // }
    
    double blueF [8][8];
    double test [8][8] = {
      {133,134,136,138,137,134,131,129},
      {133,136,136,138,137,134,131,129},
      {133,134,136,138,137,134,131,129},
      {133,134,136,38,137,134,131,129},
      {133,134,136,138,127,134,131,129},
      {133,134,136,138,137,134,131,129},
      {133,134,136,138,137,134,131,129},
      {133,134,136,138,137,134,131,129},
    };
    double end [8][8];
    
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
    
    // int ch = nextChar(secret);
    
    // std::cout << ch << std::endl;
    int pos = 7;
    int eof = 0;
    
    double sample [8][8];
    
    int set = 8;
    
    std::cout << "{" << std::endl;
    for(int i=0;i<8;i++) {
      std::cout << "{" << std::flush;
      for(int j=0;j<7;j++) {
        test[i][j] = int(stego.at<cv::Vec3b>(j+set,i)[0]);
        std::cout << int(stego.at<cv::Vec3b>(j+set,i)[0]) << "," << std::flush;
      }
      test[i][7] = int(stego.at<cv::Vec3b>(7+set,i)[0]);
      std::cout << int(stego.at<cv::Vec3b>(7+set,i)[0]) << "}" << std::endl;
    }
    
    std::cout << "}" << std::endl;
    
    std::cout << "" << std::endl;
    std::cout << "{" << std::endl;
    
    for(int u=0;u<8;u++) {
      for(int v=0;v<8;v++) {
        double bluesum = 0;
        double greensum = 0;
        double redsum = 0;
        for(int x=0;x<8;x++) {
          double bluepsum = 0;
          double greenpsum = 0;
          double redpsum = 0;
          for(int y=0;y<8;y++) {
            // bluesum+=stego.at<cv::Vec3b>(y,x)[0]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            // greensum+=stego.at<cv::Vec3b>(y,x)[1]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            // redsum+=stego.at<cv::Vec3b>(y,x)[2]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            bluesum+=test[x][y]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
          }
          // bluesum+=bluepsum;
          // greensum+=greenpsum;
          // redsum+=redpsum;
        }
        blueF[u][v] = 0.25*alpha(u)*alpha(v)*bluesum;
        // std::cout << int(stego.at<cv::Vec3b>(v,u)[0]) << " " << std::flush;
        // stego.at<cv::Vec3b>(v,u)[0] = blueF[u][v];
        end[u][v] = blueF[u][v];
        // std::cout << "(" << blueF[u][v] << ")" << std::flush;
        // std::cout << int(stego.at<cv::Vec3b>(v,u)[0])  << "," << std::flush;
        std::cout << end[u][v]  << "," << std::flush;
        // blueF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*bluesum)/QT[u][v]);
        // if((blueF[i+u][j+v]!=1)&&(blueF[i+u][j+v]!=0)) {
        //   if(pos>0) {
        //     // std::cout << blueF[i+u][j+v] << std::endl;
        //     // std::cout << (int(blueF[i+u][j+v])%2) << std::endl;
        //     // std::cout << (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2)) << std::endl;
        //     // std::cout << ch << std::endl;
        //     // std::cout << (ch%2) << std::endl;
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << " " << std::flush;
        //     // stego.at<cv::Vec3b>(j+v,i+u)[0] = (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2))+(ch%2);
        //     blueF[i+u][j+v] = 
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << std::endl;
        //     // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
        //     ch = ch>>1;
        //     pos--;
        //     if((pos==0)&&(eof==1)) goto fin;
        //   }
        //   else {
        //     ch = nextChar(secret);
        //     pos = 7;
        //     if(ch==0) eof = 1;//goto fin;
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << " " << std::flush;
        //     stego.at<cv::Vec3b>(j+v,i+u)[0] = (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2))+(ch%2);
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << std::endl;
        //     // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
        //     ch = ch>>1;
        //     pos--;
        //   }
        // }
        // greenF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*greensum)/QT[u][v]);
        // if((greenF[i+u][j+v]!=1)&&(greenF[i+u][j+v]!=0)) {
        //   if(pos>0) {
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << " " << std::flush;
        //     stego.at<cv::Vec3b>(j+v,i+u)[1] = (greenF[i+u][j+v]-(int(greenF[i+u][j+v])%2))+(ch%2);
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << std::endl;
        //     // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
        //     ch = ch>>1;
        //     pos--;
        //     if((pos==0)&&(eof==1)) goto fin;
        //   }
        //   else {
        //     ch = nextChar(secret);
        //     pos = 7;
        //     if(ch==0) eof = 1;
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << " " << std::flush;
        //     stego.at<cv::Vec3b>(j+v,i+u)[1] = (greenF[i+u][j+v]-(int(greenF[i+u][j+v])%2))+(ch%2);
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << std::endl;
        //     // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
        //     ch = ch>>1;
        //     pos--;
        //   }
        // }
        // redF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*redsum)/QT[u][v]);
        // if((redF[i+u][j+v]!=1)&&(redF[i+u][j+v]!=0)) {
        //   if(pos>0) {
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << " " << std::flush;
        //     stego.at<cv::Vec3b>(j+v,i+u)[2] = (redF[i+u][j+v]-(int(redF[i+u][j+v])%2))+(ch%2);
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << std::endl;
        //     // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
        //     ch = ch>>1;
        //     pos--;
        //     if((pos==0)&&(eof==1)) goto fin;
        //   }
        //   else {
        //     ch = nextChar(secret);
        //     pos = 7;
        //     if(ch==0) eof = 1;
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << " " << std::flush;
        //     stego.at<cv::Vec3b>(j+v,i+u)[2] = (redF[i+u][j+v]-(int(redF[i+u][j+v])%2))+(ch%2);
        //     // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << std::endl;
        //     // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
        //     ch = ch>>1;
        //     pos--;
        // stego.at<cv::Vec3b>(j+v,i+u)[0] = blueF[i+u][j+v];
        // stego.at<cv::Vec3b>(j+v,i+u)[1] = greenF[i+u][j+v];
        // stego.at<cv::Vec3b>(j+v,i+u)[2] = redF[i+u][j+v];
      }
      std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "{" << std::endl;
    for(int i=0;i<8;i++) {
      std::cout << "" << std::flush;
      for(int j=0;j<8;j++) {
        end[i][j] = round(end[i][j]/QT[i][j]);
        std::cout << end[i][j] << "," << std::flush;
      }
      std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
    // end[0][0]--;
    // end[0][2]++;
    std::cout << "{" << std::endl;
    for(int i=0;i<8;i++) {
      std::cout << "" << std::flush;
      for(int j=0;j<8;j++) {
        end[i][j] = end[i][j]*QT[i][j];
        std::cout << end[i][j] << "," << std::flush;
      }
      std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
    // end[0][0]++;
    std::cout << "" << std::endl;
    std::cout << "IDCT" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "{" << std::endl;
    for(int x=0;x<8;x++) {
      for(int y=0;y<8;y++) {
        double bluesum = 0;
        for(int u=0;u<8;u++) {
          for(int v=0;v<8;v++) {
            // bluesum+=alpha(u)*alpha(v)*stego.at<cv::Vec3b>(v,u)[0]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            bluesum+=alpha(u)*alpha(v)*end[u][v]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            // greenpsum+=stego.at<cv::Vec3b>(y,x)[1]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            // redpsum+=stego.at<cv::Vec3b>(y,x)[2]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
          }
          // bluesum+=bluepsum;
          // greensum+=greenpsum;
          // redsum+=redpsum;
        }
        bluesum *=0.25;
        // blueF[u][v] = 0.25*alpha(u)*alpha(v)*bluesum;
        blueF[x][y] = bluesum;
        // std::cout << int(stego.at<cv::Vec3b>(y,x)[0]) << " " << std::flush;
        // stego.at<cv::Vec3b>(y,x)[0] = blueF[x][y];
        test[x][y] = round(blueF[x][y]);
        if(test[x][y]>255) test[x][y]=255;
        // std::cout << int(stego.at<cv::Vec3b>(y,x)[0]) << "," << std::flush;
        std::cout << test[x][y] << "," << std::flush;
      }
      std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "{" << std::endl;
    for(int u=0;u<8;u++) {
      for(int v=0;v<8;v++) {
        double bluesum = 0;
        double greensum = 0;
        double redsum = 0;
        for(int x=0;x<8;x++) {
          double bluepsum = 0;
          double greenpsum = 0;
          double redpsum = 0;
          for(int y=0;y<8;y++) {
            // bluesum+=stego.at<cv::Vec3b>(y,x)[0]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            // greensum+=stego.at<cv::Vec3b>(y,x)[1]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            // redsum+=stego.at<cv::Vec3b>(y,x)[2]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
            bluesum+=test[x][y]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
          }
          // bluesum+=bluepsum;
          // greensum+=greenpsum;
          // redsum+=redpsum;
        }
        blueF[u][v] = 0.25*alpha(u)*alpha(v)*bluesum;
        // std::cout << int(stego.at<cv::Vec3b>(v,u)[0]) << " " << std::flush;
        // stego.at<cv::Vec3b>(v,u)[0] = blueF[u][v];
        end[u][v] = blueF[u][v];
        // std::cout << "(" << blueF[u][v] << ")" << std::flush;
        // std::cout << int(stego.at<cv::Vec3b>(v,u)[0])  << "," << std::flush;
        std::cout << end[u][v]  << "," << std::flush;
      }
      std::cout << "}" << std::endl;
    }
    std::cout << "" << std::endl;
    std::cout << "{" << std::endl;
    for(int i=0;i<8;i++) {
      std::cout << "" << std::flush;
      for(int j=0;j<8;j++) {
        end[i][j] = round(end[i][j]/QT[i][j]);
        std::cout << end[i][j] << "," << std::flush;
      }
      std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
    // vector<vector<double> > blueT(stego.cols,vector<double>(stego.rows,0));      
    // for(int i=0;i<stego.cols;i+=8) {
    //   for(int j=0;j<stego.rows;j+=8) {
    //     for(int u=0;u<8;u++) {
    //       for(int v=0;v<8;v++) {
    //         double bluesum = 0;
    //         double greensum = 0;
    //         double redsum = 0;
    //         for(int x=0;x<8;x++) {
    //           double bluepsum = 0;
    //           double greenpsum = 0;
    //           double redpsum = 0;
    //           for(int y=0;y<8;y++) {
    //             bluepsum+=stego.at<cv::Vec3b>(j+y,i+x)[0]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
    //             greenpsum+=stego.at<cv::Vec3b>(j+y,i+x)[1]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
    //             redpsum+=stego.at<cv::Vec3b>(j+y,i+x)[2]*cos(((2*x+1)*u*M_PI)/16)*cos(((2*y+1)*v*M_PI)/16);
    //           }
    //           bluesum+=bluepsum;
    //           greensum+=greenpsum;
    //           redsum+=redpsum;
    //         }
    //         blueF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*bluesum)/QT[u][v]);
    //         if((blueF[i+u][j+v]!=1)&&(blueF[i+u][j+v]!=0)) {
    //           if(pos>0) {
    //             // std::cout << blueF[i+u][j+v] << std::endl;
    //             // std::cout << (int(blueF[i+u][j+v])%2) << std::endl;
    //             // std::cout << (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2)) << std::endl;
    //             // std::cout << ch << std::endl;
    //             // std::cout << (ch%2) << std::endl;
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << " " << std::flush;
    //             // stego.at<cv::Vec3b>(j+v,i+u)[0] = (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2))+(ch%2);
    //             blueF[i+u][j+v] = 
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << std::endl;
    //             // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
    //             ch = ch>>1;
    //             pos--;
    //             if((pos==0)&&(eof==1)) goto fin;
    //           }
    //           else {
    //             ch = nextChar(secret);
    //             pos = 7;
    //             if(ch==0) eof = 1;//goto fin;
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << " " << std::flush;
    //             stego.at<cv::Vec3b>(j+v,i+u)[0] = (blueF[i+u][j+v]-(int(blueF[i+u][j+v])%2))+(ch%2);
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[0]) << std::endl;
    //             // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
    //             ch = ch>>1;
    //             pos--;
    //           }
    //         }
    //         greenF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*greensum)/QT[u][v]);
    //         if((greenF[i+u][j+v]!=1)&&(greenF[i+u][j+v]!=0)) {
    //           if(pos>0) {
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << " " << std::flush;
    //             stego.at<cv::Vec3b>(j+v,i+u)[1] = (greenF[i+u][j+v]-(int(greenF[i+u][j+v])%2))+(ch%2);
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << std::endl;
    //             // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
    //             ch = ch>>1;
    //             pos--;
    //             if((pos==0)&&(eof==1)) goto fin;
    //           }
    //           else {
    //             ch = nextChar(secret);
    //             pos = 7;
    //             if(ch==0) eof = 1;
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << " " << std::flush;
    //             stego.at<cv::Vec3b>(j+v,i+u)[1] = (greenF[i+u][j+v]-(int(greenF[i+u][j+v])%2))+(ch%2);
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[1]) << std::endl;
    //             // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
    //             ch = ch>>1;
    //             pos--;
    //           }
    //         }
    //         redF[i+u][j+v] = round((0.25*alpha(u)*alpha(v)*redsum)/QT[u][v]);
    //         if((redF[i+u][j+v]!=1)&&(redF[i+u][j+v]!=0)) {
    //           if(pos>0) {
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << " " << std::flush;
    //             stego.at<cv::Vec3b>(j+v,i+u)[2] = (redF[i+u][j+v]-(int(redF[i+u][j+v])%2))+(ch%2);
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << std::endl;
    //             // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
    //             ch = ch>>1;
    //             pos--;
    //             if((pos==0)&&(eof==1)) goto fin;
    //           }
    //           else {
    //             ch = nextChar(secret);
    //             pos = 7;
    //             if(ch==0) eof = 1;
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << " " << std::flush;
    //             stego.at<cv::Vec3b>(j+v,i+u)[2] = (redF[i+u][j+v]-(int(redF[i+u][j+v])%2))+(ch%2);
    //             // std::cout << int(stego.at<cv::Vec3b>(j+v,i+u)[2]) << std::endl;
    //             // std::cout << "[" << (i+u) << "," << (j+v) << "]" << std::endl;
    //             ch = ch>>1;
    //             pos--;
    //           }
    //         }
    //         // stego.at<cv::Vec3b>(j+v,i+u)[0] = blueF[i+u][j+v];
    //         // stego.at<cv::Vec3b>(j+v,i+u)[1] = greenF[i+u][j+v];
    //         // stego.at<cv::Vec3b>(j+v,i+u)[2] = redF[i+u][j+v];
    //       }
    //     }
    //     for(int u=0;u<8;u++) {
    //       for(int v=0;v<8v++) {
    //         
    //       }
    //     }
    //   }
    // }
    
    // for(int i=0;i<8;i++) {
    //   for(int j=0;j<7;j++) {
    //     std::cout << blueF[i][j] << "," << std::flush;
    //   }
    //   std::cout << blueF[i][7] << std::endl;
    // }
    
    // std::cout << "Error: Message is too long to encode" << std::endl;



    
    // for(int i=0;i<stego.cols;i++) {
    //   std::cout << "i" << std::endl;
    //   for(int j=0;j<stego.rows;j++) {
    //     std::cout << "j" << std::endl;
    //     double bluecsum = 0;
    //     //double greencsum = 0;
    //     //double redcsum = 0;
    //     for(int k=0;k<stego.cols;k++) {
    //       //std::cout << "k" << std::endl;
    //       double bluersum = 0;
    //       //double greenrsum = 0;
    //       //double redrsum = 0;
    //       for(int l=0;l<stego.rows;l++) {
    //         //std::cout << "l" << std::endl;
    //         bluersum += stego.at<cv::Vec3b>(l,k)[0]*cos((M_PI*(2*k+1)*i)/(2*stego.cols))*cos((M_PI*(2*l+1)*j)/(2*stego.rows));
    //         //greenrsum += stego.at<cv::Vec3b>(l,k)[1]*cos((M_PI*(2*k+1)*i)/(2*stego.cols))*cos((M_PI*(2*l+1)*j)/(2*stego.rows));
    //         //redrsum += stego.at<cv::Vec3b>(l,k)[2]*cos((M_PI*(2*k+1)*i)/(2*stego.cols))*cos((M_PI*(2*l+1)*j)/(2*stego.rows));
    //       }
    //       bluecsum += bluersum;
    //       //greencsum += greenrsum;
    //       //redcsum += redrsum;
    //     }
    //     blueT[i][j] = alpha(i,stego.cols)*alpha(j,stego.rows)*bluecsum;
    //     //greenT[i][j] = alpha(i,stego.cols)*alpha(j,stego.rows)*greencsum;
    //     //redT[i][j] = alpha(i,stego.cols)*alpha(j,stego.rows)*redcsum;
    //     stego.at<cv::Vec3b>(j,i)[0] = blueT[i][j];
    //     //stego.at<cv::Vec3b>(j,i)[1] = greenT[i][j];
    //     //stego.at<cv::Vec3b>(j,i)[2] = redT[i][j];
    //   }
    // }
    
    
    /*char ch;
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
    */     
    // fin:namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", stego);
    // imwrite("stego.png", stego);
    // 
    // waitKey(0);
    // 
    // secret.close();
    
    // for (int i=stego.cols;i>0;) {
    //   delete[] redF[--i];
    //   delete[] greenF[i];
    //   delete[] blueF[i];
    // }
    // delete[] redF;
    // delete[] greenF;
    // delete[] blueF;

    return 0;
}
