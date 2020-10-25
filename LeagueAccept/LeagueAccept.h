#include <chrono>
#include <vector>
#include <thread>
#include <opencv2/highgui/highgui.hpp>
#include "src/opencv-utils/ImageComparator.h"
#include "src/opencv-utils/ScreenCapture.h"
#include "src/opencv-utils/MouseWrapper.h"

enum QueueState {
	WAITING_FOR_POP,STOP
};

class LeagueAccept
{
	private: 	
		ImageComparator imageComparator;
		ScreenCapture* screenCapture;
		MouseWrapper mouse;
		std::vector<cv::Mat> templateImages;
		bool hasQueuePopped;

		bool captureAndCompare();
		POINT calculateAcceptLocation();

	public:
		const static int TICK_RATE = 2000;//1000mili=1sec
		const float IMAGE_THRESHOLD = 0.85f;//img cmp %
		LeagueAccept();
		~LeagueAccept();
		bool running;
		QueueState state;
		std::thread* logicThread;

		void runLogic();
		void run();
		void acceptMatch();
		int stop();
};