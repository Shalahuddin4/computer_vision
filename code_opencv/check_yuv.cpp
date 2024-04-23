#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Buka gambar dari file
    cv::Mat image = cv::imread("romat.jpeg");

    if (image.empty()) {
        std::cout << "Tidak dapat membuka gambar." << std::endl;
        return -1;
    }

    // Ambil piksel dari gambar pada koordinat (x, y)
    int x = 510; // Koordinat x piksel yang ingin diperiksa
    int y = 409; // Koordinat y piksel yang ingin diperiksa

     // Dapatkan nilai piksel pada koordinat (x, y)
    cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

    // Pisahkan komponen warna (biru, hijau, merah)
    int blue = pixel[0];
    int green = pixel[1];
    int red = pixel[2];

    // Tampilkan nilai piksel
    std::cout << "Nilai piksel pada koordinat (" << x << ", " << y << "):" << std::endl;
    std::cout << "Komponen Biru (B): " << blue << std::endl;
    std::cout << "Komponen Hijau (G): " << green << std::endl;
    std::cout << "Komponen Merah (R): " << red << std::endl;

    // Tunggu penekanan tombol sebelum menutup jendela
    cv::waitKey(0);

/
    // Dapatkan nilai komponen YUV pada piksel (x, y)
    cv::Vec3b yuv = image.at<cv::Vec3b>(y, x);

    // Nilai komponen Y, U, dan V
    int Y = yuv[0]; // Komponen Y (luminansi)
    int U = yuv[1]; // Komponen U (chrominance biru)
    int V = yuv[2]; // Komponen V (chrominance merah)

    std::cout << "Nilai Y: " << Y << std::endl;
    std::cout << "Nilai U: " << U << std::endl;
    std::cout << "Nilai V: " << V << std::endl;

    return 0;
}