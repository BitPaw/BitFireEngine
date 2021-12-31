#pragma once

namespace BF
{
	enum class TTFProportion
	{
		Invalid,

		Any,
		NoFit,
		OldStyle,
		Modern,
		EvenWidth,
		Expanded,
		Condensed,
		VeryExpanded,
		VeryCondensed,
		Monospaced
	};

	TTFProportion ConvertTTFProportion(unsigned char proportion);
}