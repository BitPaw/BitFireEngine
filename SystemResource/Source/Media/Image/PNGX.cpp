#include "PNGX.h"
#include <Memory/Memory.h>
#include <File/File.h>

BF::PNGX::PNGX()
{
    PNGConstruct(this);
}

BF::PNGX::~PNGX()
{
    PNGDestruct(this);
}

ActionResult BF::PNGX::Load(const char* filePath)
{
    File file;

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&file, filePath, MemoryReadOnly);
        const bool sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }

    {
        const ActionResult fileParsingResult = Load(file.Data, file.DataSize);

        return fileParsingResult;
    }
}

ActionResult BF::PNGX::Load(const wchar_t* filePath)
{
    File file;

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, MemoryReadOnly);
        const bool sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }

    {
        const ActionResult fileParsingResult = Load(file.Data, file.DataSize);

        return fileParsingResult;
    }
}

ActionResult BF::PNGX::Load(const unsigned char* fileData, const size_t fileDataSize)
{
    size_t readBytes = 0;

    ActionResult actionResult = PNGParse(this, fileData, fileDataSize, &readBytes);

    return actionResult;
}

ActionResult BF::PNGX::Save(const wchar_t* filePath)
{
    return ActionResult();
}

ActionResult BF::PNGX::ConvertFrom(Image& image)
{
    return ActionResult();
}

ActionResult BF::PNGX::ConvertTo(Image& image)
{
    switch(ImageHeader.ColorType)
    {
        case PNGColorGrayscale:
            image.Format = ImageDataFormat::AlphaMask;
            break;

        case PNGColorTruecolor:
            image.Format = ImageDataFormat::RGB;
            break;

        case PNGColorInvalid:
        case PNGColorIndexedColor:
        case PNGColorGrayscaleWithAlphaChannel:
            image.Format = ImageDataFormat::Invalid;
            break;

        case PNGColorTruecolorWithAlphaChannel:
            image.Format = ImageDataFormat::RGBA;
            break;
    }


    image.Resize(ImageHeader.Width, ImageHeader.Height);

    MemoryCopy(PixelData, PixelDataSize, image.PixelData, image.PixelDataSize);

    return ResultSuccessful;
}