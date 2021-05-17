#pragma once
#include "BaseState.h"
#include "../opencv-utils/ImageComparator.h"
#include "../opencv-utils/ScreenCapture.h"
#include <opencv2/highgui/highgui.hpp>

class WaitingForPopState : public BaseState
{
private:
	std::vector<cv::Mat> templateImages;
	ImageComparator imageComparator;
	ScreenCapture* screenCapture;	//Must be Heap alocated or no worki, someone tell me why please

	bool CaptureAndCompare();
	POINT CalculateAcceptPoint();
	
public:
	const float IMAGE_THRESHOLD = 0.85f;

	WaitingForPopState(StateMachine* stateMachine, HMENU hMenu) : BaseState(stateMachine, hMenu) 
	{
		this->templateImages = std::vector<cv::Mat>(3);
		this->templateImages[0] = cv::imread("res/1024x576_pop.png", cv::IMREAD_GRAYSCALE);
		this->templateImages[1] = cv::imread("res/1280x720_pop.png", cv::IMREAD_GRAYSCALE);
		this->templateImages[2] = cv::imread("res/1600x900_pop.png", cv::IMREAD_GRAYSCALE);
		this->imageComparator = ImageComparator();
		this->screenCapture = new ScreenCapture();
	};
	~WaitingForPopState();
	void Update(float deltaTime) override;
	void Render() override;
};