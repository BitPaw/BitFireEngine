#include "FileLoader.h"

std::string BF::FileLoader::ReadCompleteFile(const std::string filePath)
{
    if (filePath.empty())
    {
        throw EmptyFileName();
    }

    if (!DoesFileExist(filePath))
    {
        throw FileNotFound(filePath);
    }

    std::ifstream file(filePath);
    std::string fileContent;

    std::stringstream buffer;
    buffer << file.rdbuf();

    fileContent = buffer.str();

    file.close();

    return fileContent;
}

BF::List<std::string> BF::FileLoader::ReadFileByLines(const std::string filePath)
{
    if (filePath.empty())
    {
        throw EmptyFileName();
    }

    if (!DoesFileExist(filePath))
    {
        throw FileNotFound(filePath);
    }
  
    BF::List<std::string> lines;
    std::ifstream infile(filePath);
    std::string currentLine; 

    while (std::getline(infile, currentLine))
    {
        lines.Size.Value++;
    }

    lines.ReSize();

    infile.clear();
    infile.seekg(0, std::ios_base::beg);

    while (std::getline(infile, currentLine))
    {
        lines[lines.CurrentIndex++] = currentLine;
    }

    infile.close();

    return lines;
}

BF::TextFile BF::FileLoader::ReadTextFile(const std::string filePath)
{
    return ReadTextFile(filePath, false);
}

BF::TextFile BF::FileLoader::ReadTextFile(const std::string filePath, const bool splittLines)
{
    bool isEmpty = filePath.empty() || filePath == "";

    if (isEmpty)
    {
        throw EmptyFileName();
    }

    if (!DoesFileExist(filePath))
    {
        throw FileNotFound(filePath);        
    }

    TextFile textFile(filePath);    

    if (splittLines)
    {
        BF::List<std::string> lines = ReadFileByLines(filePath);
        textFile.Lines = lines;
    }
    else
    {
        textFile.Lines.ReSize(1);
        textFile.Lines[0] = ReadCompleteFile(filePath);
    }

    return textFile;
}

BF::List<unsigned char> BF::FileLoader::ReadFileAsBytes(const std::string filePath)
{
    bool isEmpty = filePath.empty() || filePath == "";

    if (isEmpty)
    {
        throw EmptyFileName();
    }


    if (!DoesFileExist(filePath))
    {
        throw FileNotFound(filePath);
    }

    BF::List<unsigned char> byteList;
    std::ifstream inputFileStream(filePath, std::ios::binary | std::ios::ate);

    byteList.ReSize(inputFileStream.tellg());
    inputFileStream.seekg(0, inputFileStream.beg);

    inputFileStream.read((char*)(&byteList[0]), byteList.Size.Value);

    return byteList;
}

bool BF::FileLoader::DoesFileExist(std::string filePath)
{
    std::ifstream file(filePath.c_str());
    bool fileExists = file.good();

    file.close();

    return fileExists;
}

void BF::FileLoader::WriteFileAsBytes(const std::string filePath, const unsigned int size, const unsigned char* data)
{
    unsigned int byteLengh = size;
    std::ofstream fout;

    fout.open(filePath, std::ios::binary | std::ios::out);
    fout.write((char*)data, byteLengh);

    fout.close();
}
