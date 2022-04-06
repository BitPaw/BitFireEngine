#include "Image.h"

#include "BMP/BMP.h"
#include "PNG/PNG.h"
#include "TGA/TGA.h"
#include "TIFF/TIFF.h"
#include "GIF/GIF.h"
#include "JPEG/JPEG.h"
#include "TIFF/TIFF.h"

#include "../File/File.h"
#include "../Math/Math.h"

#include <cstdlib>
#include <cstdio>
#include <cwchar>

#include <Text/Text.h>

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
    Format = ImageDataFormat::Unkown;
    PixelDataSize = 0;
    PixelData = nullptr;
}

BF::Image::~Image()
{
    free(PixelData);
}

void BF::Image::RemoveColor(unsigned char red, unsigned char green, unsigned char blue)
{
    switch (Format)
    {
        case ImageDataFormat::AlphaMask:
        {
            break;
        }

        case ImageDataFormat::RGB:
        {
            FormatChange(ImageDataFormat::RGBA);

            // no break;
        }
        case ImageDataFormat::RGBA:
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
    size_t bbp = BytesPerPixel(Format);
    size_t rowSize = (Width * bbp);
    size_t length = (Width * bbp) / 2;

    for (size_t x = 0; x < length; x += bbp) // 
    {
        size_t xB = rowSize - x - bbp;

        for (size_t y = 0; y < Height; y++)
        {
            size_t indexA = x + (y * rowSize);
            size_t indexB = xB + (y * rowSize);
            Byte tempByte[4] = {0,0,0,0};
            Byte* pixelA = PixelData + indexA;
            Byte* pixelB = PixelData + indexB;

            memcpy(tempByte, pixelA, bbp);
            memcpy(pixelA, pixelB, bbp);
            memcpy(pixelB, tempByte, bbp);       
        }
    }
}

void BF::Image::FlipVertical()
{
    unsigned int height = Height;
    unsigned int width = Width;
    unsigned int bytesPerPixel = -1;

    switch (Format)
    {
        default:
        case BF::ImageDataFormat::Unkown:
            bytesPerPixel = -1;
            break;

        case BF::ImageDataFormat::AlphaMask:
        case BF::ImageDataFormat::AlphaMaskBinary:
            bytesPerPixel = 1;
            break;

        case BF::ImageDataFormat::BGR:
        case BF::ImageDataFormat::RGB:
            bytesPerPixel = 3;
            break;

        case BF::ImageDataFormat::RGBA:
        case BF::ImageDataFormat::BGRA:
            bytesPerPixel = 4;
            break;
    }

    size_t scanLineWidthSize = width * bytesPerPixel;
    unsigned int scanLinesToSwap = height / 2;
    unsigned char* copyBufferRow = (unsigned char*)malloc(scanLineWidthSize * sizeof(char));

    if (!copyBufferRow)
    {
        return;
    }

    for (unsigned int scanlineIndex = 0; scanlineIndex < scanLinesToSwap; scanlineIndex++)
    {
        unsigned char* bufferA = PixelData + (scanlineIndex * scanLineWidthSize);
        unsigned char* bufferB = PixelData + ((height - scanlineIndex) * scanLineWidthSize) - scanLineWidthSize;

        memcpy(copyBufferRow, bufferB, scanLineWidthSize); // A -> Buffer 'Save A'
        memcpy(bufferB, bufferA, scanLineWidthSize); // B -> A 'Move B to A(override)'
        memcpy(bufferA, copyBufferRow, scanLineWidthSize); // Buffer -> B 'Move SaveCopy (A) to B'
    }

    free(copyBufferRow);
}

void BF::Image::Resize(unsigned int width, unsigned height)
{
    unsigned int pixelSize;

    Width = width;
    Height = height;

    switch (Format)
    {
        case ImageDataFormat::AlphaMask:
            pixelSize = 2;
            break;

        default:
        case ImageDataFormat::RGB:
            pixelSize = 3;
            break;
        case ImageDataFormat::RGBA:
            pixelSize = 4;
            break;
    }

    PixelDataSize = width * height * pixelSize;
    PixelData = (Byte*)realloc(PixelData, PixelDataSize * sizeof(Byte));
}

void BF::Image::FillRandome()
{
    for (size_t i = 0; i < PixelDataSize; i++)
    {
        PixelData[i] = Math::RandomeNumber() % 255;
    }
}

void BF::Image::FormatChange(ImageDataFormat imageFormat)
{
    switch (Format)
    {
        case ImageDataFormat::AlphaMask:
        {

        }
        case ImageDataFormat::BGR:
        {
            switch (imageFormat)
            {
                case ImageDataFormat::RGB:
                {
                    unsigned int dIndex = 0;
                    unsigned int index = 0;

                    while (index < PixelDataSize)
                    {
                        unsigned char& blue = PixelData[index++];
                        unsigned char& green = PixelData[index++];
                        unsigned char& red = PixelData[index++];

                        PixelData[dIndex++] = red;
                        PixelData[dIndex++] = green;
                        PixelData[dIndex++] = blue;
                    }
                }

                default:
                    break;
            }
        }

        case ImageDataFormat::RGB:
        {
            switch (imageFormat)
            {
                case ImageDataFormat::AlphaMask:
                    break;
                case ImageDataFormat::RGB:
                    break;
                case ImageDataFormat::RGBA:
                {
                    size_t newIndex = 0;
                    size_t oldSize = PixelDataSize;
                    size_t newSize = (oldSize / 3) * 4;
                    unsigned char* newData = (unsigned char*)malloc(newSize * sizeof(char));
                    unsigned char* oldData = PixelData;

                    if (!newData)
                    {
                        return;
                    }

                    memset(newData, 0xFF, newSize);

                    for (unsigned int oldIndex = 0; oldIndex < oldSize; oldIndex += 3)
                    {
                        unsigned char* source = &oldData[oldIndex];
                        unsigned char* destination = &newData[newIndex];

                        memcpy(destination, source, 3);

                        newIndex += 4;
                    }

                    Format = ImageDataFormat::RGBA;
                    PixelData = newData;
                    PixelDataSize = newSize;

                    free(oldData);

                    break;
                }          
                case ImageDataFormat::BGR:
                {
                    unsigned int dIndex = 0;
                    unsigned int index = 0;

                    while (index < PixelDataSize)
                    {
                        unsigned char& blue = PixelData[index++];
                        unsigned char& green = PixelData[index++];
                        unsigned char& red = PixelData[index++];

                        PixelData[dIndex++] = red;
                        PixelData[dIndex++] = green;
                        PixelData[dIndex++] = blue;
                    }
                }
            }
        }
        case ImageDataFormat::RGBA:
        {

        }
    }
}

BF::ImageFileFormat BF::Image::FileFormatPeek(const wchar_t* filePath)
{
    File file(filePath);

    if (file.ExtensionEquals("BMP"))  return ImageFileFormat::BitMap;
    if (file.ExtensionEquals("GIF"))  return ImageFileFormat::GIF;
    if (file.ExtensionEquals("JPEG"))  return ImageFileFormat::JPEG;
    if (file.ExtensionEquals("PNG"))  return ImageFileFormat::PNG;
    if (file.ExtensionEquals("TGA"))  return ImageFileFormat::TGA;
    if (file.ExtensionEquals("TIFF"))  return ImageFileFormat::TIFF;

    return ImageFileFormat::Unkown;
}

BF::FileActionResult BF::Image::Load(const wchar_t* filePath)
{
    if (!File::DoesFileExist(filePath))
    {
        return FileActionResult::FileNotFound;
    }

    ImageFileFormat imageFileFormat = FileFormatPeek(filePath);

    switch (imageFileFormat)
    {
        case ImageFileFormat::BitMap:
        {
            BMP bitmap;
            bitmap.Load(filePath);
            bitmap.ConvertTo(*this);         
            break;
        }
        case ImageFileFormat::GIF:
        {
            GIF gif;
            gif.Load(filePath);
            gif.ConvertTo(*this);
            break;
        }
        case ImageFileFormat::JPEG:
        {
            JPEG jpeg;
            jpeg.Load(filePath);
            jpeg.ConvertTo(*this);
            break;
        }
        case ImageFileFormat::PNG:
        {
            PNG png;
            png.Load(filePath);
            png.ConvertTo(*this);
            break;
        }
        case ImageFileFormat::TGA:
        {
            TGA tga;
            tga.Load(filePath);
            tga.ConvertTo(*this);
            break;
        }
        case ImageFileFormat::TIFF:
        {
            TIFF tiff;
            tiff.Load(filePath);
            tiff.ConvertTo(*this);
            break;
        }
        case ImageFileFormat::Unkown:
        default:
        {
            return FileActionResult::FormatNotSupported;
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::Image::Save(const wchar_t* filePath, ImageFileFormat imageFileFormat)
{
    switch (imageFileFormat)
    {
        default:
        case BF::ImageFileFormat::Unkown:
        {
            return FileActionResult::FormatNotSupported;
        }
        case BF::ImageFileFormat::BitMap:
        {
            BMP bitmap;
            bitmap.ConvertFrom(*this);
            bitmap.Save(filePath);
            break;
        }
        case BF::ImageFileFormat::PNG:
        {
            PNG png;
            png.ConvertFrom(*this);
            png.Save(filePath);
            break;
        }
        case BF::ImageFileFormat::TGA:
        {
            TGA tga;
            tga.ConvertFrom(*this);
            tga.Save(filePath);
            break;
        }
        case BF::ImageFileFormat::JPEG:
        {
            JPEG jpeg;
            jpeg.ConvertFrom(*this);
            jpeg.Save(filePath);
            break;
        }
        case BF::ImageFileFormat::TIFF:
        {
            TIFF tiff;
            tiff.ConvertFrom(*this);
            tiff.Save(filePath);
            break;
        }
        case BF::ImageFileFormat::GIF:
        {
            GIF gif;
            gif.ConvertFrom(*this);
            gif.Save(filePath);
            break;
        }
    }

    return FileActionResult::Successful;
}

size_t BF::Image::FullSizeInMemory()
{
    return sizeof(Image) + (PixelDataSize * sizeof(Byte));
}
