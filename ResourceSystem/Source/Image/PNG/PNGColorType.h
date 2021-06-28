#pragma once

namespace BF
{
	enum class PNGColorType
	{
		Grayscale, // ColorType = 0
		Truecolor,  // ColorType = 2
		IndexedColor,  // ColorType = 3
		GrayscaleWithAlphaChannel,  // ColorType = 4
		TruecolorWithAlphaChannel  // ColorType = 6
	};
}