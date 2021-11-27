#pragma once

namespace BF
{
	enum class TTFHeightX
	{
		Invalid,

		Any,
		NoFit,
		ConstantSmall,
		ConstantStandard,
		ConstantLarge,
		DuckingSmall,
		DuckingStandard,
		DuckingLarge
	};

	TTFHeightX ConvertTTFHeightX(unsigned char heightX);
}