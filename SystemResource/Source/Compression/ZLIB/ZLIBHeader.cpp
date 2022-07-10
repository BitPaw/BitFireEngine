#include "ZLIBHeader.h"

#include <cassert>

#include <Math/Math.h>

BF::ZLIBHeader::ZLIBHeader()
{
    CompressionMethod = ZLIBCompressionMethod::Invalid;
    CompressionInfo = 0;

    CheckFlag = 0;
    DictionaryPresent = false;
    CompressionLevel = ZLIBCompressionLevel::InvalidCompressionLevel;

    WindowSize = 0;
}

BF::ZLIBHeader::ZLIBHeader(unsigned char compressionFormatByte, unsigned char flagByte)
{
    Parse(compressionFormatByte, flagByte);
}

BF::ZLIBHeader::ZLIBHeader(ZLIBCompressionMethod compressionMethod)
{
    Set(compressionMethod);
}

void BF::ZLIBHeader::Set(unsigned char compressionFormatByte, unsigned char flagByte)
{
    Parse(compressionFormatByte, flagByte);
}

void BF::ZLIBHeader::Set(ZLIBCompressionMethod compressionMethod)
{
    switch (compressionMethod)
    {
        case BF::ZLIBCompressionMethod::Deflate:
        {
            CompressionMethod = ZLIBCompressionMethod::Deflate;
            CompressionInfo = 7;
            CheckFlag = 0;
            DictionaryPresent = false;
            CompressionLevel = ZLIBCompressionLevel::Fastest;

            WindowSize = 0;

            break;
        }
           
        case BF::ZLIBCompressionMethod::Invalid:
        case BF::ZLIBCompressionMethod::Reserved:
        default:
            break;
    }
}

void BF::ZLIBHeader::Parse(unsigned char compressionFormatByte, unsigned char flagByte)
{
    // Valid Check
    {
        bool validFlags = ((unsigned int)compressionFormatByte * 256u + (unsigned int)flagByte) % 31u == 0;

        assert(validFlags);
    }

    //---<Parse First Byte__ - Compression Info>---------------------------------
    {
        unsigned char compressionMethodValue = (compressionFormatByte & 0b00001111);
        CompressionMethod = ConvertCompressionMethod(compressionMethodValue);

        CompressionInfo = (compressionFormatByte & 0b11110000) >> 4;

        // log_2(WindowSize) - 8 = CompressionInfo
        // log_2(32768) - 8 = 7
        // 2^(CompressionInfo + 8)

        assert(CompressionInfo <= 7u);

        WindowSize = Math::Power(2, CompressionInfo + 8);      
    }
    //-------------------------------------------------------------------------

    //---<Parse Second Byte__ - Flags>-------------------------------------------
    {
        unsigned char compressionLevelValue = (flagByte & 0b11000000) >> 6;

        CheckFlag = (flagByte & 0b00011111);
        DictionaryPresent = ((flagByte & 0b00100000) >> 5) == 1;

        CompressionLevel = ConvertCompressionLevel(compressionLevelValue);
    }
    //-------------------------------------------------------------------------      
}

void BF::ZLIBHeader::Serialize(unsigned char& compressionFormatByte, unsigned char& flagByte)
{
    //---<Parse First Byte__ - Compression Info>---------------------------------
    {
        unsigned char WindowSizeValue = Math::LogarithmusBase2(WindowSize) - 8;
        unsigned char compressionMethodValue = ConvertCompressionMethod(CompressionMethod);

        compressionFormatByte = compressionMethodValue << 4; // 0b11110000
        compressionFormatByte += WindowSizeValue; // 0b00001111 
    }
    //-------------------------------------------------------------------------

    //---<Parse Second Byte__ - Flags>-------------------------------------------
    {
        unsigned char compressionLevelValue = ConvertCompressionLevel(CompressionLevel);

        flagByte |= compressionLevelValue << 6;
        flagByte |= DictionaryPresent << 5;
        flagByte |= CheckFlag;
    }
    //-------------------------------------------------------------------------    
}