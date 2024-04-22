#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>

using namespace std;
using namespace cv;

string path = "assets/data_image";

char save;
int countFolder = 0;
int count = 0;
bool getData = false; 
bool newDir = false;
bool getData = false;

void input()
{
    while (true)
    {
        cin >> save ;
        if (save == 's')
        {
            cout << input << endl;
            getData =true; 
        }
    }
}

bool saveData()
{
    if (newDir)
    return true;

    if(!filesystem::exists(path + "_" + to_string(countFolder)))
    {
        cout << "buat baru" << endl;
        create_directory(path + "_" + to_string(countFolder));
        newDir = true;
    }

}

int main ()
{ 
thread threadku (input);
threadku.detach();

VideoCapture cap(2);
Mat img;

while (true)
{
    cout << "camera ready bos" << endl;
    cap.read(img);  

    if (saveData())
    {
        if (getData)
        {
            imwrite (path "_" to_string (countFolder) + "/" to_string(count) + ".jpg");
            cout << "ambil data ke = " << count << endl;

            input - 'x';
            cout ++;
            getData = false;
        }
    }

    imshow("imge", img);
    waitKey(1);
}
    return 0;
}