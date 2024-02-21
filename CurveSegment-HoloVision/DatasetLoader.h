#pragma once
#include <opencv2/core.hpp>
#include <vector>
#include <string>


class DatasetLoader
{
public:
	//datasetPath should point to a folder containing image folders.
	//Each image folder should contain the images related to a single video.
	DatasetLoader(std::string datasetPath);
	std::vector<std::string> listDirectories(const std::string& s);
private:

private:
	std::vector<cv::Mat> videos;
	const std::string datasetPath;
};