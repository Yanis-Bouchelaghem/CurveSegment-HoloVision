#include "DatasetLoader.h"
#include <filesystem>

DatasetLoader::DatasetLoader(std::string datasetPath)
    :
    datasetPath(datasetPath)
{	
}

std::vector<std::string> DatasetLoader::listDirectories(const std::string& s)
{
    std::vector<std::string> directories;
    for (auto& element : std::filesystem::directory_iterator(s))
        if (element.is_directory())
            directories.push_back(element.path().string());
    return directories;
}
