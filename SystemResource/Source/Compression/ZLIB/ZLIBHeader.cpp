#include "ZLIBHeader.h"

#include <cassert>
#include <string>

#include "../../Math/Math.h"

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

void BF::ZLIBHeader::Parse(unsigned char compressionFormatByte, unsigned char flagByte)
{
    // Valid Check
    {
        bool validFlags = ((unsigned int)compressionFormatByte * 256u + (unsigned int)flagByte) % 31u == 0;

        assert(validFlags);
    }

    //---<Parse First Byte - Compression Info>---------------------------------
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

    //---<Parse Second Byte - Flags>-------------------------------------------
    {
        unsigned char compressionLevelValue = (flagByte & 0b11000000) >> 6;

        CheckFlag = (flagByte & 0b00011111);
        DictionaryPresent = ((flagByte & 0b00100000) >> 5) == 1;

        CompressionLevel = ConvertCompressionLevel(compressionLevelValue);
    }
    //-------------------------------------------------------------------------      
}