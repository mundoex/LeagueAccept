#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
class TemplateImage
{
private:
	cv::Mat image;
	int width, height;
public:
	TemplateImage(const char* filename,int flags,int width,int height);
	~TemplateImage();
};

