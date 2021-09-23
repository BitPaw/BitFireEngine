#include "ZLIBHeader.h"

#include "../../Math/Math.h"
#include "../../Container/BitStreamHusk.h"

#include "../DEFLATE/DeflateBlock.h"
#include "../HUFFMAN/HuffmanSymbol.h"

#include <cassert>

BF::ZLIBHeader::ZLIBHeader()
{
    CompressionMethod = ZLIBCompressionMethod::Invalid;
    CompressionInfo = 0;

    WindowSize = 0;
    CheckFlag = 0;
    DicttionaryPresent = false;
    CompressionLevel = ZLIBCompressionLevel::InvalidCompressionLevel;
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

            // Loop until the last marked DeflateBlock.
            do
            {
                unsigned char deflateBlockValue = subBlockStart[0] & 0b00000111; // Get the next 3 Bits
                
                deflateBlock.Set(deflateBlockValue); // Convert raw blob into unserstandable container.

                // Parse Huffman stuff...
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

                        assert(length == !lengthInverse);

                        //memcpy(0000,0000, length);

                        break;
                    }
                    case DeflateEncodingMethod::HuffmanDynamic:
                    case DeflateEncodingMethod::HuffmanStatic:
                    {
                        if (deflateBlock.EncodingMethod == DeflateEncodingMethod::HuffmanDynamic)
                        {
                            // read representation of code trees
                        }

                        while (false) // TODO
                        {
                            // Get Next ??? what
                            unsigned short value = (subBlockStart[1] & 0b00000111) | subBlockStart[0] & 0b11111000 >> 3;

                            if (value < 256)
                            {
                                // Copy 'value' into outputSteam
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