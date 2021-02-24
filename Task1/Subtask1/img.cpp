#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace cv;


struct img_points{
    Mat img;
    vector<Point2f> points;
};


void handle_clicks(int event,int x,int y,int flags,void* data){

Scalar color=Scalar(0,255,0);
Point selected=Point(x,y);
    
    if (event==EVENT_LBUTTONDOWN){
        img_points* cur_data=(img_points*) data; 
        circle((cur_data->img),selected,4,color,-1,FILLED);
        imshow("Image",cur_data->img);
        int sz=(cur_data->points).size();

        if (sz>0){
            line( cur_data->img,(cur_data->points)[sz-1],selected,Scalar( 0, 0, 255 ),1,LINE_8 );
            imshow("Image",cur_data->img);
        }
        if (sz<4){
            (cur_data->points).push_back(selected);
            sz++;

        }
         if (sz==4){
            line( cur_data->img,(cur_data->points)[0],selected,Scalar( 0, 0, 255 ),1,LINE_8);
            imshow("Image",cur_data->img);        }
    }

}



int main(int argc, char** argv)
{

	//Initializing Image
	Mat imgsrc = imread(string(argv[1]));
	
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
	// vector<Point2f> pts_src;
	// pts_src.push_back(Point2f(1500,400));
	// pts_src.push_back(Point2f(900,img_size.height-200));
	// pts_src.push_back(Point2f(2200,img_size.height-200));
	// pts_src.push_back(Point2f(2000,400));
	

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

	// cout<<img_size.width<<" "<<img_size.height<<endl;

	//A vector of pre-defined points of img_dst2 for displaying the cropped image
	vector<Point2f> pts_dst2;
	pts_dst2.push_back(Point2f(0,0));
	pts_dst2.push_back(Point2f(0,cropped_size.height-1));
	pts_dst2.push_back(Point2f(cropped_size.width-1,cropped_size.height-1));
	pts_dst2.push_back(Point2f(cropped_size.width-1,0));

	img_points userdata;
	userdata.img=resized_img;
	imshow("Image",resized_img);
	setMouseCallback("Image",handle_clicks,&userdata);
	waitKey(0);

	//Finding warped image
	Mat h1 = findHomography(userdata.points,pts_dst);
	Mat h2 = findHomography(userdata.points,pts_dst2);
	warpPerspective(resized_img,img_dst,h1,img_size);
	warpPerspective(resized_img,img_dst2,h2,cropped_size);

	//Displaying image(s)
	imshow("Warped Image",img_dst);
	imshow("Cropped Image",img_dst2);
	waitKey(0);

	//Saving the image
	imwrite("resized.jpg",resized_img);
	imwrite("warped.jpg",img_dst);
	imwrite("cropped.jpg",img_dst2);
	
	return 0;
}
