#include "PNGLoader.h"

BF::PNG BF::PNGLoader::LoadFromFile(std::string filePath)
{
    PNG portableNetworkGraphic;
    BF::List<unsigned char> bytes = FileLoader::ReadFileAsBytes(filePath);
    
    unsigned char dynamicIndex = 0;

    // Check Header
    while (dynamicIndex < PortableNetworkGraphicFileHeader::FileHeaderSize)
    {
        unsigned char target = bytes[dynamicIndex];
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
        byteA = bytes[dynamicIndex++];
        byteB = bytes[dynamicIndex++];

        portableNetworkGraphic.ImageHeader.Width = Converter::ConvertTwoBytesToNumber(EndianType::Little,byteA, byteB);

        byteA = bytes[dynamicIndex++];
        byteB = bytes[dynamicIndex++];

        portableNetworkGraphic.ImageHeader.Height = Converter::ConvertTwoBytesToNumber(EndianType::Little, byteA, byteB);

        portableNetworkGraphic.ImageHeader.BitDepth = bytes[dynamicIndex++];
        portableNetworkGraphic.ImageHeader.ColorType = bytes[dynamicIndex++];
        portableNetworkGraphic.ImageHeader.CompressionMethod = bytes[dynamicIndex++];
        portableNetworkGraphic.ImageHeader.FilterMethod = bytes[dynamicIndex++];
        portableNetworkGraphic.ImageHeader.InterlaceMethod = bytes[dynamicIndex++];
    }

    return portableNetworkGraphic;
}
