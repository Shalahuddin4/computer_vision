#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream> // Untuk mengkonversi nilai jarak ke string

using namespace std;

int main() {
    cv::VideoCapture cap(2);

    while (true) {
        cv::Mat frame;
        
        if (!cap.isOpened()) {
            cap.release();
            cap.open(0);
            perror("error : ");
            continue;
        }

        cap >> frame;
        if (frame.empty()) {
            cout << "Tidak dapat menangkap frame dari kamera." << endl;
            break;
        }

        // Konversi frame ke ruang warna YUV
        cv::Mat yuvFrame;
        cv::cvtColor(frame, yuvFrame, cv::COLOR_BGR2YUV);

        // Buat salinan komponen Y (luminansi)
        cv::Mat yChannel;
        cv::extractChannel(yuvFrame, yChannel, 0); // Komponen Y adalah komponen pertama (indeks 0)

        // Tentukan batas bawah dan atas untuk nilai Y yang mewakili warna putih
        int lowerY = 30; // Nilai Y yang rendah untuk warna putih
        int upperY = 255; // Nilai Y yang tinggi untuk warna putih

        // Buat mask untuk nilai Y yang mewakili warna putih
        cv::Mat whiteMask = (yChannel >= lowerY) & (yChannel <= upperY);

        // Elemen untuk operasi erosi
        int erosionSize = 3; // Ukuran erosi
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * erosionSize + 1, 2 * erosionSize + 1), cv::Point(erosionSize, erosionSize));

        // Erosi untuk membersihkan gambar
        cv::Mat erodedMask;
        cv::erode(whiteMask, erodedMask, element);

        // Filter Gaussian blur
        cv::Mat blurredImage;
        int kernelSize = 5; // Ukuran kernel Gaussian (harus ganjil)
        cv::GaussianBlur(erodedMask, blurredImage, cv::Size(kernelSize, kernelSize), 0);

        // Terapkan filter median dengan ukuran kernel 3x3 untuk menghilangkan noise
        cv::Mat filteredMask;
        cv::medianBlur(blurredImage, filteredMask, 3);

        // Deteksi tepi pada mask putih yang telah diperkecil
        cv::Mat whiteEdges;
        cv::Canny(filteredMask, whiteEdges, 100, 200);

        // Temukan semua kontur dalam frame
        vector<vector<cv::Point>> contours;
        cv::findContours(whiteEdges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Simpan dua sisi gawang (kiri dan kanan)
        cv::Rect leftGoalPost;
        cv::Rect rightGoalPost;

        // Post-processing: Hapus objek yang terlalu kecil (noise) berdasarkan luasnya
        double minObjectArea = 1200; // Atur sesuai kebutuhan
        cv::Mat cleanedMask = cv::Mat::zeros(filteredMask.size(), CV_8U);
        for (size_t i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);
            if (area >= minObjectArea) {
                // Gambar objek ke dalam cleanedMask
                cv::drawContours(cleanedMask, contours, static_cast<int>(i), cv::Scalar(255), cv::FILLED);
            }
        }

        // Filter kontur berdasarkan ukuran atau rasio aspek untuk mengidentifikasi sisi-sisi tiang gawang
      for (size_t i = 0; i < contours.size(); i++) {
    cv::Rect rect = cv::boundingRect(contours[i]);

    double aspectRatio = static_cast<double>(rect.width) / rect.height;

    if (rect.width > 25 && rect.height > 100 && aspectRatio > 0.8 && aspectRatio < 1.2) {
        // Filter tambahan untuk memastikan bahwa sisi-sisi tiang adalah garis lurus
        cv::Mat roi = yChannel(rect);
        cv::Mat edges;
        cv::Canny(roi, edges, 100, 200);

        std::vector<cv::Vec2f> lines;
        cv::HoughLines(edges, lines, 1, CV_PI / 180, 100);

        bool isVerticalLine = false;
        for (size_t j = 0; j < lines.size(); j++) {
            float rho = lines[j][0];
            float theta = lines[j][1];

            // Check if the line is nearly vertical
            if (theta > CV_PI / 2.0 - CV_PI / 8.0 && theta < CV_PI / 2.0 + CV_PI / 8.0) {
                isVerticalLine = true;
                break;
            }
        }

        if (isVerticalLine) {
            if (rect.x < frame.cols / 2) {
                leftGoalPost = rect;
            } else {
                rightGoalPost = rect;
            }
        }
    }
}


        // Menandai gawang kiri dengan kotak hijau
        cv::rectangle(frame, leftGoalPost, cv::Scalar(0, 255, 0), 4);
        // Menandai gawang kanan dengan kotak hijau
        cv::rectangle(frame, rightGoalPost, cv::Scalar(0, 255, 0), 4);
        // Menambahkan label "Gawang Kiri" dan "Gawang Kanan" di frame kamera
        cv::putText(frame, "Gawang Kiri", cv::Point(leftGoalPost.x, leftGoalPost.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        cv::putText(frame, "Gawang Kanan", cv::Point(rightGoalPost.x, rightGoalPost.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);

        // Misalnya, faktor konversi dari piksel ke meter adalah 0.01 (1 piksel = 0.01 meter)
        double conversionFactor = 0.01;

        // Menghitung jarak gawang kiri dan gawang kanan terhadap kamera
        double distanceToCameraLeft = leftGoalPost.x * conversionFactor;
        double distanceToCameraRight = (frame.cols - rightGoalPost.x) * conversionFactor;

        // Mengkonversi nilai jarak ke string
        ostringstream leftDistanceStream;
        leftDistanceStream << "Gawang Kiri: " << fixed << setprecision(2) << distanceToCameraLeft << " m";
        string leftDistanceText = leftDistanceStream.str();
        
        ostringstream rightDistanceStream;
        rightDistanceStream << "Gawang Kanan: " << fixed << setprecision(2) << distanceToCameraRight << " m";
        string rightDistanceText = rightDistanceStream.str();

        // Menampilkan nilai jarak gawang kiri dan gawang kanan di frame
        cv::putText(frame, leftDistanceText, cv::Point(200, 400), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
        cv::putText(frame, rightDistanceText, cv::Point(frame.cols - 400, 400), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);

        // Menampilkan jarak gawang kiri dan gawang kanan di konsol
        cout << leftDistanceText << endl;
        cout << rightDistanceText << endl;

        // Menampilkan frame hasil
        cv::imshow("Deteksi Sisi-sisi Tiang Gawang (YUV)", frame);
        cv::imshow("Channel YUV", yuvFrame);
        cv::imshow("ERODEDMASK", erodedMask);
        cv::imshow("Gaussian blur", blurredImage);
        cv::imshow("filter median", filteredMask);
        cv::imshow("GAWANG FIX", whiteEdges);
        cv::imshow("Hapus countur terkecil", cleanedMask);

        char key = cv::waitKey(1);
        if (key == 'q') {
            break;  // Keluar dari loop jika tombol 'q' ditekan
        }
    }

    return 0;
}
