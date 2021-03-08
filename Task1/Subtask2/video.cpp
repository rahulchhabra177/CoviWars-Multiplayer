//Designed by:
// 1) Rahul Chhabra (2019CS11016)
// 2) Shrey Patel (2019CS10400)

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//Checking file format for valid images
bool check_format(string video){
	int n= video.length();
	if(n<=4){
		return false;
	}else if(video.substr(n-4,4)==".mp4" || video.substr(n-4,4)==".wmv"){
		return true;
	}else if(n<=5){
		return false;
	}else if(video.substr(n-5,5)==".mpeg"){
		return true;
	}else{
		return false;
	}
}

int main(int argc,char** argv)
{
	//Checking number of arguments
	if(argc == 2){
		
		//Taking video input
		string inputVideo = string(argv[1]);
		VideoCapture cap(inputVideo);
		
		Mat img = imread("empty.jpg",IMREAD_COLOR);
		cout<<img.size().width<<" "<<img.size().height<<endl;
		
		//Checking if the video file can be opened
		if (cap.isOpened() == false)  
 		{
  			cerr << "Cannot open the video file. Please provide a correct video file. Check if the specified path is correct." << endl;
  			cin.get(); 
  			return -1;
 		}
 		
 		//Checking if the input video is of the correct format
 		if(!check_format(string(argv[1]))){
 			cerr << "Incorrect video format. Accepted file formats: .mp4, .mpeg and .wmv"<<endl;
 		}else{
 		
 			Mat initialImg;
 			cap.read(initialImg);
 			Size img_size=initialImg.size();		//Resolution=1920*1080 
 			Size cropped_size=Size(900,1200);		
 			
 			while(true){
 				
 				Mat frame;
 				bool notOver = cap.read(frame);	
 				resize(frame,frame,Size(1.5*img_size.width,1.5*img_size.height));
 				
 				//Warping the view
 				vector<Point2f> pts_dst;
 				pts_dst.push_back(Point2f(1214,309));
				pts_dst.push_back(Point2f(43,1265));
				pts_dst.push_back(Point2f(2613,1519));							
				pts_dst.push_back(Point2f(2017,303));

				vector<Point2f> pts_dst2;
				pts_dst2.push_back(Point2f(0,0));
				pts_dst2.push_back(Point2f(0,cropped_size.height-1));
				pts_dst2.push_back(Point2f(cropped_size.width-1,cropped_size.height-1));
				pts_dst2.push_back(Point2f(cropped_size.width-1,0));
 				
 				if(!notOver){
 					break;
 				}
 				
 				Mat h = findHomography(pts_dst,pts_dst2);
 				warpPerspective(frame,frame,h,cropped_size);
 				
 				imshow("Video",frame);
 				
 				
 				
 				
 				
 				
 				
 				
 				
 				//Manually exiting the video
 				if(waitKey(10) == 27){
 					break;
 				}
 			}
 		
 		}
		
	}else{
		cerr<<"Exactly two arguments are acceptable. The correct input format on the command line should be ./video sample_video.mp4"<<endl;
	}
	return 0;	
}
