#include "LeagueAccept.h"

void LeagueAccept::tick()
{
	Sleep(this->TICK_RATE);
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

LeagueAccept::LeagueAccept()
{
	this->running = false;
	this->state = QueueState::STOP;

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
	delete this->screenCapture;
	this->imageComparator.~ImageComparator();
	this->mouse.~MouseWrapper();

	//this->workerThread.~thread();
	this->templateImages[0].~Mat();
	this->templateImages[1].~Mat();
	this->templateImages[2].~Mat();
	this->templateImages.~vector<cv::Mat>();
}

void LeagueAccept::run()
{
	this->state = QueueState::WAITING_FOR_POP;
	this->running = true;
	//this->workerThread = std::thread(&LeagueAccept::start,this);
}

int LeagueAccept::stop()
{
	this->running = false;
	return 0;
}

void LeagueAccept::acceptMatch()
{
	this->mouse.moveTo(this->calculateAcceptLocation());
	this->mouse.click();
}

void LeagueAccept::start() {
	std::chrono::high_resolution_clock::time_point stopTimePoint;
	bool result;
	this->running = true;
	this->state = QueueState::WAITING_FOR_POP;
	while (this->running) {
		this->tick();
		switch (this->state)
		{
		case (QueueState::WAITING_FOR_POP):
			result = this->captureAndCompare();
			if (result) {
				state = QueueState::CHECKING_FOR_DODGE;
				stopTimePoint = std::chrono::high_resolution_clock::now() + std::chrono::minutes(this->CHECK_FOR_DODGE_MINS);
				this->acceptMatch();
			}
			break;

		case (QueueState::CHECKING_FOR_DODGE):			
			result = this->captureAndCompare();
			if (result) {
				this->acceptMatch();
			}
			if (std::chrono::high_resolution_clock::now() >= stopTimePoint) {
				this->state = QueueState::STOP;
			}
			break;

		case (QueueState::STOP):
			 this->stop();
		
		default:
			this->stop();
		}
	}
}