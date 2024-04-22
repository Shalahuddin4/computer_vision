#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

int main()
{
    cv::Mat img(512,512, CV_8UC3, cv::Scalar(0,255,255));

    cv::circle(img,cv::Point(256,256),155,cv::Scalar(0,69,255),cv::FILLED);
    cv::rectangle(img, cv::Point(130,226), cv::Point(382, 296), cv::Scalar(255,255,255),cv::FILLED);
    cv::line(img, cv::Point(130,296), cv::Point(382,296), cv::Scalar(0,0,0),2);

    cv::putText(img,"tes",cv::Point(137,262),cv::FONT_HERSHEY_DUPLEX,2,cv::Scalar(0,0,0));

    cv::imshow("image",img);
    cv::waitKey(0);
    return 0;
}