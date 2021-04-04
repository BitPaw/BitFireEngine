#include "Image.h"
#include "../../Utility/Table.hpp"

BF::RGBA<unsigned char> BF::Image::GetPixel(unsigned int x, unsigned int y)
{
    unsigned int pos = (x * Width + y) * 4;

    RGBA<unsigned char> pixel
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
    case ImageFormat::BlackAndWhite:
    {
       
    }

    case ImageFormat::RGB:
    { 
        unsigned int size = (PixelData.Size() / 3) *4;        
        unsigned char* newData = new unsigned char[size];
        unsigned char* oldData = PixelData.SwapBuffer(newData, size);
        unsigned int oldIndex = 0;

        for (unsigned int i = 0; i < size; )
        {
            newData[i++] = oldData[oldIndex++];
            newData[i++] = oldData[oldIndex++];
            newData[i++] = oldData[oldIndex++];
            newData[i++] = 0xFF;
        }
        Format = ImageFormat::RGBA;

        delete[] oldData;
    }
    case ImageFormat::RGBA:
    {    
        for (size_t i = 0; i < PixelData.Size(); )
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
    unsigned int scanLineWidth = width * bytesPerPixel;
    unsigned int scanLinesToSwap = height / 2;
    unsigned char* dataStartAdress = &PixelData[0];
    unsigned char* copyBufferRow = new unsigned char[scanLineWidth];

    for (unsigned int scanlineIndex = 0; scanlineIndex < scanLinesToSwap; scanlineIndex++)
    {
        unsigned char* destination = dataStartAdress + (scanlineIndex * scanLineWidth); // D
        unsigned char* source = dataStartAdress + ((height - scanlineIndex) * scanLineWidth) - scanLineWidth; // S

        memcpy(copyBufferRow, source, scanLineWidth); // S -> X 'Save S'
        memcpy(source, destination, scanLineWidth); // D -> S 'Move D to S(override)'
        memcpy(destination, copyBufferRow, scanLineWidth); // X -> D 'Move SaveCopy to D'
    }

    delete[] copyBufferRow;
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
    unsigned int pixelSize = 2;

    Width = width;
    Height = height;

    switch (Format)
    {
    case ImageFormat::BlackAndWhite:
        break;

    case ImageFormat::RGB:
        pixelSize = 3;
        break;
    case ImageFormat::RGBA:
        pixelSize = 4;
        break;
    }

    PixelData.ReSize(newArraySize * pixelSize);
}

void BF::Image::FillRandome()
{
    for (unsigned int y = 0; y < Width; y++)
    {
        for (unsigned int x = 0; x < Height; x++)
        {
            unsigned int index = (x + (y * Width)) * 4;

            PixelData[index + 0] = Math::RandomeNumber() % 255;
            PixelData[index + 1] = Math::RandomeNumber() % 255;
            PixelData[index + 2] = Math::RandomeNumber() % 255;
            PixelData[index + 3] = 0xFF;
        }
    }
}











/*
unsigned int length = PixelData.Size.Value;
for (unsigned int i = 0; i < length; i++)
{
    printf("%.2x ", PixelData[i]);


   if (((i+1) % 4) == 0)
    {
        printf("\n");
    }

}
printf("\n");

unsigned int pixelDataSize = PixelData.Size.Value;
unsigned int pixelListSize = pixelDataSize / 4;
unsigned int dIndex = 0;
List<RGBA8Bit> pixels;
pixels.ReSize(pixelListSize);


for (unsigned int y = Height; y > 0; y--)
{
    for (unsigned int x = 0; x < Width; x++)
    {
        pixels[dIndex++] = GetPixel(x, y-1);

        RGBA8Bit* xww = &pixels[dIndex];;

        printf("%.2x %.2x %.2x %.2x\n", xww->Red, xww->Green, xww->Blue, xww->Alpha);
    }
}

dIndex = 0;

for (unsigned int i = 0; i < pixelListSize; i++)
{
    RGBA8Bit* pixel = &pixels[i];

   PixelData[dIndex++] = pixel->Red;
   PixelData[dIndex++] = pixel->Green;
   PixelData[dIndex++] = pixel->Blue;
   PixelData[dIndex++] = pixel->Alpha;
}

pixels.DeleteAll();
}

/*
* To RGB List
*
    unsigned int pixelDataSize = PixelData.Size.Value;
    unsigned int pixelListSize = pixelDataSize / 4;
    unsigned int dIndex = 0;
    List<RGBA> pixels;

    pixels.ReSize(pixelListSize);

    for (unsigned int i = 0; i < pixelDataSize; )
    {
        RGBA pixel
        {
            PixelData[i++],
            PixelData[i++],
            PixelData[i++],
        };

        pixels[dIndex++] = pixel;
    }
*/