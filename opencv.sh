# Setup and download OpenCV all version
sudo apt-get update
sudo apt-get upgrade -y

# Install dependencies
sudo apt install build-essential cmake git unzip pkg-config libjpeg-dev libpng-dev libtiff-dev -y
sudo apt install libavcodec-dev libxvidcore-dev libx264-dev libgtk-3-dev libatlas-base-dev gfortran -y
sudo apt install python3-dev python3-pip -y

# Download and install OpenCV
opencv_version=4.2.0 # Change the version as needed

sudo apt-get install wget

wget -O opencv.zip https://github.com/opencv/opencv/archive/$opencv_version.zip
unzip opencv.zip

cd opencv-$opencv_version

wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/$opencv_version.zip
unzip opencv_contrib.zip

mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-$opencv_version/modules \
      -D BUILD_EXAMPLES=ON ..

sudo rm -r CMakeCache.txt

cmake ..
make -j4

sudo make install
sudo ldconfig
ls

echo "Yeay, OpenCV $opencv_version successfully installed!"
