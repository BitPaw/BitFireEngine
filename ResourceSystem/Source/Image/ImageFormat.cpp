#include "ImageFormat.h"

const char* BF::ImageFormatToString(ImageFormat imageFormat)
{
	switch (imageFormat)
	{
		case ImageFormat::AlphaMaskBinary:
			return "AlphaMaskBinary";

		case ImageFormat::AlphaMask:
			return "AlphaMask";

		case ImageFormat::RGB:
			return "RGB";

		case ImageFormat::RGBA:
			return "RGBA";

		case ImageFormat::BGR:
			return "BGR";

		case ImageFormat::BGRA:
			return "BGRA";

		default:
			return "Unkown";
	}
}

unsigned int BF::BytesPerPixel(ImageFormat imageFormat)
{
	switch (imageFormat)
	{
		case ImageFormat::AlphaMask:
			return 2;

		case ImageFormat::BGR:
		case ImageFormat::RGB:
			return 3;

		case ImageFormat::BGRA:
		case ImageFormat::RGBA:
			return 4;

		default:
			return -1;
	}
}
