#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat imgsrc = imread(string(argv[1]),IMREAD_GRAYSCALE);
	Mat resized_img;
	resize(imgsrc,resized_img, Size(imgsrc.cols*1.5,imgsrc.rows*1.5));
	
	//Displaying image(s)
	imshow("Entered Image",imgsrc);
	imshow("Resized Image",resized_img);
	waitKey(0);
	
	//Saving the image
	imwrite("resized.jpg",resized_img);
	
	return 0;
}
