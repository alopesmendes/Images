#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

#include "color.hpp"
#include "track.hpp"

using namespace std;
using namespace cv;


bool leftDown=false,leftup=false;
Mat frame;
Point cor1,cor2;
Rect box;
Object obj;

const string TRACKED_WINDOW = "TRACKED_WINDOW";
const string FILTER_WINDOW = "FILTER_WINDOW";
const string CROPPED_WINDOW = "CROPPED_WINDOW";
 
void mouse_call(int event,int x,int y,int,void*) {
	if(event == EVENT_LBUTTONDOWN)
	{
		leftDown = true;
		cor1.x = x;
		cor1.y = y;
		cout << "Corner 1: "<< cor1 << endl;
	 
	}
	if(event == EVENT_LBUTTONUP)
	{	
		leftup = true;
		cor2.x = x;
		cor2.y = y;
		cout << "Corner 2: " << cor2 << endl;
		
	}
 
	if(leftDown == true && leftup == false) //when the left button is down
	{
		Point pt;
		pt.x = x;
		pt.y = y;
		Mat temp_img = frame.clone();
		rectangle(temp_img, cor1, pt, Scalar(0, 0, 0)); //drawing a rectangle continuously
		imshow(TRACKED_WINDOW, temp_img);
	 
	}
	if(leftDown == true && leftup == true) //when the selection is done
	{
	 
		box.width = abs(cor1.x - cor2.x);
		box.height = abs(cor1.y - cor2.y);
		box.x = min(cor1.x, cor2.x);
		box.y = min(cor1.y ,cor2.y);
		Mat crop(frame, box); //Selecting a ROI(region of interest) from the original pic
		namedWindow(CROPPED_WINDOW);
		imshow(CROPPED_WINDOW, crop); //showing the cropped image
		leftDown = false;
		leftup = false;
		obj = createFromZone(crop);
	 
	}
 
}

//////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv) {

	int size = 9;
	// check arguments
	if(argc > 2){
		cerr << "usage: " << argv[0] << " [optional] video.mp4" << endl;
		exit(0); 
	}
	
	// input video stream
	VideoCapture capture;

	// load a video
	if(argc == 2){
		capture = VideoCapture(argv[1]);
		if(!capture.isOpened()){
			cerr << "failed to open video file : " << argv[1] << endl;
			return -1;
		}
	}
	
	// or open a web cam stream
	if(argc == 1){
		cout << "   open video stream ..." << endl;
		capture = VideoCapture(0);
		capture.set(CV_CAP_PROP_FRAME_WIDTH, 800);
		cout << "video width  : " << capture.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
		cout << "video height : " << capture.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
	}

	// grab a frame to get the video resolution
	capture >> frame;
	
	Mat crop(frame, Rect((frame.rows - size) / 2, (frame.cols - size) / 3, size, size)); //Selecting a ROI(region of interest) from the original pic
	obj = createFromZone(crop);
	// display window
	namedWindow(TRACKED_WINDOW);
	namedWindow(FILTER_WINDOW);
	moveWindow(TRACKED_WINDOW, 0, 50);
	moveWindow(FILTER_WINDOW, frame.rows, 50);

	setMouseCallback(TRACKED_WINDOW, mouse_call);

	// read video stream
	cout << "   read video stream ..." << endl;
	bool loop = true;
	while(loop){
		
		capture >> frame;
		Mat filter = filterColors(frame, obj);
		//Mat filter = redFilter(frame);
		imshow(FILTER_WINDOW, filter);
		imshow(TRACKED_WINDOW, trackFilteredObject(frame, filter));

		// events (quit)
		switch(char(waitKey(10))){
			case 27  : loop=false; break;
			case 'Q' :
			case 'q' : loop=false; break;
			case 's' : imwrite("output/monImage.jpg",frame); break;
		}

	} // main loop end

	// close the video streaming
	cout << "   close video stream ..." << endl;
	capture.release();

	return 0;
}
