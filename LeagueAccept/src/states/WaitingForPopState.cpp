#include "WaitingForPopState.h"

WaitingForPopState::~WaitingForPopState()
{

}

void WaitingForPopState::Update(float deltaTime) {
	const bool result = this->CaptureAndCompare();
	if (result) {
		POINT point = this->CalculateAcceptPoint();
		this->stateMachine->Change(State::POP, &point);
	}
}
void WaitingForPopState::Render()
{
	ModifyMenu(this->hMenu, IDR_START, MF_BYCOMMAND | MF_STRING, IDR_STOP, "Stop");
}

bool WaitingForPopState::CaptureAndCompare()
{
	cv::Mat screenshot;
	this->screenCapture->capture();
	cv::cvtColor(this->screenCapture->image, screenshot, CV_BGR2GRAY);
	cv::waitKey(1);
	bool result;
	for (size_t i = 0; i < this->templateImages.size(); i++) {
		result = this->imageComparator.contains(this->templateImages.at(i), screenshot, this->IMAGE_THRESHOLD);
		cv::waitKey(1);
		if (result) {
			return true;
		}
	}
	return false;
}

POINT WaitingForPopState::CalculateAcceptPoint()
{
	LONG acceptX = this->imageComparator.matchLocationMax.x + this->imageComparator.center.x;
	LONG acceptY = this->imageComparator.matchLocationMax.y + this->imageComparator.center.y;
	return POINT{ acceptX, acceptY };
}