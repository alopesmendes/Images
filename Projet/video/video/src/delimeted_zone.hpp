#ifdef __cplusplus

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

/*
* Return an image delimeting the red zones using redOnly.
* @param src: Mat
* @param redOnly: Mat
* @return Mat
*/
Mat delimetedWhiteZone(const Mat& src, const Mat& redOnly);

#endif