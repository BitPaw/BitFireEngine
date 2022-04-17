#pragma once

namespace BF
{
	enum class ImageDataFormat
	{
		Unkown,

		AlphaMaskBinary,
		AlphaMask,
		RGB,
		RGBA,


		// Blue Green Red 
		BGR,
		BGRA
	};

	const char* ImageFormatToString(ImageDataFormat imageFormat);
	unsigned int BytesPerPixel(ImageDataFormat imageFormat);
}