#include "DEFLATE.h"

#include <Memory/Memory.h>
#include <File/Format/HUFFMAN/HuffmanTree.h>
#include <File/BitStream.h>

#define DeflateEncodingInvalidID -1
#define DeflateEncodingLiteralRawID 0b00
#define DeflateEncodingHuffmanStaticID 0b01
#define DeflateEncodingHuffmanDynamicID 0b10
#define DeflateEncodingReserverdID 0b11

DeflateEncodingMethod ConvertToDeflateEncodingMethod(const unsigned char deflateEncodingMethod)
{
    switch(deflateEncodingMethod)
    {
        case DeflateEncodingLiteralRawID:
            return DeflateEncodingLiteralRaw;

        case DeflateEncodingHuffmanStaticID:
            return DeflateEncodingHuffmanStatic;

        case DeflateEncodingHuffmanDynamicID:
            return DeflateEncodingHuffmanDynamic;

        case DeflateEncodingReserverdID:
            return DeflateEncodingReserverd;

        default:
            return DeflateEncodingInvalid;
    }
}

unsigned char ConvertFromDeflateEncodingMethod(const DeflateEncodingMethod deflateEncodingMethod)
{
    switch(deflateEncodingMethod)
    {
        case DeflateEncodingLiteralRaw:
            return DeflateEncodingLiteralRawID;

        case DeflateEncodingHuffmanStatic:
            return DeflateEncodingHuffmanStaticID;

        case DeflateEncodingHuffmanDynamic:
            return DeflateEncodingHuffmanDynamicID;

        default:
        case DeflateEncodingReserverd:
            return DeflateEncodingReserverdID;
    }
}

int DEFLATEParse(const void* const inputBuffer, const size_t inputBufferSize, void* const outputBuffer, size_t* const outputBufferSize)
{ 
    BitStream bitStream;
    DeflateBlock deflateBlock;

    BitStreamConstruct(&bitStream, inputBuffer, inputBufferSize);

    do
    {       
        deflateBlock.IsLastBlock = BitStreamRead(&bitStream, 1u);

        {
            const unsigned char encodingMethodValue = BitStreamRead(&bitStream, 2u);

            deflateBlock.EncodingMethod = ConvertToDeflateEncodingMethod(encodingMethodValue);
        }

        switch(deflateBlock.EncodingMethod)
        {
            default:
            case DeflateEncodingReserverd:
            case DeflateEncodingInvalid:
            {
                return -1; // Invalid Mode
            }
            case DeflateEncodingLiteralRaw:
            {
                BitStreamSkipBitsToNextByte(&bitStream); // Skip remaining Bytes

                const unsigned short length = BitStreamRead(&bitStream, 16u);
                const unsigned short lengthInverse = BitStreamRead(&bitStream, 16u);
                const unsigned char* sourceAdress = BitStreamCursorPosition(&bitStream);
                const unsigned char validLength = (length + lengthInverse) == 65535;
                //const size_t bitsToJump = (size_t)length * 8;

                //assert(validLength);

                MemoryCopy(sourceAdress, BitStreamRemainingSize(&bitStream), (unsigned char*)outputBuffer + *outputBufferSize, length);

                *outputBufferSize += length;

                BitStreamCursorMoveInBytes(&bitStream, length);

                break;
            }
            case DeflateEncodingHuffmanDynamic:
            case DeflateEncodingHuffmanStatic:
            {
                HuffmanTree literalAndLengthCodes;
                HuffmanTree distanceCodes;
                unsigned char foundEndOFBlock = 0;

                HuffmanTreeConstruct(&literalAndLengthCodes);
                HuffmanTreeConstruct(&distanceCodes);

                switch(deflateBlock.EncodingMethod)
                {
                    case DeflateEncodingHuffmanDynamic:
                    {
                        const unsigned int result = GenerateDynamicTree(&bitStream, &literalAndLengthCodes, &distanceCodes);

                        if(result != 0)
                        {
                            printf("EE");
                        }

                        break;
                    }
                    case DeflateEncodingHuffmanStatic:
                    {
                        GenerateFixedLiteralLengthTree(&literalAndLengthCodes);
                        GenerateFixedDistanceTree(&distanceCodes);
                        break;
                    }
                }

                while(!foundEndOFBlock)
                {
                    unsigned int resultLengthCode = huffmanDecodeSymbol(&bitStream, &literalAndLengthCodes);
                    HuffmanCodeType huffmanCodeType = HuffmanCodeTypeFromCode(resultLengthCode);

                    switch(huffmanCodeType)
                    {
                        case HuffmanCodeInvalid:
                        {
                            // printf("[Symbol] Error: Invalid\n");
                            break; // ERROR
                        }
                        case HuffmanCodeLiteral:
                        {
                            // printf("[Symbol] <%2x>(%3i) Literal.\n", resultLengthCode, resultLengthCode);
                            ((unsigned char*)outputBuffer)[(*outputBufferSize)++] = resultLengthCode;
                            break;
                        }
                        case HuffmanCodeLength:
                        {
                            // printf("[Symbol] <%2x>(%3i) Length.\n", resultLengthCode, resultLengthCode);


                            size_t distance = 0;
                            size_t numextrabits_l = 0;
                            size_t numextrabits_d = 0; /*extra bits for length and distance*/
                            size_t start, backward, length;

                            /*the base lengths represented by codes 257-285*/
                            const unsigned int LENGTHBASE[29] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258 };

                            /*the extra bits used by codes 257-285 (added to base length)*/
                            const unsigned int LENGTHEXTRA[29] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0 };

                            /*the base backwards distances (the bits of distance codes appear after length codes and use their own huffman tree)*/
                            static const unsigned DISTANCEBASE[30] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513,                                           769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577 };

                            /*the extra bits of backwards distances (added to base)*/
                            static const unsigned DISTANCEEXTRA[30] = { 0, 0, 0, 0, 1, 1, 2,  2,  3,  3,  4,  4,  5,  5,   6,   6,   7,   7,   8, 8,    9,    9,   10,   10,   11,   11,   12,    12,    13,    13 };


                            {
                                const unsigned int FIRST_LENGTH_CODE_INDEX = 257u;
                                const unsigned int LAST_LENGTH_CODE_INDEX = 285u;

                                /*part 1: get length base*/
                                length = LENGTHBASE[resultLengthCode - FIRST_LENGTH_CODE_INDEX];

                                /*part 2: get extra bits and add the value of that to length*/
                                numextrabits_l = LENGTHEXTRA[resultLengthCode - FIRST_LENGTH_CODE_INDEX];
                            }


                            if(numextrabits_l != 0)
                            {
                                /* bits already ensured above */
                                length += BitStreamRead(&bitStream, numextrabits_l);
                            }

                            /*part 3: get distance code*/
                            //ensureBits32(reader, 28); /* up to 15 for the huffman symbol, up to 13 for the extra bits */
                            unsigned int resultDistanceCode = huffmanDecodeSymbol(&bitStream, &distanceCodes);
                            unsigned char isUnsupportedCode = resultDistanceCode > 29;
                            unsigned char isIllegalCode = resultDistanceCode > 31;

                            if(isUnsupportedCode)
                            {
                                if(isIllegalCode)  /* if(code_d == INVALIDSYMBOL) */
                                {
                                    return(16); /*error: tried to read disallowed huffman symbol*/
                                }
                                else
                                {
                                    return(18); /*error: invalid distance code (30-31 are never used)*/
                                }
                            }

                            distance = DISTANCEBASE[resultDistanceCode];

                            /*part 4: get extra bits from distance*/
                            numextrabits_d = DISTANCEEXTRA[resultDistanceCode];
                            if(numextrabits_d != 0)
                            {
                                /* bits already ensured above */
                                distance += BitStreamRead(&bitStream, numextrabits_d);
                            }

                            /*part 5: fill in all the out[n] values based on the length and dist*/
                            start = (*outputBufferSize);
                            if(distance > start) return (52); /*too long backward distance*/
                            backward = start - distance;

                            (*outputBufferSize) += length;

                            // if (!ucvector_resize(out, out->size + length)) ERROR_BREAK(83 /*alloc fail*/);


                            if(distance < length)
                            {
                                MemoryCopy((unsigned char*)outputBuffer + backward, distance, (unsigned char*)outputBuffer + start, distance);

                                start += distance;

                                for(size_t forward = distance; forward < length; ++forward)
                                {
                                    ((unsigned char*)outputBuffer)[start++] = ((unsigned char*)outputBuffer)[backward++];
                                }
                            }
                            else
                            {
                                MemoryCopy((unsigned char*)outputBuffer + backward, length, (unsigned char*)outputBuffer + start, length);
                            }
                            break;
                        }
                        case HuffmanCodeEndOfBlock:
                        {
                            //printf("[Symbol] <%2x>(%3i) End of Block.\n", resultLengthCode, resultLengthCode);
                            foundEndOFBlock = 1u;

                            break; // FINISHED!
                        }
                    }
                }

                break;
            }
        }
    }
    while(!deflateBlock.IsLastBlock);   

    return bitStream.DataCursor;
}

int DEFLATESerialize(const void* const inputBuffer, const size_t inputBufferSize, void* const outputBuffer, size_t* const outputBufferSize)
{
    BitStream bitStream;
    DeflateBlock deflateBlock;

    BitStreamConstruct(&bitStream, inputBuffer, inputBufferSize);

    do
    {   
        deflateBlock.IsLastBlock = 1u;
        deflateBlock.EncodingMethod = DeflateEncodingHuffmanDynamic;
     

        // Write block
        {
            unsigned char isLastBlock = deflateBlock.IsLastBlock;
            unsigned char encodingMethod = ConvertFromDeflateEncodingMethod(deflateBlock.EncodingMethod);          

            BitStreamWrite(&bitStream, isLastBlock, 1u);
            BitStreamWrite(&bitStream, encodingMethod, 2u);         
        }       

        switch(deflateBlock.EncodingMethod)
        {
            case DeflateEncodingLiteralRaw:
            {
                break;
            }
            case DeflateEncodingHuffmanStatic:
            {
                break;
            }
            case DeflateEncodingHuffmanDynamic:
            {
                break;
            }
            case DeflateEncodingInvalid:
            case DeflateEncodingReserverd:
            default:
                return ResultFormatInvalid;
        }
    }
    while(!deflateBlock.IsLastBlock);

    return bitStream.DataCursor;
}