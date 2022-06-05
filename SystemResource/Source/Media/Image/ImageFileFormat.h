#pragma once

namespace BF
{
	enum class ImageFileFormat
	{
		Unkown,

		BitMap,
		PNG,
		TGA,

		JPEG, // Joint Photographic Experts Group
		TIFF, 
		GIF
	};

	ImageFileFormat ConvertImageFileFormat(const unsigned int imageFileFormatID);
	unsigned int ConvertImageFileFormat(const ImageFileFormat imageFileFormat);
}