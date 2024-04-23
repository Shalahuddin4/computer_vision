#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

int main() {
    cv::Mat image = cv::imread("docs/5meter.jpeg", cv::IMREAD_GRAYSCALE);
    cv::Mat output;

    // Konversi gambar ke skala abu-abu
    cv::cvtColor(image, output, cv::COLOR_GRAY2BGR);

    // Deteksi garis menggunakan Transformasi Hough
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(image, lines, 1, CV_PI / 180, 100);

    // Hapus garis horizontal
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        // Filter garis horizontal dengan kemiringan mendekati 0 atau PI
        if (theta < CV_PI / 4 || theta > 3 * CV_PI / 4) {
            // Gambar garis yang terdeteksi
            cv::Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            // Hapus garis dari gambar
            cv::line(output, pt1, pt2, cv::Scalar(255, 255, 255), 3, cv::LINE_AA);
        }
    }

    cv::imshow("Original Image", image);
    cv::imshow("Hough Lines Removed", output);
    cv::waitKey(0);

    return 0;
}
