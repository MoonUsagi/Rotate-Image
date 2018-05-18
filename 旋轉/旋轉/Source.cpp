//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

// 利用opencv 內建函數作rotate
Mat rotate(Mat src, float angle)
{
	int x, y, cx, cy, w, h, newW, newH;
	float cosine, sine;
	float PI = 3.141592653;
	float anglePI = angle * CV_PI / 180;
	w = src.rows;
	h = src.cols;
	cx = w / 2;
	cy = h / 2;

	cosine = cos(PI * angle / 180.);  // 要換成弳度(radian): 1 度 = PI/180 弳度
	sine = sin(PI * angle / 180.);

	int side = (int)sqrt(w*w + h*h) + 1;   // 用畢氏定理算出斜邊長再加 1
	newW = side;
	newH = side;

	Mat img;
	img.create(newW, newH, CV_8UC3); // 創建一個寬高為(newW,newH)的RGB影像

	for (int r = 0; r < img.rows; ++r)
	{
		for (int c = 0; c < img.cols; ++c)
		{
			x = (int)((r - img.rows / 2)*cos(anglePI) - (c - img.cols / 2)*sin(anglePI) + 0.5);    // 算出旋轉後的新位置 
			y = (int)((r - img.rows / 2)*sin(anglePI) + (c - img.cols / 2)*cos(anglePI) + 0.5);
			x += src.rows / 2;
			y += src.cols / 2;
			
			// 直接將旋轉前點的顏色填在旋轉後的新位置
			//img.at<Vec3b>(x, y)[0] = src.at<Vec3b>(r, c)[0];
			//img.at<Vec3b>(x, y)[1] = src.at<Vec3b>(r, c)[1];
			//img.at<Vec3b>(x, y)[2] = src.at<Vec3b>(r, c)[2];

			if (x >= src.rows || y >= src.cols || x <= 0 || y <= 0) {
				img.at<Vec3b>(r, c) = 0;
			}
			else {
				img.at<Vec3b>(r, c) = src.at<Vec3b>(x, y);
			}
		}
	}
	return(img);
}


int main(int argc, char *argv[])
{

	Mat imgS, imgD;

	//imgS = imread(argv[1], CV_LOAD_IMAGE_COLOR); //讀取圖像
	imgS = imread("lenaRGB.jpg", CV_LOAD_IMAGE_COLOR); //讀取圖像

    // 由引數讀取旋轉角度
	float angle = 30.0;
	imgD = rotate(imgS, angle);

	// 把目錄去掉得到圖像檔案名稱
	// string filename = argv[1];
	// size_t last_slash_idx = filename.find_last_of("\\/");
	// filename.erase(0, last_slash_idx);
	// 加上目錄 \output 寫出檔案
	// string pathOfile = ".\\output\\" + filename;
	// imwrite(pathOfile, imgD);

	// 

	namedWindow("Source image", CV_WINDOW_AUTOSIZE);
	imshow("Source image", imgS);
	namedWindow("Output image", CV_WINDOW_AUTOSIZE);
	imshow("Output image", imgD);

	waitKey(0);

	return 0;

}