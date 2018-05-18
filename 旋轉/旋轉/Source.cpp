//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

// �Q��opencv ���ب�Ƨ@rotate
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

	cosine = cos(PI * angle / 180.);  // �n�����y��(radian): 1 �� = PI/180 �y��
	sine = sin(PI * angle / 180.);

	int side = (int)sqrt(w*w + h*h) + 1;   // �β���w�z��X������A�[ 1
	newW = side;
	newH = side;

	Mat img;
	img.create(newW, newH, CV_8UC3); // �Ыؤ@�Ӽe����(newW,newH)��RGB�v��

	for (int r = 0; r < img.rows; ++r)
	{
		for (int c = 0; c < img.cols; ++c)
		{
			x = (int)((r - img.rows / 2)*cos(anglePI) - (c - img.cols / 2)*sin(anglePI) + 0.5);    // ��X����᪺�s��m 
			y = (int)((r - img.rows / 2)*sin(anglePI) + (c - img.cols / 2)*cos(anglePI) + 0.5);
			x += src.rows / 2;
			y += src.cols / 2;
			
			// �����N����e�I���C���b����᪺�s��m
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

	//imgS = imread(argv[1], CV_LOAD_IMAGE_COLOR); //Ū���Ϲ�
	imgS = imread("lenaRGB.jpg", CV_LOAD_IMAGE_COLOR); //Ū���Ϲ�

    // �Ѥ޼�Ū�����ਤ��
	float angle = 30.0;
	imgD = rotate(imgS, angle);

	// ��ؿ��h���o��Ϲ��ɮצW��
	// string filename = argv[1];
	// size_t last_slash_idx = filename.find_last_of("\\/");
	// filename.erase(0, last_slash_idx);
	// �[�W�ؿ� \output �g�X�ɮ�
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