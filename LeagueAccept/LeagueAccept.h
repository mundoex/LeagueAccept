#pragma once
//#include <thread>
#include <chrono>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "src/opencv-utils/ImageComparator.h"
#include "src/opencv-utils/ScreenCapture.h"
#include "src/opencv-utils/MouseWrapper.h"
//#include "src/opencv-utils/TemplateImage.h"

enum QueueState {
	WAITING_FOR_POP,CHECKING_FOR_DODGE,STOP
};

class LeagueAccept
{
private: 
	const static int TICK_RATE = 2000;//1000mili=1sec
	const static int CHECK_FOR_DODGE_MINS = 5;
	const float IMAGE_THRESHOLD = 0.85f;//img cmp %
	
	//std::thread workerThread;

	ImageComparator imageComparator;
	ScreenCapture* screenCapture;
	MouseWrapper mouse;
	std::vector<cv::Mat> templateImages;

	void tick();
	bool captureAndCompare();
	POINT calculateAcceptLocation();
public:
	LeagueAccept();
	~LeagueAccept();

	bool running;
	QueueState state;

	void run();
	void start();
	int stop();
	void acceptMatch();
};