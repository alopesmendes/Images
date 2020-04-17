
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


    class Hsv {
        private:
            unsigned char hue;
            unsigned char saturation;
            unsigned char value;

        public:
            /*
            *   Constructs an Hsv with it's hue, saturation and value componements.
            *   @param: hue a unsigned char.
            *   @param: saturation a unsigned char.
            *   @param: value a unsigned char.
            */
            Hsv(unsigned char hue, unsigned char saturation, unsigned char value);

            /*
            *   Constructs an Hsv with every componement at 0.
            */
            Hsv();

            operator std::string() const { 
                stringstream ss;
                ss << "Hue: " << (int)hue << " Saturation:" << (int)saturation << " Value:" << (int)value;
                return ss.str(); 
            }

            /*
            *   Returns the Scalar corresponding to our Hsv.
            *   @return: a Scalar.
            */
            Scalar color();

            /*
            *   Update the current hsv with aonther hsv and function.
            *   Update the value of hue, saturation and value with this function.
            *   @param hsv: Hsv.
            *   @param f: function taking two unsigned char and returning a unsigned char.  
            */
            void update(Hsv hsv, unsigned char (*f)(unsigned char, unsigned char)); 
            
            /*
            *   Getter for hue
            *   @return: unsigned char
            */
            unsigned char getHue();
    };

    class Rgb {
        

        private:
            unsigned char red;
            unsigned char green;
            unsigned char blue;

        public:
            /*
            *   Constructs an Rgb with it's red, green and blue componements.
            *   @param red: red a unsigned char.
            *   @param green: green a unsigned char.
            *   @param blue: blue a unsigned char.
            */
            Rgb(unsigned char red, unsigned char green, unsigned char blue);

            /*
            *   Returns the Scalar corresponding to our Bgr.
            *   @return: a Scalar.
            */
            Scalar color();
            
            /*
            *   Converts our Rgb into a Hsv.
            */
            Hsv rgbToHsv();

    };

    class Object {
        private:
            Hsv hmin;
            Hsv hmax;
            bool init;

        public:
            /*
            *   Constructs an object with init a false.
            */
            Object();

            /*  Will update the hmin and hmax according to hsv.
            *   @param: hsv a Hsv.
            */
            void update(Hsv hsv);

            /*
            *   Getter for hmin.
            *   @return: a Hsv.
            */
            Hsv getHmin();

            /*
            *   Getter for hmax.
            *   @return: a Hsv.
            */
            Hsv getHmax();
    };

    /*
    *   Fills and fixes the filter white spaces of image. 
    *   @param thresh: Mat      
    */
    void morphOps(Mat &thresh);

    /*
    *   Return an image where every red enough zones turns white.
    *   Other colors zone turn black.
    *   @param src: Mat
    *   @return: Mat
    */
    Mat redFilter(const Mat& src);


    /*
    *   Return the object created from a certain zone.
    *   The function will travel the zone and update the min and max hsv of the Object.
    *   @param: Mat
    *   @return: Object
    */
    Object createFromZone(const Mat& zone);

    /*
    *   Return an image where every color from obj and each color turn white.
    *   Other colors obj turn black.
    *   @param: Mat
    *   @return: Mat
    */
    Mat filterColors(const Mat& src, Object obj);
    
#endif