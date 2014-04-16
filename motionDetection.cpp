/*

Ellen Burke
Raspberry Spi - Motion Detection

*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
/*
filePath - When motion is detected it will be stored in this path.
	   THe format is monthDay_Hour.Minute.Second.png
differencePath - Where the difference image is going to be stored.
*/
#define filePath "/var/www/RaspberrySpi/photos/motionPictures/%m%d_%H.%M.%S.png"
#define differencePath "/var/www/RaspberrySpi/photos/motionPictures/difference.png"

using namespace std;
using namespace cv;

int main(){

/*
Initialize camera and check to see if it has opened.
If camera doesn't open program ends because no motion can be detected.
If the camera is set up successfully the width and height are set.
Default width and height are 320x240.
*/
	VideoCapture cap(-1);

	if (!cap.isOpened()){
		return 0;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

/*
All variables that will be used later in the code are initialized here.

whiteCount - Where white pixel count will be stored.
frameCount, nextFrameCount - Used to tell how many frames have been read in.
now - Used when finding the current localtime.
time_data - File path where motion images will be saved. It will contain the path but with a timestamp.

*/

	Mat difference, frame, prevFrame, currFrame, nextFrame;
	int whiteCount;
	int frameCount=0, nextFrameCount = 0;
	time_t now;
	char time_data[256];
	time_data[0] = '\0';
/*
Not every frame is used for comparison to avoid killing the raspberry.
5 frames are read in and the last is used. Then another 4 frames read in and that will also be used.
*/
	while(true){
		cap >> frame;
		frame.copyTo(prevFrame);
		frameCount++;
		if(frameCount == 3){
			now = time(0);
			while( nextFrameCount != 3 ){
				cap >> frame;
				frame.copyTo(currFrame);
				nextFrameCount++;
			}

/*
Motion Detection

For detecting whether motion has occured the absolute difference (absdiff()) method is used.
This method will take in two images and subtract them from each other creating a new one.
This RGB image is then converted to greyscale. All white pixels represent the differences in the images.
Using the greyscale image all white pixels are couted.
If the white pixel count is above a count of 1000 then motion has been deteced.
The two images passed into absdiff() are then both saved for the RaspberrySpi user to see.
*/

			absdiff(currFrame, prevFrame, difference);
			cvtColor(difference, difference, CV_BGR2GRAY);
			threshold(difference, difference, 30, 255, CV_THRESH_BINARY);
			whiteCount = cv::countNonZero(difference == 255);

			if(whiteCount >= 1000){

				/*Save greyscale difference image*/
				imwrite (differencePath, difference);

				/*Save the first image*/
				strftime (time_data, 256, filePath, localtime(&now));
				imwrite (time_data, prevFrame );

				/*Save the second image*/
				now = time(0);
				strftime (time_data, 256, filePath, localtime(&now));
				imwrite (time_data, currFrame );

			}
			/*Reset both counts for next two images*/
			frameCount = 0;
			nextFrameCount = 0;
		}
	}		
	return 0;
}
