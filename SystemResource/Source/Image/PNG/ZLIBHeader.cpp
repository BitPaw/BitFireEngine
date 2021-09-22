#include "ZLIBHeader.h"

#include "../../Math/Math.h"
#include "DeflateBlock.h"
#include "../../Container/BitStreamHusk.h"
#include <cassert>

BF::ZLIBCompressionLevel BF::ZLIBHeader::ConvertCompressionLevel(unsigned char compressionLevel)
{
    switch (compressionLevel)
    {
        case 0u:
            return BF::ZLIBCompressionLevel::Fastest;

        case 1u:
            return BF::ZLIBCompressionLevel::Fast;

        case 2u:
            return BF::ZLIBCompressionLevel::Default;

        case 3u:
            return BF::ZLIBCompressionLevel::Slowest;

        default:
            return BF::ZLIBCompressionLevel::InvalidCompressionLevel;
    }
}

unsigned char BF::ZLIBHeader::ConvertCompressionLevel(ZLIBCompressionLevel compressionLevel)
{
    switch (compressionLevel)
    {
        default:
        case BF::ZLIBCompressionLevel::InvalidCompressionLevel:
            return -1;

        case BF::ZLIBCompressionLevel::Default:
            return 2u;

        case BF::ZLIBCompressionLevel::Slowest:
            return 3u;

        case BF::ZLIBCompressionLevel::Fast:
            return 1u;

        case BF::ZLIBCompressionLevel::Fastest:
            return 0u;
    }
}

BF::ZLIBCompressionMethod BF::ZLIBHeader::ConvertCompressionMethod(unsigned char compressionMethod)
{
    switch (compressionMethod)
    {
        case 8u:
            return BF::ZLIBCompressionMethod::Deflate;

        case 15u:
            return BF::ZLIBCompressionMethod::Reserved;

        default:
            return BF::ZLIBCompressionMethod::Invalid;
    }
}

unsigned char BF::ZLIBHeader::ConvertCompressionMethod(ZLIBCompressionMethod compressionMethod)
{
    switch (compressionMethod)
    {
        default:
        case BF::ZLIBCompressionMethod::Invalid:
            return -1;

        case BF::ZLIBCompressionMethod::Deflate:
            return 8u;

        case BF::ZLIBCompressionMethod::Reserved:
            return 15u;
    }
}

BF::ZLIBHeader::ZLIBHeader()
{
    CompressionMethod = ZLIBCompressionMethod::Invalid;
    CompressionInfo = 0;

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
        default:
        case BF::ZLIBCompressionMethod::Invalid:
        {
            break;
        }
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


            }
            while (!deflateBlock.IsLastBlock);

            break;
        }
        case BF::ZLIBCompressionMethod::Reserved:
        {
            break;
        }
    }
    //-------------------------------------------------------------------------

    //---<ADLER32 Check>------------------------------------------------------- 
    bool isValidCheck = 0;
    //-------------------------------------------------------------------------
}