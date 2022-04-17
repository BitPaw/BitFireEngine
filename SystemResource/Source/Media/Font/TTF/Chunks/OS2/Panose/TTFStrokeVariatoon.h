#pragma once

namespace BF
{
	enum class TTFStrokeVariatoon
	{
		Invalid,

		Any,
		NoFit,
		GradualDiagonal,
		GradualTransitional,
		GradualVertical,
		GradualHorizontal,
		RapidVertical,
		RapidHorizontal,
		InstantVertical
	};

	TTFStrokeVariatoon ConvertTTFStrokeVariatoon(unsigned char strokeVariatoon);
}