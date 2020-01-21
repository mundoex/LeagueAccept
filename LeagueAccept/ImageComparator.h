#pragma once
#include <opencv2/imgproc.hpp>

class ImageComparator
{
public:
	float result;
	cv::Point matchLocation;

	ImageComparator();
	~ImageComparator();

	bool compare(cv::Mat templateImage, cv::Mat image, float threshold);
};

