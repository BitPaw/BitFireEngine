#pragma once

namespace BF
{
	enum class TGABitsPerPixel
	{
		Invalid,

		X1,
		X8,
		X15,
		X16,
		X24,
		X32
	};

	TGABitsPerPixel ConvertPixelDepth(unsigned char pixelDepth);
	unsigned char ConvertPixelDepth(TGABitsPerPixel bitsPerPixel);
}