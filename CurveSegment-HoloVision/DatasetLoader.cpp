#include "DatasetLoader.h"
#include <filesystem>
#include <limits>
#include <algorithm>
#include "settings.h"
#include "utils.h"

DatasetLoader::DatasetLoader(Path datasetPath)
    :
    datasetPath(datasetPath)
{
    std::vector<std::vector<Path>> videosPaths;
    int leastFrames = std::numeric_limits<int>::max();
    std::vector<Path> videoPaths = listDirectories(datasetPath);
    for (auto& directoryPath : videoPaths)
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
        //Load the frames into a cube cv::Mat
        int sizes[] = {settings::imageHeight,settings::imageWidth, leastFrames};
        cv::Mat videoCube(3, sizes, CV_8UC3, cv::Scalar(0));
        //Read frame by frame and fill the 3D matrix
        for (int frameIndex = 0; frameIndex < leastFrames; ++frameIndex)
        {
            cv::Mat frame = utils::LoadImage(video[frameIndex], cv::IMREAD_COLOR);
            for (int x = 0; x < frame.cols; ++x)
            {
                for (int y = 0; y < frame.rows; ++y)
                {
                    videoCube.at<cv::Vec3b>(y,x,frameIndex) = frame.at<cv::Vec3b>(y,x);
                }
            }
        }
        videos.push_back(videoCube);
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

