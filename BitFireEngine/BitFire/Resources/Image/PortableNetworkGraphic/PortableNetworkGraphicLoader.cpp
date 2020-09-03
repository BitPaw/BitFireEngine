#include "PortableNetworkGraphicLoader.h"
#include "../../../Mathematic/Converter/Converter.h"

PortableNetworkGraphic PortableNetworkGraphicLoader::LoadFromFile(std::string filePath)
{
    PortableNetworkGraphic portableNetworkGraphic;
    std::vector<unsigned char> bytes = FileLoader::ReadFileAsBytes(filePath);
    
    unsigned char dynamicIndex = 0;

    // Check Header
    while (dynamicIndex < PortableNetworkGraphicFileHeader::FileHeaderSize)
    {
        unsigned char target = bytes.at(dynamicIndex);
        unsigned char source = PortableNetworkGraphicFileHeader::FileHeader[dynamicIndex];
        bool sameValue = target == source;

        printf("%c:%u | %c:%u\n", target, target, source, source);

        if (!sameValue)
        {
            if (target == '\r' || target == '\n')
            {

            }
            else
            {
                printf("Error\n");
               // throw std::exception("Inavlid Header / PNG File");
            }           
        }

        dynamicIndex++;
    }

    // Check Image Header
    {
        unsigned char byteA;
        unsigned char byteB;

        /*
        Width:             4 bytes
        Height:             4 bytes
        Bit depth:          1 byte
        Color type:         1 byte
        Compression method: 1 byte
        Filter method:      1 byte
        Interlace method:   1 byte
        */
        byteA = bytes.at(dynamicIndex++);
        byteB = bytes.at(dynamicIndex++);

        portableNetworkGraphic.ImageHeader.Width = Converter::ConvertTwoBytesToNumber(EndianType::Little,byteA, byteB);

        byteA = bytes.at(dynamicIndex++);
        byteB = bytes.at(dynamicIndex++);

        portableNetworkGraphic.ImageHeader.Height = Converter::ConvertTwoBytesToNumber(EndianType::Little, byteA, byteB);

        portableNetworkGraphic.ImageHeader.BitDepth = bytes.at(dynamicIndex++);
        portableNetworkGraphic.ImageHeader.ColorType = bytes.at(dynamicIndex++);
        portableNetworkGraphic.ImageHeader.CompressionMethod = bytes.at(dynamicIndex++);
        portableNetworkGraphic.ImageHeader.FilterMethod = bytes.at(dynamicIndex++);
        portableNetworkGraphic.ImageHeader.InterlaceMethod = bytes.at(dynamicIndex++);
    }

    return portableNetworkGraphic;
}
