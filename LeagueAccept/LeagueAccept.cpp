#include "LeagueAccept.h"

LeagueAccept::LeagueAccept()
{
	running = false;
	state = QueueState::STOP;

	this->screenCapture = new ScreenCapture();
	this->imageComparator = ImageComparator();
	this->mouse = MouseWrapper();

	this->templateImages = std::vector<cv::Mat>(3);
	this->templateImages[0] = cv::imread("res/1024x576_pop.png", cv::IMREAD_GRAYSCALE);
	this->templateImages[1] = cv::imread("res/1280x720_pop.png", cv::IMREAD_GRAYSCALE);
	this->templateImages[2] = cv::imread("res/1600x900_pop.png", cv::IMREAD_GRAYSCALE);
}

LeagueAccept::~LeagueAccept()
{
	//this->screenCapture->~ScreenCapture();
	//this->imageComparator.~ImageComparator();

	//this->templateImages[0].~Mat();
	//this->templateImages[1].~Mat();
	//this->templateImages[2].~Mat();
	//this->templateImages.~vector<cv::Mat>();
}

bool LeagueAccept::captureAndCompare()
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

POINT LeagueAccept::calculateAcceptLocation()
{
	LONG acceptX = this->imageComparator.matchLocationMax.x + this->imageComparator.center.x;
	LONG acceptY = this->imageComparator.matchLocationMax.y + this->imageComparator.center.y;
	return POINT{ acceptX,acceptY };
}

void LeagueAccept::run()
{
	state= QueueState::WAITING_FOR_POP;
	running = true;
}

int LeagueAccept::stop()
{
	state = QueueState::STOP;
	running = false;
	return 0;
}

void LeagueAccept::acceptMatch()
{
	this->mouse.moveTo(this->calculateAcceptLocation());
	this->mouse.click();
}

void LeagueAccept::runLogic() {
	switch (state) {
	case (QueueState::WAITING_FOR_POP):
		hasQueuePopped = this->captureAndCompare();
		if (hasQueuePopped) {
			this->acceptMatch();
			hasQueuePopped = false;	
		}
		break;

	case (QueueState::STOP): stop(); break;
	default: stop(); break;
	}
}