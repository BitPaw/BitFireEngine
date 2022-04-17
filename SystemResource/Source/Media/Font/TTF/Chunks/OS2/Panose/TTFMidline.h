#pragma once

namespace BF
{
	enum class TTFMidline
	{
		Invalid,

		Any,
		NoFit,
		StandardTrimmed,
		StandardPointed,
		StandardSerifed,
		HighTrimmed,
		HighPointed,
		HighSerifed,
		ConstantTrimmed,
		ConstantPointed,
		ConstantSerifed,
		LowTrimmed,
		LowPointed,
		LowSerifed
	};

	TTFMidline ConvertTTFMidline(unsigned char midline);
}