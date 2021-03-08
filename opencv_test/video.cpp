//Uncomment the following line if you are compiling this code in Visual Studio
//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
 //open the video file for reading
 VideoCapture cap("/home/shrey/Downloads/trafficvideo.mp4"); 
 Mat src;
 // src = imread("/home/rahul/Downloads/empty.jpg",IMREAD_COLOR);
 
 // if not success, exit program
 if (cap.isOpened() == false)  
 {
  cout << "Cannot open the video file" << endl;
  cin.get(); //wait for any key press
  return -1;
 }
 
 double fps = cap.get(CAP_PROP_FPS); 
 cout << "Frames per seconds : " << fps << endl;

 String window_name = "Queue Density";
 String window2 = "Dynamic Density";
 String window3 = "Alternate";

 namedWindow(window_name, WINDOW_NORMAL); //create a window
 namedWindow(window2,WINDOW_NORMAL);
 namedWindow(window3,WINDOW_NORMAL);
  Ptr<BackgroundSubtractor> pBackSub=createBackgroundSubtractorMOG2();
 Mat initialImg;
 cap.read(initialImg);
 src=initialImg;
 
 int counter = 0;
 int threshold_value = 255;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

 while (true)
 {
  Mat frame;
  bool bSuccess = cap.read(frame); // read a new frame from video 
  //cvtColor(frame,frame,COLOR_BGR2GRAY);

  if (bSuccess == false) 
  {
   cout << "Found the end of the video" << endl;
   break;
  }

  Mat frame1;
  Mat frame2;
  Mat frame3;

  Mat fram1;
  Mat fram2;
  Mat fram3;
          pBackSub->apply(frame, fram1);

  absdiff(src,frame,frame2);
// frame2=frame-src;
  cvtColor(frame2,fram2,COLOR_BGR2GRAY);
  absdiff(frame,initialImg,frame3);
  // frame3=frame-initialImg;
  cvtColor(frame3,fram3,COLOR_BGR2GRAY);
  // absdiff(frame2,frame3,frame1);
  // cvtColor(frame1,frame1,COLOR_BGR2GRAY);
  // absdiff(frame2,frame3,frame1);
  // frame1 = (frame2+frame3);
  // cvtColor(fram1,fram1,COLOR_BGR2GRAY);
    threshold(frame3, frame3, threshold_value, max_binary_value, threshold_type );

  imshow(window_name,fram1);
  // imshow(window3,frame1);
  imshow(window3,fram2);
  imshow(window2,fram3);
  // counter+=1;
  // counter%=2;
  if (counter==0){
  initialImg=frame;}
  if (waitKey(10) == 27)
  {
   cout << "Esc key is pressed by user. Stopping the video" << endl;
   break;
  }
 }

 return 0;

}
