#include "PNGChunkTypeBlock.h"

bool BF::PNGChunkTypeBlock::IsEssential()
{
	unsigned char byte = Value[0];
	bool IsAncillary = byte >= 'A' && byte <= 'Z';

	return IsAncillary;
}

bool BF::PNGChunkTypeBlock::IsRegisteredStandard()
{
	unsigned char byte = Value[2];
	bool IsRegistered = byte >= 'A' && byte <= 'Z';

	return IsRegistered;
}

bool BF::PNGChunkTypeBlock::IsSafeToCopy()
{
	unsigned char byte = Value[3];
	bool IsSaveToCopy = byte >= 'a' && byte <= 'z';

	return IsSaveToCopy;
}

void BF::PNGChunkTypeBlock::Set(unsigned char chunk[4])
{
    Value[0] = chunk[0];
    Value[1] = chunk[1];
    Value[2] = chunk[2];
    Value[3] = chunk[3];

    Type = ConvertChunkType(chunk);
}

BF::PNGChunkType BF::PNGChunkTypeBlock::ConvertChunkType(unsigned char chunk[4])
{
    char byteA = chunk[0];
    char byteB = chunk[1];
    char byteC = chunk[2];
    char byteD = chunk[3];

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
