#include "TemplateImage.h"

TemplateImage::TemplateImage(const char * filename, int flags, int width, int height)
{
	this->image = cv::imread(filename, flags);
	this->width = width;
	this->height = height;
}

TemplateImage::~TemplateImage()
{
}
