#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

int main()
{
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;
    std::string path = "media/minion.jpg";
    cv::Mat img = cv::imread(path), imgHsv, mask;
    cv::cvtColor(img, imgHsv, cv::COLOR_BGR2HSV);

    cv::namedWindow("trackbars", (640,200));
    cv::createTrackbar("hue min","trackbars", &hmin, 179);
    cv::createTrackbar("hue max","trackbars", &hmin, 179);
    cv::createTrackbar("sat min","trackbars", &smin, 255);
    cv::createTrackbar("sat max","trackbars", &smax, 255);
    cv::createTrackbar("val min","trackbars", &vmin, 255);
    cv::createTrackbar("val max","trackbars", &vmax, 255);

    while(1)
    {
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(imgHsv,lower,upper,mask);

        cv::imshow("image", img);
        cv::imshow("image_hsv", imgHsv);
        cv::imshow("image_mask", mask);

        cv::waitKey(1);
    }
    return 0;
}