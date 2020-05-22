
/*
*   @Authors: LOPES MENDES Ailton, MALEK Akram
*/
#ifdef __cplusplus

    #include <opencv2/opencv.hpp>
    #include <opencv2/core/core.hpp>
    #include <opencv2/highgui/highgui.hpp>

    #include <iostream>

    using namespace cv;
    using namespace std;


    class Hsv {
        private:
            unsigned char hue;
            unsigned char saturation;
            unsigned char value;

        public:
            /**
            *   @brief Constructs an Hsv with it's hue, saturation and value componements.
            *   @param: hue a unsigned char.
            *   @param: saturation a unsigned char.
            *   @param: value a unsigned char.
            */
            Hsv(unsigned char hue, unsigned char saturation, unsigned char value);

            /**
            *   @brief Constructs an Hsv with every componement at 0.
            */
            Hsv();

            operator std::string() const { 
                stringstream ss;
                ss << "Hue: " << (int)hue << " Saturation:" << (int)saturation << " Value:" << (int)value;
                return ss.str(); 
            }

            /**
            *   @brief Returns the Scalar corresponding to our Hsv.
            *   @return: a Scalar.
            */
            Scalar color();

            /**
            *   Update the current hsv with another hsv and function.
            *   Update the value of hue, saturation and value with this function.
            *   @param hsv: Hsv.
            *   @param f: function taking two unsigned char and returning a unsigned char.  
            */
            void update(Hsv hsv, unsigned char (*f)(unsigned char, unsigned char)); 
            
            /**
            *   @brief Verify if the following hsv correspond to the red color.
            *   @return: bool.
            */
            bool isRed();
    };

    class Rgb {
        

        private:
            unsigned char red;
            unsigned char green;
            unsigned char blue;

        public:
            /**
            *   @brief Constructs an Rgb with it's red, green and blue componements.
            *   @param red: red a unsigned char.
            *   @param green: green a unsigned char.
            *   @param blue: blue a unsigned char.
            */
            Rgb(unsigned char red, unsigned char green, unsigned char blue);

            /**
            *   @brief Returns the Scalar corresponding to our Bgr.
            *   @return: a Scalar.
            */
            Scalar color();
            
            /**
            *   @brief Converts our Rgb into a Hsv.
            */
            Hsv rgbToHsv();

    };

    class Object {
        private:
            Hsv hmin;
            Hsv hmax;
            bool init;

        public:
            /**
            *   @brief Constructs an object with init a false.
            */
            Object();

            /**  
            *   @brief Will update the hmin and hmax according to hsv.
            *   @param: hsv a Hsv.
            */
            void update(Hsv hsv);

            /**
            *   @brief Getter for hmin.
            *   @return: a Hsv.
            */
            Hsv getHmin();

            /**
            *   @brief Getter for hmax.
            *   @return: a Hsv.
            */
            Hsv getHmax();
    };

    /**
    *   @brief Fills and fixes the filter white spaces of image. 
    *   @param thresh: Mat      
    */
    void morphOps(Mat &thresh);

    /**
    *   @brief Return an image where every red enough zones turns white.
    *   Other colors zone turn black.
    *   @param src: Mat
    *   @return: Mat
    */
    Mat redFilter(const Mat& src);


    /**
    *   @brief Return the object created from a certain zone.
    *   The function will travel the zone and update the min and max hsv of the Object.
    *   @param: Mat
    *   @return: Object
    */
    Object createFromZone(const Mat& zone);

    /**
    *   @brief Return an image where every color from obj and each color turn white.
    *   Other colors obj turn black.
    *   @param: Mat
    *   @return: Mat
    */
    Mat filterColors(const Mat& src, Object obj);
    
#endif