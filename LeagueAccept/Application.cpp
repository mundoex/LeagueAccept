#include <iostream>
#include <memory>
#include "LeagueAccept.h"

int main()
{
	LeagueAccept la = LeagueAccept();
	la.running = true;
	la.state = QueueState::WAITING_FOR_POP;
	la.start();
	//ScreenCapture sc = ScreenCapture();
	//sc.capture();
	//cv::imshow("GUI", sc.image);
	//cv::waitKey(1);
	
}