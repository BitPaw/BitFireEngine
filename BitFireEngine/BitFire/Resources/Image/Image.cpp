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

void BF::Image::FlipHorizontal()
{
    unsigned int length = PixelData.Size();
    unsigned int height = Height;

    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int dIndex = 0;
    Table<RGBA<unsigned char>> table(Width, Height);
       
    for (unsigned int i = 0; i < length; )
    {
        unsigned int r = PixelData[i++];
        unsigned int g = PixelData[i++];
        unsigned int b = PixelData[i++];
        unsigned int a = PixelData[i++];

        table[x++][y] = RGBA<unsigned char>(r, g, b, a);

        //printf("[%i|%i] %.2x %.2x %.2x %.2x\n", x, y, r, g, b, a);

        if (x == Width)
        {
            x = 0;
            y++;
        }
    }

    for (unsigned int y = Height; y > 0; y--)
    {
        for (unsigned int x = 0; x < Width; x++)
        {
            RGBA<unsigned char>* pixel = &table[x][y-1];

           // printf("[%i|%i] %.2x %.2x %.2x %.2x\n", x, y-1, pixel->Red, pixel->Green, pixel->Blue, pixel->Alpha);

            PixelData[dIndex++] = pixel->Red;
            PixelData[dIndex++] = pixel->Green;
            PixelData[dIndex++] = pixel->Blue;
            PixelData[dIndex++] = '\xFF';//pixel->Alpha;
        }
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
        Width* Height * 4
    );
}

void BF::Image::Resize(unsigned int width, unsigned height)
{
    unsigned int newArraySize = width * height;
    unsigned int pixelSize = 2;

    switch (Information.Format)
    {
        case BF::ImageFormatMode::BlackAndWhite:
            break;

        case BF::ImageFormatMode::RGB:
            pixelSize = 3;
            break;
        case BF::ImageFormatMode::RGBA:
            pixelSize = 4;
            break;
    }

    Width = width;
    Height = height;

    PixelData.ReSize(newArraySize * pixelSize);
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