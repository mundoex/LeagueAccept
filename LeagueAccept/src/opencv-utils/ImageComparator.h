#pragma once
#include <opencv2/imgproc.hpp>
class ImageComparator
{
public:
	float result;
	cv::Point matchLocation;

	ImageComparator();
	~ImageComparator();

	bool contains(cv::Mat templateImage, cv::Mat image, float threshold);
};

