#include "ZLIBCompressionLevel.h"

BF::ZLIBCompressionLevel BF::ConvertCompressionLevel(unsigned char compressionLevel)
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

unsigned char BF::ConvertCompressionLevel(ZLIBCompressionLevel compressionLevel)
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