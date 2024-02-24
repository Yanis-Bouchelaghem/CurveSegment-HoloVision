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
	int GetVideoCount() const;
	const std::vector<cv::Mat>& GetVideo(int index) const;
	int GetFrameCountPerVideo() const;
private:
	std::vector<Path> ListDirectories(Path path) const;
	std::vector<Path> ListFramesInOrder(Path path) const;
private:
	std::vector<std::vector<cv::Mat>> videos;
	const std::string datasetPath;
	int frameCountPerVideo;
};