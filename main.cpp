#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;

int main() {

    // More Comments
    

    cv::Mat imgL = cv::imread("TsukubaL.png", cv::IMREAD_GRAYSCALE);
    cv::Mat imgR = cv::imread("TsukubaR.png", cv::IMREAD_GRAYSCALE);
    namedWindow("Window");
    int numDisparities;
    int numwindow;
    int sliderPosition;

    cv::createTrackbar("Disparity", "Window", NULL, 10);

    if(imgL.empty() || imgR.empty())
    {
        std::cout << "Error reading message" << std::endl;
        return -1;
    }
//    imshow("imgL", imgL);
//    imshow("imgR", imgR);

    Ptr<StereoBM> stereo;

    Mat outputArray = Mat( imgL.rows, imgL.cols, CV_16S );
    Mat displayArray = Mat( imgL.rows, imgL.cols, CV_8U );

    int count = 0;
    while(1) {
        count ++;
        sliderPosition = getTrackbarPos("Disparity", "Window");
        std::cout << count << "    ";
        std::cout << sliderPosition << "    ";
        numDisparities = 16 * sliderPosition;
        std::cout << numDisparities << std::endl;
        //      StereoBM stereo(StereoBM::BASIC_PRESET, numDisparities, 25);
        stereo = new StereoBM(StereoBM::BASIC_PRESET, numDisparities, 25);

        (*stereo)(imgL, imgR, outputArray, CV_16S);
        outputArray.convertTo( displayArray, CV_8UC3);

        imshow("Window", displayArray);
        waitKey(50);

    }
    
    return 0;
}



