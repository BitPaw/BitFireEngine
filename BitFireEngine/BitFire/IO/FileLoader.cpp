#include "FileLoader.h"

std::string FileLoader::ReadCompleteFile(std::string filePath)
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

std::string* FileLoader::ReadFileByLines(std::string filePath, unsigned int* numberOfLines)
{
    std::ifstream infile(filePath);
    std::string currentLine;
    std::string* lines;
    unsigned int lineIndex = 0;

    while (std::getline(infile, currentLine))
    {
        (*numberOfLines)++;
    }

    infile.clear();
    infile.seekg(0, std::ios_base::beg);

    lines = new std::string[*numberOfLines];
    
    while (std::getline(infile, currentLine))
    {
        lines[lineIndex++] = currentLine;
    }

    infile.close();

    return lines;
}