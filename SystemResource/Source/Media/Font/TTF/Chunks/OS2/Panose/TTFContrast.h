#pragma once

namespace BF
{
	enum class TTFContrast
	{
		Invalid,

		Any,
		NoFit,
		None,
		VeryLow,
		Low,
		MediumLow,
		Medium,
		MediumHigh,
		High,
		VeryHigh
	};

	TTFContrast ConvertTTFContrast(unsigned char contrast);
}