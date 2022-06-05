#include "IImageFormat.h"

BF::ImageFileFormat BF::ConvertImageFileFormat(const unsigned int imageFileFormatID)
{
	switch(imageFileFormatID)
	{
		case (unsigned int)ImageFileFormat::BitMap:return ImageFileFormat::BitMap;
		case (unsigned int)ImageFileFormat::PNG:return ImageFileFormat::PNG;
		case (unsigned int)ImageFileFormat::TGA:return ImageFileFormat::TGA;
		case (unsigned int)ImageFileFormat::JPEG:return ImageFileFormat::JPEG;
		case (unsigned int)ImageFileFormat::TIFF:return ImageFileFormat::TIFF;
		case (unsigned int)ImageFileFormat::GIF: return ImageFileFormat::GIF;

		default:
			return ImageFileFormat::Unkown;
	}
}

unsigned int BF::ConvertImageFileFormat(const ImageFileFormat imageFileFormat)
{
	return 0;
}