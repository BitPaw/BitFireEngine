#include "PixelArrayLoader.h"

PixelArray PixelArrayLoader::LoadFromFile(std::string filePath)
{
    std::vector<unsigned char> bytes = FileLoader::ReadFileAsBytes(filePath);
    PixelArray pixels;

    pixels.Size = bytes.size();
    pixels.PixelData = new unsigned char[pixels.Size] {0};

    for (unsigned int i = 0; i < pixels.Size; i++)
    {
        pixels.PixelData[i] = bytes.at(i);;
    }

    return pixels;
}

void PixelArrayLoader::SaveToFile(std::string filePath, PixelArray& pixelArray)
{
    FileLoader::WriteFileAsBytes(filePath, pixelArray.Size, pixelArray.PixelData);
}

void PixelArrayLoader::PrintPixelArray(PixelArray& pixelArray)
{
    printf("[PixelArray] size=%u", pixelArray.Size);

    for (unsigned int i = 0; i < pixelArray.Size; i++)
    {
        printf("%02x ", pixelArray.PixelData[i]);

        if (i % 30 == 0)
        {
            printf("\n");
        }
    }

    printf("\n");
}
