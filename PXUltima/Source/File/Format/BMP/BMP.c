#include "BMP.h"

#include <Container/ClusterShort.h>
#include <Container/ClusterInt.h>
#include <File/ParsingStream.h>
#include <Memory/Memory.h>

#define BMPHeaderIDWindows                  MakeShort('B', 'M')
#define BMPHeaderIDOS2StructBitmapArray     MakeShort('B', 'A')
#define BMPHeaderIDOS2StructColorIcon       MakeShort('C', 'I')
#define BMPHeaderIDOS2ConstColorPointer     MakeShort('C', 'P')
#define BMPHeaderIDOS2StructIcon            MakeShort('I', 'C')
#define BMPHeaderIDOS2Pointer               MakeShort('P', 'T')


BMPType ConvertToBMPType(const unsigned short bmpTypeID)
{
    switch(bmpTypeID)
    {
        case BMPHeaderIDOS2StructBitmapArray:
            return BMPOS2StructBitmapArray;

        case BMPHeaderIDWindows:
            return BMPWindows;

        case BMPHeaderIDOS2StructColorIcon:
            return BMPOS2StructColorIcon;

        case BMPHeaderIDOS2ConstColorPointer:
            return BMPOS2ConstColorPointer;

        case BMPHeaderIDOS2StructIcon:
            return BMPOS2StructIcon;

        case BMPHeaderIDOS2Pointer:
            return BMPOS2Pointer;

        default:
            return BMPInvalid;
    }
}

unsigned short ConvertFromBMPType(const BMPType headerType)
{
    switch(headerType)
    {
        default:
        case BMPInvalid:
            return 0;

        case BMPWindows:
            return BMPHeaderIDWindows;

        case BMPOS2StructBitmapArray:
            return BMPHeaderIDOS2StructBitmapArray;

        case BMPOS2StructColorIcon:
            return BMPHeaderIDOS2StructColorIcon;

        case BMPOS2ConstColorPointer:
            return BMPHeaderIDOS2ConstColorPointer;

        case BMPOS2StructIcon:
            return BMPHeaderIDOS2StructIcon;

        case BMPOS2Pointer:
            return BMPHeaderIDOS2Pointer;
    }
}

BMPInfoHeaderType ConvertToBMPInfoHeaderType(const unsigned int infoHeaderType)
{
    switch(infoHeaderType)
    {
        case 12u:
            //const unsigned char bitMapCoreHeaderSize = 12;
            return OS21XBitMapHeader;

        case 16u:
            return OS22XBitMapHeader;

        case 40u:
            return BitMapInfoHeader;

        case 52u:
            return BitMapV2InfoHeader;

        case 56u:
            return BitMapV3InfoHeader;

        case 108u:
            return BitMapV4Header;

        case 124u:
            return BitMapV5Header;

        default:
            return UnkownOrInvalid;
    }
}

unsigned int ConvertFromBMPInfoHeaderType(const BMPInfoHeaderType infoHeaderType)
{
    switch(infoHeaderType)
    {
        default:
        case UnkownOrInvalid:
            return -1;

        case BitMapCoreHeader:
        case OS21XBitMapHeader:
            return 12u;

        case OS22XBitMapHeader:
            return 16u;

        case BitMapInfoHeader:
            return 40u;

        case BitMapV2InfoHeader:
            return 52u;

        case BitMapV3InfoHeader:
            return 56u;

        case BitMapV4Header:
            return 108u;

        case BitMapV5Header:
            return 124u;
    }
}

ActionResult BMPParse(BMP* bmp, const void* data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;

    BMPCreate(bmp);

    *dataRead = 0;

    ParsingStreamConstruct(&parsingStream, data, dataSize);

    //---[ Parsing Header ]----------------------------------------------------
    {
        ClusterInt byteCluster;
        unsigned int sizeOfFile = 0;
        unsigned int reservedBlock = 0;
        unsigned int dataOffset = 0;

        ParsingStreamReadD(&parsingStream, byteCluster.Data, 2u);
        ParsingStreamReadIU(&parsingStream, &sizeOfFile, EndianLittle);
        ParsingStreamReadIU(&parsingStream, &reservedBlock, EndianLittle);
        ParsingStreamReadIU(&parsingStream, &dataOffset, EndianLittle);

        const BMPType type = ConvertToBMPType(byteCluster.Value);

        {
            const unsigned char isValidType = type != BMPInvalid;

            if(!isValidType)
            {
                return ResultInvalidHeaderSignature;
            }
        }

        bmp->Type = type;
    }
    //-------------------------------------------------------------------------

    //---[ DIP ]---------------------------------------------------------------
    {
        ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.HeaderSize, EndianLittle);

        bmp->InfoHeaderType = ConvertToBMPInfoHeaderType(bmp->InfoHeader.HeaderSize);

        switch(bmp->InfoHeaderType)
        {
            case BitMapInfoHeader:
            {
                ParsingStreamReadI(&parsingStream, &bmp->InfoHeader.Width, EndianLittle);
                ParsingStreamReadI(&parsingStream, &bmp->InfoHeader.Height, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp->InfoHeader.NumberOfColorPlanes, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp->InfoHeader.NumberOfBitsPerPixel, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.CompressionMethod, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.ImageSize, EndianLittle);
                ParsingStreamReadI(&parsingStream, &bmp->InfoHeader.HorizontalResolution, EndianLittle);
                ParsingStreamReadI(&parsingStream, &bmp->InfoHeader.VerticalResolution, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.NumberOfColorsInTheColorPalette, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.NumberOfImportantColorsUsed, EndianLittle);

                break;
            }
            case OS21XBitMapHeader:
            case OS22XBitMapHeader:
            {
                unsigned short width = 0;
                unsigned short height = 0;

                ParsingStreamReadSU(&parsingStream, &width, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &height, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp->InfoHeader.NumberOfColorPlanes, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp->InfoHeader.NumberOfBitsPerPixel, EndianLittle);

                bmp->InfoHeader.Width = width;
                bmp->InfoHeader.Height = height;

                if(bmp->InfoHeaderType == OS22XBitMapHeader)
                {
                    unsigned short paddingBytes = 0; // Padding.Ignored and should be zero

                    ParsingStreamReadSU(&parsingStream, &bmp->InfoHeader.HorizontalandVerticalResolutions, EndianLittle);
                    ParsingStreamReadSU(&parsingStream, &paddingBytes, EndianLittle);
                    ParsingStreamReadSU(&parsingStream, &bmp->InfoHeader.DirectionOfBits, EndianLittle);
                    ParsingStreamReadSU(&parsingStream, &bmp->InfoHeader.halftoningAlgorithm, EndianLittle);

                    ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.HalftoningParameterA, EndianLittle);
                    ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.HalftoningParameterB, EndianLittle);
                    ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.ColorEncoding, EndianLittle);
                    ParsingStreamReadIU(&parsingStream, &bmp->InfoHeader.ApplicationDefinedByte, EndianLittle);
                }

                break;
            }
            default:
            {
                // Unkown Header
                return ResultFormatNotSupported;
            }
        }
    }
    //-----------------------------------------------------------

    bmp->PixelDataSize = bmp->InfoHeader.Width * bmp->InfoHeader.Height * (bmp->InfoHeader.NumberOfBitsPerPixel / 8);
    bmp->PixelData = MemoryAllocate(sizeof(unsigned char) * bmp->PixelDataSize);

    // Check if enogh memory
    {
        const unsigned char allocationSucessful = bmp->PixelData;

        if(!allocationSucessful)
        {
            return ResultOutOfMemory;
        }
    }

    //---[ Pixel Data ]--------------------------------------------------------
    const size_t dataRowSize = bmp->InfoHeader.Width * (bmp->InfoHeader.NumberOfBitsPerPixel / 8);
    const size_t fullRowSize = MathFloorD((bmp->InfoHeader.NumberOfBitsPerPixel * bmp->InfoHeader.Width + 31) / 32.0f) * 4;
    const int paddingSUM = (int)fullRowSize - (int)dataRowSize;
    const size_t padding = MathAbsoluteI(paddingSUM);
    size_t amountOfRows = bmp->PixelDataSize / fullRowSize;
    size_t pixelDataOffset = 0;

    while(amountOfRows--)
    {      
        unsigned char* data = bmp->PixelData + pixelDataOffset;

        ParsingStreamReadD(&parsingStream, data, dataRowSize);
        ParsingStreamCursorAdvance(&parsingStream, padding);

        pixelDataOffset += dataRowSize;
    }

    return ResultSuccessful;
}

void BMPCreate(BMP* bmp)
{
    MemorySet(bmp, sizeof(BMP), 0);
}

void BMPDelete(BMP* bmp)
{
    MemoryRelease(bmp->PixelData, bmp->PixelDataSize);

    bmp->PixelData = 0;
    bmp->PixelDataSize = 0;
}