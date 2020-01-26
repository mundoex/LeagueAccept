#pragma once
#include <thread>
#include <chrono>
#include <vector>
#include <limits>
#include "ImageComparator.h"
#include "src/ScreenCapture.h"
#include "MouseWrapper.h"
#include "TemplateImage.h"

enum QueueState {
	WAITING_FOR_POP,CHECKING_FOR_DODGE,STOP
};

class LeagueAccept
{
private: 
	const int TICK_RATE = 1000;//1000mili=1sec
	const int CHECK_FOR_DODGE_MINS = 5;
	const float IMAGE_THRESHOLD = 0.85f;//img cmp %

	TemplateImage pop1024x576 = TemplateImage("1024x576_pop.png", cv::IMREAD_GRAYSCALE, 1024, 576);
	TemplateImage pop1280x720 = TemplateImage("1280x720_pop.png", cv::IMREAD_GRAYSCALE, 1280, 720);
	TemplateImage pop1600x900 = TemplateImage("1600x900_pop.png", cv::IMREAD_GRAYSCALE, 1600, 900);

	bool running;
	QueueState state;
	int matchedTemplateWidth;
	int matchedTemplateHeight;
	std::thread workerThread;

	ImageComparator imageComparator;
	ScreenCapture screenCapture;
	MouseWrapper mouse;
	std::vector<TemplateImage> templateImages;

	int start();
	void tick();
	bool captureAndCompare();
	POINT calculateAcceptLocation();
public:
	LeagueAccept();
	~LeagueAccept();
	void run();
	int stop();
	void acceptMatch();
};

