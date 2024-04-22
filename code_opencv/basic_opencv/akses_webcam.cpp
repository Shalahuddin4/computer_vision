#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>


void TampilkanGambar()
{
    std::string path = "media/warna.png";
    cv::Mat img = cv::imread(path);
    cv::imshow("image", img);
    cv::waitKey(0);
}
void TampilkanVideo()
{
    std::string path = "media/test.mp4";
    cv::VideoCapture cap(path);
    cv::Mat img;

    while (1)
    {
        cap.read(img);
        cv::imshow("image", img);
        cv::waitKey(20);
    }
    
}
void Webcam()
{
    cv::VideoCapture cap(0);
    cv::Mat img, imgLap;


    while (1)
    {

        cap.read(img);
        cv::imshow("image", img);
        cv::waitKey(1);
    }
    
}
int main() {
    //TampilkanGambar();
    //TampilkanVideo();
    Webcam();
    return 0;
}