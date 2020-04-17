#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "color.hpp"
#include <cmath>

using namespace cv;

// --------------------------- begin Hsv class code ----------------------------------------
Hsv::Hsv(unsigned char hue, unsigned char saturation, unsigned char value) {
    Hsv::hue = hue;
    Hsv::saturation = saturation;
    Hsv::value = value;
}

Hsv::Hsv() {
    Hsv(0, 0, 0);
}

Scalar Hsv::color() {
    return Scalar(hue, saturation, value);
}

void Hsv::update(Hsv hsv, unsigned char (*f)(unsigned char, unsigned char)) {
    hue = (*f)(hue, hsv.hue);
    saturation = (*f)(saturation, hsv.saturation);
    value = (*f)(value, hsv.value);
}

unsigned char Hsv::getHue() {
    return hue;
}
// --------------------------- end Hsv class code -------------------------------------------


// --------------------------- begin Rgb class code -----------------------------------------
Rgb::Rgb(unsigned char red, unsigned char green, unsigned char blue) {
    Rgb::red = red;
    Rgb::green = green;
    Rgb::blue = blue;
}

Scalar Rgb::color() {
    return Scalar(blue, green, red);
}

Hsv Rgb::rgbToHsv() {
    Vec3b bgrPixel(blue, green, red);
    Mat3b bgr (bgrPixel);
    Mat3b hsv;
    cvtColor(bgr, hsv, COLOR_BGR2HSV);
    Vec3b hsvPixel(hsv.at<Vec3b>(0,0));
    return Hsv(hsvPixel[0], hsvPixel[1], hsvPixel[2]);

}
// --------------------------- end Rgb class code -------------------------------------------

// --------------------------- begin Object class code --------------------------------------
Object::Object() {
    Object::init = false;
}

unsigned char ucMin(unsigned char a, unsigned char b) {
    return std::min(a, b);
}

unsigned char ucMax(unsigned char a, unsigned char b) {
    return std::max(a, b);
}

void Object::update(Hsv hsv) {
    if (!init) {
        hmin = hmax = hsv;
        init = true;
    }
    hmin.update(hsv, ucMin);
    hmax.update(hsv, ucMax);
}

Hsv Object::getHmin() {
    return hmin;
}

Hsv Object::getHmax() {
    return hmax;
}
// --------------------------- end Object class code ----------------------------------------


std::ostream & operator<<(std::ostream & os, const Hsv & obj) {
    String text = obj;
    os << text;
    return os;
}

Mat redFilter(const Mat& src) {
    Mat hsv;
    medianBlur(src, src, 3);
    cvtColor(src, hsv, COLOR_BGR2HSV);

    Mat mask1,mask2;

    inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(170, 120, 70), Scalar(180, 255, 255), mask2);
    mask1 = mask1 | mask2;
    GaussianBlur(mask1, mask1, Size(9, 9), 2, 2);
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

Object createFromZone(const Mat& zone) {
    Object obj;
    for (int i = 0; i < zone.rows; i++) {
        for(int j = 0; j < zone.cols; j++) {
            unsigned char r, g, b;
            r = zone.at<Vec3b>(i, j)[2];
            g = zone.at<Vec3b>(i, j)[1];
            b = zone.at<Vec3b>(i, j)[0];
            Rgb rgb = Rgb(r, g, b);
            obj.update(rgb.rgbToHsv());
        }
    }

    return obj;
}

Mat filterColors(const Mat& src, Object obj) {
    if (obj.getHmin().getHue() <= 10 && obj.getHmax().getHue() >= 170) {
        return redFilter(src);
    }
    Mat mask;
    
    Mat hsv;
    medianBlur(src, src, 3);
    cvtColor(src, hsv, COLOR_BGR2HSV);
    inRange(hsv, obj.getHmin().color(), obj.getHmax().color(), mask);
    GaussianBlur(mask, mask, Size(9, 9), 2, 2);
    morphOps(mask);
    return mask;
}


