#pragma once

#include <cstddef>

namespace BF
{
	struct PNGPaletteHistogram
	{
		public:
		size_t ColorFrequencyListSize;
		unsigned short* ColorFrequencyList;
	};
}