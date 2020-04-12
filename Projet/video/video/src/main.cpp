#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

#include "color.hpp"
#include "delimeted_zone.hpp"

using namespace std;
using namespace cv;


//////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv) {
/*
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
		capture.set(CV_CAP_PROP_FRAME_WIDTH,800);
		cout << "video width  : " << capture.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
		cout << "video height : " << capture.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
	}

	// grab a frame to get the video resolution
	Mat frame;
	capture >> frame;
 
	// display window
	namedWindow("video");
	moveWindow("video",0, 50);

	// read video stream
	cout << "   read video stream ..." << endl;
	bool loop = true;
	while(loop){
 
		// get the next frame
		capture >> frame;

		// display the image
		imshow("video", delimetedWhiteZone(frame, redFilter(frame)));

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
*/

	if(argc != 2){
    	cout << "usage: " << argv[0] << " image" << endl;
    	return -1;
  	}

  	cout << "load image ..." << endl;
  	Mat image = imread(argv[1]);
  	if(image.empty()){
    	cout << "error loading " << argv[1] << endl;
    	return -1;
  	}

	namedWindow("Input image");
	imshow("Input image", image);
	waitKey();	
	imshow("Input image", redFilter(image));
	waitKey();
	//imshow("Input image", delimetedWhiteZone(image, redFilter(image)));
	//waitKey();

	return 0;
}
