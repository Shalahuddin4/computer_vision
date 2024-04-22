#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

void gantiSize(std::string path, int width, int height)
{
    cv::Mat img = cv::imread(path), imgResize;
    cv::resize(img, imgResize, cv::Size(width,height));

    cv::imshow("image",img);
    cv::imshow("image_resize",imgResize);
    cv::waitKey(0);
}
void gantiSizeSkala(std::string path, float width, float height)
{
    cv::Mat img = cv::imread(path), imgResize;
    cv::resize(img, imgResize, cv::Size(),width,height);

    cv::imshow("image",img);
    cv::imshow("image_resize",imgResize);
    cv::waitKey(0);
}
void cropGambar(std::string path)
{
    cv::Mat img = cv::imread(path),imgCrop;

    cv::Rect roi(200,100,300,500);
    imgCrop = img(roi);
    cv::imshow("image",img);
    cv::imshow("image_crop",imgCrop);
    cv::waitKey(0);

}
int main()
{
    // gantiSize("media/orang.png",640,480);
    // gantiSizeSkala("media/orang.png",0.1,1);
    // cropGambar("media/orang.png");


    return 0; 
}