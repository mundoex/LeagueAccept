#include "ImageComparator.h"

ImageComparator::ImageComparator()
{
	//error default values
	this->result = -1;
	this->center = cv::Point(-1, -1);
	this->matchLocationMax = cv::Point(-1, -1);
}

ImageComparator::~ImageComparator()
{
	
}

bool ImageComparator::contains(cv::Mat templateImage, cv::Mat image, float threshold)
{
	if (!templateImage.empty() || !image.empty()) {
		cv::Mat resultMat;
		cv::matchTemplate(templateImage, image, resultMat, cv::TM_CCOEFF_NORMED);
		double minVal; double maxVal; cv::Point min;
		minMaxLoc(resultMat, &minVal, &maxVal, &min, &this->matchLocationMax);
		
		result = (float)maxVal;
		if (result > threshold) {
			this->center = { templateImage.cols/2,templateImage.rows/2};
			return true;
		}
	}
	return result > threshold;
}