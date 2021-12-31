#include "ZLIBCompressionMethod.h"

BF::ZLIBCompressionMethod BF::ConvertCompressionMethod(unsigned char compressionMethod)
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

unsigned char BF::ConvertCompressionMethod(ZLIBCompressionMethod compressionMethod)
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

const char* BF::CompressionMethodToString(ZLIBCompressionMethod compressionMethod)
{
    switch (compressionMethod)
    {
        default:
        case BF::ZLIBCompressionMethod::Invalid:
            return "Invalid";

        case BF::ZLIBCompressionMethod::Deflate:
            return "Deflate";

        case BF::ZLIBCompressionMethod::Reserved:
            return "Reserved";
    }
}
