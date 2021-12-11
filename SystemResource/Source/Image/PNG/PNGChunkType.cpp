#include "PNGChunkType.h"

BF::PNGChunkType BF::ConvertChunkType(unsigned char chunk[4])
{
    unsigned char byteA = chunk[0];
    unsigned char byteB = chunk[1];
    unsigned char byteC = chunk[2];
    unsigned char byteD = chunk[3];

    switch (byteA)
    {
        case 'I':
        {
            if (byteB == 'H' && byteC == 'D' && byteD == 'R') return PNGChunkType::ImageHeader;
            if (byteB == 'D' && byteC == 'A' && byteD == 'T') return PNGChunkType::ImageData;
            if (byteB == 'E' && byteC == 'N' && byteD == 'D') return PNGChunkType::ImageEnd;
            break;
        }

        case 'i':
        {
            if (byteB == 'C' && byteC == 'C' && byteD == 'P') return PNGChunkType::EmbeddedICCProfile; // iCCP
            if (byteB == 'T' && byteC == 'X' && byteD == 't') return PNGChunkType::Transparency; // iTXt
            break;
        }

        case 's':
        {
            if (byteB == 'B' && byteC == 'I' && byteD == 'T') return PNGChunkType::SignificantBits; // sBIT
            if (byteB == 'R' && byteC == 'G' && byteD == 'B') return PNGChunkType::StandardRGBColorSpace; // sRGB
            break;
        }

        case 't':
        {
            if (byteB == 'R' && byteC == 'N' && byteD == 'S') return PNGChunkType::Transparency; // tRNS
            if (byteB == 'E' && byteC == 'X' && byteD == 't') return PNGChunkType::Transparency; // tEXt
            if (byteB == 'I' && byteC == 'M' && byteD == 'E') return PNGChunkType::LastModificationTime; // tIME
            break;
        }

        default:
        {
            if (byteA == 'P' && byteB == 'L' && byteC == 'T' && byteD == 'E') return PNGChunkType::Palette;

            if (byteA == 'c' && byteB == 'H' && byteC == 'R' && byteD == 'M') return PNGChunkType::PrimaryChromaticities; // cHRM
            if (byteA == 'g' && byteB == 'A' && byteC == 'M' && byteD == 'A') return PNGChunkType::ImageGamma; // gAMA
            if (byteA == 'b' && byteB == 'K' && byteC == 'G' && byteD == 'D') return PNGChunkType::BackgroundColor; // bKGD
            if (byteA == 'h' && byteB == 'I' && byteC == 'S' && byteD == 'T') return PNGChunkType::PaletteHistogram; // hIST   
            if (byteA == 'p' && byteB == 'H' && byteC == 'Y' && byteD == 's') return PNGChunkType::PhysicalPixelDimensions; //pHYs
            if (byteA == 's' && byteB == 'P' && byteC == 'L' && byteD == 'T') return PNGChunkType::Transparency; // sPLT    
            if (byteA == 'z' && byteB == 'T' && byteC == 'X' && byteD == 't') return PNGChunkType::Transparency; // zTXt

            break;
        }
    }

    return PNGChunkType::Invalid;
}

void BF::ConvertChunkType(unsigned char chunk[4], PNGChunkType pngchunkType)
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