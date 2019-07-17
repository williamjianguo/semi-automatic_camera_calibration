#include "pch.h"
#include "opencv2/opencv.hpp"
#include "IPM.h"
#include <iostream>
using namespace std;
using namespace cv;

static void ContrastAndBright(int, void *);
Mat g_srcImage, g_dstImage;
int g_left;
int g_right;
int g_rows;//�߶ȵ�������
int main()
{
	//�ı����̨ǰ��ɫ�ͱ���ɫ
	//system("color5F");

	//�����û��ṩ��ͼ��
	g_srcImage = imread("test1.jpg");
	if (!g_srcImage.data) { printf("Oh��no����ȡg_srcImageͼƬ����~��\n"); return false; }
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	//�趨�ԱȶȺ����ȵĳ�ֵ
	g_left = 80;
	g_right = 80;

	//��������
	namedWindow("Input", WINDOW_NORMAL);

	//�����켣��
	createTrackbar("g_left��", "Input", &g_left, 600, ContrastAndBright);
	createTrackbar("g_right", "Input", &g_right, 500, ContrastAndBright);
	createTrackbar("g_rows", "Input", &g_rows, 1000, ContrastAndBright);

	//���ûص�����
	ContrastAndBright(g_left, 0);
	ContrastAndBright(g_right, 0);
	ContrastAndBright(g_rows, 0);


	//���һЩ������Ϣ
	cout << endl << "\t�š����ˣ�������������۲�ͼ��Ч��~\n\n"
		<< "\t���¡�q����ʱ�������˳�~!\n"
		<< "\n\n\t\t\t\tbyǳī";

	//���¡�q����ʱ�������˳�
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

static void ContrastAndBright(int, void *)
{
	namedWindow("Input",  WINDOW_NORMAL);
	namedWindow("Output",  WINDOW_NORMAL);

		Mat inputImg;//, inputImgGray;
		Mat outputImg;
		inputImg = imread("test1.jpg");
		int height = inputImg.rows;
		int width = inputImg.cols;
		// The 4-points at the input image	
		vector<Point2f> origPoints;
		origPoints.push_back(Point2f(0, height));
		origPoints.push_back(Point2f(width, height));
		origPoints.push_back(Point2f(width / 2 + g_left, g_rows));
		origPoints.push_back(Point2f(width / 2 - g_right, g_rows));
	
		// The 4-points correspondences in the destination image
		vector<Point2f> dstPoints;
		dstPoints.push_back(Point2f(0, height));
		dstPoints.push_back(Point2f(width, height));
		dstPoints.push_back(Point2f(width, 0));
		dstPoints.push_back(Point2f(0, 0));
	
		// IPM object
		IPM ipm(Size(width, height), Size(width, height), origPoints, dstPoints);
	
		// Main loop
		int frameNum = 0;
		{
			ipm.applyHomography(inputImg, outputImg);

			ipm.drawPoints(origPoints, inputImg);

			imshow("Input", inputImg);
			imshow("Output", outputImg);
			waitKey(1);
		}
}