#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    // Read in the two images and create a new window
    cv::Mat imgL = cv::imread("TsukubaL.png", cv::IMREAD_GRAYSCALE);
    cv::Mat imgR = cv::imread("TsukubaR.png", cv::IMREAD_GRAYSCALE);
    namedWindow("Window", WINDOW_NORMAL);

    // Set the initial dispariy and window value to 5
    int numDisparities = 5;
    int numWindow = 5;

    // Create the trackbar with size of 10
    // range of disparity: 0 - 160
    // Range of window: 5 - 105
    cv::createTrackbar("Disparity", "Window", &numDisparities, 10);
    cv::createTrackbar("numWindow", "Window", &numWindow, 10);

    // Exit program if either image failed to load
    if(imgL.empty() || imgR.empty())
    {
        std::cout << "Error reading message" << std::endl;
        return -1;
    }

    // outputArrays to hold the disparity map
    Mat outputArray = Mat( imgL.rows, imgL.cols, CV_16S );
    Mat displayArray = Mat( imgL.rows, imgL.cols, CV_8U );

    while(1) {
        // Initialze a new stereoBM object
        StereoBM stereo(StereoBM::BASIC_PRESET, numDisparities * 16, numWindow * 2 + 5);
        // get the disparity between the two images, and comvert 16S to 8UC3
        (stereo)(imgL, imgR, outputArray, CV_16S);
        outputArray.convertTo( displayArray, CV_8UC3);

        // Display the image in window, wait.
        imshow("Window", displayArray);
        waitKey(100);
        
    }
    
    return 0;
}



