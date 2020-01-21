#pragma once
#include "wtypes.h"
#include <opencv2/imgproc.hpp>
class ScreenCapture
{
private:
	HWND hwnd;
	HDC hwindowDC, hwindowCompatibleDC;
	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	BITMAPINFOHEADER  bi;
public:
	cv::Mat image;
	ScreenCapture(float scale=1);
	~ScreenCapture();
	void capture();
};

