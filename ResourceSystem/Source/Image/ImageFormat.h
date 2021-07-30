#pragma once

namespace BF
{
	enum class ImageFormat
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

	const char* ImageFormatToString(ImageFormat imageFormat);
	unsigned int BytesPerPixel(ImageFormat imageFormat);
}