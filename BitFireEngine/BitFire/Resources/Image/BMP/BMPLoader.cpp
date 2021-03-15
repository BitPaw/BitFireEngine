#include "BMPLoader.h"

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

BF::BMP* BF::BMPLoader::LoadFromFile(ASCIIString& path)
{
    BMP* bitMap = new BMP();
    ByteString bytes;

    FileLoader::ReadFileAsBytes(path, bytes);

    unsigned int dynamicIndex = 0;
    unsigned char byteA = bytes[dynamicIndex++]; // Index = 0
    unsigned char byteB = bytes[dynamicIndex++]; // Index = 1
    unsigned char byteC = 0;
    unsigned char byteD = 0;

    int size = 0;
    int dip = 0;

    // Parsing Header
    {
        bitMap->Header.Type = ParseType(byteA, byteB);

        byteA = bytes[dynamicIndex++];// Index = 2
        byteB = bytes[dynamicIndex++];// Index = 3
        byteC = bytes[dynamicIndex++]; // Index = 4
        byteD = bytes[dynamicIndex++];// Index = 5
        bitMap->Header.SizeOfFile = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

        byteA = bytes[dynamicIndex++];// Index = 6
        byteB = bytes[dynamicIndex++]; // Index = 7
        byteC = bytes[dynamicIndex++]; // Index = 8
        byteD = bytes[dynamicIndex++];// Index = 9
        bitMap->Header.ActualSizeOfFile = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

        byteA = bytes[dynamicIndex++]; // Index = 10
        byteB = bytes[dynamicIndex++]; // Index = 11
        byteC = bytes[dynamicIndex++]; // Index = 12
        byteD = bytes[dynamicIndex++]; // Index = 13
        bitMap->Header.DataOffset = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);
    }

    // DIP
    {
        // Get Header Version
        byteA = bytes[dynamicIndex++]; // Index = 14
        byteB = bytes[dynamicIndex++];// Index = 15
        byteC = bytes[dynamicIndex++];// Index = 16
        byteD = bytes[dynamicIndex++]; // Index = 17
        unsigned char result = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);
        bitMap->InformationHeaderType = GetType(result);

        switch (bitMap->InformationHeaderType)
        {
        case BMPInformationHeaderType::BitMapInfoHeader:

        {
            BMPInfoHeader* bitMapInfoHeader = new BMPInfoHeader();

            bitMapInfoHeader->HeaderSize = byteA;

            byteA = bytes[dynamicIndex++]; // Index = 18
            byteB = bytes[dynamicIndex++]; // Index = 19
            byteC = bytes[dynamicIndex++]; // Index = 20
            byteD = bytes[dynamicIndex++]; // Index = 21
            bitMapInfoHeader->Width = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++];// Index = 22
            byteB = bytes[dynamicIndex++]; // Index = 23
            byteC = bytes[dynamicIndex++]; // Index = 24
            byteD = bytes[dynamicIndex++];// Index = 25
            bitMapInfoHeader->Height = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);
           
            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->NumberOfColorPlanes = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->NumberOfBitsPerPixel = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->CompressionMethod = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++];// Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->ImageSize = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->HorizontalResolution = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->VerticalResolution = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++];// Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++]; // Index = 
            byteD = bytes[dynamicIndex++];// Index = 
            bitMapInfoHeader->NumberOfColorsInTheColorPalette = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

            byteA = bytes[dynamicIndex++]; // Index = 
            byteB = bytes[dynamicIndex++]; // Index = 
            byteC = bytes[dynamicIndex++];// Index = 
            byteD = bytes[dynamicIndex++]; // Index = 
            bitMapInfoHeader->NumberOfImportantColorsUsed = ByteString::ToUnsignedInt(EndianType::Big, byteA, byteB, byteC, byteD);

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

void BF::BMPLoader::SaveToFile(ASCIIString& path, BMP& bitMap)
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