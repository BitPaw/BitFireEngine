#include "BMP.h"

#include <Container/ClusterShort.h>
#include <Container/ClusterInt.h>
#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <Math/Math.h>
#include <File/Image.h>

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

    BMPConstruct(bmp);
    ParsingStreamConstruct(&parsingStream, data, dataSize);

    *dataRead = 0;

    //---[ Parsing Header ]----------------------------------------------------
    {
        ClusterShort byteCluster;
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
    BMPImageDataLayout imageDataLayout;
    size_t pixelDataOffset = 0;

    BMPImageDataLayoutCalculate(&imageDataLayout, bmp->InfoHeader.Width, bmp->InfoHeader.Height, bmp->InfoHeader.NumberOfBitsPerPixel);

    while(imageDataLayout.RowAmount--)
    {      
        unsigned char* data = bmp->PixelData + pixelDataOffset;

        pixelDataOffset += ParsingStreamReadD(&parsingStream, data, imageDataLayout.RowImageDataSize);
        ParsingStreamCursorAdvance(&parsingStream, imageDataLayout.RowPaddingSize);
    }

    return ResultSuccessful;
}

ActionResult BMPParseToImage(Image* const image, const void* const data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;
    BMP bmp;
    
    BMPConstruct(&bmp);
    ParsingStreamConstruct(&parsingStream, data, dataSize);

    *dataRead = 0;

    //---[ Parsing Header ]----------------------------------------------------
    {
        ClusterShort byteCluster;
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

        bmp.Type = type;
    }
    //-------------------------------------------------------------------------

    //---[ DIP ]---------------------------------------------------------------
    {
        ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.HeaderSize, EndianLittle);

        bmp.InfoHeaderType = ConvertToBMPInfoHeaderType(bmp.InfoHeader.HeaderSize);

        switch(bmp.InfoHeaderType)
        {
            case BitMapInfoHeader:
            {
                ParsingStreamReadI(&parsingStream, &bmp.InfoHeader.Width, EndianLittle);
                ParsingStreamReadI(&parsingStream, &bmp.InfoHeader.Height, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp.InfoHeader.NumberOfColorPlanes, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp.InfoHeader.NumberOfBitsPerPixel, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.CompressionMethod, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.ImageSize, EndianLittle);
                ParsingStreamReadI(&parsingStream, &bmp.InfoHeader.HorizontalResolution, EndianLittle);
                ParsingStreamReadI(&parsingStream, &bmp.InfoHeader.VerticalResolution, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.NumberOfColorsInTheColorPalette, EndianLittle);
                ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.NumberOfImportantColorsUsed, EndianLittle);

                break;
            }
            case OS21XBitMapHeader:
            case OS22XBitMapHeader:
            {
                unsigned short width = 0;
                unsigned short height = 0;

                ParsingStreamReadSU(&parsingStream, &width, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &height, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp.InfoHeader.NumberOfColorPlanes, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &bmp.InfoHeader.NumberOfBitsPerPixel, EndianLittle);

                bmp.InfoHeader.Width = width;
                bmp.InfoHeader.Height = height;

                if(bmp.InfoHeaderType == OS22XBitMapHeader)
                {
                    unsigned short paddingBytes = 0; // Padding.Ignored and should be zero

                    ParsingStreamReadSU(&parsingStream, &bmp.InfoHeader.HorizontalandVerticalResolutions, EndianLittle);
                    ParsingStreamReadSU(&parsingStream, &paddingBytes, EndianLittle);
                    ParsingStreamReadSU(&parsingStream, &bmp.InfoHeader.DirectionOfBits, EndianLittle);
                    ParsingStreamReadSU(&parsingStream, &bmp.InfoHeader.halftoningAlgorithm, EndianLittle);

                    ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.HalftoningParameterA, EndianLittle);
                    ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.HalftoningParameterB, EndianLittle);
                    ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.ColorEncoding, EndianLittle);
                    ParsingStreamReadIU(&parsingStream, &bmp.InfoHeader.ApplicationDefinedByte, EndianLittle);
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


    // Generate imagedata
    {
        size_t size = image->PixelDataSize = bmp.InfoHeader.Width * bmp.InfoHeader.Height * (bmp.InfoHeader.NumberOfBitsPerPixel / 8);
        void* adress = MemoryAllocate(sizeof(unsigned char) * size);

        if(!adress) // Allocation failed
        {
            return ResultOutOfMemory;
        }

        image->PixelDataSize = size;
        image->PixelData = adress;
        image->Format = ImageDataFormatRGB;
        image->Width = bmp.InfoHeader.Width;
        image->Height = bmp.InfoHeader.Height;
    }

    //---[ Pixel Data ]--------------------------------------------------------
    BMPImageDataLayout imageDataLayout;

    BMPImageDataLayoutCalculate(&imageDataLayout, bmp.InfoHeader.Width, bmp.InfoHeader.Height, bmp.InfoHeader.NumberOfBitsPerPixel);

    while(imageDataLayout.RowAmount--)
    {
        unsigned char* const data = (unsigned char* const)image->PixelData + (imageDataLayout.RowFullSize * imageDataLayout.RowAmount);

        ParsingStreamReadD(&parsingStream, data, imageDataLayout.RowImageDataSize);
        ParsingStreamCursorAdvance(&parsingStream, imageDataLayout.RowPaddingSize);

        for(size_t i = 0; i < imageDataLayout.RowImageDataSize; i += 3)
        {
            const unsigned char swap = data[i]; // Save Blue(current)

            data[i] = data[i + 2]; // Override Blue(current) with Red(new)
            data[i+2] = swap; // Override Red(current) with Blue(new) 
        }
    }

    return ResultSuccessful;
}

ActionResult BMPSerialize(const BMP* const bmp, void* data, const size_t dataSize, size_t* dataWritten)
{
    return ResultSuccessful;
}

ActionResult BMPSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten)
{
    ParsingStream parsingStream;
    BMPInfoHeader bmpInfoHeader;

    ParsingStreamConstruct(&parsingStream, data, dataSize);
    *dataWritten = 0;

    //---<Header>-----
    {
        ClusterShort byteCluster;
        unsigned int sizeOfFile = dataSize;
        unsigned int reservedBlock = 0;
        unsigned int dataOffset = 54u;

        byteCluster.Value = ConvertFromBMPType(BMPWindows);

        ParsingStreamWriteD(&parsingStream, byteCluster.Data, 2u);
        ParsingStreamWriteIU(&parsingStream, sizeOfFile, EndianLittle);
        ParsingStreamWriteIU(&parsingStream, reservedBlock, EndianLittle);
        ParsingStreamWriteIU(&parsingStream, dataOffset, EndianLittle);
    }
    //----------------

    //---<DIP>
    {
        const BMPInfoHeaderType bmpInfoHeaderType = BitMapInfoHeader; 
        
        //---<Shared>---
        bmpInfoHeader.HeaderSize = ConvertFromBMPInfoHeaderType(bmpInfoHeaderType);
        bmpInfoHeader.NumberOfBitsPerPixel = ImageBytePerPixel(image->Format) * 8u;
        bmpInfoHeader.NumberOfColorPlanes = 1;
        bmpInfoHeader.Width = image->Width;
        bmpInfoHeader.Height = image->Height;
        //------------

        //---<BitMapInfoHeader ONLY>-------------------------------------------	
        bmpInfoHeader.CompressionMethod = 0; // [4-Bytes] compression method being used.See the next table for a list of possible values	
        bmpInfoHeader.ImageSize = 0; 	// [4-Bytes] image size.This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
        bmpInfoHeader.HorizontalResolution = 1u;	
        bmpInfoHeader.VerticalResolution = 1u;
        bmpInfoHeader.NumberOfColorsInTheColorPalette = 0;
        bmpInfoHeader.NumberOfImportantColorsUsed = 0;
        //---------------------------------------------------------------------

        ParsingStreamWriteIU(&parsingStream, bmpInfoHeader.HeaderSize, EndianLittle);

        switch (bmpInfoHeaderType)
        {
        case BitMapInfoHeader:
        {
            ParsingStreamWriteI(&parsingStream, bmpInfoHeader.Width, EndianLittle);
            ParsingStreamWriteI(&parsingStream, bmpInfoHeader.Height, EndianLittle);
            ParsingStreamWriteSU(&parsingStream, bmpInfoHeader.NumberOfColorPlanes, EndianLittle);
            ParsingStreamWriteSU(&parsingStream, bmpInfoHeader.NumberOfBitsPerPixel, EndianLittle);
            ParsingStreamWriteIU(&parsingStream, bmpInfoHeader.CompressionMethod, EndianLittle);
            ParsingStreamWriteIU(&parsingStream, bmpInfoHeader.ImageSize, EndianLittle);
            ParsingStreamWriteI(&parsingStream, bmpInfoHeader.HorizontalResolution, EndianLittle);
            ParsingStreamWriteI(&parsingStream, bmpInfoHeader.VerticalResolution, EndianLittle);
            ParsingStreamWriteIU(&parsingStream, bmpInfoHeader.NumberOfColorsInTheColorPalette, EndianLittle);
            ParsingStreamWriteIU(&parsingStream, bmpInfoHeader.NumberOfImportantColorsUsed, EndianLittle);
            break;
        }
        }
    }
    //------------
    
    {
        BMPImageDataLayout imageDataLayout;

        BMPImageDataLayoutCalculate(&imageDataLayout, bmpInfoHeader.Width, bmpInfoHeader.Height, bmpInfoHeader.NumberOfBitsPerPixel);  

        while (imageDataLayout.RowAmount--)
        {
            unsigned char* const dataInsertPoint = (unsigned char* const)image->PixelData + (imageDataLayout.RowFullSize * imageDataLayout.RowAmount);

            for(size_t i = 0; i < imageDataLayout.RowImageDataSize; i += 3) // Will result in RGB Pixel Data
            {
                unsigned char pixelBuffer[3u];

                pixelBuffer[2u] = dataInsertPoint[i]; // Blue
                pixelBuffer[1u] = dataInsertPoint[i+1u]; // Green 
                pixelBuffer[0u] = dataInsertPoint[i+2u]; // Red

                ParsingStreamWriteD(&parsingStream, pixelBuffer, 3u);
            }

            //ParsingStreamWriteD(&parsingStream, dataInsertPoint, imageDataLayout.RowImageDataSize); // Will result in BGR Pixel Data
            ParsingStreamWriteFill(&parsingStream, 0, imageDataLayout.RowPaddingSize);
        }
    }

    *dataWritten = parsingStream.DataCursor;

    return ResultSuccessful;
}

void BMPConstruct(BMP* const bmp)
{
    MemorySet(bmp, sizeof(BMP), 0);
}

void BMPDestruct(BMP* const bmp)
{
    MemoryRelease(bmp->PixelData, bmp->PixelDataSize);

    bmp->PixelData = 0;
    bmp->PixelDataSize = 0;
}

void BMPImageDataLayoutCalculate(BMPImageDataLayout* const bmpImageDataLayout, const size_t width, const size_t height, const size_t bbp)
{
    bmpImageDataLayout->RowImageDataSize = width * (bbp / 8u);
    bmpImageDataLayout->ImageSize = bmpImageDataLayout->RowImageDataSize * height;
    bmpImageDataLayout->RowFullSize = MathFloorD((width * bbp + 31u) / 32.0f) * 4u;
    const int paddingSUM = (int)bmpImageDataLayout->RowFullSize - (int)bmpImageDataLayout->RowImageDataSize;
    bmpImageDataLayout->RowPaddingSize = MathAbsoluteI(paddingSUM);
    bmpImageDataLayout->RowAmount = bmpImageDataLayout->ImageSize / bmpImageDataLayout->RowFullSize;
}

size_t BMPFilePredictSize(const size_t width, const size_t height, const size_t bitsPerPixel)
{
    const size_t sizeBMPHeader = 14u;
    const size_t sizeBMPDIP = 40u;
    const size_t imageDataSize = (MathFloorD((width * bitsPerPixel + 31u) / 32.0f) * 4u) * height;
    const size_t fullSize = sizeBMPHeader + sizeBMPDIP + imageDataSize;

    return fullSize;
}