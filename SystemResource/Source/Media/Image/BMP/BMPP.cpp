#include "BMPP.h"

#include <cassert>

#include <File/File.h>
#include <Math/Math.h>

#include <Memory/MemoryX.h>

BF::BMPP::BMPP()
{
    BMPConstruct(this);
}

BF::BMPP::~BMPP()
{
    BMPDestruct(this);
}

ActionResult BF::BMPP::Load(const char* filePath)
{
    File file;

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&file, filePath, MemoryReadOnly);
        const bool sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return ResultInvalid;
        }
    }

    {
        const ActionResult fileParsingResult = Load(file.Data, file.DataSize);

        return fileParsingResult;
    }
}

ActionResult BF::BMPP::Load(const wchar_t* filePath)
{
    File file;

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, MemoryReadOnly);
        const bool sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return ResultInvalid;
        }
    }

    {
        const ActionResult fileParsingResult = Load(file.Data, file.DataSize);

        return fileParsingResult;
    }
}

ActionResult BF::BMPP::Load(const unsigned char* fileData, const size_t fileDataSize)
{
    size_t bytes = 0;
    ActionResult qctionResult = BMPParse(this, fileData, fileDataSize, &bytes);

    return ResultSuccessful;
}

ActionResult BF::BMPP::Save(const wchar_t* filePath)
{
    /*
    File file;

    // Open file
    {
        const ActionResult openResult = file.Open(filePath, FileOpenMode::Write);
        const bool sucessful = openResult == ResultSuccessful;

        if(!sucessful)
        {
            return openResult;
        }
    }

    // Write header
    {
        unsigned int fileSize = InfoHeader.Width * InfoHeader.Height * 3 + 54u;

        file.Write("BM", 2u);
        file.Write(fileSize, EndianLittle);
        file.Write(0u, EndianLittle);
        file.Write(54u, EndianLittle);
    }

    //------<Windows-Header>-----------
    file.Write(InfoHeader.HeaderSize, EndianLittle);
    file.Write(InfoHeader.Width, EndianLittle);
    file.Write(InfoHeader.Height, EndianLittle);
    file.Write(InfoHeader.NumberOfColorPlanes, EndianLittle);
    file.Write(InfoHeader.NumberOfBitsPerPixel, EndianLittle);
    file.Write(InfoHeader.CompressionMethod, EndianLittle);
    file.Write(InfoHeader.ImageSize, EndianLittle);
    file.Write(InfoHeader.HorizontalResolution, EndianLittle);
    file.Write(InfoHeader.VerticalResolution, EndianLittle);
    file.Write(InfoHeader.NumberOfColorsInTheColorPalette, EndianLittle);
    file.Write(InfoHeader.NumberOfImportantColorsUsed, EndianLittle);

    file.Write(PixelData, PixelDataSize);

    // Close file
    {
        const ActionResult closeResult = file.Close();
        const bool sucessful = closeResult == ResultSuccessful;

        if(!sucessful)
        {
            return closeResult;
        }
    }*/

    return ResultSuccessful;
}

ActionResult BF::BMPP::ConvertFrom(Image& image)
{
   PixelData = Memory::Allocate<unsigned char>(image.PixelDataSize);

    if (!PixelData)
    {
        return ResultOutOfMemory;
    }

    PixelDataSize = image.PixelDataSize;

    InfoHeader.Width = image.Width;
    InfoHeader.Height = image.Height;
    InfoHeader.ImageSize = PixelDataSize;

    MemoryCopy(PixelData, PixelDataSize, image.PixelData, image.PixelDataSize);

    return ResultSuccessful;
}

ActionResult BF::BMPP::ConvertTo(Image& image)
{
    unsigned char* pixelData = Memory::Allocate<unsigned char>(PixelDataSize);

    if(!pixelData)
    {
        return ResultOutOfMemory;
    }

    image.Format = ImageDataFormatBGR;
    image.Height = InfoHeader.Height;
    image.Width = InfoHeader.Width;
    image.PixelDataSize = PixelDataSize;
    image.PixelData = pixelData;

    MemoryCopy(PixelData, PixelDataSize, image.PixelData, image.PixelDataSize);

    //image.FlipHorizontal(); ??

    //image.RemoveColor(0,0,0);

    return ResultSuccessful;
}

ActionResult BF::BMPP::ConvertTo(Image& image, BMP& alphaMap)
{
    size_t pixelDataSize = (PixelDataSize / 3) * 4;
    unsigned char* pixelData = Memory::Allocate<unsigned char>(pixelDataSize);

    if(!pixelData)
    {
        return ResultOutOfMemory;
    }

    image.Format = ImageDataFormatBGRA;
    image.Height = InfoHeader.Height;
    image.Width = InfoHeader.Width;
    image.PixelDataSize = pixelDataSize;
    image.PixelData = pixelData;

    size_t imageDataIndex = 0;
    size_t alphaDataIndex = 0;

    for(size_t i = 0; i < pixelDataSize; )
    {
        unsigned char blue = PixelData[imageDataIndex++];
        unsigned char green = PixelData[imageDataIndex++];
        unsigned char red = PixelData[imageDataIndex++];
        unsigned char alpha = alphaMap.PixelData[alphaDataIndex++];
        bool isTansparanetColor = blue == 0xFF && green == 0xFF && red == 0xFF;

        pixelData[i++] = blue;
        pixelData[i++] = green;
        pixelData[i++] = red;
        pixelData[i++] = isTansparanetColor ? 0x00 : 0xFF;
    }

    ImageFlipHorizontal(&image);

    return ResultSuccessful;
}