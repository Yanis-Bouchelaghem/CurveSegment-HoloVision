#pragma once
#include <opencv2/core.hpp>
#include <vector>
#include <string>

typedef std::string Path;

class DatasetLoader
{
public:
	//datasetPath should point to a folder containing image folders.
	//Each image folder should contain the images related to a single video.
	DatasetLoader(Path datasetPath);
private:
	std::vector<Path> listDirectories(Path path);
	std::vector<Path> listFramesInOrder(Path path);
private:
	std::vector<cv::Mat> videos;
	const std::string datasetPath;
};