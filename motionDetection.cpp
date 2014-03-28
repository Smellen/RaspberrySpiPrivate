#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>

#define filePath "/var/www/RaspberrySpi/photos/motionPictures/%m%d_%H.%M.%S.png"
#define differencePath "/var/www/RaspberrySpi/photos/motionPictures/difference.png"

using namespace std;
using namespace cv;

int main(){

	VideoCapture cap(-1);

	if (!cap.isOpened()){
		cout << "Camera didn't open" << endl;
	}

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);


	Mat difference, frame, prevFrame, currFrame, nextFrame;
	int whiteCount;
	int frameCount=0, nextFrameCount = 0;
	time_t now;
	char time_data[256];
	time_data[0] = '\0';

	while(true){
		cap >> frame;
		frame.copyTo(prevFrame);
		frameCount++;
		if(frameCount == 5){
			now = time(0);
			while( nextFrameCount != 4 ){
				cap >> frame;
				frame.copyTo(currFrame);
				nextFrameCount++;
			}

			absdiff(currFrame, prevFrame, difference);
			cvtColor(difference, difference, CV_BGR2GRAY);
			threshold(difference, difference, 30, 255, CV_THRESH_BINARY);
			whiteCount = cv::countNonZero(difference == 255);

			if(whiteCount >= 1000){

				imwrite (differencePath, difference);
				strftime (time_data, 256, filePath, localtime(&now));
				imwrite (time_data, prevFrame );

				now = time(0);
				strftime (time_data, 256, filePath, localtime(&now));
				imwrite (time_data, currFrame );

			}
			frameCount = 0;
			nextFrameCount = 0;
		}
	}		
	return 0;
}

