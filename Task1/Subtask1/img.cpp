#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	//Initializing Image
	Mat imgsrc = imread(string(argv[1]),IMREAD_GRAYSCALE);
	
	//Resizing Image
	Mat resized_img;
	resize(imgsrc,resized_img, Size(imgsrc.cols*1.5,imgsrc.rows*1.5));
	Size img_size=resized_img.size();
	Size size=imgsrc.size();
	
	//Destination image initialized as blank/empty canvas i.e. a black screen	
	Mat img_dst = Mat::zeros(img_size,CV_32F);

	//A vector of points to be selected by mouse input
	vector<Point2f> pts_src;
	pts_src.push_back(Point2f(0,0));
	pts_src.push_back(Point2f(0,img_size.height-1));
	pts_src.push_back(Point2f(img_size.width-1,img_size.height-1));
	pts_src.push_back(Point2f(img_size.width-1,0));

	//A vector of pre-defined points of img_dst
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(0,0));
	pts_dst.push_back(Point2f(636,img_size.height-1));
	pts_dst.push_back(Point2f(img_size.width-637,img_size.height-1));
	pts_dst.push_back(Point2f(img_size.width-1,0));

	//Finding warped image
	Mat h = findHomography(pts_src,pts_dst);
	warpPerspective(resized_img,img_dst,h,img_size);

	//Displaying image(s)
	imshow("Resized Image",resized_img);
	imshow("Warped Image",img_dst);
	waitKey(0);

	//Saving the image
	imwrite("resized.jpg",resized_img);
	imwrite("warped.jpg",img_dst);
	
	return 0;
}
