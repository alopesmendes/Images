#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "track.hpp"

using namespace cv;

string intToString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}

void draw(Mat& frame, vector< vector<Point> > contours, vector<Vec4i> hierarchy) {
    Scalar color = Scalar( 255, 255, 255 );
    for (size_t i = 0; i < contours.size(); i++) {
        Moments moment = moments((cv::Mat)contours.at(i));
	    double area = moment.m00;
        if (area < 150) {
            continue;
        }
        double x = moment.m10/area;
        double y = moment.m01/area;
        cv::drawContours(frame, contours, i, color, 2, 8, hierarchy, 0, Point());
        cv::circle(frame,cv::Point(x, y), 10, cv::Scalar(0, 0, 0));
        cv::putText(frame, intToString(x)+ " , " + intToString(y), cv::Point(x, y+20), 1, 1, Scalar(0, 0, 0) );

    }
    
}

Mat trackFilteredObject(const Mat& src, const Mat& filter) {
    Mat temp, img;
	filter.copyTo(temp);
    src.copyTo(img);
    vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    draw(img, contours, hierarchy);
    return img;
}