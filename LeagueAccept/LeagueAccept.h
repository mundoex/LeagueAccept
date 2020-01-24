#pragma once
#include <thread>
#include <chrono>
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

	bool running;
	QueueState state;
	int matchedTemplateWidth;
	int matchedTemplateHeight;
	std::thread workerThread;

	ImageComparator imageComparator;
	ScreenCapture screenCapture;
	MouseWrapper mouse;
	std::array<TemplateImage,3> templateImages;

	int start();
	void tick();
	bool captureAndCompare();
	POINT calculateAcceptLocation(int width,int height);
public:
	LeagueAccept();
	~LeagueAccept();
	void run();
	int stop();
	void acceptMatch();
};

