#pragma once

#include "TIFF/TIFF.h"
#include "JPEG/JPEG.h"
#include "GIF/GIF.h"
#include "TGA/TGA.h"
#include "BMP/BMP.h"

#include "Image.h"
#include "ImageFileExtension.h"

#include "../../IO/File/TextFile.h"
#include "../../IO/Log/Log.h"

namespace BF
{
	class ImageLoader
	{
	public:
		static Image* LoadFromFile(AsciiString& filePath);

		static ImageFileExtension CheckImageFormat(AsciiString& fileExtension);

		static bool IsImageFileExtension(AsciiString& fileExtension);
	};
}