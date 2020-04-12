#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "color.hpp"
#include <cmath>

using namespace cv;

map<uchar, Vec3b> allColorInZone(const Mat& zone) {
    map<uchar, Vec3b> colors;
    for (int i = 0; i < zone.rows; i++) {
       for (int j = 0; j < zone.cols; j++) {
            colors[zone.at<uchar>(i,j)] = zone.at<Vec3b>(i, j);
            /*if (colors.find(zone.at<Vec3b>(i, j)) == colors.end()) {
                colors.insert(pair<Vec3b, int>(zone.at<Vec3b>(i, j), 0));
            } else {
                colors[zone.at<Vec3b>(i, j)] = 1;
            }*/
       } 
    }
    return colors;
}

void rgbToHsv(unsigned char r, unsigned char g, unsigned char b) {


    // h, s, v = hue, saturation, value 
    unsigned char cmax = std::max(r, std::max(g, b)); // maximum of r, g, b 
    unsigned char cmin = std::min(r, std::min(g, b)); // minimum of r, g, b 
    unsigned char h, s, v; 

    v = cmax;
    if (v == 0) {
        h = s = 0;
        std::cout << "h is " << (int)h << " s is " << (int)s << " v is " << (int)v << std::endl;
        return;
    } 
    s = 255 * long(cmax - cmin) / v;
    if (s == 0) {
        h = 0;
        std::cout << "h is " << (int)h << " s is " << (int)s << " v is " << (int)v << std::endl;
        return; 
    }
    if (cmax == r)
        h = 0 + 43 * (g - b) / (cmax - cmin);
    else if (cmax == g)
        h = 85 + 43 * (b - r) / (cmax - cmin);
    else
        h = 171 + 43 * (r - g) / (cmax - cmin);
    std::cout << "h is " << (int)h << " s is " << (int)s << " v is " << (int)v << std::endl;
}

Mat redFilter(const Mat& src) {
    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);
    rgbToHsv(255, 0, 0);
    rgbToHsv(255, 204, 204);
    rgbToHsv(128, 0, 0);
    rgbToHsv(0, 255, 0);
    rgbToHsv(0, 0, 255);
    
    Mat mask1,mask2;

    inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(170, 120, 70), Scalar(180, 255, 255), mask2);

    mask1 = mask1 | mask2;
    morphOps(mask1);

    return mask1;
}

void morphOps(Mat &thresh) {

    //morphological opening (remove small objects from the foreground)
    erode( thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

    //morphological closing (fill small holes in the foreground)
    dilate( thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
    erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
}

Mat filterColors(const Mat& src, const Mat& zone) {
    Mat mask;
    bool first = true;
    map<uchar, Vec3b> colors = allColorInZone(zone);
    map<uchar, Vec3b>::iterator itr;
    for (itr = colors.begin(); itr != colors.end(); ++itr) { 
        Mat mask2;
        Vec3b vec = itr->second;
        Scalar lower = Scalar(255-vec[0], 255-vec[1], 255-vec[2]);
        Scalar upper = Scalar(vec[0], vec[1], vec[2]);
        inRange(src, lower, upper, mask2);
        if (first) {
            mask = mask2;
            first = false;
        } else {
            mask += mask2;
        }
    }
    return mask;
}


