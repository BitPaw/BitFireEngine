#include "FileLoader.h"

std::string FileLoader::ReadCompleteFile(std::string filePath)
{
    std::ifstream file(filePath);
    std::string fileContent; 

    bool isOpen = file.good();

    if (isOpen)
    {
        //char* fileContentBuffer;
        std::stringstream buffer;
        buffer << file.rdbuf();

        /*
        file.seekg(0, std::ios::end);
        int size = file.tellg();

        printf("Size of File : %i\n", size);

        file.seekg(0, std::ios::beg);

        fileContent = new char[size];

        file.read(fileContent, size);    

        */
       

        fileContent = buffer.str();
        file.close();

        printf("-----------------------------------------\n");
        printf("%s\n", fileContent.c_str());
        printf("-----------------------------------------\n");



        //std::string news(fileContent);

        //delete[] fileContent;
    }
    else
    {
        throw std::exception("File could not be loaded");
    }

 

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