#pragma once

namespace BF
{
	enum class PNGColorType
	{
		InvalidColorType,

		Grayscale, // ColorType = 0
		Truecolor,  // ColorType = 2
		IndexedColor,  // ColorType = 3
		GrayscaleWithAlphaChannel,  // ColorType = 4
		TruecolorWithAlphaChannel  // ColorType = 6
	};

	const char* PNGColorTypeToString(PNGColorType pngColorType);

	PNGColorType ConvertColorType(unsigned int colorType);
	unsigned int ConvertColorType(PNGColorType colorType);

	unsigned int NumberOfColorChannels(PNGColorType pngColorType);
}