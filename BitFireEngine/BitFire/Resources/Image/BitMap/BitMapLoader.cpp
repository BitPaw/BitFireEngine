#include "BitMapLoader.h"

BitMapInformationHeaderType BitMapLoader::GetType(unsigned char byte)
{
    //const unsigned char bitMapCoreHeaderSize = 12;
    //const unsigned char os21XBitMapHeaderSize = 12;
    //const unsigned char os22XBitMapHeaderSizeTypeA = 16;
    //const unsigned char os22XBitMapHeaderSizeTypeB = 16;
    const unsigned char bitMapInfoHeaderSize = 40;
    const unsigned char bitMapV2InfoHeaderSize = 52;
    const unsigned char bitMapV3InfoHeaderSize = 56;
    const unsigned char bitMapV4HeaderSize = 108;
    const unsigned char bitMapV5HeaderSize = 124;

    BitMapInformationHeaderType type = BitMapInformationHeaderType::UnkownOrInvalid;

    switch (byte)
    {
    case 12:
        //type = BitMapInformationHeaderType::BitMapV5Header;
        break;

    case 16:
        //type = BitMapInformationHeaderType::BitMapV5Header;
        break;

    case bitMapInfoHeaderSize:
        type = BitMapInformationHeaderType::BitMapInfoHeader;
        break;

    case bitMapV2InfoHeaderSize:
        type = BitMapInformationHeaderType::BitMapV2InfoHeader;
        break;

    case bitMapV3InfoHeaderSize:
        type = BitMapInformationHeaderType::BitMapV3InfoHeader;
        break;

    case bitMapV4HeaderSize:
        type = BitMapInformationHeaderType::BitMapV4Header;
        break;

    case bitMapV5HeaderSize:
        type = BitMapInformationHeaderType::BitMapV5Header;
        break;
    }

    return type;
}

BitMapType BitMapLoader::ParseType(unsigned char leftByte, unsigned char rightByte)
{
    BitMapType type = BitMapType::UnkownOrInavlid;

    switch (leftByte)
    {
    case 'B':    
        switch (rightByte)
        {
        case 'A':
            type = BitMapType::OS2StructBitmapArray;
            break;

        case 'M':
            type = BitMapType::Windows;
            break;
        }    
        break;

    case 'C':
        switch (rightByte)
        {
        case 'I':
            type = BitMapType::OS2StructColorIcon;
            break;

        case 'P':
            type = BitMapType::OS2ConstColorPointer;
            break;
        }
        break;

    case 'I':
        if ('C' == rightByte)
        {
            type = BitMapType::OS2StructIcon;
        }
        break;

    case 'P':
        if ('C' == rightByte)
        {
            type = BitMapType::OS2Pointer;
        }
        break;
    }   

    return type;
}


unsigned int CalculateNeddedRowSize(unsigned int bitsPerPixel, unsigned int imageWidth)
{
    float x = (bitsPerPixel * imageWidth) / (32.0f);
    x = std::ceilf(x); 
    x *= 4;

    return x;
}

BitMap BitMapLoader::LoadFromFile(std::string path)
{
    BitMap bitMap;
    BF::List<unsigned char> bytes = FileLoader::ReadFileAsBytes(path);

    int width = 0;
    unsigned int dynamicIndex = 0;
    unsigned char byteA = bytes[dynamicIndex++]; // Index = 0
    unsigned char byteB = bytes[dynamicIndex++]; // Index = 1
    unsigned char byteC = 0;
    unsigned char byteD = 0;

    int size = 0;

    // Parsing Header
    {
        bitMap.Header.Type = ParseType(byteA, byteB);

        byteA = bytes[dynamicIndex++];// Index = 2
        byteB = bytes[dynamicIndex++];// Index = 3
        byteC = bytes[dynamicIndex++]; // Index = 4
        byteD = bytes[dynamicIndex++];// Index = 5
        bitMap.Header.SizeOfFile = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

        byteA = bytes[dynamicIndex++];// Index = 6
        byteB = bytes[dynamicIndex++]; // Index = 7
        byteC = bytes[dynamicIndex++]; // Index = 8
        byteD = bytes[dynamicIndex++];// Index = 9
        bitMap.Header.ActualSizeOfFile = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

        byteA = bytes[dynamicIndex++]; // Index = 10
        byteB = bytes[dynamicIndex++]; // Index = 11
        byteC = bytes[dynamicIndex++]; // Index = 12
        byteD = bytes[dynamicIndex++]; // Index = 13
        bitMap.Header.DataOffset = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);
    }

    // DIP
    {
        // Get Header Version
        byteA = bytes[dynamicIndex++]; // Index = 14
        byteB = bytes[dynamicIndex++];// Index = 15
        byteC = bytes[dynamicIndex++];// Index = 16
        byteD = bytes[dynamicIndex++]; // Index = 17
        unsigned char result = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);
        bitMap.InformationHeaderType = GetType(result);

        switch (bitMap.InformationHeaderType)
        {
        case BitMapInformationHeaderType::BitMapInfoHeader:

        {
            BitMapInfoHeader* bitMapInfoHeader = new BitMapInfoHeader();

            bitMapInfoHeader->HeaderSize = byteA;

            byteA = bytes[dynamicIndex++]; // Index = 18
            byteB = bytes[dynamicIndex++]; // Index = 19
            byteC = bytes[dynamicIndex++]; // Index = 20
            byteD = bytes[dynamicIndex++]; // Index = 21
            bitMapInfoHeader->Width = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++];// Index = 22
            byteB = bytes[dynamicIndex++]; // Index = 23
            byteC = bytes[dynamicIndex++]; // Index = 24
            byteD = bytes[dynamicIndex++];// Index = 25
            bitMapInfoHeader->Height = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);
           
            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->NumberOfColorPlanes = Converter::ConvertTwoBytesToNumber(EndianType::Little, byteA, byteB);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->NumberOfBitsPerPixel = Converter::ConvertTwoBytesToNumber(EndianType::Little, byteA, byteB);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->CompressionMethod = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++];// Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->ImageSize = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->HorizontalResolution = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->VerticalResolution = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++];// Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++];// Index = 
            bitMapInfoHeader->NumberOfColorsInTheColorPalette = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++];// Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->NumberOfImportantColorsUsed = Converter::Convert4BytesToNumber(EndianType::Little, byteA, byteB, byteC, byteD);

            bitMap.InformationHeader = bitMapInfoHeader;

            width = bitMapInfoHeader->Width;
            size = bitMapInfoHeader->Width * bitMapInfoHeader->Height;         
        }

            break;
        }
    }

    // Pixel
    {
        RGBEightBit color;     

        bitMap.Pixel.reserve(size);

        unsigned int leftbits = bytes.Size.Value;
        unsigned int neededRows = CalculateNeddedRowSize(24, width);
        unsigned int paddingCOunter = 0;
        unsigned int paddingSize = neededRows % 3;

        while (dynamicIndex < (leftbits))
        {       
            if (paddingCOunter >= (neededRows - paddingSize))
            {
                for (unsigned int i = 0; i < paddingSize; i++)
                {
                    dynamicIndex++;
                    paddingCOunter++;

                   // printf("[Pixel][%05u/%05u] Padding\n", dynamicIndex, leftbits);
                }

                paddingCOunter = 0;
            }
            else
            {
                paddingCOunter += 3;

                color.Blue = bytes[dynamicIndex++];// Index = 
                color.Green = bytes[dynamicIndex++];// Index = 
                color.Red = bytes[dynamicIndex++]; // Index = 

                bitMap.Pixel.push_back(color);

              //  printf("[Pixel][%05u/%05u] %03u %03u %03u\n", dynamicIndex, leftbits, color.Red, color.Green, color.Blue);
            }

           


                /*                
                A 24-bit bitmap with 
                Width=1 would have  3 bytes of data per row (blue, green, red) and 1 byte of padding. 
                Width=2 would have  6 bytes of data and 2 bytes of padding.
                Width=3 would have  9 bytes of data and 3 bytes of padding.
                Width=4 would have 12 bytes of data and no padding.                 
         */}        
    }

    return bitMap;
}

void BitMapLoader::SaveToFile(std::string path, BitMap& bitMap)
{
    
}

PixelArray BitMapLoader::GeneratePixelArray(BitMap& bitmap)
{
    PixelArray pixelArray;

    unsigned int dynIndex = 0;
    unsigned int dataSize = bitmap.Pixel.size();
    unsigned int height = bitmap.InformationHeader->Height;
    unsigned int width = bitmap.InformationHeader->Width;

    pixelArray.Size = dataSize * 4;
    pixelArray.PixelData = new unsigned char[pixelArray.Size];

    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            RGBEightBit* rgb = bitmap.GetPixel(x, y);

            pixelArray.PixelData[dynIndex++] = rgb->Red;
            pixelArray.PixelData[dynIndex++] = rgb->Green;
            pixelArray.PixelData[dynIndex++] = rgb->Blue;
            pixelArray.PixelData[dynIndex++] = '\xFF';
        }
    }

    return pixelArray;
}

void BitMapLoader::PrintBitMapInformation(BitMap& bitMap)
{
    printf("[BitMap] (.bmp)");
    printf("Type      : %u\n", bitMap.Header.Type);
    printf("SizeOfFile: %i\n", bitMap.Header.SizeOfFile);
    printf("Unsued    : %i\n", bitMap.Header.ActualSizeOfFile);
    printf("DataOffset: %i\n", bitMap.Header.DataOffset);

    switch (bitMap.InformationHeaderType)
    {
    case BitMapInformationHeaderType::BitMapInfoHeader:
       
        BitMapInfoHeader* bitMapInfoHeader = (BitMapInfoHeader*)(bitMap.InformationHeader);
       
        printf("Size : %u\n", bitMapInfoHeader->HeaderSize);
        printf("Width : %i\n", bitMapInfoHeader->Width);
        printf("Height : %i\n", bitMapInfoHeader->Height);
        printf("NumberOfColorPlanes : %u\n", bitMapInfoHeader->NumberOfColorPlanes);
        printf("NumberOfBitsPerPixel : %u\n", bitMapInfoHeader->NumberOfBitsPerPixel);
        printf("CompressionMethod : %u\n", bitMapInfoHeader->CompressionMethod);
        printf("ImageSize : %u\n", bitMapInfoHeader->ImageSize);
        printf("HorizontalResolution : %i\n", bitMapInfoHeader->HorizontalResolution);
        printf("VerticalResolution : %i\n", bitMapInfoHeader->VerticalResolution);
        printf("NumberOfColorsInTheColorPalette : %u\n", bitMapInfoHeader->NumberOfColorsInTheColorPalette);
        printf("NumberOfImportantColorsUsed : %u\n", bitMapInfoHeader->NumberOfImportantColorsUsed);

        break;
    }

}
