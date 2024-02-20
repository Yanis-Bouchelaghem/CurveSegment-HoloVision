#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "settings.h"

int main()
{
	//Create a matrix
	cv::Mat image(settings::imageHeight, settings::imageWidth, CV_8UC3); //BGR image with 3 channels of uchar
	cv::imshow("image", image);
	cv::waitKey();
	return 0;
}