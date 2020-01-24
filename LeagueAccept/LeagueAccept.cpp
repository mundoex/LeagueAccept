#include "LeagueAccept.h"

void LeagueAccept::tick()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(this->TICK_RATE));
}

bool LeagueAccept::captureAndCompare()
{
	cv::Mat screenshot;
	this->screenCapture.capture();
	cv::cvtColor(this->screenCapture.image, screenshot, CV_BGR2GRAY);
	int result;
	for (int i = 0; i < this->templateImages.size; i++) {
		result+=this->imageComparator.contains(this->templateImages[i], screenshot, this->IMAGE_THRESHOLD);
	}
	return result > 0;
	
}

POINT LeagueAccept::calculateAcceptLocation(int width,int height)
{
	float acceptX = (this->imageComparator.matchLocation.x + width) / 2;
	float acceptY = (this->imageComparator.matchLocation.x + height) / 2;
	return POINT{ acceptX,acceptY };
}

LeagueAccept::LeagueAccept()
{
	this->running = false;
	this->state = QueueState::STOP;
	this->screenCapture = ScreenCapture();
	this->imageComparator = ImageComparator();
	this->mouse = MouseWrapper();
	
	//fix array
	this->templateImages.at(0)= TemplateImage("", cv::IMREAD_GRAYSCALE, 1920, 1080);


	this->matchedTemplateWidth = 0;
	this->matchedTemplateHeight = 0;
}

LeagueAccept::~LeagueAccept()
{
	this->screenCapture.~ScreenCapture();
	this->imageComparator.~ImageComparator();
	this->mouse.~MouseWrapper();
}

void LeagueAccept::run()
{
	this->state = QueueState::WAITING_FOR_POP;
	this->running = true;
	this->workerThread = std::thread(this->start);
}

int LeagueAccept::stop()
{
	this->running = false;
	return 0;
}

void LeagueAccept::acceptMatch()
{
	this->mouse.moveTo(this->calculateAcceptLocation(1920, 1080));
	this->mouse.click();
}

int LeagueAccept::start() {
	std::chrono::high_resolution_clock::time_point stopTimePoint;
	bool result;
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
			return this->stop();
		
		default:
			return this->stop();
		}
	}
}