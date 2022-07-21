#include "JPEG.h"

#include <cassert>
#include <stdlib.h>

#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <Container/ClusterShort.h>

#define PNGMarkerStartKey 0xFF
#define PNGMarkerInvalid 0xFF
#define PNGMarkerUnkownTypeCHANGETHIS       MakeShort(PNGMarkerStartKey, 0xC2)
#define PNGMarkerStartOfScan                MakeShort(PNGMarkerStartKey, 0xDA)
#define PNGMarkerStartOfImage               MakeShort(PNGMarkerStartKey, 0xD8)
#define PNGMarkerEndOfImage                 MakeShort(PNGMarkerStartKey, 0xD9)
#define PNGMarkerDefineQuantizationTable    MakeShort(PNGMarkerStartKey, 0xDB)
#define PNGMarkerStartOfFrame               MakeShort(PNGMarkerStartKey, 0xC0)
#define PNGMarkerDefineHuffmanTable         MakeShort(PNGMarkerStartKey, 0xC4)
#define PNGMarkerHeaderFileInfo             MakeShort(PNGMarkerStartKey, 0xE0)

JPEGMarker ConvertToJPEGMarker(const unsigned short jpegMarker)
{
    switch(jpegMarker)
    {
        case PNGMarkerUnkownTypeCHANGETHIS:
            return JPEGMarkerInvalid;

        case PNGMarkerStartOfScan:
            return JPEGMarkerStartOfScan;

        case PNGMarkerStartOfImage:
            return JPEGMarkerStartOfImage;

        case PNGMarkerEndOfImage:
            return JPEGMarkerEndOfImage;

        case PNGMarkerDefineQuantizationTable:
            return JPEGMarkerDefineQuantizationTable;

        case PNGMarkerStartOfFrame:
            return JPEGMarkerStartOfFrame;

        case PNGMarkerDefineHuffmanTable:
            return JPEGMarkerDefineHuffmanTable;

        case PNGMarkerHeaderFileInfo:
            return JPEGMarkerHeaderFileInfo;

        default:
            return JPEGMarkerInvalid;
    }
}

unsigned short ConvertFromJPEGMarker(JPEGMarker jpegMarker)
{
    switch(jpegMarker)
    {
        default:
        case JPEGMarkerInvalid:        return PNGMarkerInvalid;
        case JPEGMarkerStartOfImage: return PNGMarkerEndOfImage;
        case JPEGMarkerHeaderFileInfo:return PNGMarkerHeaderFileInfo;
        case JPEGMarkerStartOfFrame:return PNGMarkerStartOfFrame;
        case JPEGMarkerDefineQuantizationTable:return PNGMarkerDefineQuantizationTable;
        case JPEGMarkerDefineHuffmanTable:return PNGMarkerDefineHuffmanTable;
        case JPEGMarkerStartOfScan:return PNGMarkerStartOfScan;
        case JPEGMarkerEndOfImage:return PNGMarkerEndOfImage;
    }
}

ActionResult JPEGParse(JPEG* jpeg, const void* data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;

    MemorySet(jpeg, sizeof(JPEG), 0);
    *dataRead = 0;
    ParsingStreamConstruct(&parsingStream, data, dataSize);

    // Check Start of Image
    {
        unsigned char startBlock[2];

        ParsingStreamReadD(&parsingStream, startBlock, 2u);

        const JPEGMarker marker = ConvertJPEGMarker(startBlock);
        const unsigned char validStart = marker == JPEGMarkerStartOfImage;

        if(!validStart)
        {
            return ResultInvalidHeaderSignature;
        }
    }

    while(!ParsingStreamIsAtEnd(&parsingStream))
    {
        unsigned char markerData[2];

        ParsingStreamReadD(&parsingStream, markerData, 2u);

        const JPEGMarker marker = ConvertJPEGMarker(markerData);

        switch(marker)
        {
            default:
            case JPEGMarkerInvalid:
            {
                unsigned short length = 0;

                ParsingStreamReadIU(&parsingStream, &length, EndianBig);

                ParsingStreamCursorAdvance(&parsingStream, length - 2);

                break;
            }

            case JPEGMarkerEndOfImage:
            {
                return ResultSuccessful;
            }

            case JPEGMarkerStartOfImage:
            {
                // We read the start tag already. Reading it again is not valid.
                return ResultFormatNotAsExpected;
            }

            case JPEGMarkerStartOfFrame:
            {
                unsigned short length = 0;
                JPEGFrame frame;

                ParsingStreamReadSU(&parsingStream, length, EndianBig);
                ParsingStreamReadSU(&parsingStream, &frame.Precusion, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &frame.LineNb, EndianLittle);
                ParsingStreamReadC(&parsingStream, &frame.LineSamples);
                ParsingStreamReadC(&parsingStream, &frame.ComponentListSize);

                for(size_t i = 0; i < frame.ComponentListSize; ++i)
                {
                    JPEGFrameComponent* frameComponent = &frame.ComponentList[i];
                    unsigned char size = 0;

                    ParsingStreamReadC(&parsingStream, &frameComponent->ID);
                    ParsingStreamReadC(&parsingStream, &size);
                    ParsingStreamReadC(&parsingStream, &frameComponent->Key);

                    frameComponent->Width = (unsigned char)((size & 0b11110000) >> 4u);
                    frameComponent->Height = (unsigned char)(size & 0b00001111);
                }

                break;
            }

            case JPEGMarkerDefineQuantizationTable:
            {
                unsigned short length = 0;
                unsigned char chrominance = 0;
                unsigned char buffer[64];

                ParsingStreamReadSU(&parsingStream, &length, EndianBig);
                ParsingStreamReadCU(&parsingStream, &chrominance);
                ParsingStreamReadD(&parsingStream, buffer, 64);

                break;
            }
            case JPEGMarkerDefineHuffmanTable:
            {
                unsigned short length = 0;
                JPEGHuffmanTable jpegHuffmanTable;

                ParsingStreamReadSU(&parsingStream, &length, EndianBig);
                ParsingStreamReadCU(&parsingStream, &jpegHuffmanTable.Class);
                ParsingStreamReadCU(&parsingStream, &jpegHuffmanTable.Destination);

                ParsingStreamCursorAdvance(&parsingStream, (length - 2) - 2);

                break;
            }
            case JPEGMarkerStartOfScan:
            {
                unsigned short length = 0;

                ParsingStreamReadSU(&parsingStream, &length, EndianBig);
                ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.ScanSelectorSize);

                for(size_t i = 0; i < jpeg->ScanStart.ScanSelectorSize; i++)
                {
                    JPEGScanSelector* scanSelector = &jpeg->ScanStart.ScanSelector[i];
                    unsigned char dcacTable = 0;

                    ParsingStreamReadCU(&parsingStream, scanSelector->Selector);
                    ParsingStreamReadCU(&parsingStream, dcacTable);

                    scanSelector->DC = (unsigned char)((dcacTable & 0b11110000) >> 4u);
                    scanSelector->ACTable = (unsigned char)(dcacTable & 0b00001111);
                }

                ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.SpectralSelectFrom);
                ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.SpectralSelectTo);
                ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.SuccessiveAproximation);

                jpeg->CompressedImageDataSize = ParsingStreamRemainingSize(&parsingStream) -2u;
                jpeg->CompressedImageData = MemoryAllocate(sizeof(unsigned char) * jpeg->CompressedImageDataSize);

                ParsingStreamReadD(&parsingStream, jpeg->CompressedImageData, jpeg->CompressedImageDataSize);

                break;
            }
            case JPEGMarkerHeaderFileInfo:
            {
                ParsingStreamReadSU(&parsingStream, &jpeg->FileInfo.Length, EndianLittle);
                ParsingStreamReadD(&parsingStream, jpeg->FileInfo.Identifier, 5u);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.VersionMajor);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.VersionMinor);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.DensityUnits);
                ParsingStreamReadSU(&parsingStream, &jpeg->FileInfo.DensityX, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &jpeg->FileInfo.DensityY, EndianLittle);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.ThumbnailX);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.ThumbnailY);

                if(jpeg->FileInfo.ThumbnailX > 0 && jpeg->FileInfo.ThumbnailY > 0)
                {
                    jpeg->FileInfo.ThumbnailDataSize = jpeg->FileInfo.ThumbnailX * jpeg->FileInfo.ThumbnailY * 3u;
                    jpeg->FileInfo.ThumbnailData = MemoryAllocate(sizeof(unsigned char) * jpeg->FileInfo.ThumbnailDataSize);

                    ParsingStreamReadD(&parsingStream, jpeg->FileInfo.ThumbnailData, jpeg->FileInfo.ThumbnailDataSize);
                }

                break;
            }
        }
    }

    return ResultInvalid;
}
