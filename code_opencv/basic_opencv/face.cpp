#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>

void gambarWajah(std::string path)
{
    cv::Mat img = cv::imread(path);

    cv::CascadeClassifier faceCascade;
    faceCascade.load("media/haarcascade_frontalface_default.xml");
    if(faceCascade.empty())
    {
        std::cout << "XML file not found" << std::endl;
    }
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++)
	{
		cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);
	}
    std::cout << "jumlah = " <<  faces.size() << std::endl;

	cv::imshow("Image", img);
	cv::waitKey(0);
}
void faceWebcam()
{
    cv::VideoCapture cap(0);
    cv::Mat img;

    while (1)
    {
        cap.read(img);
        cv::CascadeClassifier faceCascade;
        faceCascade.load("media/haarcascade_frontalface_default.xml");
        if(faceCascade.empty())
        {
            std::cout << "XML file not found" << std::endl;
        }
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(img, faces, 1.1, 10);
    
	    for (int i = 0; i < faces.size(); i++)
	    {
	    	cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);
	    }
        std::cout << "jumlah = " <<  faces.size() << std::endl;
        cv::imshow("image", img);
        cv::waitKey(1);
    }
    
}
int main()
{
    // gambarWajah("media/kumpul.jpg");
    faceWebcam();

    return 0;
}