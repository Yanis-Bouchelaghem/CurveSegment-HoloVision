#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "settings.h"
#include "RandomWalk.h"
#include "DatasetLoader.h"

int main()
{
	DatasetLoader datasetLoader{settings::datasetPath};
	const std::vector<cv::Mat>& video = datasetLoader.GetVideo(0);
	RandomWalk randomWalk(settings::imageHeight, settings::imageWidth);
	auto curveSegment = randomWalk.GenerateCurveSegment(settings::curveSegmentLength);
	cv::Mat curveSegmentResult(curveSegment.size(), datasetLoader.GetFrameCountPerVideo(), CV_8UC3);

	for (int i = 0; i < curveSegment.size(); ++i)
	{
		Vec2 position = curveSegment[i];
		for (int frameIndex = 0; frameIndex < video.size(); ++frameIndex)
		{
			curveSegmentResult.at<cv::Vec3b>(i, frameIndex) = video[frameIndex].at<cv::Vec3b>(position.y, position.x);
		}

	}
	cv::imshow("image", curveSegmentResult);
	cv::imwrite("output.jpg", curveSegmentResult);
	cv::waitKey();
	return 0;
}