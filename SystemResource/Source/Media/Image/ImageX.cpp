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
        ((unsigned char*)PixelData)[pos++],
        ((unsigned char*)PixelData)[pos++],
        ((unsigned char*)PixelData)[pos++],
        ((unsigned char*)PixelData)[pos++]
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
    ImageResize(this, ImageDataFormatRGB,width, height);
}

void BF::ImageX::FillRandome()
{
    for (size_t i = 0; i < PixelDataSize; i++)
    {
        ((unsigned char*)PixelData)[i] = MathRandomeNumber() % 255;
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