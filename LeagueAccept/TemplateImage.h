#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
class TemplateImage
{
private:
	
	
public:
	cv::Mat image;
	int clientWidth, clientHeight;
	TemplateImage(const char* filename,int flags,int clientWidth,int clientHeight);
	~TemplateImage();
};

