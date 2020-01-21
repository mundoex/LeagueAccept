#include <opencv2/opencv.hpp>
#include <iostream>
#include "wtypes.h"
#include "opencv2/highgui.hpp"
#include "src/ScreenCapture.h"
#include "ImageComparator.h"
#define MATCH_THRESHOLD 0.85
#define TICK_RATE 1

int main(int argc, char** argv)
{
	ScreenCapture sc = ScreenCapture();
	sc.capture();
	ImageComparator ic = ImageComparator();

	cv::Mat acceptPng = cv::imread("accept.png", cv::IMREAD_GRAYSCALE);
	cv::Mat cropped = cv::imread("cropped.png", cv::IMREAD_GRAYSCALE);
	cv::Mat pop720 = cv::imread("1280x720.jpg", cv::IMREAD_GRAYSCALE);

	cv::Mat opencvImg = cv::imread("opencv.png", cv::IMREAD_GRAYSCALE);
	cv::Mat opencv2Img = cv::imread("opencv2.png", cv::IMREAD_GRAYSCALE);

	//screenshot + convert to gray
	cv::Mat screenshot;
	cv::cvtColor(sc.image, screenshot, CV_BGR2GRAY);
	
	ic.compare(acceptPng, cropped, 0.85f);
	std::cout << ic.result << std::endl;
	cv::waitKey(5000);
}