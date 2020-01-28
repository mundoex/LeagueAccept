#include "LeagueAccept.h"

void LeagueAccept::tick()
{
	std::cout << "Tick" << std::endl;
	Sleep(this->TICK_RATE);
}

void LeagueAccept::captureAndDisplay() {
	cv::Mat screenshot;
	this->screenCapture->capture();

	cv::cvtColor(this->screenCapture->image, screenshot, CV_BGR2GRAY);
	cv::imshow("QWE", screenshot);

	cv::waitKey(1);
}

bool LeagueAccept::captureAndCompare()
{
	cv::Mat screenshot;
	this->screenCapture->capture();
	cv::cvtColor(this->screenCapture->image, screenshot, CV_BGR2GRAY);
	cv::waitKey(1);
	bool result;
	for (size_t i = 0; i < this->templateImages.size(); i++) {
		//cv::imshow("Window", this->templateImages.at(i).image);
		//cv::waitKey(this->TICK_RATE);
		result = this->imageComparator.contains(this->templateImages.at(i).image, screenshot, this->IMAGE_THRESHOLD);
		cv::waitKey(1);
		std::cout << "Result: "<< result << std::endl;
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
	//1920 1080 this->mouse.screenWidth this->mouse.screenHeight
	LONG acceptX = this->imageComparator.matchLocation.x+ (1920 / 2);
	LONG acceptY = this->imageComparator.matchLocation.y+(1080 / 2);
	std::cout << "Width:" << acceptX << "Height:" << acceptY << std::endl;
	return POINT{ acceptX,acceptY };
}

LeagueAccept::LeagueAccept()
{
	this->running = false;
	this->state = QueueState::STOP;

	this->screenCapture = new ScreenCapture();
	this->imageComparator = ImageComparator();
	this->mouse = MouseWrapper();

	this->templateImages = std::vector<TemplateImage>(3);
	this->templateImages[0] = this->pop1024x576;
	this->templateImages[1] = this->pop1280x720;
	this->templateImages[2] = this->pop1600x900;
	
	this->matchedTemplateWidth = 0;
	this->matchedTemplateHeight = 0;
}

LeagueAccept::~LeagueAccept()
{
	delete this->screenCapture;
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
	this->workerThread = std::thread(&LeagueAccept::start,this);
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