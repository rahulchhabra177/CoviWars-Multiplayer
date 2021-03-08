#include <opencv2/highgui.hpp>
#include <iostream>
 
using namespace cv;
using namespace std; 
 
int main( int argc, char** argv ) {
  
  Mat image1;
  Mat image2;
  Mat dst;
  image1 = imread("empty.jpg" ,IMREAD_GRAYSCALE);
  image2 = imread("traffic.jpg" ,IMREAD_GRAYSCALE);
  absdiff(image1,image2,dst);
  
  imshow( "Techawarey:OpenCV Test Program", dst );
  
  waitKey(0);
  return 0;
}
