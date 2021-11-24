#include "DeflateBlock.h"

#include "../../Container/BitStreamHusk.h"
#include "../HUFFMAN/HuffmanCodeType.h"
#include "../HUFFMAN/HuffmanSymbol.h"
#include "../HUFFMAN/HuffmanTree.h"
#include <stdio.h>
#include <cassert>

BF::DeflateBlock::DeflateBlock()
{
	IsLastBlock = false;
	EncodingMethod = DeflateEncodingMethod::Invalid;
}

void BF::DeflateBlock::Parse(BitStreamHusk& bitStream)
{
    IsLastBlock = bitStream.ExtractBitsAndMove(1);
    unsigned char encodingMethodValue = bitStream.ExtractBitsAndMove(2);
   
    EncodingMethod = ConvertDeflateEncodingMethod(encodingMethodValue);
}


void BF::DeflateBlock::Inflate(BitStreamHusk& bitStream, unsigned char* dataOut, size_t& dataOutSize)
{
    switch (EncodingMethod)
    {
        default:
        case DeflateEncodingMethod::Reserverd:
        case DeflateEncodingMethod::Invalid:
        {
            return; // Invalid Mode
        }
        case DeflateEncodingMethod::LiteralRaw:
        {
            // Skip remaining Bytes
            unsigned char* literalData = bitStream.StartAdress + bitStream.CurrentPosition;
            unsigned short length = literalData[1] << 8 | literalData[2];
            unsigned short lengthInverse = literalData[3] << 8 | literalData[4];
            unsigned char* sourceAdress = literalData + 5u;

            assert(length == !lengthInverse);

            dataOutSize += length;

            memcpy(dataOut, sourceAdress, length);

            break;
        }
        case DeflateEncodingMethod::HuffmanDynamic:
        case DeflateEncodingMethod::HuffmanStatic:
        {
            HuffmanTree literalAndLengthCodes;
            HuffmanTree distanceCodes;
            bool foundEndOFBlock = false;

            switch (EncodingMethod)
            {
                case DeflateEncodingMethod::HuffmanDynamic:
                {
                    unsigned int result = HuffmanTree::GenerateDynamicTree(bitStream, literalAndLengthCodes, distanceCodes);

                    if (result != 0)
                    {
                        printf("EE");
                    }

                    break;
                }
                case DeflateEncodingMethod::HuffmanStatic:
                {
                    literalAndLengthCodes.GenerateFixedLiteralLengthTree();
                    distanceCodes.GenerateFixedDistanceTree();
                    break;
                }
            }

            while (!foundEndOFBlock)
            {
                unsigned int resultLengthCode = HuffmanTree::huffmanDecodeSymbol(bitStream, literalAndLengthCodes);
                HuffmanCodeType huffmanCodeType = HuffmanCodeTypeFromCode(resultLengthCode);

                switch (huffmanCodeType)
                {
                    case BF::HuffmanCodeType::InvalidCode:
                    {
                        // printf("[Symbol] Error: Invalid\n");
                        break; // ERROR
                    }
                    case BF::HuffmanCodeType::Literal:
                    {
                        // printf("[Symbol] <%2x>(%3i) Literal.\n", resultLengthCode, resultLengthCode);
                        dataOut[dataOutSize++] = resultLengthCode;
                        break;
                    }
                    case BF::HuffmanCodeType::Length:
                    {
                        // printf("[Symbol] <%2x>(%3i) Length.\n", resultLengthCode, resultLengthCode);

#define FIRST_LENGTH_CODE_INDEX 257
#define LAST_LENGTH_CODE_INDEX 285

                        unsigned int distance = 0;
                        unsigned int numextrabits_l = 0;
                        unsigned int numextrabits_d = 0; /*extra bits for length and distance*/
                        size_t start, backward, length;

                        /*the base lengths represented by codes 257-285*/
                        const unsigned int LENGTHBASE[29] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258 };

                        /*the extra bits used by codes 257-285 (added to base length)*/
                        const unsigned int LENGTHEXTRA[29] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0 };

                        /*the base backwards distances (the bits of distance codes appear after length codes and use their own huffman tree)*/
                        static const unsigned DISTANCEBASE[30] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513,                                           769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577 };

                        /*the extra bits of backwards distances (added to base)*/
                        static const unsigned DISTANCEEXTRA[30] = { 0, 0, 0, 0, 1, 1, 2,  2,  3,  3,  4,  4,  5,  5,   6,   6,   7,   7,   8, 8,    9,    9,   10,   10,   11,   11,   12,    12,    13,    13 };


                        /*part 1: get length base*/
                        length = LENGTHBASE[resultLengthCode - FIRST_LENGTH_CODE_INDEX];

                        /*part 2: get extra bits and add the value of that to length*/
                        numextrabits_l = LENGTHEXTRA[resultLengthCode - FIRST_LENGTH_CODE_INDEX];
                        if (numextrabits_l != 0)
                        {
                            /* bits already ensured above */
                            length += bitStream.ExtractBitsAndMove(numextrabits_l);
                        }

                        /*part 3: get distance code*/
                        //ensureBits32(reader, 28); /* up to 15 for the huffman symbol, up to 13 for the extra bits */
                        unsigned int resultDistanceCode = HuffmanTree::huffmanDecodeSymbol(bitStream, distanceCodes);
                        bool isUnsupportedCode = resultDistanceCode > 29;
                        bool isIllegalCode = resultDistanceCode > 31;

                        if (isUnsupportedCode)
                        {
                            if (isIllegalCode)  /* if(code_d == INVALIDSYMBOL) */
                            {
                                throw(16); /*error: tried to read disallowed huffman symbol*/
                            }
                            else
                            {
                                throw(18); /*error: invalid distance code (30-31 are never used)*/
                            }
                        }

                        distance = DISTANCEBASE[resultDistanceCode];

                        /*part 4: get extra bits from distance*/
                        numextrabits_d = DISTANCEEXTRA[resultDistanceCode];
                        if (numextrabits_d != 0)
                        {
                            /* bits already ensured above */
                            distance += bitStream.ExtractBitsAndMove(numextrabits_d);
                        }

                        /*part 5: fill in all the out[n] values based on the length and dist*/
                        start = dataOutSize;
                        if (distance > start) throw 52; /*too long backward distance*/
                        backward = start - distance;

                        dataOutSize += length;

                        // if (!ucvector_resize(out, out->size + length)) ERROR_BREAK(83 /*alloc fail*/);


                        if (distance < length)
                        {
                            memcpy(dataOut + start, dataOut + backward, distance);

                            start += distance;

                            for (size_t forward = distance; forward < length; ++forward)
                            {
                                dataOut[start++] = dataOut[backward++];
                            }
                        }
                        else
                        {
                            memcpy(dataOut + start, dataOut + backward, length);
                        }
                        break;
                    }
                    case BF::HuffmanCodeType::EndOfBlock:
                    {
                        //printf("[Symbol] <%2x>(%3i) End of Block.\n", resultLengthCode, resultLengthCode);
                        foundEndOFBlock = true;   

                        break; // FINISHED!
                    }
                }
            }

            break;
        }
    }
}