#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "settings.h"
#include "RandomWalk.h"
#include "DatasetLoader.h"

int main()
{
	DatasetLoader datasetLoader{"dataset\\images\\origins\\passport"};
	//Create a matrix
	cv::Mat image(settings::imageHeight, settings::imageWidth, CV_8UC3); //BGR image with 3 channels of uchar
	RandomWalk randomWalk(settings::imageHeight, settings::imageWidth);
	auto curveSegment = randomWalk.GenerateCurveSegment(254);
	for (const auto& position : curveSegment)
	{
		image.at<cv::Vec3b>(position.y, position.x) = cv::Vec3b{0,0,0};
	}
	cv::imshow("image", image);
	cv::waitKey();
	return 0;
}