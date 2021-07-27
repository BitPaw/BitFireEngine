#include "ImageFormat.h"

const char* BF::ImageFormatToString(ImageFormat imageFormat)
{
	switch (imageFormat)
	{
		case ImageFormat::BlackAndWhite:
			 return "BW";

			 case 	ImageFormat::RGB:
				 return "RGB";

			 case ImageFormat::RGBA:
				 return "RGBA";

		default:
			return "Unkown";
	}
}
