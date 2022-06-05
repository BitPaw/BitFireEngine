#include "TIFF.h"

#include <File/File.h>

#define GIFFormatA {'I','I'}
#define GIFFormatB {'M','M'}

BF::TIFF::TIFF()
{

}

BF::FileActionResult BF::TIFF::Load(const char* filePath)
{
    File file;

    {
        const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
        const bool sucessful = fileLoadingResult == FileActionResult::Successful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }

    {
        const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

        return fileParsingResult;
    }
}

BF::FileActionResult BF::TIFF::Load(const wchar_t* filePath)
{
    File file;

    {
        const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
        const bool sucessful = fileLoadingResult == FileActionResult::Successful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }

    {
        const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

        return fileParsingResult;
    }    
}

BF::FileActionResult BF::TIFF::Load(const unsigned char* fileData, const size_t fileDataSize)
{
    ByteStream dataStream(fileData, fileDataSize);

    // Check Header
    {
        const char versionA[2] = GIFFormatA;
        const char versionB[2] = GIFFormatB;
        char headerTag[2] = { '#', '#' };

        dataStream.Read(headerTag, sizeof(headerTag));

        const bool useBigEndian = headerTag[0] == versionB[0] && headerTag[1] == versionB[1];
        const bool useLittleEndian = headerTag[0] == versionA[0] && headerTag[1] == versionA[1];
        const bool validVersion = useBigEndian != useLittleEndian;

        if(!validVersion)
        {
            return FileActionResult::InvalidVersion;
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::Save(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::ConvertTo(Image& image)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}