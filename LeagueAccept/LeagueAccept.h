#pragma once
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include "src/opencv-utils/ImageComparator.h"
#include "src/opencv-utils/ScreenCapture.h"
#include "src/opencv-utils/MouseWrapper.h"
#include "src/opencv-utils/TemplateImage.h"

enum QueueState {
	WAITING_FOR_POP,CHECKING_FOR_DODGE,STOP
};

class LeagueAccept
{
private: 
	const static int TICK_RATE = 1000;//1000mili=1sec
	const static int CHECK_FOR_DODGE_MINS = 5;
	const float IMAGE_THRESHOLD = 0.85f;//img cmp %
	
	int matchedTemplateWidth;
	int matchedTemplateHeight;
	std::thread workerThread;

	ImageComparator imageComparator;
	ScreenCapture* screenCapture;
	MouseWrapper mouse;
	std::vector<TemplateImage> templateImages;

	
	void tick();
	bool captureAndCompare();
	POINT calculateAcceptLocation();
public:
	LeagueAccept();
	~LeagueAccept();

	bool running;
	QueueState state;
	TemplateImage pop1024x576 = TemplateImage("res/1024x576_pop.png", cv::IMREAD_GRAYSCALE, 1024, 576);
	TemplateImage pop1280x720 = TemplateImage("res/1280x720_pop.png", cv::IMREAD_GRAYSCALE, 1280, 720);
	TemplateImage pop1600x900 = TemplateImage("res/1600x900_pop.png", cv::IMREAD_GRAYSCALE, 1600, 900);

	void captureAndDisplay();
	void run();
	void start();
	int stop();
	void acceptMatch();
};

