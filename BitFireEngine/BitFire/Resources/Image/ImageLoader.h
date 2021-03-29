#pragma once

#include "TIFF/TIFF.h"
#include "JPEG/JPEG.h"
#include "GIF/GIF.h"
#include "TGA/TGA.h"
#include "BMP/BMP.h"

#include "Image.h"
#include "ImageFileExtension.h"

#include "../ErrorCode.h"

namespace BF
{
	class ImageLoader
	{
	public:
		static ErrorCode LoadFromFile(AsciiString& filePath, Image& image);

		static ImageFileExtension CheckImageFormat(AsciiString& fileExtension);

		static bool IsImageFileExtension(AsciiString& fileExtension);
	};
}