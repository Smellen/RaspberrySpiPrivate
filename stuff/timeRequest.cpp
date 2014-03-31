#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv){

	//	time_t now = time (0);
	//	char * dt = ctime(&now);
	VideoCapture cap(-1);
	if (!cap.isOpened()){
		//    \r\n\r\n
		cout << "Content-type: text/html\n\n";

		cout << "<html>";
		cout << "<h1> Camera didn't open </h1>";
		cout << "</html>";
		return -1; 
	}   
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	int count = 400000; 
	//cv::Mat frame;
	Mat frame;
	bool bSuccess = cap.read(frame);
	while (count != 0){ 
		count--;	
	}
	if (!bSuccess){   

		cout << "Content-type: text/html\n\n";

		cout << "<html>";
		cout << "<h1> Photo did't work get read in</h1>";
		cout << "</html>";

		return 0;
	} 

	cout << "Content-type:text/html\n";
	cout << "<html>";
	cout << "<h1> Photo Taken + Saved</h1>";
	cout << "</html>";
	imwrite("/var/www/RaspberrySpi/photos/time.png", frame); 

	return 0;
}
