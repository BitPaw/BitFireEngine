#include "JPEG.h"

#include <cassert>
#include <stdlib.h>

#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <Container/ClusterShort.h>

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

    const size_t sum = beginning + end + app0;

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

ActionResult JPEGSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten)
{
    ParsingStream parsingStream;

    ParsingStreamConstruct(&parsingStream, data, dataSize);
    *dataWritten = 0;

    // Header Signature
    {
        ParsingStreamWriteSU(&parsingStream, JPEGMarkerStartOfImageID, EndianCurrentSystem);
    }

    // APP0
    {
        JPEGFileInfo jpegFileInfo;
        jpegFileInfo.VersionMajor = 1u;
        jpegFileInfo.VersionMinor = 2u;
        jpegFileInfo.DensityUnits = 0;
        jpegFileInfo.DensityX = 0;
        jpegFileInfo.DensityY = 0;
        jpegFileInfo.ThumbnailX = 0;
        jpegFileInfo.ThumbnailY = 0;
        jpegFileInfo.ThumbnailDataSize = 0;
        jpegFileInfo.ThumbnailData = 0;

        ParsingStreamWriteSU(&parsingStream, JPEGMarkerApplicationSegment00ID, EndianCurrentSystem);
        ParsingStreamWriteSU(&parsingStream, 14u, EndianLittle);
        ParsingStreamWriteD(&parsingStream, "JFIF", 5u);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.VersionMajor);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.VersionMinor);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.DensityUnits);
        ParsingStreamWriteSU(&parsingStream, jpegFileInfo.DensityX, EndianLittle);
        ParsingStreamWriteSU(&parsingStream, jpegFileInfo.DensityY, EndianLittle);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.ThumbnailX);
        ParsingStreamWriteCU(&parsingStream, jpegFileInfo.ThumbnailY);
    }

    // DefineQuantizationTable
    {
        /*
        unsigned short length = 0;
        unsigned char chrominance = 0;
        unsigned char buffer[64];

        ParsingStreamWriteSU(&parsingStream, length, EndianBig);
        ParsingStreamWriteCU(&parsingStream, chrominance);
        ParsingStreamWriteD(&parsingStream, buffer, 64);*/
    }

    // End Tag
    {
        ParsingStreamWriteSU(&parsingStream, JPEGMarkerEndOfImageID, EndianCurrentSystem);
    }

    *dataWritten = parsingStream.DataCursor;

    return ResultSuccessful;
}