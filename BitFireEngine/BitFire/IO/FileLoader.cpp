#include "FileLoader.h"

std::string FileLoader::ReadFile(std::string filePath)
{
    std::ifstream file;
    std::string fileContent;
    file.open(filePath);

    file.seekg(0, std::ios::end);
    fileContent.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    fileContent.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return fileContent;
}
