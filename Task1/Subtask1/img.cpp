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
	Size cropped_size(600,800);
	
	//Destination images initialized as blank/empty canvas i.e. a black screen	
	Mat img_dst = Mat::zeros(img_size,CV_32F);
	Mat img_dst2 = Mat::zeros(img_size,CV_32F);

	//A vector of points to be selected by mouse input
	vector<Point2f> pts_src;
	pts_src.push_back(Point2f(1500,400));
	pts_src.push_back(Point2f(900,img_size.height-200));
	pts_src.push_back(Point2f(2200,img_size.height-200));
	pts_src.push_back(Point2f(2000,400));
	
	//vector<Point2f> pts_src;
	//pts_src.push_back(Point2f(0,0));
	//pts_src.push_back(Point2f(0,img_size.height-1));
	//pts_src.push_back(Point2f(img_size.width-1,img_size.height-1));
	//pts_src.push_back(Point2f(img_size.width-1,0));
	

	//A vector of pre-defined points of img_dst for displaying the warped image
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(1500,400));
	pts_dst.push_back(Point2f(1200,img_size.height-200));
	pts_dst.push_back(Point2f(2000,img_size.height-200));
	pts_dst.push_back(Point2f(2000,400));

	//A vector of pre-defined points of img_dst2 for displaying the cropped image
	vector<Point2f> pts_dst2;
	pts_dst2.push_back(Point2f(0,0));
	pts_dst2.push_back(Point2f(0,cropped_size.height-1));
	pts_dst2.push_back(Point2f(cropped_size.width-1,cropped_size.height-1));
	pts_dst2.push_back(Point2f(cropped_size.width-1,0));

	//Finding warped image
	Mat h1 = findHomography(pts_src,pts_dst);
	Mat h2 = findHomography(pts_src,pts_dst2);
	warpPerspective(resized_img,img_dst,h1,img_size);
	warpPerspective(resized_img,img_dst2,h2,cropped_size);

	//Displaying image(s)
	imshow("Resized Image",resized_img);
	imshow("Warped Image",img_dst);
	imshow("Cropped Image",img_dst2);
	waitKey(0);

	//Saving the image
	imwrite("resized.jpg",resized_img);
	imwrite("warped.jpg",img_dst);
	imwrite("cropped.jpg",img_dst2);
	
	return 0;
}
