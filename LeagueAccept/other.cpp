//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include "wtypes.h"
//#include "opencv2/highgui.hpp"
//#include "src/ScreenCapture.h"
//#include "ImageComparator.h"

//int main(int argc, char** argv)
//{
//	ScreenCapture sc = ScreenCapture();
//	sc.capture();
//	ImageComparator ic = ImageComparator();
//
//	cv::Mat acceptTemplate = cv::imread("accept.png", cv::IMREAD_GRAYSCALE);
//	cv::Mat cropped = cv::imread("cropped.png", cv::IMREAD_GRAYSCALE);
//	cv::Mat pop720 = cv::imread("1280x720.jpg", cv::IMREAD_GRAYSCALE);
//	cv::Mat full_queue_pop_1280x720 = cv::imread("full_queue_pop_1280x720.png", cv::IMREAD_GRAYSCALE);
//	cv::Mat full_queue_pop_1280x720_2 = cv::imread("full_queue_pop_1280x720_2.png", cv::IMREAD_GRAYSCALE);
//
//
//	cv::Mat opencvImg = cv::imread("opencv.png", cv::IMREAD_GRAYSCALE);//n da pq e mais pequeno q o template
//	cv::Mat opencv2Img = cv::imread("opencv2.png", cv::IMREAD_GRAYSCALE);//n da pq e mais pequeno q o template
//
//	//screenshot + convert to gray
//	cv::Mat screenshot;
//	cv::cvtColor(sc.image, screenshot, CV_BGR2GRAY);
//	
//	ic.contains(acceptTemplate, cropped, 0.85f);
//	std::cout << ic.result << std::endl;
//	
//	cv::waitKey(5000);
//}

#include "SystemTray.h"
int main()
{
	SystemTray sysTray = SystemTray();
	std::wstring stringo = L"TESTE";
	sysTray.setToolTip(stringo);
	sysTray.show();
	Sleep(10000);
}