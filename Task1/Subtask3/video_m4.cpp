//Designed by:
// 1) Rahul Chhabra (2019CS11016)
// 2) Shrey Patel (2019CS10400)

#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>
#include<fstream>
#include<pthread.h>

using namespace std;
using namespace cv;

struct currentThread{
	Mat currentFrame;
	Mat lastFrame;
};

Mat initialImg;
int frameNo=0;
vector<double> qDensity;
vector<double> dDensity;

//Helper Function to calculate the proportion of black color on screen, this helps us to calculate
//the queue density and the dynamic density 
double black_density(Mat mat)
{      
	double k=0.0;

	for(int i=0; i<mat.size().height; i++)
	{
		for(int j=0; j<mat.size().width; j++)
		{
				//Checking if the current pixel is black i.e. value = 0.0
				if (mat.at<double>(i,j)==0.0){k=k+1.0;}
		}
	}
	double area=(double)mat.size().height*mat.size().width;
	
	//k = Total black coloured area on screen, area = Total area of screen
	return k/area;

}

void *processFrame(void *frameData){
	struct currentThread *myFrames;
	myFrames = (struct currentThread *) frameData;

	Mat frame = myFrames->currentFrame;
	Mat currentImg = myFrames->lastFrame;

	//queueImg = Image showing the queued traffic of the current frame
	//diffImg = Image showing the moving traffic of the current frame  
	Mat queueImg;
	Mat diffImg;
	
	//queueImg can be obtained by background subtraction, i.e. by subtracting 
	//the background/reference frame from the current frame.
	absdiff(frame,initialImg,queueImg);
	absdiff(frame,currentImg,diffImg);
	
	//Removing distortions(noise) from both the images by applying a 
	//threshold filter and a Gaussian blur
	threshold(queueImg,queueImg,50,255,0); 
	GaussianBlur(queueImg,queueImg,Size(45,45),10,10);
	threshold(diffImg,diffImg,20,255,0); 
	GaussianBlur(diffImg,diffImg,Size(45,45),10,10); 

	//This block of code applies a filter to the queue density and dynamic 
	//density values to reduce fluctuations and distortions in adjacent 
	//values to obtain a "relatively" smooth graph
	if(frameNo == 0){
		qDensity.push_back(1-black_density(queueImg));
		dDensity.push_back(1-black_density(diffImg));
	}else{
		double q = 1-black_density(queueImg);
		double d = 1-black_density(diffImg);
			
		//If the density values of consecutive frames differ by more than
		//0.2, we extrapolate the last value, else we accept the density
		//values of current frame. 
		if(abs(q-qDensity[frameNo-1])<=0.1){
			qDensity.push_back(q);
		}else{
			qDensity.push_back(qDensity[frameNo-1]);
		}
		if(abs(d-dDensity[frameNo-1])<=0.1){
			dDensity.push_back(d);
		}else{
			dDensity.push_back(dDensity[frameNo-1]);
		}
	}

	frameNo++;
	
	//Writing the frame number and density values in the command line
	//fstream myfile("out.txt",std::ios_base::app);
	//myfile<<frameNo<<","<<(qDensity)<<","<<(dDensity)<<endl;
	//cout<<frameNo++<<","<<(qDensity)<<","<<(dDensity)<<endl;

	pthread_exit(NULL);
}

//Helper function to check file format for valid videos
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//Checking number of arguments
	if(argc == 2){
		
		//Taking video input
		string inputVideo = string(argv[1]);
		VideoCapture cap(inputVideo);
		
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

			int numberOfThreads;
			cerr<<"Enter the number of threads for temporal threading: ";cin>>numberOfThreads;
 		
 			//The first frame of the video, which we have taken as the background/reference
 			//frame for calculating queue density.
 			cap.read(initialImg);
 			Size img_size=initialImg.size();		//Resolution=1920*1080 
 			//resize(initialImg,initialImg,Size(1.5*img_size.width,1.5*img_size.height));
			cvtColor(initialImg,initialImg,COLOR_BGR2GRAY);
 			
 			//Size of the cropped image which we are interested in
 			Size cropped_size=Size(900,1200);

			//Warping the frame to fit in the cropped frame whose size we defined above
 			vector<Point2f> pts_dst;
 			pts_dst.push_back(Point2f(1214/1.5,309/1.5));
			pts_dst.push_back(Point2f(43/1.5,1265/1.5));
			pts_dst.push_back(Point2f(2613/1.5,1519/1.5));							
			pts_dst.push_back(Point2f(2017/1.5,303/1.5));

			vector<Point2f> pts_dst2;
			pts_dst2.push_back(Point2f(0,0));
			pts_dst2.push_back(Point2f(0,cropped_size.height-1));
			pts_dst2.push_back(Point2f(cropped_size.width-1,cropped_size.height-1));
			pts_dst2.push_back(Point2f(cropped_size.width-1,0));

			Mat h = findHomography(pts_dst,pts_dst2);		
 			warpPerspective(initialImg,initialImg,h,cropped_size);

			//We store the recently processed frame in currentImg, for calculating dynamic
			//density. The initial value of currentImg is the first frame i.e. initialImg
			Mat currentImg = initialImg;

			//Queue density and Dynamic density values for the last frame. Note that we 
			//don't calculate these values for the first frame, as we have taken the first 
			//frame as reference.

			auto startTime = chrono::high_resolution_clock::now();

			pthread_t threads[numberOfThreads];
			void *status;

 			while(true){ 

 				//Processing the current frame of the video
 				Mat frame;
 				//Indicates if we reached the end of the video i.e. no more frames to 
 				//process
 				bool notOver = cap.read(frame);
 				
 				//Exiting the loop if video is over
 				if(!notOver){
 					break;
 				}
 				
 				//Manipulating the current frame so that it can be operated with the 
 				//reference frame
 				//resize(frame,frame,Size(1.5*img_size.width,1.5*img_size.height));
 				cvtColor(frame,frame,COLOR_BGR2GRAY);
 				warpPerspective(frame,frame,h,cropped_size);

				struct currentThread newThread;
				newThread.currentFrame=frame;
				newThread.lastFrame=currentImg;

				if(frameNo/numberOfThreads!=0){
					pthread_join(threads[frameNo%numberOfThreads],&status);
				}
				pthread_create(&threads[frameNo%numberOfThreads],NULL,processFrame,(void *)&newThread);

				currentImg = frame;

				if(waitKey(10) == 27){
                    break;
                }
 			}

			for(int i=0;i<qDensity.size();i++){
				cout<<(i+1)<<","<<qDensity[i]<<","<<dDensity[i]<<"\n";
			}
			
			auto endTime = chrono::high_resolution_clock::now(); 

            chrono::duration<float> execTime = endTime - startTime;
            cout<<execTime.count()<<endl;
  		}
		
	}else{
		cerr<<"Exactly two arguments are acceptable. The correct input format on the command line should be ./video sample_video.mp4"<<endl;
	}
	pthread_exit(NULL);	
}
