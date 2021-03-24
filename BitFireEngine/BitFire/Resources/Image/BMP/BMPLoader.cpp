#include "BMPLoader.h"
#include "../../../Utility/DoubleWord.h"
#include "../../../Utility/Word.h"

BF::BMPInformationHeaderType BF::BMPLoader::GetType(unsigned char byte)
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

    BMPInformationHeaderType type = BMPInformationHeaderType::UnkownOrInvalid;

    switch (byte)
    {
    case 12:
        //type = BitMapInformationHeaderType::BitMapV5Header;
        break;

    case 16:
        //type = BitMapInformationHeaderType::BitMapV5Header;
        break;

    case bitMapInfoHeaderSize:
        type = BMPInformationHeaderType::BitMapInfoHeader;
        break;

    case bitMapV2InfoHeaderSize:
        type = BMPInformationHeaderType::BitMapV2InfoHeader;
        break;

    case bitMapV3InfoHeaderSize:
        type = BMPInformationHeaderType::BitMapV3InfoHeader;
        break;

    case bitMapV4HeaderSize:
        type = BMPInformationHeaderType::BitMapV4Header;
        break;

    case bitMapV5HeaderSize:
        type = BMPInformationHeaderType::BitMapV5Header;
        break;
    }

    return type;
}

BF::BMPType BF::BMPLoader::ParseType(unsigned char leftByte, unsigned char rightByte)
{
    BMPType type = BMPType::UnkownOrInavlid;

    switch (leftByte)
    {
    case 'B':    
        switch (rightByte)
        {
        case 'A':
            type = BMPType::OS2StructBitmapArray;
            break;

        case 'M':
            type = BMPType::Windows;
            break;
        }    
        break;

    case 'C':
        switch (rightByte)
        {
        case 'I':
            type = BMPType::OS2StructColorIcon;
            break;

        case 'P':
            type = BMPType::OS2ConstColorPointer;
            break;
        }
        break;

    case 'I':
        if ('C' == rightByte)
        {
            type = BMPType::OS2StructIcon;
        }
        break;

    case 'P':
        if ('C' == rightByte)
        {
            type = BMPType::OS2Pointer;
        }
        break;
    }   

    return type;
}

unsigned int CalculateNeddedRowSize(unsigned int bitsPerPixel, unsigned int imageWidth)
{
    float x = (bitsPerPixel * imageWidth) / (32.0f);
    unsigned int cappedValue = BF::Math::Ceiling(x) * 4;

    return cappedValue;
}




BF::BMP* BF::BMPLoader::LoadFromFile(AsciiString& path)
{
    BMP* bitMap = new BMP();
    AsciiString bytes;
    Word word;
    DoubleWord dWord;
    unsigned int dynamicIndex = 0;
    int size = 0;
    int dip = 0;

    FileLoader::ReadFileAsBytes(path, bytes);
  
    word.ByteA = bytes[dynamicIndex++]; // Index = 0
    word.ByteB = bytes[dynamicIndex++]; // Index = 1

    // Parsing Header
    {
        bitMap->Header.Type = ParseType(word.ByteA, word.ByteB);

        dWord.ByteA = bytes[dynamicIndex++];
        dWord.ByteB = bytes[dynamicIndex++];
        dWord.ByteC = bytes[dynamicIndex++]; 
        dWord.ByteD = bytes[dynamicIndex++];
        bitMap->Header.SizeOfFile = dWord.ExtractInt(EndianType::Big);

        dWord.ByteA = bytes[dynamicIndex++];
        dWord.ByteB = bytes[dynamicIndex++];
        dWord.ByteC = bytes[dynamicIndex++];
        dWord.ByteD = bytes[dynamicIndex++];
        bitMap->Header.ActualSizeOfFile = dWord.ExtractInt(EndianType::Big);

        dWord.ByteA = bytes[dynamicIndex++];
        dWord.ByteB = bytes[dynamicIndex++];
        dWord.ByteC = bytes[dynamicIndex++];
        dWord.ByteD = bytes[dynamicIndex++];
        bitMap->Header.DataOffset = dWord.ExtractInt(EndianType::Big);
    }

    // DIP
    {
        // Get Header Version
        dWord.ByteA = bytes[dynamicIndex++];
        dWord.ByteB = bytes[dynamicIndex++];
        dWord.ByteC = bytes[dynamicIndex++];
        dWord.ByteD = bytes[dynamicIndex++];
        unsigned char result = dWord.ExtractInt(EndianType::Big);
        bitMap->InformationHeaderType = GetType(result);

        switch (bitMap->InformationHeaderType)
        {
        case BMPInformationHeaderType::BitMapInfoHeader:

        {
            BMPInfoHeader* bitMapInfoHeader = new BMPInfoHeader();

            bitMapInfoHeader->HeaderSize = dWord.ByteA;

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->Width = dWord.ExtractInt(EndianType::Big);

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->Height = dWord.ExtractInt(EndianType::Big);
           
            word.ByteA = bytes[dynamicIndex++]; 
            word.ByteB = bytes[dynamicIndex++]; 
            bitMapInfoHeader->NumberOfColorPlanes = word.ExtractInt(EndianType::Big);

            word.ByteA = bytes[dynamicIndex++];
            word.ByteB = bytes[dynamicIndex++];
            bitMapInfoHeader->NumberOfBitsPerPixel = word.ExtractInt(EndianType::Big);

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->CompressionMethod = dWord.ExtractInt(EndianType::Big);

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->ImageSize = dWord.ExtractInt(EndianType::Big);

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->HorizontalResolution = dWord.ExtractInt(EndianType::Big);

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->VerticalResolution = dWord.ExtractInt(EndianType::Big);

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->NumberOfColorsInTheColorPalette = dWord.ExtractInt(EndianType::Big);

            dWord.ByteA = bytes[dynamicIndex++];
            dWord.ByteB = bytes[dynamicIndex++];
            dWord.ByteC = bytes[dynamicIndex++];
            dWord.ByteD = bytes[dynamicIndex++];
            bitMapInfoHeader->NumberOfImportantColorsUsed = dWord.ExtractInt(EndianType::Big);

            bitMap->InformationHeader = bitMapInfoHeader;


            // Copy Data (Make a bit redundant data)
            bitMap->Width = bitMapInfoHeader->Width;
            bitMap->Height = bitMapInfoHeader->Height;

            size = bitMapInfoHeader->Width * bitMapInfoHeader->Height;    

            dip = bitMapInfoHeader->NumberOfBitsPerPixel;
        }

            break;
        }
    }

    // Pixel
    { 
        unsigned int pixelIndex = 0;
        unsigned int width = bitMap->Width;
        unsigned int size = width * bitMap->Height;

        bitMap->Pixel.ReSize(size);

        unsigned int length = bytes.Size();
        unsigned int neededRows = CalculateNeddedRowSize(dip, width);
        unsigned int paddingSize = neededRows % 4; // <--  hardcoded
        unsigned int rowIndex = 0;
        const unsigned int rowWidth = width * 3;             

        printf("Width=%i Rows size=%u padding=%u\n", width, neededRows, paddingSize);   

        while (pixelIndex < size)
        {       
            bool ifPixelData = rowIndex < rowWidth; 

            if (ifPixelData)
            {    
                unsigned char blue = bytes[dynamicIndex++];
                unsigned char green = bytes[dynamicIndex++];
                unsigned char red = bytes[dynamicIndex++];

                RGB<unsigned char> color(red, green, blue);

                rowIndex += 3;

                bitMap->Pixel[pixelIndex++] = color;

               // printf("[Pixel][%05u/%05u] Pixel: ", pixelNr++, size);
               // printf("%03u %03u %03u\n", red, green, blue);
            }
            else
            {     
                for (unsigned int i = 0; i < paddingSize; i++)
                {
                    dynamicIndex++;
                    rowIndex++;

                    //printf("[Pixel][xxxxx/%05u] Padding\n", size);
                }

                rowIndex = 0;
            }
        }        
    }

    return bitMap;
}

void BF::BMPLoader::SaveToFile(AsciiString& path, BMP& bitMap)
{
    
}

void BF::BMPLoader::PrintBitMapInformation(BF::BMP& bitMap)
{
    printf("[BitMap] (.bmp)");
    printf("Type      : %u\n", bitMap.Header.Type);
    printf("SizeOfFile: %i\n", bitMap.Header.SizeOfFile);
    printf("Unsued    : %i\n", bitMap.Header.ActualSizeOfFile);
    printf("DataOffset: %i\n", bitMap.Header.DataOffset);

    switch (bitMap.InformationHeaderType)
    {
    case BMPInformationHeaderType::BitMapInfoHeader:
       
        BMPInfoHeader* bitMapInfoHeader = (BMPInfoHeader*)(bitMap.InformationHeader);
       
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