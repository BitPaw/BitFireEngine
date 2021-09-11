#include "Image.h"
#include "../File/File.h"
#include "BMP/BMP.h"
#include "PNG/PNG.h"
#include "TGA/TGA.h"
#include <malloc.h>
#include "../Math/Math.h"

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

    LayoutNear = ImageLayout::Nearest;
    LayoutFar = ImageLayout::Nearest;

    WrapHeight = ImageWrap::Repeat;
    WrapWidth = ImageWrap::Repeat;
}

void BF::Image::RemoveColor(unsigned char red, unsigned char green, unsigned char blue)
{
    switch (Format)
    {
        case ImageFormat::AlphaMask:
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
        case ImageFormat::AlphaMask:
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
        case ImageFormat::AlphaMask:
        {

        }
        case ImageFormat::BGR:
        {
            switch (imageFormat)
            {
                case ImageFormat::RGB:
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

        case ImageFormat::RGB:
        {
            switch (imageFormat)
            {
                case ImageFormat::AlphaMask:
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
                case ImageFormat::BGR:
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
        case ImageFormat::RGBA:
        {

        }
    }
}

BF::ImageFileExtension BF::Image::FileFormatPeek(const char* filePath)
{
    File file(filePath);
    AsciiString fileExtension(file.Extension);

    if (fileExtension.CompareIgnoreCase("bmp")) return ImageFileExtension::BMP;
    if (fileExtension.CompareIgnoreCase("gif")) return ImageFileExtension::GIF;
    if (fileExtension.CompareIgnoreCase("jpeg")) return ImageFileExtension::JPEG;
    if (fileExtension.CompareIgnoreCase("png")) return ImageFileExtension::PNG;
    if (fileExtension.CompareIgnoreCase("tga")) return ImageFileExtension::TGA;
    if (fileExtension.CompareIgnoreCase("tiff")) return ImageFileExtension::TIFF;

    return ImageFileExtension::Unkown;
}

BF::ResourceLoadingResult BF::Image::Load(const char* filePath)
{
    ID = ResourceIDLoading;

    if (!File::DoesFileExist(filePath))
    {
        ID = ResourceIDFileNotFound;
        return ResourceLoadingResult::FileNotFound;
    } 

    ImageFileExtension imageFormat = FileFormatPeek(filePath);

    strcpy(FilePath, filePath);

    switch (imageFormat)
    {
        case ImageFileExtension::BMP:
        {
            BMP bitmap;
            bitmap.Load(filePath);
            bitmap.ConvertTo(*this);
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
        {
            ID = ResourceIDUnsuportedFormat;

            return ResourceLoadingResult::FormatNotSupported;
        }       
    }

    ID = ResourceIDLoaded;

    return ResourceLoadingResult::Successful;
}
