/*

   Ellen Burke
   Raspberry Spi - Take a live frame and save it.

 */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main (){
	/*
	   This .cpp file will be compiled and the output will be a CGI script. 
	   CGI (common gateway interface) will allow a user to send a request to the .cpp 
	   application and get some information back. All cout commands produce the html that will
	   be displayed on the webpage.

	   If the camera fails to open the only imformation displayed will be that 
	   the Camera didn't open.

	   If the frame is empty afer reading through several frames it will display 
	   that the frame was not able to be read correctly.

	   If there are no problems then the webpage will load and display the frame taken.

	 */
	VideoCapture cap(-1);
	if (!cap.isOpened()){
		cout << "Content-type:text/html\r\n\r\n";
		cout << "<html>\n";
		cout << "<h1> Camera didn't open </h1>\n";
		cout << "</html>\n";
		return 0;
	}
	/*
	   Set camera dimensions to 320x240
	 */
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	Mat frame;
	/*
	   The count will be the amount of frames read in.
	   Final frame is the frame that will be saved.
	 */
	int count = 5;
	bool bSuccess;
	/*
	   Read in frames until count is 0.
	 */
	while(count != 0){
		bSuccess = cap.read(frame);
		count--;
	}

	/*
	   If the final frame read in wasn;t successfull the html displayed
	   will only let the user know the frame wasn't read in correctly.
	 */
	if (!bSuccess){
		cout << "Content-type: text/html\r\n\r\n";
		cout << "<html>\n";
		cout << "<h1> Frame not read correctly! </h1>\n";
		cout << "</html>\n";

		return 0;
	}	

	imwrite("/var/www/RaspberrySpi/photos/time.png", frame);
	/*
	   If the camera has opened and the frame being read in was successfull
	   then the normal Raspberry Spi layout will be displayed along with 
	   the image just taken.

	   Raspberry Spi layout is used. The image just taken will be displayed.	
	 */
	 /*
	 
	 External IP replaced by http://XX.XXX.XXX.XXX/
	 
	 */
	cout << "Content-type: text/html\r\n\r\n";
	cout << "<!DOCTYPE html>";
	cout << "<html>";

	cout << "<head>";
	cout << "<title>Raspberry Spi</title>";
	cout << "<link href=\"http://XX.XXX.XXX.XXX/css/main.css\" rel=\"stylesheet\" type=\"text/css\">";

	cout << "<link rel=\"shortcut icon\" href=\"http://XX.XXX.XXX.XXX/raspberrySpi.ico\">";
	cout << "<link rel=\"apple-touch-icon\" href=\"http://XX.XXX.XXX.XXX/raspberrySpi.ico\">";

	cout << "</head>";

	cout << "<body>";
	cout << "<div id=\"wrap\">";
	cout << "<div class=\"logo\">";
	cout << "<img src=\"http://XX.XXX.XXX.XXX/img/raspberrySPY.png\"/>";
	cout << "</div>";

	cout << "<form action= \"http://XX.XXX.XXX.XXX/index.html\">";
	cout << "<input type =\"submit\" value=\"   &larr;   \" style= \" position: absolute; left: 500px; top: 100px;\">";
	cout <<	"</form>";

	cout << "<h1> Frame Saved! </h1>\n";
	cout << "<img src=\"http://XX.XXX.XXX.XXX/photos/time.png\" alt=\"Raspberry SPY\" />";
	
	cout <<	"<div id=\"footer\">";
        cout << "<p> <a href=\"/help.html\">Help Page</a> </p>";
	cout << "<div>";

	cout << "</div>";
	cout << "</body>";
	cout << "</html>";
	return 0;
}
