#include "PNGChunkType.h"

#define MakeInt(a, b, c, d) ((unsigned int)a << 24) | ((unsigned int)b << 16) | ((unsigned int)c << 8) | ((unsigned int)d)

constexpr const unsigned int BF::PNGChunkTypeIDMake(const char a, const char b, const char c, const char d)
{
    PNGChunkTypeID chunkTypeID{ a, b, c, d };

    return chunkTypeID.Value;
}

BF::PNGChunkType BF::ConvertChunkType(const PNGChunkTypeID chunkTypeID)
{
    switch (chunkTypeID.Value)
    {
        case MakeInt('I', 'H', 'D', 'R'): return PNGChunkType::ImageHeader; // IHDR
        case MakeInt('I', 'D', 'A', 'T'): return PNGChunkType::ImageData; // PLTE
        case MakeInt('I', 'E', 'N', 'D'): return PNGChunkType::ImageEnd; // IEND
        case MakeInt('i', 'C', 'C', 'P'): return PNGChunkType::EmbeddedICCProfile; // iCCP
        case MakeInt('i', 'T', 'X', 't'): return PNGChunkType::Transparency; // tRNS
        case MakeInt('s', 'B', 'I', 'T'): return PNGChunkType::SignificantBits; // sBIT
        case MakeInt('s', 'R', 'G', 'B'): return PNGChunkType::StandardRGBColorSpace; // sRGB
        case MakeInt('t', 'R', 'N', 'S'): return PNGChunkType::Transparency; // tRNS
        case MakeInt('t', 'E', 'X', 't'): return PNGChunkType::TextualData; // tEXt
        case MakeInt('t', 'I', 'M', 'E'): return PNGChunkType::LastModificationTime; // tIME
        case MakeInt('P', 'L', 'T', 'E'): return PNGChunkType::Palette; // PLTE
        case MakeInt('c', 'H', 'R', 'M'): return PNGChunkType::PrimaryChromaticities; // cHRM
        case MakeInt('g', 'A', 'M', 'A'): return PNGChunkType::ImageGamma;// gAMA
        case MakeInt('b', 'K', 'G', 'D'): return PNGChunkType::BackgroundColor;// bKGD
        case MakeInt('h', 'I', 'S', 'T'): return PNGChunkType::PaletteHistogram;// hIST   
        case MakeInt('p', 'H', 'Y', 's'): return PNGChunkType::PhysicalPixelDimensions; //pHYs
        case MakeInt('s', 'P', 'L', 'T'): return PNGChunkType::SuggestedPalette;// sPLT   
        case MakeInt('z', 'T', 'X', 't'): return PNGChunkType::CompressedTextualData;// zTXt

        default: return PNGChunkType::Invalid;
    }
}

void BF::ConvertChunkType(PNGChunkTypeID& chunkTypeID, const PNGChunkType pngchunkType)
{
    // TODO: implement
}

const char* BF::ChunkTypeToString(PNGChunkType pngchunkType)
{
    switch (pngchunkType)
    {
        default:
        case BF::PNGChunkType::Invalid:
            return "Invalid";

        case BF::PNGChunkType::ImageHeader:
            return "Image Header";

        case BF::PNGChunkType::Palette:
            return "Palette";

        case BF::PNGChunkType::ImageData:
            return "Image Data";

        case BF::PNGChunkType::ImageEnd:
            return "Image End";

        case BF::PNGChunkType::Transparency:
            return "Transparency";

        case BF::PNGChunkType::ImageGamma:
            return "ImageGamma";

        case BF::PNGChunkType::PrimaryChromaticities:
            return "Primary Chromaticities";

        case BF::PNGChunkType::StandardRGBColorSpace:
            return "Standard RGB ColorSpace";

        case BF::PNGChunkType::EmbeddedICCProfile:
            return "Embedded ICC Profile";

        case BF::PNGChunkType::TextualData:
            return "Textual Data";

        case BF::PNGChunkType::CompressedTextualData:
            return "Compressed TextualData";

        case BF::PNGChunkType::InternationalTextualData:
            return "International TextualData";

        case BF::PNGChunkType::BackgroundColor:
            return "Background Color";

        case BF::PNGChunkType::PhysicalPixelDimensions:
            return "Physical Pixel Dimensions";

        case BF::PNGChunkType::SignificantBits:
            return "Significant Bits";

        case BF::PNGChunkType::SuggestedPalette:
            return "Suggested Palette";

        case BF::PNGChunkType::PaletteHistogram:
            return "Palette Histogram";

        case BF::PNGChunkType::LastModificationTime:
            return "Last Modification Time";

        case BF::PNGChunkType::Custom:
            return "Custom";

     }
}