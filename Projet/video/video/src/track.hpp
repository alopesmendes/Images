#ifdef __cplusplus

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

/*
* Return an image delimeting the red zones using filter.
* @param src: Mat
* @param filter: Mat
* @return Mat
*/
Mat trackFilteredObject(const Mat& src, const Mat& filter);

#endif