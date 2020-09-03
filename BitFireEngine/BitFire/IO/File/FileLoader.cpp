#include "FileLoader.h"

std::string FileLoader::ReadCompleteFile(std::string filePath)
{
    std::ifstream file(filePath);
    std::string fileContent;

    bool isOpen = file.good();

    if (isOpen)
    {
        std::stringstream buffer;
        buffer << file.rdbuf();

        fileContent = buffer.str();    

        file.close();
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

TextFile FileLoader::ReadTextFile(std::string filePath)
{
    std::string content = ReadCompleteFile(filePath);

    TextFile textFile(filePath, content);

    return textFile;
}

std::vector<unsigned char> FileLoader::ReadFileAsBytes(std::string filePath)
{
    char* rawDataSigned;
    unsigned char* rawData;
    std::vector<unsigned char> finalData;

    std::ifstream ifs(filePath, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type size = ifs.tellg();

    rawDataSigned = new char[size];
    rawData = new unsigned char[size];
    finalData.reserve(size);

    ifs.seekg(0, std::ios::beg);
    ifs.read(rawDataSigned, size);
    
    rawData = reinterpret_cast<unsigned char*>(rawDataSigned);

    for (unsigned int i = 0; i < size; i++)
    {
        finalData.push_back(rawData[i]);
    }

    //delete[] rawDataSigned;
    delete[] rawData;

    return finalData;



    /*
    std::vector<unsigned char> bytes;
    std::ifstream infile(filePath);

    //get length of file
    infile.seekg(0, infile.end);
    unsigned int length = infile.tellg();
    infile.seekg(0, infile.beg);

    //read file
    if (length > 0) 
    {
        char* message = new char[length];

        bytes.reserve(length);
        infile.read(message, length);

        for (unsigned int i = 0; i < length; i++)
        {
            unsigned char x = reinterpret_cast<unsigned char>(message[i]);

            bytes.push_back(x);

           // printf("%x ", x);
        }

        delete[] message;
    }   
    */
}
