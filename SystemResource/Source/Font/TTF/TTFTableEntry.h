#pragma once

#include "TTFTableEntryType.h"

namespace BF
{
	struct TTFTableEntry
	{
		public:
		char TypeRaw[4];
		TTFTableEntryType Type;
		unsigned int CheckSum;
		unsigned int Offset;
		unsigned int Length;

		TTFTableEntry();
	};
}