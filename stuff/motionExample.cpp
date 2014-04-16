#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;
using namespace cv;

int main(){

	VideoCapture cap(-1);

	if (!cap.isOpened()){

		//cout << "Content-type:text/html\r\n\r\n";
		//cout << "<html>\n";
		//cout << "<h1> Camera didn't open </h1>\n";
		//cout << "</html>\n";
		return 0;
		//cout << "Camera didn't open" << endl;
	}

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	//cout << "Camera dimensions set ( 320 X 240 )" << endl;

	int whiteCount, count = 50, count2 = 50;
	Mat difference, diffGray, frame, prevFrame, currFrame, nextFrame;

	/*After 5 frames of been read in check for differences*/
	int frameCount=0;
	int nextFrameCount = 0;
	int countqwe = 20;
	while(countqwe != 0){
		cap >> frame;
		frame.copyTo(prevFrame);
		frameCount++;
		//cout << frameCount << endl;
		if(frameCount == 5){

			while( nextFrameCount != 4 ){
				cap >> frame;
				frame.copyTo(currFrame);
				nextFrameCount++;
			}

			absdiff(currFrame, prevFrame, difference);
			cvtColor(difference, difference, CV_BGR2GRAY);
			threshold(difference, difference, 30, 255, CV_THRESH_BINARY);
			whiteCount = cv::countNonZero(difference == 255);

			cout << "White count = " << whiteCount << endl;
			if(whiteCount >= 1000){
				//time_t now = time(0);
				//cout << now << endl;
				imwrite ("/var/www/RaspberrySpi/photos/motionPictures/differenceExample.png", difference );
				imwrite ("/var/www/RaspberrySpi/photos/motionPictures/prevFrameExample.png", prevFrame );
				imwrite ("/var/www/RaspberrySpi/photos/motionPictures/currFrameExample.png", currFrame );

				//cout << "White count = " << whiteCount << endl;
			}
			frameCount = 0;
			nextFrameCount = 0;
		}
	}		
	return 0;
}
