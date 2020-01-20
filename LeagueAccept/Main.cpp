#include <opencv2/opencv.hpp>
#include <iostream>

bool exists_test3(const std::string& name);

int main(int argc, char** argv)
{
	std::string imageName = "C:\\Users\\Bruno\\source\\repos\\LeagueAccept\\LeagueAccept\\opencv.jpg";

	if (argc > 1)
	{
		imageName = argv[1];
	}

	cv::Mat image;

	image = cv::imread("opencv.jpg");

	if (!image.empty()) {
		cv::namedWindow("Window Here", cv::WINDOW_AUTOSIZE);
		cv::imshow("Window Here", image);
		cv::waitKey(0);
		return 0;
	}
	else {
		std::cout << "NOP" << std::endl;
		cv::waitKey(5000);
		return -1;
	}
}

bool exists_test3(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}