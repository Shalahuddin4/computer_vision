#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {

    //buka file video
    VideoCapture cap(2);
    if (!cap.isOpened())
    {
        cout<<" kamera tidak bisa diakses, pastikan id kamera dan terpasang dengan benar." << endl;
        return -1;
    }

    while (true)
    {
        Mat frame;
        cap >> frame;
    if (frame.empty())
    {
        cout << " kamera tidak bisa dapat membaca frame. " << endl;
    }

/*    // Membaca gambar
    Mat image = imread("gambar/2.jpeg");
    if (image.empty()) 
    {
        cout << "Gambar tidak dapat dibuka. Pastikan file gambar ada di direktori yang benar." << endl;
        return -1;
    }
*/
    
    // Konversi gambar ke dalam format HSV
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2YCrCb);

/////////////////////////* Deteksi lapangan hijau *///////////////////////////////////

    // Menentukan range warna hijau dalam HSV
    Scalar lower_green = Scalar(0, 65, 35);
    Scalar upper_green = Scalar(255, 193, 188);

    // Membuat mask untuk menentukan area hijau dalam gambar
    Mat green_mask;
    inRange(hsv, lower_green, upper_green, green_mask);

    //  blur green field
    Mat green_blur;
    GaussianBlur(green_mask, green_blur, Size(5,5), 0);

    //  morphology dilasi pada lapangan
    Mat green_dilate;
    dilate(green_blur, green_dilate, Mat(), Point(-1,-1),4, 1,1);


/////////////////////////* Deteksi lapangan putih *///////////////////////////////////

    // Menentukan range warna putih dalam HSV
    Scalar lower_white = Scalar(68, 122, 113);
    Scalar upper_white = Scalar(249, 126, 127);

    // Membuat mask untuk deteksi warna putih
    Mat white_mask;
    inRange(hsv, lower_white, upper_white, white_mask);

    //  blur line white
    Mat white_blur;
    GaussianBlur(white_mask, white_blur, Size(15,15), 0);
    
    Mat white_dilate;
    dilate(white_blur, white_dilate, Mat(), Point(-1, -1), 2, 1, 1);

    // Gabungkan mask hijau dan mask putih
    Mat combined_mask;
    bitwise_and(green_dilate, white_dilate, combined_mask);

    // Deteksi tepi pada gambar dengan mask gabungan
    Mat edges;
    Canny(combined_mask, edges, 30, 150, 3);

    // Deteksi kontur pada gambar dengan tepi
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Gambar kontur pada gambar asli
    for (size_t i = 0; i < contours.size(); i++) {
        drawContours(frame, contours, static_cast<int>(i), Scalar(255, 255, 255), 2);
    }

    // Menerapkan transformasi Hough untuk mendeteksi garis putih
    vector<Vec4i> lines;
    HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 100, 10);

    // Menggambar garis pada gambar asli
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 2);
    }

    // Menampilkan gambar
    imshow("filter blur pada lapangan", green_blur);
    imshow("filter dilasi pada lapangan", green_dilate);
    imshow("filter blur pada garis", white_blur);
    imshow("filter dilasi pada garis", white_dilate);
    imshow("hasil", frame);
    
    //keluar dari loop 
    if (waitKey(10) == 'q')
    break;
}
    waitKey(0);
    destroyAllWindows();

    return 0;
}
