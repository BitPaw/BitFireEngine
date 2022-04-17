#include "ImageDataFormat.h"

const char* BF::ImageFormatToString(ImageDataFormat imageFormat)
{
	switch (imageFormat)
	{
		case ImageDataFormat::AlphaMaskBinary:
			return "AlphaMaskBinary";

		case ImageDataFormat::AlphaMask:
			return "AlphaMask";

		case ImageDataFormat::RGB:
			return "RGB";

		case ImageDataFormat::RGBA:
			return "RGBA";

		case ImageDataFormat::BGR:
			return "BGR";

		case ImageDataFormat::BGRA:
			return "BGRA";

		default:
			return "Unkown";
	}
}

unsigned int BF::BytesPerPixel(ImageDataFormat imageFormat)
{
	switch (imageFormat)
	{
		case ImageDataFormat::AlphaMask:
			return 2;

		case ImageDataFormat::BGR:
		case ImageDataFormat::RGB:
			return 3;

		case ImageDataFormat::BGRA:
		case ImageDataFormat::RGBA:
			return 4;

		default:
			return -1;
	}
}
