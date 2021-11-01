#include "PNGColorType.h"

BF::PNGColorType BF::ConvertColorType(unsigned int colorType)
{
    switch (colorType)
    {
        case 0u:
            return PNGColorType::Grayscale;

        case 2u:
            return PNGColorType::Truecolor;

        case 3u:
            return PNGColorType::IndexedColor;

        case 4u:
            return PNGColorType::GrayscaleWithAlphaChannel;

        case 6u:
            return PNGColorType::TruecolorWithAlphaChannel;

        default:
            return PNGColorType::InvalidColorType;
    }
}

unsigned int BF::ConvertColorType(PNGColorType colorType)
{
    switch (colorType)
    {
        default:
        case BF::PNGColorType::InvalidColorType:
            return -1;

        case BF::PNGColorType::Grayscale:
            return 0u;

        case BF::PNGColorType::Truecolor:
            return 2u;

        case BF::PNGColorType::IndexedColor:
            return 3u;

        case BF::PNGColorType::GrayscaleWithAlphaChannel:
            return 4u;

        case BF::PNGColorType::TruecolorWithAlphaChannel:
            return 6u;
    }
}