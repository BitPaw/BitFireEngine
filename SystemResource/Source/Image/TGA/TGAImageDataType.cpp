#include "TGAImageDataType.h"

BF::TGAImageDataType BF::ConvertImageDataType(unsigned char id)
{
	switch (id)
	{
		case 0u:
			return TGAImageDataType::NoImageDataIsPresent;

		case 1u:
			return TGAImageDataType::UncompressedColorMapped;

		case 2u:
			return TGAImageDataType::UncompressedTrueColor;

		case 3u:
			return TGAImageDataType::UncompressedBlackAndWhite;

		case 9u:
			return TGAImageDataType::RunLengthEncodedColorMapped;

		case 10u:
			return TGAImageDataType::RunLengthEncodedTrueColor;

		case 11u:
			return TGAImageDataType::RunLengthEncodedBlackAndWhite;

		default:
			return TGAImageDataType::UnkownImageDataType;
	}
}

unsigned char BF::ConvertImageDataType(TGAImageDataType imageDataType)
{
	switch (imageDataType)
	{
		default:
		case BF::TGAImageDataType::UnkownImageDataType:
			return -1;

		case BF::TGAImageDataType::NoImageDataIsPresent:
			return 0;

		case BF::TGAImageDataType::UncompressedColorMapped:
			return 1u;

		case BF::TGAImageDataType::UncompressedTrueColor:
			return 2u;

		case BF::TGAImageDataType::UncompressedBlackAndWhite:
			return 3u;

		case BF::TGAImageDataType::RunLengthEncodedColorMapped:
			return 9u;

		case BF::TGAImageDataType::RunLengthEncodedTrueColor:
			return 10u;

		case BF::TGAImageDataType::RunLengthEncodedBlackAndWhite:
			return 11u;
	}
}
