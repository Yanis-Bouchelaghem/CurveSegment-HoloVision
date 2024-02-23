#include "DatasetLoader.h"
#include <filesystem>
#include <limits>
#include <algorithm>
#include "settings.h"
#include "utils.h"
#include <iostream>

DatasetLoader::DatasetLoader(Path datasetPath)
    :
    datasetPath(datasetPath)
{
    std::vector<std::vector<Path>> videosPaths;
    int leastFrames = std::numeric_limits<int>::max();
    std::vector<Path> directoryPaths = listDirectories(datasetPath);
    for (auto& directoryPath : directoryPaths)
    {
        std::vector<std::string> images = listFramesInOrder(directoryPath);

        if (images.size() < leastFrames)
            leastFrames = images.size();
        videosPaths.emplace_back(images);
    }
    
    //Truncate the number of frames for each video to the global minimum
    for (auto& videoFramesPath : videosPaths)
    {
        videoFramesPath.resize(leastFrames);
    }

    for (auto& video : videosPaths)
    {
        std::vector<cv::Mat> frames;
        frames.reserve(video.size());
        for (const std::string& framePath : video)
        {
            cv::Mat frame = utils::LoadImage(framePath, cv::IMREAD_COLOR);
            frames.push_back(frame);
        }
        videos.push_back(frames);
    }



}

std::vector<std::string> DatasetLoader::listDirectories(Path path)
{
    std::vector<Path> directories;

    for (auto& element : std::filesystem::directory_iterator(path))
        if (element.is_directory())
            directories.push_back(element.path().string());

    return directories;
}

std::vector<std::string> DatasetLoader::listFramesInOrder(Path path)
{
    std::vector<std::string> images;
    for (auto& element : std::filesystem::directory_iterator(path))
    {
        if (element.is_regular_file() && element.path().extension() == ".jpg")
            images.push_back(element.path().string());
    }
    //Sort the images lexicographically
    std::sort(images.begin(), images.end());
    return images;
}

