#include "ImageComparator.h"

ImageComparator::ImageComparator()
{
	//error default values
	result = -1;
	matchLocation = cv::Point(-1, -1);
}

ImageComparator::~ImageComparator()
{

}

bool ImageComparator::contains(cv::Mat templateImage, cv::Mat image, float threshold)
{
	if (!templateImage.empty() || !image.empty()) {
		cv::Mat resultMat;
		cv::matchTemplate(templateImage, image, resultMat, cv::TM_CCOEFF_NORMED);
		double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
		cv::Point matchLoc;
		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc);
		matchLoc = minLoc;
		result = (float)maxVal;
		matchLocation = matchLoc;
	}
	return result >= threshold;
}