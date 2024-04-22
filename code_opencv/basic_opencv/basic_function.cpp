#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

void gambarGray(std::string path){
    cv::Mat img = cv::imread(path), imgGray;

    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    cv::imshow("image", img);
    cv::imshow("image_gray", imgGray);
    cv::waitKey(0);
}
void gambarBlur(std::string path){
    cv::Mat img = cv::imread(path), imgBlur;

    cv::GaussianBlur(img,imgBlur, cv::Size(3,3),3,0);

    cv::imshow("image", img);
    cv::imshow("image_blur", imgBlur);
    cv::waitKey(0);
}

void gambarGaris(std::string path){
    cv::Mat img = cv::imread(path),kernel, imgCanny, imgDil,  imgErode;
    kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::Canny(img, imgCanny, 25,75);
    cv::dilate(imgCanny, imgDil, kernel);
    cv::erode(imgDil, imgErode, kernel);

    cv::imshow("image",img);
    cv::imshow("image_canny",imgCanny);
    cv::imshow("image_dilate",imgDil);
    cv::imshow("image_erode",imgErode);
    cv::waitKey(0);
}
int main()
{
    // gambarGray("media/warna.png");
    // gambarBlur("media/jokowi.jpeg");
    // gambarGaris("media/jokowi.jpeg");

    return 0;
}