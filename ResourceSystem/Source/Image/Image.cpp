#include "Image.h"
#include "../File/File.h"
#include "BMP/BMP.h"
#include "PNG/PNG.h"
#include "TGA/TGA.h"
#include <malloc.h>

BF::Vector4<unsigned char> BF::Image::GetPixel(unsigned int x, unsigned int y)
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

BF::Image::Image()
{
    Width = 0;
    Height = 0;

    Type = ImageType::Texture2D;

    Format = ImageFormat::RGB;
    Filter = ImageFilter::NoFilter;

    LayoutNear = ImageLayout::Linear;
    LayoutFar = ImageLayout::Nearest;

    WrapHeight = ImageWrap::Repeat;
    WrapWidth = ImageWrap::Repeat;
}

void BF::Image::RemoveColor(unsigned char red, unsigned char green, unsigned char blue)
{
    switch (Format)
    {
        case ImageFormat::BlackAndWhite:
        {
            break;
        }

        case ImageFormat::RGB:
        {
            FormatChange(ImageFormat::RGBA);

            // no break;
        }
        case ImageFormat::RGBA:
        {
            for (size_t i = 0; i < PixelDataSize; )
            {
                unsigned char cred = PixelData[i++];
                unsigned char cgreen = PixelData[i++];
                unsigned char cblue = PixelData[i++];
                unsigned char& calpha = PixelData[i++];

                if (cred == red && cgreen == green && cblue == blue)
                {
                    calpha = 0u;
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void BF::Image::FlipHorizontal()
{
    unsigned int height = Height;
    unsigned int width = Width;
    unsigned int bytesPerPixel = 3;
    unsigned int scanLineWidthSize = width * bytesPerPixel;
    unsigned int scanLinesToSwap = height / 2;
    unsigned char copyBufferRow[2048];

    for (unsigned int scanlineIndex = 0; scanlineIndex < scanLinesToSwap; scanlineIndex++)
    {
        unsigned char* bufferA = PixelData + (scanlineIndex * scanLineWidthSize);
        unsigned char* bufferB = PixelData + ((height - scanlineIndex) * scanLineWidthSize) - scanLineWidthSize;

        memcpy(copyBufferRow, bufferB, scanLineWidthSize); // A -> Buffer 'Save A'
        memcpy(bufferB, bufferA, scanLineWidthSize); // B -> A 'Move B to A(override)'
        memcpy(bufferA, copyBufferRow, scanLineWidthSize); // Buffer -> B 'Move SaveCopy (A) to B'
    }
}

void BF::Image::PrintData()
{
    printf
    (
        "+------------------------------+\n"
        "| Registered image ID:%u\n"
        "| - Width  : %i\n"
        "| - Height : %i\n"
        "| - Size   : %i\n"
        "+------------------------------+\n",

        ID,
        Width,
        Height,
        Width * Height * 4
    );
}

void BF::Image::Resize(unsigned int width, unsigned height)
{
    unsigned int newArraySize = width * height;
    unsigned int pixelSize;

    Width = width;
    Height = height;

    switch (Format)
    {
        case ImageFormat::BlackAndWhite:
            pixelSize = 2;
            break;

        default:
        case ImageFormat::RGB:
            pixelSize = 3;
            break;
        case ImageFormat::RGBA:
            pixelSize = 4;
            break;
    }

    PixelData = (unsigned char*)realloc(PixelData,newArraySize * pixelSize);
}

void BF::Image::FillRandome()
{
    for (size_t i = 0; i < PixelDataSize; i++)
    {
        PixelData[i] = Math::RandomeNumber() % 255;
    }
}

void BF::Image::FormatChange(ImageFormat imageFormat)
{
    switch (Format)
    {
        case ImageFormat::BlackAndWhite:
        {

        }
        case ImageFormat::RGB:
        {
            switch (imageFormat)
            {
                case ImageFormat::BlackAndWhite:
                    break;
                case ImageFormat::RGB:
                    break;
                case ImageFormat::RGBA:
                {
                    unsigned int newIndex = 0;
                    unsigned int oldSize = PixelDataSize;
                    unsigned int newSize = (oldSize / 3) * 4;
                    unsigned char* newData = (unsigned char*)malloc(newSize * sizeof(char));
                    unsigned char* oldData = PixelData;

                    memset(newData, 0xFF, newSize);

                    for (unsigned int oldIndex = 0; oldIndex < oldSize; oldIndex += 3)
                    {
                        unsigned char* source = &oldData[oldIndex];
                        unsigned char* destination = &newData[newIndex];

                        memcpy(destination, source, 3);

                        newIndex += 4;
                    }

                    Format = ImageFormat::RGBA;
                    PixelData = newData;
                    PixelDataSize = newSize;

                    free(oldData);

                    break;
                }                 
            }
        }
        case ImageFormat::RGBA:
        {

        }
    }
}

BF::ImageFileExtension BF::Image::CheckFileExtension(AsciiString& fileExtension)
{
    bool isBMP = fileExtension.CompareIgnoreCase("bmp");
    bool isGIF = fileExtension.CompareIgnoreCase("gif");
    bool isJPEG = fileExtension.CompareIgnoreCase("jpeg");
    bool isPNG = fileExtension.CompareIgnoreCase("png");
    bool isTGA = fileExtension.CompareIgnoreCase("tga");
    bool isTIFF = fileExtension.CompareIgnoreCase("tiff");

    if (isBMP) return ImageFileExtension::BMP;
    if (isGIF) return ImageFileExtension::GIF;
    if (isJPEG) return ImageFileExtension::JPEG;
    if (isPNG) return ImageFileExtension::PNG;
    if (isTGA) return ImageFileExtension::TGA;
    if (isTIFF) return ImageFileExtension::TIFF;

    return ImageFileExtension::Unkown;
}

BF::ErrorCode BF::Image::Load(const char* filePath)
{
    File file(filePath);
    AsciiString fileExtension(file.Extension);
    ImageFileExtension imageFormat = CheckFileExtension(fileExtension);

    FilePathSet(file.Path);

    if (!file.DoesFileExist())
    {
        return ErrorCode::FileNotFound;
    }

    switch (imageFormat)
    {
        case ImageFileExtension::BMP:
        {
            BMP bitmap;
            bitmap.Load(filePath);
            bitmap.Convert(*this);
            break;
        }
        case ImageFileExtension::GIF:
        {
            break;
        }
        case ImageFileExtension::JPEG:
        {
            break;
        }
        case ImageFileExtension::PNG:
        {
            PNG png;
            png.Load(filePath);
            png.Convert(*this);
            break;
        }
        case ImageFileExtension::TGA:
        {
            TGA tga;
            tga.Load(filePath);
            tga.Convert(*this);
            break;
        }
        case ImageFileExtension::TIFF:
        {
            break;
        }

        case ImageFileExtension::Unkown:
        default:
            return ErrorCode::NotSupported;
    }

    return ErrorCode::NoError;
}
