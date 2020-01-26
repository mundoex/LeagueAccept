#include "TemplateImage.h"

TemplateImage::TemplateImage(const char * filename, int flags, int clientWidth, int clientHeight)
{
	this->image = cv::imread(filename, flags);
	this->clientWidth = clientWidth;
	this->clientHeight = clientHeight;
}

TemplateImage::~TemplateImage()
{
}
