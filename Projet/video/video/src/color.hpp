
/*
@Authors: LOPES MENDES Ailton, MALEK Akram
*/
#ifdef __cplusplus

    #include <opencv2/opencv.hpp>
    #include <opencv2/core/core.hpp>
    #include <opencv2/highgui/highgui.hpp>

    #include <iostream>
    #include <map>

    using namespace cv;
    using namespace std;



    void morphOps(Mat &thresh);

    /*
    *   Return an map with an Point for every every color
    *   @param: Mat
    *   @return: map*/
    map<uchar, Vec3b> allColorInZone(const Mat& zone);

    /*
    *   Return an image where every red enough zones turns white.
    *   Other colors zone turn black.
    *   @param: Mat
    *   @return: Mat
    */
    Mat redFilter(const Mat& src);


    /*
    *   Return an image where every color from zone and each color turn white.
    *   Other colors zone turn black.
    *   @param: Mat
    *   @return: Mat
    */
    Mat filterColors(const Mat& src, const Mat& zone);
    
#endif