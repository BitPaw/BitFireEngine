#include "ImageX.h"

#include "BMP/BMPP.h"

#include <File/File.h>
#include <Math/Math.h>

#include <cstdlib>
#include <cstdio>
#include <cwchar>

#include <Text/Text.h>
#include <Memory/MemoryX.h>
#include <File/Format/JPEG/JPEG.h>
#include <File/Format/TIFF/TIFF.h>
#include <File/Format/PNG/PNG.h>
#include <File/Format/TGA/TGA.h>
#include <Media/Image/PNGX.h>

BF::Vector4<unsigned char> BF::ImageX::GetPixel(unsigned int x, unsigned int y)
{
    unsigned int pos = (x * Width + y) * 4;

    Vector4<unsigned char> pixel
    (
        PixelData[pos++],
        PixelData[pos++],
        PixelData[pos++],
        PixelData[pos++]
    );

    return pixel;
}

BF::ImageX::ImageX()
{
    ImageConstruct(this);
}

BF::ImageX::~ImageX()
{
    ImageDestruct(this);
}

void BF::ImageX::FlipHorizontal()
{
    ImageFlipHorizontal(this);
}

void BF::ImageX::FlipVertical()
{
    ImageFlipVertical(this);
}

void BF::ImageX::Resize(const size_t width, const size_t height)
{
    unsigned int pixelSize;

    Width = width;
    Height = height;

    switch (Format)
    {
        case ImageDataFormatAlphaMask:
            pixelSize = 2;
            break;

        default:
        case ImageDataFormatRGB:
            pixelSize = 3;
            break;
        case ImageDataFormatRGBA:
            pixelSize = 4;
            break;
    }

    PixelDataSize = width * height * pixelSize;
    PixelData = Memory::Reallocate<unsigned char>(PixelData, PixelDataSize);
}

void BF::ImageX::FillRandome()
{
    for (size_t i = 0; i < PixelDataSize; i++)
    {
        PixelData[i] = MathRandomeNumber() % 255;
    }
}

ActionResult BF::ImageX::Load(const char* filePath)
{
    return ImageLoadA(this, filePath);
}

ActionResult BF::ImageX::Load(const wchar_t* filePath)
{
    return ImageLoadW(this, filePath);
}

ActionResult BF::ImageX::Load(const unsigned char* fileData, const size_t fileDataSize, const ImageFileFormat imageFileFormat)
{
    return ImageLoadD(this, fileData, fileDataSize, imageFileFormat);
}