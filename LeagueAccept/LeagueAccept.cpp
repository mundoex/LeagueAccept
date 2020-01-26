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
	bool result;
	for (size_t i = 0; i < this->templateImages.size(); i++) {
		result = this->imageComparator.contains(this->templateImages.at(i).image, screenshot, this->IMAGE_THRESHOLD);
		if (result) {
			this->matchedTemplateWidth = this->templateImages.at(i).clientWidth;
			this->matchedTemplateHeight = this->templateImages.at(i).clientHeight;
			return true;
		}
	}
	return false;
}

POINT LeagueAccept::calculateAcceptLocation()
{
	LONG acceptX = (this->imageComparator.matchLocation.x + this->matchedTemplateWidth) / 2;
	LONG acceptY = (this->imageComparator.matchLocation.x + this->matchedTemplateHeight) / 2;
	return POINT{ acceptX,acceptY };
}

LeagueAccept::LeagueAccept()
{
	this->running = false;
	this->state = QueueState::STOP;

	this->screenCapture = ScreenCapture();
	this->imageComparator = ImageComparator();
	this->mouse = MouseWrapper();

	this->templateImages = std::vector<TemplateImage>(3);
	templateImages.push_back(this->pop1024x576);
	templateImages.push_back(this->pop1280x720);
	templateImages.push_back(this->pop1600x900);
	
	this->matchedTemplateWidth = 0;
	this->matchedTemplateHeight = 0;
}

LeagueAccept::~LeagueAccept()
{
	this->screenCapture.~ScreenCapture();
	this->imageComparator.~ImageComparator();
	this->mouse.~MouseWrapper();

	this->workerThread.~thread();

	this->templateImages.~vector<TemplateImage>();
	this->pop1024x576.~TemplateImage();
	this->pop1280x720.~TemplateImage();
	this->pop1600x900.~TemplateImage();
}

void LeagueAccept::run()
{
	this->state = QueueState::WAITING_FOR_POP;
	this->running = true;
	this->workerThread = std::thread(this->start());
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