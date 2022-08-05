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
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&file, filePath, 0, MemoryReadOnly);
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
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, 0, MemoryReadOnly);
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
    ImageDataFormat format;

    switch(ImageHeader.ColorType)
    {
        case PNGColorGrayscale:
            format = ImageDataFormatAlphaMask;
            break;

        case PNGColorTruecolor:
            format = ImageDataFormatRGB;
            break;

        case PNGColorInvalid:
        case PNGColorIndexedColor:
        case PNGColorGrayscaleWithAlphaChannel:
            format = ImageDataFormatInvalid;
            break;

        case PNGColorTruecolorWithAlphaChannel:
            format = ImageDataFormatRGBA;
            break;
    }


    ImageResize(&image, format, ImageHeader.Width, ImageHeader.Height);

    MemoryCopy(PixelData, PixelDataSize, image.PixelData, image.PixelDataSize);

    return ResultSuccessful;
}