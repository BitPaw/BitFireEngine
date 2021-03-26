#include "FileLoader.h"

void BF::FileLoader::ReadCompleteFile(AsciiString& filePath, AsciiString& fileContent)
{
    if (filePath.Empty())
    {
        throw EmptyFileName();
    }

    if (!DoesFileExist(filePath))
    {
        throw FileNotFound(filePath);
    }
    
    std::ifstream file(&filePath[0]);
    std::stringstream buffer;
   
    buffer << file.rdbuf();

    fileContent.Copy(buffer.str().c_str());

    file.close();
}

void BF::FileLoader::ReadFileByLines(AsciiString& filePath, List<AsciiString>& stringList)
{
    if (filePath.Empty())
    {
        throw EmptyFileName();
    }

    if (!DoesFileExist(filePath))
    {
        throw FileNotFound(filePath);
    }
  
    std::ifstream infile(&filePath[0]);
    std::string currentLine; 
    unsigned int amountOfLines = 0;
    unsigned int dynamicIndex = 0;

    while (std::getline(infile, currentLine))
    {
        amountOfLines++;
    }

    stringList.ReSize(amountOfLines);

    infile.clear();
    infile.seekg(0, std::ios_base::beg);

    while (std::getline(infile, currentLine))
    {
        stringList[dynamicIndex++] = currentLine;
    }

    infile.close();
}

void BF::FileLoader::ReadTextFile(TextFile& textFile)
{
    return ReadTextFile(textFile, false);
}

void BF::FileLoader::ReadTextFile(TextFile& textFile, const bool splittLines)
{
    bool isEmpty = textFile.Path.Empty();

    if (isEmpty)
    {
        throw EmptyFileName();
    }

    if (!DoesFileExist(textFile.Path))
    {
        throw FileNotFound(textFile.Path);
    }

    if (splittLines)
    {
        ReadFileByLines(textFile.Path, textFile.Lines);
    }
    else
    {
        textFile.Lines.ReSize(1);
        ReadCompleteFile(textFile.Path, textFile.Lines[0]);
    }
}

void BF::FileLoader::GetFileExtension(AsciiString& fileName, AsciiString& extension)
{
    if (!fileName.Empty())
    {
        int position = fileName.FindLast('.');

        if (position != -1)
        {
            fileName.Cut(position + 1, extension);
        }
    }
}
void BF::FileLoader::ReadFileAsBytes(AsciiString& filePath, AsciiString& byteString)
{
    bool isEmpty = filePath.Empty();

    if (isEmpty)
    {
        throw EmptyFileName();
    }

    if (!DoesFileExist(filePath))
    {
        throw FileNotFound(filePath);
    }

    std::ifstream inputFileStream(&filePath[0], std::ios::binary | std::ios::ate);
    unsigned int length = inputFileStream.tellg();

    byteString.ReSize(length);

    char* stringAdress = &byteString[0];

    inputFileStream.seekg(0, inputFileStream.beg);
    inputFileStream.read(stringAdress, length);
}

bool BF::FileLoader::DoesFileExist(AsciiString& filePath)
{
    char* string = &filePath.operator[](0);
    std::ifstream file(string);
    bool fileExists = file.good();

    file.close();

    return fileExists;
}

void BF::FileLoader::WriteFileAsBytes(AsciiString& filePath, AsciiString& byteString)
{
    std::ofstream fout;

    fout.open(&filePath[0], std::ios::binary | std::ios::out);
    fout.write((char*)(&byteString[0]),(std::streamsize)byteString.Size());

    fout.close();
}
