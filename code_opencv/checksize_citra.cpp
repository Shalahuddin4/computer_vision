#include <opencv2/opencv.hpp>

int main() {
    // Baca citra
    cv::Mat image = cv::imread("romat.jpeg");

    // Periksa ukuran citra
    if (!image.empty()) {
        int width = image.cols;
        int height = image.rows;
        int channels = image.channels(); // 3 channel untuk citra berwarna (RGB)

        std::cout << "Lebar: " << width << " Tinggi: " << height << " Channel: " << channels << std::endl;
    } else {
        std::cerr << "Gagal membaca gambar." << std::endl;
    }

    return 0;
}