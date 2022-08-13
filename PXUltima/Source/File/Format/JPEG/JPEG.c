#include "JPEG.h"

#include <cassert>
#include <stdlib.h>

#include <Container/ClusterShort.h>
#include <Memory/Memory.h>
#include <Math/Math.h>
#include <File/ParsingStream.h>
#include <File/BitStream.h>
#include <File/Color.h>

#define JPGDebug 1

#if JPGDebug
#include <stdio.h>
#endif

#define JPEGMarkerInvalidID                                             MakeShort(0xFF, 0xFF)
#define JPEGMarkerStartOfFrameHuffmanBaselineDCTID                      MakeShort(0xFF, 0xC0) 
#define JPEGMarkerStartOfFrameHuffmanSequentialExtendedDCTID            MakeShort(0xFF, 0xC1)
#define JPEGMarkerStartOfFrameHuffmanProgressiveDCTID                   MakeShort(0xFF, 0xC2) 
#define JPEGMarkerStartOfFrameHuffmanSequentialLosslessID               MakeShort(0xFF, 0xC3) 
#define JPEGMarkerDefineHuffmanTableListID                              MakeShort(0xFF, 0xC4) 
#define JPEGMarkerStartOfFrameHuffmanDifferentialSequentialID           MakeShort(0xFF, 0xC5) 
#define JPEGMarkerStartOfFrameHuffmanDifferentialProgressiveDCTID       MakeShort(0xFF, 0xC6) 
#define JPEGMarkerStartOfFrameHuffmanDifferentialLosslessSequentialID   MakeShort(0xFF, 0xC7)
#define JPEGMarkerStartOfFrameArithmeticJPEGExtensionID                 MakeShort(0xFF, 0xC8) 
#define JPEGMarkerStartOfFrameArithmeticExtendedSequentialDCTID         MakeShort(0xFF, 0xC9)
#define JPEGMarkerStartOfFrameArithmeticProgressiveDCTID                  MakeShort(0xFF, 0xCA) 
#define JPEGMarkerStartOfFrameArithmeticLosslessSequentialID              MakeShort(0xFF, 0xCB)
#define JPEGMarkerDefineArithmeticCodingID                                MakeShort(0xFF, 0xCC)
#define JPEGMarkerStartOfFrameArithmeticDifferentialSequentialDCTID       MakeShort(0xFF, 0xCD)
#define JPEGMarkerStartOfFrameArithmeticDifferentialProgressiveDCTID      MakeShort(0xFF, 0xCE) 
#define JPEGMarkerStartOfFrameArithmeticDifferentialLosslessSequentialID  MakeShort(0xFF, 0xCF) 
#define JPEGMarkerIntervalTerminationRestart0ID MakeShort(0xFF, 0xD0) 
#define JPEGMarkerIntervalTerminationRestart1ID MakeShort(0xFF, 0xD1) 
#define JPEGMarkerIntervalTerminationRestart2ID MakeShort(0xFF, 0xD2)
#define JPEGMarkerIntervalTerminationRestart3ID MakeShort(0xFF, 0xD3) 
#define JPEGMarkerIntervalTerminationRestart4ID MakeShort(0xFF, 0xD4) 
#define JPEGMarkerIntervalTerminationRestart5ID MakeShort(0xFF, 0xD5) 
#define JPEGMarkerIntervalTerminationRestart6ID MakeShort(0xFF, 0xD6) 
#define JPEGMarkerIntervalTerminationRestart7ID MakeShort(0xFF, 0xD7)
#define JPEGMarkerStartOfImageID              MakeShort(0xFF, 0xD8) 
#define JPEGMarkerEndOfImageID            MakeShort(0xFF, 0xD9) 
#define JPEGMarkerStartOfScanID           MakeShort(0xFF, 0xDA) 
#define JPEGMarkerDefineQuantizationTableListID MakeShort(0xFF, 0xDB) 
#define JPEGMarkerDefineNumberOfLinesID MakeShort(0xFF, 0xDC) 
#define JPEGMarkerDefineRestartIntervalID             MakeShort(0xFF, 0xDD) 
#define JPEGMarkerDefineHierarchicalProgressionID     MakeShort(0xFF, 0xDE) 
#define JPEGMarkerExpandReferenceComponentListID      MakeShort(0xFF, 0xDF)
#define JPEGMarkerApplicationSegment00ID MakeShort(0xFF, 0xE0) 
#define JPEGMarkerApplicationSegment01ID MakeShort(0xFF, 0xE1) 
#define JPEGMarkerApplicationSegment02ID MakeShort(0xFF, 0xE2) 
#define JPEGMarkerApplicationSegment03ID MakeShort(0xFF, 0xE3) 
#define JPEGMarkerApplicationSegment04ID MakeShort(0xFF, 0xE4)
#define JPEGMarkerApplicationSegment05ID MakeShort(0xFF, 0xE5) 
#define JPEGMarkerApplicationSegment06ID MakeShort(0xFF, 0xE6) 
#define JPEGMarkerApplicationSegment07ID MakeShort(0xFF, 0xE7) 
#define JPEGMarkerApplicationSegment08ID MakeShort(0xFF, 0xE8) 
#define JPEGMarkerApplicationSegment09ID MakeShort(0xFF, 0xE9) 
#define JPEGMarkerApplicationSegment10ID MakeShort(0xFF, 0xEA) 
#define JPEGMarkerApplicationSegment11ID MakeShort(0xFF, 0xEB) 
#define JPEGMarkerApplicationSegment12ID MakeShort(0xFF, 0xEC)
#define JPEGMarkerApplicationSegment13ID MakeShort(0xFF, 0xED) 
#define JPEGMarkerApplicationSegment14ID MakeShort(0xFF, 0xEE) 
#define JPEGMarkerApplicationSegment15ID MakeShort(0xFF, 0xEF) 
#define JPEGMarkerJPEGExtension00ID MakeShort(0xFF, 0xF0) 
#define JPEGMarkerJPEGExtension01ID MakeShort(0xFF, 0xF1) 
#define JPEGMarkerJPEGExtension02ID MakeShort(0xFF, 0xF2)
#define JPEGMarkerJPEGExtension03ID MakeShort(0xFF, 0xF3) 
#define JPEGMarkerJPEGExtension04ID MakeShort(0xFF, 0xF4) 
#define JPEGMarkerJPEGExtension05ID MakeShort(0xFF, 0xF5) 
#define JPEGMarkerJPEGExtension06ID MakeShort(0xFF, 0xF6) 
#define JPEGMarkerJPEGExtension07ID MakeShort(0xFF, 0xF7) 
#define JPEGMarkerJPEGExtension08ID MakeShort(0xFF, 0xF8)
#define JPEGMarkerJPEGExtension09ID MakeShort(0xFF, 0xF9) 
#define JPEGMarkerJPEGExtension10ID MakeShort(0xFF, 0xFA)
#define JPEGMarkerJPEGExtension11ID MakeShort(0xFF, 0xFB) 
#define JPEGMarkerJPEGExtension12ID MakeShort(0xFF, 0xFC) 
#define JPEGMarkerJPEGExtension13ID MakeShort(0xFF, 0xFD) 
#define JPEGMarkerCommentID MakeShort(0xFF, 0xFE)
#define JPEGMarkerTemporaryID MakeShort(0xFF, 0x01) 
#define JPEGMarkerReservedID MakeShort(0xFF, 0x02) 

JPEGMarker ConvertToJPEGMarker(const unsigned short jpegMarker)
{
    switch(jpegMarker)
    {
        case  JPEGMarkerStartOfFrameHuffmanBaselineDCTID: return JPEGMarkerStartOfFrameHuffmanBaselineDCT;
        case  JPEGMarkerStartOfFrameHuffmanSequentialExtendedDCTID: return JPEGMarkerStartOfFrameHuffmanSequentialExtendedDCT;
        case  JPEGMarkerStartOfFrameHuffmanProgressiveDCTID: return JPEGMarkerStartOfFrameHuffmanProgressiveDCT;
        case  JPEGMarkerStartOfFrameHuffmanSequentialLosslessID: return JPEGMarkerStartOfFrameHuffmanSequentialLossless;
        case  JPEGMarkerDefineHuffmanTableListID: return JPEGMarkerDefineHuffmanTableList;
        case  JPEGMarkerStartOfFrameHuffmanDifferentialSequentialID: return JPEGMarkerStartOfFrameHuffmanDifferentialSequential;
        case  JPEGMarkerStartOfFrameHuffmanDifferentialProgressiveDCTID: return JPEGMarkerStartOfFrameHuffmanDifferentialProgressiveDCT;
        case  JPEGMarkerStartOfFrameHuffmanDifferentialLosslessSequentialID: return JPEGMarkerStartOfFrameHuffmanDifferentialLosslessSequential;
        case  JPEGMarkerStartOfFrameArithmeticJPEGExtensionID: return JPEGMarkerStartOfFrameArithmeticJPEGExtension;
        case  JPEGMarkerStartOfFrameArithmeticExtendedSequentialDCTID: return JPEGMarkerStartOfFrameArithmeticExtendedSequentialDCT;
        case  JPEGMarkerStartOfFrameArithmeticProgressiveDCTID: return JPEGMarkerStartOfFrameArithmeticProgressiveDCT;
        case  JPEGMarkerStartOfFrameArithmeticLosslessSequentialID: return JPEGMarkerStartOfFrameArithmeticLosslessSequential;
        case  JPEGMarkerDefineArithmeticCodingID: return JPEGMarkerDefineArithmeticCoding;
        case  JPEGMarkerStartOfFrameArithmeticDifferentialSequentialDCTID: return JPEGMarkerStartOfFrameArithmeticDifferentialSequentialDCT;
        case  JPEGMarkerStartOfFrameArithmeticDifferentialProgressiveDCTID: return JPEGMarkerStartOfFrameArithmeticDifferentialProgressiveDCT;
        case  JPEGMarkerStartOfFrameArithmeticDifferentialLosslessSequentialID: return JPEGMarkerStartOfFrameArithmeticDifferentialLosslessSequential;
        case  JPEGMarkerIntervalTerminationRestart0ID: return JPEGMarkerIntervalTerminationRestart0;
        case  JPEGMarkerIntervalTerminationRestart1ID: return JPEGMarkerIntervalTerminationRestart1;
        case  JPEGMarkerIntervalTerminationRestart2ID: return JPEGMarkerIntervalTerminationRestart2;
        case  JPEGMarkerIntervalTerminationRestart3ID: return JPEGMarkerIntervalTerminationRestart3;
        case  JPEGMarkerIntervalTerminationRestart4ID: return JPEGMarkerIntervalTerminationRestart4;
        case  JPEGMarkerIntervalTerminationRestart5ID: return JPEGMarkerIntervalTerminationRestart5;
        case  JPEGMarkerIntervalTerminationRestart6ID: return JPEGMarkerIntervalTerminationRestart6;
        case  JPEGMarkerIntervalTerminationRestart7ID: return JPEGMarkerIntervalTerminationRestart7;
        case  JPEGMarkerStartOfImageID: return JPEGMarkerStartOfImage;
        case  JPEGMarkerEndOfImageID: return JPEGMarkerEndOfImage;
        case  JPEGMarkerStartOfScanID: return JPEGMarkerStartOfScan;
        case  JPEGMarkerDefineQuantizationTableListID: return JPEGMarkerDefineQuantizationTableList;
        case  JPEGMarkerDefineNumberOfLinesID: return JPEGMarkerDefineNumberOfLines;
        case  JPEGMarkerDefineRestartIntervalID: return JPEGMarkerDefineRestartInterval;
        case  JPEGMarkerDefineHierarchicalProgressionID: return JPEGMarkerDefineHierarchicalProgression;
        case  JPEGMarkerExpandReferenceComponentListID: return JPEGMarkerExpandReferenceComponentList;
        case  JPEGMarkerApplicationSegment00ID: return JPEGMarkerApplicationSegment00;
        case  JPEGMarkerApplicationSegment01ID: return JPEGMarkerApplicationSegment01;
        case  JPEGMarkerApplicationSegment02ID: return JPEGMarkerApplicationSegment02;
        case  JPEGMarkerApplicationSegment03ID: return JPEGMarkerApplicationSegment03;
        case  JPEGMarkerApplicationSegment04ID: return JPEGMarkerApplicationSegment04;
        case  JPEGMarkerApplicationSegment05ID: return JPEGMarkerApplicationSegment05;
        case  JPEGMarkerApplicationSegment06ID: return JPEGMarkerApplicationSegment06;
        case  JPEGMarkerApplicationSegment07ID: return JPEGMarkerApplicationSegment07;
        case  JPEGMarkerApplicationSegment08ID: return JPEGMarkerApplicationSegment08;
        case  JPEGMarkerApplicationSegment09ID: return JPEGMarkerApplicationSegment09;
        case  JPEGMarkerApplicationSegment10ID: return JPEGMarkerApplicationSegment10;
        case  JPEGMarkerApplicationSegment11ID: return JPEGMarkerApplicationSegment11;
        case  JPEGMarkerApplicationSegment12ID: return JPEGMarkerApplicationSegment12;
        case  JPEGMarkerApplicationSegment13ID: return JPEGMarkerApplicationSegment13;
        case  JPEGMarkerApplicationSegment14ID: return JPEGMarkerApplicationSegment14;
        case  JPEGMarkerApplicationSegment15ID: return JPEGMarkerApplicationSegment15;
        case  JPEGMarkerJPEGExtension00ID: return JPEGMarkerJPEGExtension00;
        case  JPEGMarkerJPEGExtension01ID: return JPEGMarkerJPEGExtension01;
        case  JPEGMarkerJPEGExtension02ID: return JPEGMarkerJPEGExtension02;
        case  JPEGMarkerJPEGExtension03ID: return JPEGMarkerJPEGExtension03;
        case  JPEGMarkerJPEGExtension04ID: return JPEGMarkerJPEGExtension04;
        case  JPEGMarkerJPEGExtension05ID: return JPEGMarkerJPEGExtension05;
        case  JPEGMarkerJPEGExtension06ID: return JPEGMarkerJPEGExtension06;
        case  JPEGMarkerJPEGExtension07ID: return JPEGMarkerJPEGExtension07;
        case  JPEGMarkerJPEGExtension08ID: return JPEGMarkerJPEGExtension08;
        case  JPEGMarkerJPEGExtension09ID: return JPEGMarkerJPEGExtension09;
        case  JPEGMarkerJPEGExtension10ID: return JPEGMarkerJPEGExtension10;
        case  JPEGMarkerJPEGExtension11ID: return JPEGMarkerJPEGExtension11;
        case  JPEGMarkerJPEGExtension12ID: return JPEGMarkerJPEGExtension12;
        case  JPEGMarkerJPEGExtension13ID: return JPEGMarkerJPEGExtension13;
        case  JPEGMarkerCommentID: return JPEGMarkerComment;
        case  JPEGMarkerTemporaryID: return JPEGMarkerTemporary;
        case  JPEGMarkerReservedID: return JPEGMarkerReserved;

        default:
            return JPEGMarkerInvalid;
    }
}

unsigned short ConvertFromJPEGMarker(const JPEGMarker jpegMarker)
{
    switch(jpegMarker)
    {
        case  JPEGMarkerStartOfFrameHuffmanBaselineDCT: return JPEGMarkerStartOfFrameHuffmanBaselineDCTID;
        case  JPEGMarkerStartOfFrameHuffmanSequentialExtendedDCT: return JPEGMarkerStartOfFrameHuffmanSequentialExtendedDCTID;
        case  JPEGMarkerStartOfFrameHuffmanProgressiveDCT: return JPEGMarkerStartOfFrameHuffmanProgressiveDCTID;
        case  JPEGMarkerStartOfFrameHuffmanSequentialLossless: return JPEGMarkerStartOfFrameHuffmanSequentialLosslessID;
        case  JPEGMarkerDefineHuffmanTableList: return JPEGMarkerDefineHuffmanTableListID;
        case  JPEGMarkerStartOfFrameHuffmanDifferentialSequential: return JPEGMarkerStartOfFrameHuffmanDifferentialSequentialID;
        case  JPEGMarkerStartOfFrameHuffmanDifferentialProgressiveDCT: return JPEGMarkerStartOfFrameHuffmanDifferentialProgressiveDCTID;
        case  JPEGMarkerStartOfFrameHuffmanDifferentialLosslessSequential: return JPEGMarkerStartOfFrameHuffmanDifferentialLosslessSequentialID;
        case  JPEGMarkerStartOfFrameArithmeticJPEGExtension: return JPEGMarkerStartOfFrameArithmeticJPEGExtensionID;
        case  JPEGMarkerStartOfFrameArithmeticExtendedSequentialDCT: return JPEGMarkerStartOfFrameArithmeticExtendedSequentialDCTID;
        case  JPEGMarkerStartOfFrameArithmeticProgressiveDCT: return JPEGMarkerStartOfFrameArithmeticProgressiveDCTID;
        case  JPEGMarkerStartOfFrameArithmeticLosslessSequential: return JPEGMarkerStartOfFrameArithmeticLosslessSequentialID;
        case  JPEGMarkerDefineArithmeticCoding: return JPEGMarkerDefineArithmeticCodingID;
        case  JPEGMarkerStartOfFrameArithmeticDifferentialSequentialDCT: return JPEGMarkerStartOfFrameArithmeticDifferentialSequentialDCTID;
        case  JPEGMarkerStartOfFrameArithmeticDifferentialProgressiveDCT: return JPEGMarkerStartOfFrameArithmeticDifferentialProgressiveDCTID;
        case  JPEGMarkerStartOfFrameArithmeticDifferentialLosslessSequential: return JPEGMarkerStartOfFrameArithmeticDifferentialLosslessSequentialID;
        case  JPEGMarkerIntervalTerminationRestart0: return JPEGMarkerIntervalTerminationRestart0ID;
        case  JPEGMarkerIntervalTerminationRestart1: return JPEGMarkerIntervalTerminationRestart1ID;
        case  JPEGMarkerIntervalTerminationRestart2: return JPEGMarkerIntervalTerminationRestart2ID;
        case  JPEGMarkerIntervalTerminationRestart3: return JPEGMarkerIntervalTerminationRestart3ID;
        case  JPEGMarkerIntervalTerminationRestart4: return JPEGMarkerIntervalTerminationRestart4ID;
        case  JPEGMarkerIntervalTerminationRestart5: return JPEGMarkerIntervalTerminationRestart5ID;
        case  JPEGMarkerIntervalTerminationRestart6: return JPEGMarkerIntervalTerminationRestart6ID;
        case  JPEGMarkerIntervalTerminationRestart7: return JPEGMarkerIntervalTerminationRestart7ID;
        case  JPEGMarkerStartOfImage: return JPEGMarkerStartOfImageID;
        case  JPEGMarkerEndOfImage: return JPEGMarkerEndOfImageID;
        case  JPEGMarkerStartOfScan: return JPEGMarkerStartOfScanID;
        case  JPEGMarkerDefineQuantizationTableList: return JPEGMarkerDefineQuantizationTableListID;
        case  JPEGMarkerDefineNumberOfLines: return JPEGMarkerDefineNumberOfLinesID;
        case  JPEGMarkerDefineRestartInterval: return JPEGMarkerDefineRestartIntervalID;
        case  JPEGMarkerDefineHierarchicalProgression: return JPEGMarkerDefineHierarchicalProgressionID;
        case  JPEGMarkerExpandReferenceComponentList: return JPEGMarkerExpandReferenceComponentListID;
        case  JPEGMarkerApplicationSegment00: return JPEGMarkerApplicationSegment00ID;
        case  JPEGMarkerApplicationSegment01: return JPEGMarkerApplicationSegment01ID;
        case  JPEGMarkerApplicationSegment02: return JPEGMarkerApplicationSegment02ID;
        case  JPEGMarkerApplicationSegment03: return JPEGMarkerApplicationSegment03ID;
        case  JPEGMarkerApplicationSegment04: return JPEGMarkerApplicationSegment04ID;
        case  JPEGMarkerApplicationSegment05: return JPEGMarkerApplicationSegment05ID;
        case  JPEGMarkerApplicationSegment06: return JPEGMarkerApplicationSegment06ID;
        case  JPEGMarkerApplicationSegment07: return JPEGMarkerApplicationSegment07ID;
        case  JPEGMarkerApplicationSegment08: return JPEGMarkerApplicationSegment08ID;
        case  JPEGMarkerApplicationSegment09: return JPEGMarkerApplicationSegment09ID;
        case  JPEGMarkerApplicationSegment10: return JPEGMarkerApplicationSegment10ID;
        case  JPEGMarkerApplicationSegment11: return JPEGMarkerApplicationSegment11ID;
        case  JPEGMarkerApplicationSegment12: return JPEGMarkerApplicationSegment12ID;
        case  JPEGMarkerApplicationSegment13: return JPEGMarkerApplicationSegment13ID;
        case  JPEGMarkerApplicationSegment14: return JPEGMarkerApplicationSegment14ID;
        case  JPEGMarkerApplicationSegment15: return JPEGMarkerApplicationSegment15ID;
        case  JPEGMarkerJPEGExtension00: return JPEGMarkerJPEGExtension00ID;
        case  JPEGMarkerJPEGExtension01: return JPEGMarkerJPEGExtension01ID;
        case  JPEGMarkerJPEGExtension02: return JPEGMarkerJPEGExtension02ID;
        case  JPEGMarkerJPEGExtension03: return JPEGMarkerJPEGExtension03ID;
        case  JPEGMarkerJPEGExtension04: return JPEGMarkerJPEGExtension04ID;
        case  JPEGMarkerJPEGExtension05: return JPEGMarkerJPEGExtension05ID;
        case  JPEGMarkerJPEGExtension06: return JPEGMarkerJPEGExtension06ID;
        case  JPEGMarkerJPEGExtension07: return JPEGMarkerJPEGExtension07ID;
        case  JPEGMarkerJPEGExtension08: return JPEGMarkerJPEGExtension08ID;
        case  JPEGMarkerJPEGExtension09: return JPEGMarkerJPEGExtension09ID;
        case  JPEGMarkerJPEGExtension10: return JPEGMarkerJPEGExtension10ID;
        case  JPEGMarkerJPEGExtension11: return JPEGMarkerJPEGExtension11ID;
        case  JPEGMarkerJPEGExtension12: return JPEGMarkerJPEGExtension12ID;
        case  JPEGMarkerJPEGExtension13: return JPEGMarkerJPEGExtension13ID;
        case  JPEGMarkerComment: return JPEGMarkerCommentID;
        case  JPEGMarkerTemporary: return JPEGMarkerTemporaryID;
        case  JPEGMarkerReserved: return JPEGMarkerReservedID;

        case JPEGMarkerInvalid:
        default:
            return JPEGMarkerInvalidID;
    }
}

size_t JPEGFilePredictSize(const size_t width, const size_t height, const size_t bbp)
{
    const size_t beginning = 2;
    const size_t end = 2;
    const size_t app0 = 20;

    const size_t sum = beginning + end + app0 + (height*width*3u);

    return sum;
}

void JPEGConstruct(JPEG* jpeg)
{
    MemorySet(jpeg, sizeof(JPEG), 0);
}

void JPEGDestruct(JPEG* jpeg)
{

}

ActionResult JPEGParseToImage(Image* const image, const void* data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;
    JPEG jpeXg;
    JPEG* jpeg = &jpeXg;

    ParsingStreamConstruct(&parsingStream, data, dataSize);
    JPEGConstruct(jpeg);
    *dataRead = 0;

    // Check Start of Image
    {
        ClusterShort startBlock;

        ParsingStreamReadD(&parsingStream, startBlock.Data, 2u);

        const JPEGMarker marker = ConvertToJPEGMarker(startBlock.Value);
        const unsigned char validStart = marker == JPEGMarkerStartOfImage;

        if(!validStart)
        {
            return ResultInvalidHeaderSignature;
        }

#if JPGDebug
        printf("[i][JPG] Start of Image\n");
#endif
    }

    while(!ParsingStreamIsAtEnd(&parsingStream))
    {
        JPEGMarker chunkMarker = JPEGMarkerInvalid;
        unsigned short chunkLength = -1;
        size_t expectedOffset = -1;

        // Parse info
        {
            ClusterShort markerData;

            ParsingStreamReadD(&parsingStream, markerData.Data, 2u);  

            chunkMarker = ConvertToJPEGMarker(markerData.Value);

            if(chunkMarker == JPEGMarkerEndOfImage)
            {
#if JPGDebug
                printf("[i][JPG] End of Image\n");
#endif

                return ResultSuccessful;
            }

            ParsingStreamReadSU(&parsingStream, &chunkLength, EndianBig);
          
            chunkLength -= 2u; // dont count header

            expectedOffset = parsingStream.DataCursor + chunkLength;

#if JPGDebug

            unsigned int percentage = (parsingStream.DataCursor / (float)parsingStream.DataSize) * 100;

            printf("\n[i][JPG] Chunk <%2x%2x> deteced. Size:%i Bytes (Parsed : %i%%)\n", markerData.A, markerData.B, chunkLength, percentage);
#endif
        }

        switch(chunkMarker)
        {          
            case JPEGMarkerStartOfImage:
            {
                // We read the start tag already. Reading it again is not valid.
                return ResultFormatNotAsExpected;
            }

            case JPEGMarkerStartOfFrameHuffmanBaselineDCT:
            {
                JPEGFrame frame;

                ParsingStreamReadCU(&parsingStream, &frame.Precision, EndianBig);
                ParsingStreamReadSU(&parsingStream, &frame.Height, EndianBig);
                ParsingStreamReadSU(&parsingStream, &frame.Width, EndianBig);
                ParsingStreamReadCU(&parsingStream, &frame.ComponentListSize);

                for(size_t i = 0; i < frame.ComponentListSize; ++i)
                {
                    JPEGFrameComponent* frameComponent = &frame.ComponentList[i];
                    unsigned char samplingFactor = 0;

                    ParsingStreamReadC(&parsingStream, &frameComponent->ID);
                    ParsingStreamReadC(&parsingStream, &samplingFactor);
                    ParsingStreamReadC(&parsingStream, &frameComponent->QuantizationTableID);

                    frameComponent->SamplingFactorHorizonal = ((samplingFactor & 0b11110000) >> 4u);
                    frameComponent->SamplingFactorVertical = (samplingFactor & 0b00001111);
                }

#if JPGDebug
                printf
                (
                    "[i][JPG] Start of Frame (DCT Baseline)\n"
                    " | Precision  : %3i |\n"
                    " | Size       : %i, %i |\n"
                    " | Components : %3i |\n",
                    frame.Precision,
                    frame.Width,
                    frame.Height,                  
                    frame.ComponentListSize                
                );
#endif

                break;
            }
            case JPEGMarkerDefineQuantizationTableList:
            {
                size_t remainingBytes = chunkLength;

                while(remainingBytes)
                {

                    unsigned char precision = 0;
                    unsigned char matixID = 0;

                    {
                        unsigned char cluster = 0;

                        remainingBytes -= ParsingStreamReadCU(&parsingStream, &cluster);

                        precision = (cluster & 0b11110000) >> 4;
                        matixID = (cluster & 0b00001111);
                    }

                    unsigned char* matrixAdress = jpeg->QuantizationTable[matixID];

                    remainingBytes -= ParsingStreamReadD(&parsingStream, matrixAdress, 64u);

#if JPGDebug
                    printf("[i][JPG] Define Quantization Table <%i>\n", matixID);



                    for(size_t y = 0; y < 8u; ++y)
                    {
                        printf("|");

                        for(size_t x = 0; x < 8u; ++x)
                        {
                            printf("%3i |", matrixAdress[y * 8u + x]);
                        }

                        printf("\n");
                    }
#endif   
                }    

                break;



            }
            case JPEGMarkerDefineHuffmanTableList:
            {
                size_t remainingBytes = chunkLength;

                while(remainingBytes)
                {
                    JPEGHuffmanTable jpegHuffmanTable;

                    {
                        unsigned char huffmanTableInfo;

                        remainingBytes -= ParsingStreamReadCU(&parsingStream, &huffmanTableInfo);

                        jpegHuffmanTable.ID = (huffmanTableInfo & 0b00001111);
                        jpegHuffmanTable.Type = (huffmanTableInfo & 0b00010000) >> 4u;
                        // unused 0b11100000
                    }
#if JPGDebug
                    printf
                    (
                        "[i][JPG] Define Huffman table\n"
                        " | ID   : %2i \n"
                        " | Type : %2i \n",
                        jpegHuffmanTable.ID,
                        jpegHuffmanTable.Type
                    );
#endif

                    size_t symbolSum = 0;

                    // 16 Bytes symbopls
                    // 
                    for(size_t i = 0; i < 16u; ++i)
                    {
                        unsigned char symbol = 0;

                        remainingBytes -= ParsingStreamReadCU(&parsingStream, &symbol);

#if JPGDebug
                        printf
                        (
                            " | Symbol length <%zi>\n",
                            symbol
                        );
#endif

                        symbolSum += symbol;
                    }

#if JPGDebug
                    printf
                    (
                        " | Symbol sum <%zi>\n",
                        symbolSum
                    );
#endif


                    // n bytes from that data
                    for(size_t i = 0; i < symbolSum; ++i)
                    {
                        unsigned char symbol = 0;

                        remainingBytes -= ParsingStreamReadCU(&parsingStream, &symbol);

#if JPGDebug
                        printf
                        (
                            " | Symbol <%i>\n",
                            symbol
                        );
#endif

                        // Save?
                    }

                }
                break;
            }
            case JPEGMarkerStartOfScan:
            {
                ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.ScanSelectorSize);

                for(size_t i = 0; i < jpeg->ScanStart.ScanSelectorSize; ++i)
                {
                    JPEGScanSelector* scanSelector = &jpeg->ScanStart.ScanSelector[i];
                    unsigned char huffmanTableUsed = 0;

                    ParsingStreamReadCU(&parsingStream, &scanSelector->ID);
                    ParsingStreamReadCU(&parsingStream, &huffmanTableUsed);

                    scanSelector->DC = ((huffmanTableUsed & 0b11110000) >> 4u);
                    scanSelector->ACTable = (huffmanTableUsed & 0b00001111);
                }

                ParsingStreamCursorAdvance(&parsingStream, 3u); // mandatorily to skip these, why?

                // Compressed image data starts here --------------------------------

                //ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.SpectralSelectFrom);
                //ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.SpectralSelectTo);
                //ParsingStreamReadCU(&parsingStream, &jpeg->ScanStart.SuccessiveAproximation);

                //jpeg->CompressedImageDataSize = ParsingStreamRemainingSize(&parsingStream) - 2u;
                //jpeg->CompressedImageData = MemoryAllocate(sizeof(unsigned char) * jpeg->CompressedImageDataSize);

                //ParsingStreamReadD(&parsingStream, jpeg->CompressedImageData, jpeg->CompressedImageDataSize);

                const size_t imageDataSize = ParsingStreamRemainingSize(&parsingStream) - 2u;

                // Correct expected offset, as the "chunk length" seems to be only considering the data iself and not the whole chunk.

                expectedOffset += imageDataSize;

#if JPGDebug
                printf
                (
                    "[i][JPG] Start of Scan...\n"
                    " - Image Data <%i> Bytes\n",
                    imageDataSize
                );
#endif
                ParsingStreamCursorAdvance(&parsingStream, imageDataSize);

                break;
            }
            case JPEGMarkerApplicationSegment00:
            {
                char identifier[5];

                ParsingStreamReadD(&parsingStream, identifier, 5u);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.VersionMajor);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.VersionMinor);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.DensityUnits);
                ParsingStreamReadSU(&parsingStream, &jpeg->FileInfo.DensityX, EndianLittle);
                ParsingStreamReadSU(&parsingStream, &jpeg->FileInfo.DensityY, EndianLittle);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.ThumbnailX);
                ParsingStreamReadCU(&parsingStream, &jpeg->FileInfo.ThumbnailY);

#if JPGDebug
                printf
                (
                    "[i][JPG] Header Info\n"
                    " | Identifier   : %8s |\n"
                    " | Version      : %3i, %3i |\n"
                    " | Density Unit : %8i |\n"
                    " | Density      : %3i, %3i |\n"
                    " | Thumbnail    : %3i, %3i |\n",
                    identifier,
                    jpeg->FileInfo.VersionMajor,
                    jpeg->FileInfo.VersionMinor,
                    jpeg->FileInfo.DensityUnits,
                    jpeg->FileInfo.DensityX,
                    jpeg->FileInfo.DensityY,
                    jpeg->FileInfo.ThumbnailX,
                    jpeg->FileInfo.ThumbnailY
                );
#endif

                // Load Thumbnail
                {
                    const unsigned char hasThumbnail = jpeg->FileInfo.ThumbnailX > 0 && jpeg->FileInfo.ThumbnailY > 0;

                    if(hasThumbnail)
                    {
                        jpeg->FileInfo.ThumbnailDataSize = jpeg->FileInfo.ThumbnailX * jpeg->FileInfo.ThumbnailY * 3u;
                        jpeg->FileInfo.ThumbnailData = MemoryAllocate(sizeof(unsigned char) * jpeg->FileInfo.ThumbnailDataSize);

                        ParsingStreamReadD(&parsingStream, jpeg->FileInfo.ThumbnailData, jpeg->FileInfo.ThumbnailDataSize);
                    }
                }        

                break;
            }
            case JPEGMarkerComment:
            {
                jpeg->CommentSize = chunkLength;
                jpeg->Comment = MemoryAllocate(sizeof(char) * chunkLength);

                ParsingStreamReadD(&parsingStream, jpeg->Comment, chunkLength);

                break;
            }
        }

#if JPGDebug
        if(parsingStream.DataCursor != expectedOffset)
        {
            printf("[!][JPG] Chunk has unhandled data! Skipping <%zi> Bytes\n", expectedOffset - parsingStream.DataCursor);
        }
#endif
        //--<Allign>----
        parsingStream.DataCursor = expectedOffset;
        //--------------
    }

    return ResultSuccessful;
}

ActionResult JPEGParse(JPEG* jpeg, const void* data, const size_t dataSize, size_t* dataRead)
{
    

    return ResultInvalid;
}















    // ////////////////////////////////////////
    // data types (for internal use only)

    // one byte
    typedef unsigned char   uint8_t;
    // two bytes
    typedef unsigned short uint16_t;
    typedef          short  int16_t;
    // four bytes (or more)
    typedef          int    int32_t;

    // ////////////////////////////////////////
    // basic structs (for internal use only)

    // represent a few bits, typically a Huffman code
    typedef struct BitCode_
    {
       // BitCode() {}       // undefined state, must be initialized at a later time
       // BitCode(uint16_t code_, uint8_t numBits_) : code(code_), numBits(numBits_) {}
        uint16_t code;     // JPEG's Huffman codes are limited to 16 bits
        uint8_t  numBits;  // actual number of bits
    }BitCode;



    // store the most recently encoded bits that are not written yet
    typedef struct BitBuffer_
    {
       // BitBuffer()        // actually, there will be only one instance of this object
        //    : bits(0), numBits(0) {}
        int32_t bits;      // actually only at most 24 bits are used
        uint8_t numBits;   // number of valid bits (the right-most bits)
    }BitBuffer;

    // ////////////////////////////////////////
    // constants (for internal use only)

    // quantization tables from JPEG Standard, Annex K
    // there are a few experts proposing slightly more efficient values, e.g. https://www.imagemagick.org/discourse-server/viewtopic.php?t=20333
    // btw: Google's Guetzli project optimizes the quantization tables per image
    const unsigned char DefaultQuantLuminance[8 * 8] =
    { 16, 11, 10, 16, 24, 40, 51, 61,
      12, 12, 14, 19, 26, 58, 60, 55,
      14, 13, 16, 24, 40, 57, 69, 56,
      14, 17, 22, 29, 51, 87, 80, 62,
      18, 22, 37, 56, 68,109,103, 77,
      24, 35, 55, 64, 81,104,113, 92,
      49, 64, 78, 87,103,121,120,101,
      72, 92, 95, 98,112,100,103, 99 };
    const unsigned char DefaultQuantChrominance[8 * 8] =
    { 17, 18, 24, 47, 99, 99, 99, 99,
      18, 21, 26, 66, 99, 99, 99, 99,
      24, 26, 56, 99, 99, 99, 99, 99,
      47, 66, 99, 99, 99, 99, 99, 99,
      99, 99, 99, 99, 99, 99, 99, 99,
      99, 99, 99, 99, 99, 99, 99, 99,
      99, 99, 99, 99, 99, 99, 99, 99,
      99, 99, 99, 99, 99, 99, 99, 99 };

    // 8x8 blocks are processed in zig-zag order
    // most encoders use a zig-zag table, I switched to its inverse for performance reasons
    // note: ZigZagInv[ZigZag[i]] = i
    const uint8_t ZigZagInv[8 * 8] =
    { 0, 1, 8,16, 9, 2, 3,10,   // ZigZag[] =  0, 1, 5, 6,14,15,27,28,
      17,24,32,25,18,11, 4, 5,   //             2, 4, 7,13,16,26,29,42,
      12,19,26,33,40,48,41,34,   //             3, 8,12,17,25,30,41,43,
      27,20,13, 6, 7,14,21,28,   //             9,11,18,24,31,40,44,53,
      35,42,49,56,57,50,43,36,   //            10,19,23,32,39,45,52,54,
      29,22,15,23,30,37,44,51,   //            20,22,33,38,46,51,55,60,
      58,59,52,45,38,31,39,46,   //            21,34,37,47,50,56,59,61,
      53,60,61,54,47,55,62,63 }; //            35,36,48,49,57,58,62,63

// some constants for our DCT
    #define SqrtHalfSqrt 1.306562965f // sqrt((2 + sqrt(2)) / 2)  = cos(pi * 1 / 8) * sqrt(2)
#define HalfSqrtSqrt  0.382683432f // sqrt( 2 - sqrt(2)) / 2   = cos(pi * 3 / 8)
#define InvSqrt 0.707106781f // 1 / sqrt(2)              = cos(pi * 2 / 8)
#define InvSqrtSqrt 0.541196100f // 1 / sqrt(2 - sqrt(2))    = cos(pi * 3 / 8) * sqrt(2)
    // scaling constants for AAN DCT algorithm: AanScaleFactors[0] = 1, AanScaleFactors[k=1..7] = cos(k*PI/16) * sqrt(2)
    const float AanScaleFactors[8] = { 1, 1.387039845f, SqrtHalfSqrt, 1.175875602f, 1, 0.785694958f, InvSqrtSqrt, 0.275899379f };

    // use Huffman code tables recommended by the JPEG standard Annex K
    // - they work quite well for most images but are not optimal
    // - CodesPerBitsize tables define how many Huffman codes will have a certain bitsize (plus 1),
    //   e.g. DcLuminanceCodesPerBitsize[2] = 5 because there are 5 Huffman codes being 2+1=3 bits long
    // - Values tables are a list of values ordered by their Huffman code bitsize,
    //   e.g. AcLuminanceValues => Huffman(0x01,0x02,0x03) will have 2 bits, Huffman(0x00) will have 3 bits, Huffman(0x04,0x11,0x05) will have 4 bits, ...

    // Huffman definitions for first DC/AC tables (luminance / Y channel)
    const uint8_t DcLuminanceCodesPerBitsize[16] = { 0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0 };   // sum = 12
    const uint8_t DcLuminanceValues[12] = { 0,1,2,3,4,5,6,7,8,9,10,11 };         // => 12 codes
    const uint8_t AcLuminanceCodesPerBitsize[16] = { 0,2,1,3,3,2,4,3,5,5,4,4,0,0,1,125 }; // sum = 162
    const uint8_t AcLuminanceValues[162] =                                        // => 162 codes
    { 0x01,0x02,0x03,0x00,0x04,0x11,0x05,0x12,0x21,0x31,0x41,0x06,0x13,0x51,0x61,0x07,0x22,0x71,0x14,0x32,0x81,0x91,0xA1,0x08, // 16*10+2 because
      0x23,0x42,0xB1,0xC1,0x15,0x52,0xD1,0xF0,0x24,0x33,0x62,0x72,0x82,0x09,0x0A,0x16,0x17,0x18,0x19,0x1A,0x25,0x26,0x27,0x28, // upper 4 bits can be 0..F
      0x29,0x2A,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x53,0x54,0x55,0x56,0x57,0x58,0x59, // while lower 4 bits can be 1..A
      0x5A,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x83,0x84,0x85,0x86,0x87,0x88,0x89, // plus two special codes 0x00 and 0xF0
      0x8A,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xB2,0xB3,0xB4,0xB5,0xB6, // order of these symbols was determined empirically by JPEG committee
      0xB7,0xB8,0xB9,0xBA,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xE1,0xE2,
      0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA };
    // Huffman definitions for second DC/AC tables (chrominance / Cb and Cr channels)
    const uint8_t DcChrominanceCodesPerBitsize[16] = { 0,3,1,1,1,1,1,1,1,1,1,0,0,0,0,0 };   // sum = 12
    const uint8_t DcChrominanceValues[12] = { 0,1,2,3,4,5,6,7,8,9,10,11 };         // => 12 codes (identical to DcLuminanceValues)
    const uint8_t AcChrominanceCodesPerBitsize[16] = { 0,2,1,2,4,4,3,4,7,5,4,4,0,1,2,119 }; // sum = 162
    const uint8_t AcChrominanceValues[162] =                                        // => 162 codes
    { 0x00,0x01,0x02,0x03,0x11,0x04,0x05,0x21,0x31,0x06,0x12,0x41,0x51,0x07,0x61,0x71,0x13,0x22,0x32,0x81,0x08,0x14,0x42,0x91, // same number of symbol, just different order
      0xA1,0xB1,0xC1,0x09,0x23,0x33,0x52,0xF0,0x15,0x62,0x72,0xD1,0x0A,0x16,0x24,0x34,0xE1,0x25,0xF1,0x17,0x18,0x19,0x1A,0x26, // (which is more efficient for AC coding)
      0x27,0x28,0x29,0x2A,0x35,0x36,0x37,0x38,0x39,0x3A,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x53,0x54,0x55,0x56,0x57,0x58,
      0x59,0x5A,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x82,0x83,0x84,0x85,0x86,0x87,
      0x88,0x89,0x8A,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xB2,0xB3,0xB4,
      0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,
      0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA };

    // ////////////////////////////////////////
    // helper functions / templates


    // write bits stored in BitCode, keep excess bits in BitBuffer
    void writeBits(ParsingStream* parsingStream, BitBuffer* buffer, BitCode data)
    {
        // append the new bits to those bits leftover from previous call(s)
        buffer->numBits += data.numBits;
        buffer->bits <<= data.numBits;
        buffer->bits |= data.code;

        // write all "full" bytes
        while (buffer->numBits >= 8)
        {
            // extract highest 8 bits
            buffer->numBits -= 8;
            auto oneByte = (buffer->bits >> buffer->numBits) & 0xFF;
            ParsingStreamWriteCU(parsingStream, oneByte);

            if (oneByte == 0xFF) // 0xFF has a special meaning for JPEGs (it's a block marker)
                ParsingStreamWriteCU(parsingStream, 0);         // therefore pad a zero to indicate "nope, this one ain't a marker, it's just a coincidence"

              // note: I don't clear those written bits, therefore buffer.bits contains garbage in the high bits
              //       if you really want to "clean up" (e.g. for debugging purposes) then uncomment the following line
              //buffer.bits &= (1 << buffer.numBits) - 1;
        }
    }

    // convert to a JPEG codeword
    void convertCode(BitCode* bitCode, int value)
    {
        // positive value: code = value,     numBits = position of highest set bit
        // negative value: ignore sign, then numBits = position of highest set bit, and code = (2^numBits) - 1 + value
        int absolute = value >= 0 ? +value : -value; // by the way: value is never zero
        int mask = 0;       // will be 2^numBits - 1
        // find position of highest set bit, fast way for GCC: result.numBits = 32 - __builtin_clz(value);
        int numBits = 0;
        while (absolute > mask)
        {
            numBits++;
            mask = 2 * mask + 1; // append a set bit (numBits increased by one, so we need to update 2^numBits - 1)
        }

        // remember: mask = 2^numBits - 1, so if the original value was negative we can cheaply compute code = (2^numBits) - 1 + value = mask + value
        bitCode->code = value >= 0 ? value : value + mask;
        bitCode->numBits = numBits;;
    }

    // forward DCT computation "in one dimension" (fast AAN algorithm: Arai, Agui and Nakajima: "A fast DCT-SQ scheme for images")
    // stride must be 1 (=horizontal) or 8 (=vertical)
    void DCT(int stride, float block[8 * 8])
    {
        // modify in-place
        float* block0 = &block[0 * stride];
        float* block1 = &block[1 * stride];
        float* block2 = &block[2 * stride];
        float* block3 = &block[3 * stride];
        float* block4 = &block[4 * stride];
        float* block5 = &block[5 * stride];
        float* block6 = &block[6 * stride];
        float* block7 = &block[7 * stride];

        // based on https://dev.w3.org/Amaya/libjpeg/jfdctflt.c , the original variable names can be found in my comments
        float add07 = *block0 + *block7; float sub07 = *block0 - *block7; // tmp0, tmp7
        float add16 = *block1 + *block6; float sub16 = *block1 - *block6; // tmp1, tmp6
        float add25 = *block2 + *block5; float sub25 = *block2 - *block5; // tmp2, tmp5
        float add34 = *block3 + *block4; float sub34 = *block3 - *block4; // tmp3, tmp4

        float add0347 = add07 + add34; float sub07_34 = add07 - add34; // tmp10, tmp13 ("even part" / "phase 2")
        float add1256 = add16 + add25; float sub16_25 = add16 - add25; // tmp11, tmp12

        *block0 = add0347 + add1256; *block4 = add0347 - add1256; // "phase 3"

        float z1 = (sub16_25 + sub07_34) * InvSqrt; // all temporary z-variables kept their original names
        *block2 = sub07_34 + z1; *block6 = sub07_34 - z1; // "phase 5"

        float sub23_45 = sub25 + sub34; // tmp10 ("odd part" / "phase 2")
        float sub12_56 = sub16 + sub25; // tmp11
        float sub01_67 = sub16 + sub07; // tmp12

        float z5 = (sub23_45 - sub01_67) * HalfSqrtSqrt;
        float z2 = sub23_45 * InvSqrtSqrt + z5;
        float z3 = sub12_56 * InvSqrt;
        float z4 = sub01_67 * SqrtHalfSqrt + z5;
        float z6 = sub07 + z3; // z11 ("phase 5")
        float z7 = sub07 - z3; // z13
        *block1 = z6 + z4; *block7 = z6 - z4; // "phase 6"
        *block5 = z7 + z2; *block3 = z7 - z2;
    }

    // run DCT, quantize and write Huffman bit codes
    short JPEGEncodeBlock
    (
        ParsingStream* parsingStream,
        BitBuffer* buffer,
        float block[8][8],
        const float scaled[8 * 8], 
        int16_t lastDC,
        const BitCode huffmanDC[256],
        const BitCode huffmanAC[256]
    )    
    {

        // "linearize" the 8x8 block, treat it as a flat array of 64 floats
        float* block64 = block;

        // DCT: rows
        for (size_t offset = 0; offset < 8; offset++)
            DCT(1u, block64 + offset * 8);
        // DCT: columns
        for (size_t offset = 0; offset < 8; offset++)
            DCT(8u, block64 + offset * 1);

        // scale
        for (size_t i = 0; i < 8 * 8; i++)
            block64[i] *= scaled[i];

        // encode DC (the first coefficient is the "average color" of the 8x8 block)
        // convert to an integer
        short DC = (short)(block64[0] + (block64[0] >= 0 ? +0.5f : -0.5f)); // C++11's nearbyint() achieves a similar effect
        // same "average color" as previous block ?
        if (DC == lastDC)
            writeBits(parsingStream, buffer, huffmanDC[0x00]); // yes, write a special short symbol
        else
        {
            BitCode bitCode;
            convertCode(&bitCode, DC - lastDC);       // nope, encode the difference to previous block's average color
            writeBits(parsingStream, buffer, huffmanDC[bitCode.numBits]);
            writeBits(parsingStream, buffer, bitCode);
        }

        // quantize and zigzag the other 63 coefficients
        size_t posNonZero = 0; // find last coefficient which is not zero (because trailing zeros are encoded very efficiently)
        int16_t quantized[8 * 8];
        for (size_t i = 1; i < 8 * 8; i++) // start at 1 because block64[0]=DC was already processed
        {
            float value = block64[ZigZagInv[i]];
            // round to nearest integer (actually, rounding is performed by casting from float to int16)
            quantized[i] = (int16_t)(value + (value >= 0 ? +0.5f : -0.5f)); // C++11's nearbyint() achieves a similar effect
            // remember offset of last non-zero coefficient
            if (quantized[i] != 0)
                posNonZero = i;
        }

        // encode ACs (Q[1..63])
        for (size_t i = 1; i <= posNonZero; i++) // Q[0] was already written, start at Q[1] and skip all trailing zeros
        {
            // zeros are encoded in a special way
            size_t offset = 0; // upper 4 bits count the number of consecutive zeros
            while (quantized[i] == 0) // found a few zeros, let's count them
            {
                i++;
                offset += 1 << 4; // add 1 to the upper 4 bits
                // split into blocks of at most 16 consecutive zeros
                if (offset > 15 << 4) // remember, the counter is in the upper 4 bits
                {
                    offset = 0;
                    writeBits(parsingStream, buffer, huffmanAC[0xF0]); // 0xF0 is a special code for "16 zeros"
                }
            }

            // merge number of zeros with the number of bits of the next non-zero value
            BitCode bitCode;
            convertCode(&bitCode, quantized[i]);
            offset += bitCode.numBits;
            writeBits(parsingStream, buffer, huffmanAC[offset]);
            writeBits(parsingStream, buffer, bitCode);
        }

        // send end-of-block code (0x00), only needed if there are trailing zeros
        if (posNonZero < 8 * 8 - 1) // = 63
            writeBits(parsingStream, buffer, huffmanAC[0x00]);

        return DC;
    }

    // Jon's code includes the pre-generated Huffman codes
    // I don't like these "magic constants" and compute them on my own :-)
    void generateHuffmanTable(const uint8_t numCodes[16], const uint8_t* values, BitCode result[256])
    {
        uint16_t huffmanCode = 0; // no JPEG Huffman code exceeds 16 bits
        // process all bitsizes 1 thru 16
        for (auto numBits = 1; numBits <= 16; numBits++)
        {
            // ... and each code of these bitsizes
            for (auto i = 0; i < numCodes[numBits - 1]; i++) // note: numCodes array starts at zero, but smallest bitsize is 1
            {
                auto current = *values++;
                result[current].code = huffmanCode++;
                result[current].numBits = numBits;
            }
            // next Huffman code needs to be one bit wider
            huffmanCode <<= 1;
        }
    }
















ActionResult JPEGSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten)
{
    unsigned char isRGB = 1u;
    unsigned char quality = 100u;
    unsigned char downsample = 0;
    const char* comment = 0;

    ParsingStream parsingStream;

    ParsingStreamConstruct(&parsingStream, data, dataSize);
    *dataWritten = 0;


    quality = MathLimitCU(quality, 1u, 100u);
    // formula taken from libjpeg
    quality = quality < 50 ? 5000 / quality : 200 - quality * 2;



    // Header Signature
    {
        ParsingStreamWriteSU(&parsingStream, JPEGMarkerStartOfImageID, EndianCurrentSystem);
    }

    // APP0
    {
        JPEGFileInfo jpegFileInfo;
        jpegFileInfo.VersionMajor = 1u;
        jpegFileInfo.VersionMinor = 1u;
        jpegFileInfo.DensityUnits = 0;
        jpegFileInfo.DensityX = 1;
        jpegFileInfo.DensityY = 1;
        jpegFileInfo.ThumbnailX = 0;
        jpegFileInfo.ThumbnailY = 0;
        jpegFileInfo.ThumbnailDataSize = 0;
        jpegFileInfo.ThumbnailData = 0;

        ParsingStreamWriteSU(&parsingStream, JPEGMarkerApplicationSegment00ID, EndianCurrentSystem);
        ParsingStreamWriteSU(&parsingStream, 16u, EndianBig);
        ParsingStreamWriteD(&parsingStream, "JFIF", 5u);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.VersionMajor);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.VersionMinor);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.DensityUnits);
        ParsingStreamWriteSU(&parsingStream, jpegFileInfo.DensityX, EndianBig);
        ParsingStreamWriteSU(&parsingStream, jpegFileInfo.DensityY, EndianBig);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.ThumbnailX);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.ThumbnailY);
    }

    // ////////////////////////////////////////
    // adjust quantization tables to desired quality
    uint8_t quantLuminance[8 * 8];
    uint8_t quantChrominance[8 * 8];
    for (size_t i = 0; i < 8 * 8; i++)
    {
        const unsigned char luminance = (DefaultQuantLuminance[ZigZagInv[i]] * quality + 50u) / 100u;
        const unsigned char chrominance = (DefaultQuantChrominance[ZigZagInv[i]] * quality + 50u) / 100u;
        
        // clamp to 1..255
        quantLuminance[i] = (MathLimitCU(luminance, 1u, 255u));
        quantChrominance[i] = (MathLimitCU(chrominance, 1u, 255u));
    }

    // write quantization tables        
    ParsingStreamWriteSU(&parsingStream, JPEGMarkerDefineQuantizationTableListID, EndianCurrentSystem);
    ParsingStreamWriteSU(&parsingStream, 2 + (isRGB ? 2 : 1) * (1 + 8 * 8), EndianBig);  // length: 65 bytes per table + 2 bytes for this length field

    // each table has 64 entries and is preceded by an ID byte
    ParsingStreamWriteCU(&parsingStream, 0u); // first  quantization table
    ParsingStreamWriteD(&parsingStream, quantLuminance, sizeof(unsigned char) * 64u);

    if (isRGB)// chrominance is only relevant for color images
    {
        ParsingStreamWriteCU(&parsingStream, 1u);  // second quantization table
        ParsingStreamWriteD(&parsingStream, quantChrominance, sizeof(unsigned char) * 64u);
    }

    // ////////////////////////////////////////
    // write image infos (SOF0 - start of frame)
    // length: 6 bytes general info + 3 per channel + 2 bytes for this length field
    unsigned char numComponents = isRGB ? 3 : 1;

    ParsingStreamWriteSU(&parsingStream, JPEGMarkerStartOfFrameHuffmanBaselineDCTID, EndianCurrentSystem);
    ParsingStreamWriteSU(&parsingStream, 2 + 6 + 3 * numComponents, EndianBig);


    ParsingStreamWriteCU(&parsingStream, 8u); // 8 bits per channel

    // image dimensions (big-endian)
    ParsingStreamWriteSU(&parsingStream, image->Height, EndianBig);
    ParsingStreamWriteSU(&parsingStream, image->Width, EndianBig);

    // sampling and quantization tables for each component
            // 1 component (grayscale, Y only) or 3 components (Y,Cb,Cr)
    ParsingStreamWriteCU(&parsingStream, numComponents);


    for (size_t id = 1; id <= numComponents; ++id)
    {
        ParsingStreamWriteCU(&parsingStream, id);                    // component ID (Y=1, Cb=2, Cr=3)
        // bitmasks for sampling: highest 4 bits: horizontal, lowest 4 bits: vertical
        ParsingStreamWriteCU(&parsingStream, id == 1 && downsample ? 0x22 : 0x11); // 0x11 is default YCbCr 4:4:4 and 0x22 stands for YCbCr 4:2:0
        ParsingStreamWriteCU(&parsingStream, id == 1 ? 0 : 1);       // use quantization table 0 for Y, else table 1
    }

    // ////////////////////////////////////////
    // Huffman tables
    // DHT marker - define Huffman tables
    ParsingStreamWriteSU(&parsingStream, JPEGMarkerDefineHuffmanTableListID, EndianCurrentSystem);
    ParsingStreamWriteSU(&parsingStream, isRGB ? (2 + 208 + 208) : (2 + 208), EndianBig);


    // 2 bytes for the length field, store chrominance only if needed
    //   1+16+12  for the DC luminance
    //   1+16+162 for the AC luminance   (208 = 1+16+12 + 1+16+162)
    //   1+16+12  for the DC chrominance
    //   1+16+162 for the AC chrominance (208 = 1+16+12 + 1+16+162, same as above)

// store luminance's DC+AC Huffman table definitions
    // highest 4 bits: 0 => DC, lowest 4 bits: 0 => Y (baseline)
    ParsingStreamWriteCU(&parsingStream, 0x00);

    ParsingStreamWriteD(&parsingStream, DcLuminanceCodesPerBitsize, sizeof(DcLuminanceCodesPerBitsize));
    ParsingStreamWriteD(&parsingStream, DcLuminanceValues, sizeof(DcLuminanceValues));

    ParsingStreamWriteCU(&parsingStream, 0x10);// highest 4 bits: 1 => AC, lowest 4 bits: 0 => Y (baseline)

    ParsingStreamWriteD(&parsingStream, AcLuminanceCodesPerBitsize, sizeof(AcLuminanceCodesPerBitsize));
    ParsingStreamWriteD(&parsingStream, AcLuminanceValues, sizeof(AcLuminanceValues));


    // compute actual Huffman code tables (see Jon's code for precalculated tables)
    BitCode huffmanLuminanceDC[256];
    BitCode huffmanLuminanceAC[256];
    generateHuffmanTable(DcLuminanceCodesPerBitsize, DcLuminanceValues, huffmanLuminanceDC);
    generateHuffmanTable(AcLuminanceCodesPerBitsize, AcLuminanceValues, huffmanLuminanceAC);

    // chrominance is only relevant for color images
    BitCode huffmanChrominanceDC[256];
    BitCode huffmanChrominanceAC[256];
    if (isRGB)
    {
        // store luminance's DC+AC Huffman table definitions
        // highest 4 bits: 0 => DC, lowest 4 bits: 1 => Cr,Cb (baseline)
        ParsingStreamWriteCU(&parsingStream, 0x01);

        ParsingStreamWriteD(&parsingStream, DcChrominanceCodesPerBitsize, sizeof(DcChrominanceCodesPerBitsize));
        ParsingStreamWriteD(&parsingStream, DcChrominanceValues, sizeof(DcChrominanceValues));

        
       // highest 4 bits: 1 => AC, lowest 4 bits: 1 => Cr,Cb (baseline)
        ParsingStreamWriteCU(&parsingStream, 0x11);
        
        ParsingStreamWriteD(&parsingStream, AcChrominanceCodesPerBitsize, sizeof(AcChrominanceCodesPerBitsize));
        ParsingStreamWriteD(&parsingStream, AcChrominanceValues, sizeof(AcChrominanceValues));

        // compute actual Huffman code tables (see Jon's code for precalculated tables)
        generateHuffmanTable(DcChrominanceCodesPerBitsize, DcChrominanceValues, huffmanChrominanceDC);
        generateHuffmanTable(AcChrominanceCodesPerBitsize, AcChrominanceValues, huffmanChrominanceAC);
    }

    // ////////////////////////////////////////
    // start of scan (there is only a single scan for baseline JPEGs)
    ParsingStreamWriteSU(&parsingStream, JPEGMarkerStartOfScanID, EndianCurrentSystem);
    ParsingStreamWriteSU(&parsingStream, 2 + 1 + 2 * numComponents + 3, EndianBig);


    // assign Huffman tables to each component
    ParsingStreamWriteCU(&parsingStream, numComponents);

    for (size_t id = 1; id <= numComponents; ++id)
    {
        // component ID (Y=1, Cb=2, Cr=3)
        ParsingStreamWriteCU(&parsingStream, id);
        // highest 4 bits: DC Huffman table, lowest 4 bits: AC Huffman table
        ParsingStreamWriteCU(&parsingStream, id == 1 ? 0x00 : 0x11); // Y: tables 0 for DC and AC; Cb + Cr: tables 1 for DC and AC
    }

    // constant values for our baseline JPEGs with a single sequential scan
    ParsingStreamWriteCU(&parsingStream, 0u); // spectral selection: must start at  0
    ParsingStreamWriteCU(&parsingStream, 63u); // spectral selection: must stop  at 63
    ParsingStreamWriteCU(&parsingStream, 0u); // successive approximation: must be  0

    // adjust quantization tables with AAN scaling factors to simplify DCT
    float scaledLuminance[8 * 8];
    float scaledChrominance[8 * 8];
    for (auto i = 0; i < 8 * 8; ++i)
    {
        auto row = ZigZagInv[i] / 8; // same as i >> 3
        auto column = ZigZagInv[i] % 8; // same as i &  7
        float factor = 1 / (AanScaleFactors[row] * AanScaleFactors[column] * 8);
        scaledLuminance[ZigZagInv[i]] = factor / quantLuminance[i];
        scaledChrominance[ZigZagInv[i]] = factor / quantChrominance[i];
        // if you really want JPEGs that are bitwise identical to Jon's code then you need slightly different formulas (note: sqrt(8) = 2.828427125f)
        //const float aasf[] = { 1.0f * 2.828427125f, 1.387039845f * 2.828427125f, 1.306562965f * 2.828427125f, 1.175875602f * 2.828427125f, 1.0f * 2.828427125f, 0.785694958f * 2.828427125f, 0.541196100f * 2.828427125f, 0.275899379f * 2.828427125f }; // line 240 of jo_jpeg.cpp
        //scaledLuminance  [ZigZagInv[i]] = 1 / (quantLuminance  [i] * aasf[row] * aasf[column]); // lines 266-267 of jo_jpeg.cpp
        //scaledChrominance[ZigZagInv[i]] = 1 / (quantChrominance[i] * aasf[row] * aasf[column]);
    }

    // all encoded bits pass through this buffer, it writes to output whenever a byte is completed
    BitBuffer buffer;

    buffer.bits = 0;      // actually only at most 24 bits are used
    buffer.numBits = 0;   // number of valid bits (the right-most bits)

    // just convert image data from void*
    const unsigned char* pixels = image->PixelData;

    // break down the image into 8x8 blocks and convert from RGB or grayscale to YCbCr color space
    float Y[8][8], Cb[8][8], Cr[8][8];
    // average color of the previous 8x8 block
    int16_t lastYDC = 0, lastCbDC = 0, lastCrDC = 0;

    // downsampling of Cb and Cr channels, if sampling = 2 then 2x2 samples are used
    const size_t sampling = downsample ? 2 : 1;
    const size_t numSamples = sampling * sampling; // 1 (grayscale, YCbCr444) or 4 (YCbCr420)
    // only for downsampled: sum of four pixels' red, green, blue components
    float red[8][8];
    float green[8][8];
    float blue[8][8]; // uint16_t works, too, but float is faster
    
    MemorySet(red, sizeof(float) * 8 * 8, 0);
    MemorySet(green, sizeof(float) * 8 * 8, 0);
    MemorySet(blue, sizeof(float) * 8 * 8, 0);

    // process MCUs (minimum codes units)
    for (int mcuY = 0; mcuY < image->Height; mcuY += 8u * sampling)
        for (int mcuX = 0; mcuX < image->Width; mcuX += 8u * sampling)
        {
            // YCbCr 4:4:4 format: each MCU is a 8x8 block - the same applies to grayscale images, too
            // YCbCr 4:2:0 format: each MCU represents a 16x16 block, stored as 4x 8x8 Y-blocks plus 1x 8x8 Cb and 1x 8x8 Cr blocks)
            for (int block = 0; block < numSamples; block++) // this loop is iterated once (grayscale, 4:4:4) or four times (4:2:0)
            {
                // subdivide into 8x8 blocks where blockX and blockY indicate the minimum x and y of the current block
                int blockX = 8 * (block & 1); // same as 8 * (block % 2) => { 0, 8, 0, 8 }
                int blockY = 4 * (block & 2); // same as 8 * (block / 2) => { 0, 0, 8, 8 }

                // now we finally have an 8x8 block ...
                for (int deltaY = 0; deltaY < 8; deltaY++)
                    for (int deltaX = 0; deltaX < 8; deltaX++)
                    {
                        // find actual pixel position within the current image
                        int column = MathMinimumI(mcuX + blockX + deltaX, image->Width - 1); // must not exceed image borders, replicate last row/column if needed
                        int row = MathMinimumI(mcuY + blockY + deltaY, image->Height - 1);
                        int pixelPos = row * image->Width + column; // the cast ensures that we don't run into multiplication overflows

                        // grayscale images have solely a Y channel which can be easily derived from the input pixel by shifting it by 128
                        if (!isRGB)
                        {
                            Y[deltaY][deltaX] = pixels[pixelPos] - 128.f;
                            continue;
                        }

                        // RGB: 3 bytes per pixel (whereas grayscale images have only 1 byte per pixel)
                        pixelPos *= numComponents;
                        float r = pixels[pixelPos];
                        float g = pixels[pixelPos + 1];
                        float b = pixels[pixelPos + 2];

                        // compute Y channel
                        Y[deltaY][deltaX] = ConvertColorRGBToY(r, g, b) - 128; // again, the JPEG standard requires Y to be shifted by 128

                        if (downsample)
                        {
                            // defer Cb/Cr computation if YCbCr420 mode: we must average 2x2 pixels, so let's "shrink" a 16x16 area to 8x8
                            int x = (blockX + deltaX) / 2;
                            int y = (blockY + deltaY) / 2;

                            // add red, green, blue (note: each number should be weighted by 1/4, this is done later)
                            red[y][x] += r;
                            green[y][x] += g;
                            blue[y][x] += b;
                        }
                        else
                        {
                            // YCbCr444: computation of Cb and Cr is similar to Y channel but without the need to subtract 128
                            Cb[deltaY][deltaX] = ConvertColorRGBToCb(r, g, b);
                            Cr[deltaY][deltaX] = ConvertColorRGBToCr(r, g, b);
                        }
                    }

                // encode Y channel
                lastYDC = JPEGEncodeBlock(&parsingStream, &buffer, Y, scaledLuminance, lastYDC, huffmanLuminanceDC, huffmanLuminanceAC);
            }

            if (!isRGB)
                continue;

            // ////////////////////////////////////////
            // YCbCr420 / downsampled: convert summed RGB values to Cb and Cr
            if (downsample)
                for (int y = 0; y < 8; y++)
                    for (int x = 0; x < 8; x++)
                    {
                        // each number in the arrays "red", "green" and "blue" consists of the summed values of four pixels
                        // so I still have to divide them by 4 to get their average value
                        float r = red[y][x] / 4.f; // numSamples = 4
                        float g = green[y][x] / 4.f;
                        float b = blue[y][x] / 4.f;

                        Cb[y][x] = ConvertColorRGBToCb(r, g, b);
                        Cr[y][x] = ConvertColorRGBToCr(r, g, b);

                        // reset arrays for next block
                        red[y][x] = green[y][x] = blue[y][x] = 0;
                    }

            // encode Cb + Cr channels
            lastCbDC = JPEGEncodeBlock(&parsingStream, &buffer, Cb, scaledChrominance, lastCbDC, huffmanChrominanceDC, huffmanChrominanceAC);
            lastCrDC = JPEGEncodeBlock(&parsingStream, &buffer, Cr, scaledChrominance, lastCrDC, huffmanChrominanceDC, huffmanChrominanceAC);
        }

    // fill remaining bits with 1s
    BitCode bitCode;
    bitCode.code = 0x7F;
    bitCode.numBits = 7;

    writeBits(&parsingStream, &buffer, bitCode); // seven set bits: 0x7F = binary 0111 1111

   // ParsingStreamWriteCU(&parsingStream, &buffer);
   // ParsingStreamWriteSU(&parsingStream, );

    // End Tag
    {
        ParsingStreamWriteSU(&parsingStream, JPEGMarkerEndOfImageID, EndianCurrentSystem);
    }

    *dataWritten = parsingStream.DataCursor;

    return ResultSuccessful;
}