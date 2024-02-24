#include "DatasetLoader.h"
#include <filesystem>
#include <limits>
#include <algorithm>
#include <assert.h>
#include "settings.h"
#include "utils.h"

DatasetLoader::DatasetLoader(Path datasetPath)
    :
    datasetPath(datasetPath)
{
    std::vector<std::vector<Path>> videosPaths;
    frameCountPerVideo = std::numeric_limits<int>::max();
    std::vector<Path> directoryPaths = ListDirectories(datasetPath);
    for (auto& directoryPath : directoryPaths)
    {
        std::vector<std::string> images = ListFramesInOrder(directoryPath);

        if (images.size() < frameCountPerVideo)
            frameCountPerVideo = images.size();
        videosPaths.emplace_back(images);
    }
    
    //Truncate the number of frames for each video to the global minimum
    for (auto& videoFramesPath : videosPaths)
    {
        videoFramesPath.resize(frameCountPerVideo);
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

int DatasetLoader::GetVideoCount() const
{
    return videos.size();
}

const std::vector<cv::Mat>& DatasetLoader::GetVideo(int index) const
{
    assert(index < GetVideoCount());//If assertion triggers: Index out of bounds
    assert(index >= 0);
    return videos[index];
}

int DatasetLoader::GetFrameCountPerVideo() const
{
    return frameCountPerVideo;
}

std::vector<std::string> DatasetLoader::ListDirectories(Path path) const
{
    std::vector<Path> directories;

    for (auto& element : std::filesystem::directory_iterator(path))
        if (element.is_directory())
            directories.push_back(element.path().string());

    return directories;
}

std::vector<std::string> DatasetLoader::ListFramesInOrder(Path path) const
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

