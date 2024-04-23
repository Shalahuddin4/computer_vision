#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // Baca gambar
    Mat image = imread("putih.jpeg");

    if (image.empty()) {
        cout << "Gambar tidak dapat dibuka. Pastikan file gambar ada di direktori yang benar." << endl;
        return -1;
    }

    // Konversi gambar ke format YCrCb
    Mat ycrcbImage;
    cvtColor(image, ycrcbImage, COLOR_BGR2YCrCb);

    // Ambil nilai lower dan upper untuk setiap komponen Y, Cr, dan Cb
    Vec3b lower = Vec3b(255, 255, 255); // Nilai awal yang besar untuk nilai lower
    Vec3b upper = Vec3b(0, 0, 0); // Nilai awal yang kecil untuk nilai upper

    for (int y = 0; y < ycrcbImage.rows; ++y) {
        for (int x = 0; x < ycrcbImage.cols; ++x) {
            Vec3b ycrcb = ycrcbImage.at<Vec3b>(y, x);

            // Perbarui nilai lower dan upper untuk setiap komponen
            for (int i = 0; i < 3; ++i) {
                lower[i] = min(lower[i], ycrcb[i]);
                upper[i] = max(upper[i], ycrcb[i]);
            }
        }
    }

    // Cetak nilai lower dan upper untuk setiap komponen
    cout << "Lower Y: " << (int)lower[0] << ", Cr: " << (int)lower[1] << ", Cb: " << (int)lower[2] << endl;
    cout << "Upper Y: " << (int)upper[0] << ", Cr: " << (int)upper[1] << ", Cb: " << (int)upper[2] << endl;

    return 0;
}
