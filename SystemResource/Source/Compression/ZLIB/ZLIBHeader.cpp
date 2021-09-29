#include "ZLIBHeader.h"

#include "../../Math/Math.h"
#include "../../Container/BitStreamHusk.h"

#include "../DEFLATE/DeflateBlock.h"
#include "../HUFFMAN/HuffmanSymbol.h"
#include "../HUFFMAN/HuffmanCodeBlock.h"

#include <cassert>
#include <string>

BF::ZLIBHeader::ZLIBHeader()
{
    CompressionMethod = ZLIBCompressionMethod::Invalid;
    CompressionInfo = 0;

    WindowSize = 0;
    CheckFlag = 0;
    DicttionaryPresent = false;
    CompressionLevel = ZLIBCompressionLevel::InvalidCompressionLevel;

    DataSize = 0;
    Data[0] = 0;
}

void BF::ZLIBHeader::Parse(unsigned char* data, unsigned int length)
{
    const unsigned int infoBlockSize = 2;
    const unsigned int adlerBlockSize = 4;
    const unsigned int subBlockSize = length - infoBlockSize - adlerBlockSize;
    unsigned char* subBlockStart = data + infoBlockSize;

    unsigned char compressionFormatByte = data[0];
    unsigned char flagByte = data[1];
    unsigned int adler32CheckSum = 
        (unsigned int)data[length - 4] << 24 | 
        (unsigned int)data[length - 3] << 16 |
        (unsigned int)data[length - 2] << 8  |
        (unsigned int)data[length - 1];


    //---<Parse First Byte - Compression Info>---------------------------------
    unsigned char compressionMethodValue = (compressionFormatByte & 0b00001111);
    CompressionMethod = ConvertCompressionMethod(compressionMethodValue);

    CompressionInfo = (compressionFormatByte & 0b11110000) >> 4;
    WindowSize = Math::Power(2, CompressionInfo);

    assert(CompressionInfo <= 7u);
    //-------------------------------------------------------------------------
  
    //---<Parse Second Byte - Flags>-------------------------------------------
    CheckFlag = (flagByte & 0b00011111);
    DicttionaryPresent = ((flagByte & 0b00100000) >> 5) == 1;
    unsigned char compressionLevelValue = (flagByte & 0b11000000) >> 6;

    CompressionLevel = ConvertCompressionLevel(compressionLevelValue);

    // Asserttion??
    bool validFlags = ((unsigned int)compressionFormatByte * 256 + (unsigned int)flagByte) % 31 == 0;
    //-------------------------------------------------------------------------


    //---<Dictionary Parse>----------------------------------------------------
    if (DicttionaryPresent)
    {
        // Parse DICT dictionary identifier 

    }
    //-------------------------------------------------------------------------

    //---<Decompress DataBlock>------------------------------------------------
    unsigned int dataCursor = 0;
    
    switch (CompressionMethod)
    {
        case BF::ZLIBCompressionMethod::Deflate:
        {
            DeflateBlock deflateBlock;

            /*
                WARNING! You'll need to read the Bits from RIGHT to LEFT

                NO  : 01234657
                YES : 76543210

                Byte Boundarys are also ignored! 
                ~~Watch out while skipping Bits like a broken record~~
            */

            BitStreamHusk bitStream(subBlockStart, subBlockSize, false);

            // Loop until the last marked DeflateBlock.
            do
            {   //---<Parse Header>---
                {
                    unsigned char isLastBlockValue = bitStream.ExtractBitsAndMove(1);
                    unsigned char encodingMethodValue = bitStream.ExtractBitsAndMove(2);

                    deflateBlock.IsLastBlock = isLastBlockValue == 1;
                    deflateBlock.EncodingMethod = ConvertDeflateEncodingMethod(encodingMethodValue);
                }            
                
                switch (deflateBlock.EncodingMethod)
                {
                    default:
                    case DeflateEncodingMethod::Reserverd:
                    case DeflateEncodingMethod::Invalid:
                    {
                        return;
                    }
                    case DeflateEncodingMethod::LiteralRaw:
                    {
                        // Skip remaining Bytes
                        unsigned short length = subBlockStart[1] << 8 | subBlockStart[2];
                        unsigned short lengthInverse = subBlockStart[3] << 8 | subBlockStart[4];
                        unsigned char* sourceAdress = subBlockStart + 5u;

                        assert(length == !lengthInverse);

                        DataSize += length;

                        memcpy(Data, sourceAdress, length);

                        break;
                    }
                    case DeflateEncodingMethod::HuffmanDynamic:
                    case DeflateEncodingMethod::HuffmanStatic:
                    {                               
                        if (deflateBlock.EncodingMethod == DeflateEncodingMethod::HuffmanDynamic)
                        {
                            // read representation of code trees
                            const unsigned char fixedCodes[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

                            HuffmanCodeBlock huffmanCodeBlock;

                            huffmanCodeBlock.NumberOfLiteralValues = (subBlockStart[0] & 0b11111000 >> 3) + 257u; // 5-Bits
                            huffmanCodeBlock.NumberOfDistanceCodes = (subBlockStart[1] & 0b00011111) - 1u; // 5-Bits
                            huffmanCodeBlock.NumberOfCodeLengthCodes = ((subBlockStart[2] & 0b11100000) >> 5) - 1u;

                            unsigned int lengthsOfPrefixCodes = huffmanCodeBlock.NumberOfCodeLengthCodes * 3;
                            unsigned int lengthsOfTheCodes = huffmanCodeBlock.NumberOfLiteralValues + huffmanCodeBlock.NumberOfDistanceCodes;
                            unsigned int compressedDataLength = 0;
                        }

#if 0 // TEST
                        for (int i = 0; bitStream.CurrentPosition < bitStream.DataLengh; )
                        {
                            unsigned short codeA = bitStream.ExtractBitsAndMove(5); // 5-Bits     
                            unsigned short codeB = bitStream.ExtractBitsAndMove(codeA); // 5-Bits    

                            printf("A:%i B:%i =:%i\n", codeA, codeB, codeA + codeB);

                            i += codeA + codeB;

                            if (((i) % 8+1) == 8)
                            {
                                printf("\n");
                            }
                        }
#endif

                        while (true) // loop(until end of block code recognized)
                        {
                            // TODO
                            // Start at compressedDataBlock 
                            //unsigned short value = bitStream.ExtractBitsAndMove(5) + 257u; // 5-Bits     
                            unsigned short value = HuffmanSymbolEndOfBlock;

                            if (value < 256)
                            {
                                Data[dataCursor++] = value; // Copy 'value' into outputSteam                        
                            }
                            else
                            {
                                bool isEndofBlock = value == HuffmanSymbolEndOfBlock;
                                bool isValidCode = value >= 257 && value <= 285;

                                if (isEndofBlock)
                                {
                                    break;
                                }

                                if(isValidCode)
                                {
                                    // decode distance from input stream
                                    unsigned char bitLength = DeflateBlock::HuffmanFixedCodeLength(value);

                                    assert(bitLength != 0);

                                    unsigned char distance = subBlockStart[1];

                                    // move backwards distance bytes in the output
                                    // stream, and copy length bytes from this
                                    // position to the output stream.
                                }
                            }                            
                        }                     

                        break;
                    }
                }
            }
            while (!deflateBlock.IsLastBlock);

            break;
        }
        default:
        case BF::ZLIBCompressionMethod::Reserved:
        case BF::ZLIBCompressionMethod::Invalid:
        {
            break;
        }
    }
    //-------------------------------------------------------------------------

    //---<ADLER32 Check>------------------------------------------------------- 
    bool isValidCheck = 0;
    //-------------------------------------------------------------------------
}