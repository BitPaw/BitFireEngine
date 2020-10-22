#pragma once

#include <string>

#include "TIFF/TIFF.h"
#include "JPEG/JPEG.h"
#include "GIF/GIF.h"

#include "BMP/BMPLoader.h"
#include "GIF/GIFLoader.h"
#include "JPEG/JPEGLoader.h"
#include "PNG/PNGLoader.h"
#include "TIFF/TIFFLoader.h"

#include "IImage.h"
#include "Image.h"
#include "ImageFormat.h"

#include "../../IO/File/TextFile.h"
#include "../../IO/Message/MessageSystem.h"

namespace BF
{
	class ImageLoader
	{
	public:
		static IImage* LoadFromFile(std::string filePath);

		static Image* BMPToImage(BMP* bitmap);
		static Image* GIFToImage(GIF* bitmap);
		static Image* JPEGToImage(JPEG* bitmap);
		static Image* PNGToImage(PNG* bitmap);
		static Image* TIFFToImage(TIFF* bitmap);
	};
}