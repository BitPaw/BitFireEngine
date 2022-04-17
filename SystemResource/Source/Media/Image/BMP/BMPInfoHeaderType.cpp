#include "BMPInfoHeaderType.h"

BF::BMPInfoHeaderType BF::ConvertBMPInfoHeaderType(unsigned int infoHeaderType)
{
    switch (infoHeaderType)
    {
        case 12u:
            //const unsigned char bitMapCoreHeaderSize = 12;
            return BMPInfoHeaderType::OS21XBitMapHeader;

        case 16u:
            return BMPInfoHeaderType::OS22XBitMapHeader;

        case 40u:
            return BMPInfoHeaderType::BitMapInfoHeader;

        case 52u:
            return BMPInfoHeaderType::BitMapV2InfoHeader;

        case 56u:
            return BMPInfoHeaderType::BitMapV3InfoHeader;

        case 108u:
            return BMPInfoHeaderType::BitMapV4Header;

        case 124u:
            return BMPInfoHeaderType::BitMapV5Header;

        default:
            return BMPInfoHeaderType::UnkownOrInvalid;
    }
}

unsigned int BF::ConvertBMPInfoHeaderType(BMPInfoHeaderType infoHeaderType)
{
    switch (infoHeaderType)
    {
        default:
        case BF::BMPInfoHeaderType::UnkownOrInvalid:
            return -1;

        case BF::BMPInfoHeaderType::BitMapCoreHeader:
        case BF::BMPInfoHeaderType::OS21XBitMapHeader:
            return 12u;

        case BF::BMPInfoHeaderType::OS22XBitMapHeader:
            return 16u;

        case BF::BMPInfoHeaderType::BitMapInfoHeader:
            return 40u;

        case BF::BMPInfoHeaderType::BitMapV2InfoHeader:
            return 52u;

        case BF::BMPInfoHeaderType::BitMapV3InfoHeader:
            return 56u;

        case BF::BMPInfoHeaderType::BitMapV4Header:
            return 108u;

        case BF::BMPInfoHeaderType::BitMapV5Header:
            return 124u;
    }
}