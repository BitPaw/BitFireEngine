#include "TGABitsPerPixel.h"

BF::TGABitsPerPixel BF::ConvertPixelDepth(unsigned char pixelDepth)
{
	switch (pixelDepth)
	{
		case 1u:
			return TGABitsPerPixel::X1;

		case 8u:
			return TGABitsPerPixel::X8;

		case 15u:
			return TGABitsPerPixel::X15;

		case 16u:
			return TGABitsPerPixel::X16;

		case 24u:
			return TGABitsPerPixel::X24;

		case 32u:
			return TGABitsPerPixel::X32;

		default:
			return TGABitsPerPixel::Invalid;
	}
}

unsigned char BF::ConvertPixelDepth(TGABitsPerPixel bitsPerPixel)
{
	switch (bitsPerPixel)
	{
		default:
		case BF::TGABitsPerPixel::Invalid:
			return -1;

		case BF::TGABitsPerPixel::X1:
			return 1u;

		case BF::TGABitsPerPixel::X8:
			return 8u;

		case BF::TGABitsPerPixel::X15:
			return 15u;

		case BF::TGABitsPerPixel::X16:
			return 16u;

		case BF::TGABitsPerPixel::X24:
			return 24u;

		case BF::TGABitsPerPixel::X32:
			return 32u;
	}
}