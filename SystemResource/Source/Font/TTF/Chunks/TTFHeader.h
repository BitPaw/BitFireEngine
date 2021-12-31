#pragma once

#include "TTFVersion.h"

namespace BF
{
	struct TTFHeader
	{
		public:
		TTFVersion Version;
		TTFVersion Revision;

		unsigned int CheckSumAdjustment;
		unsigned int MagicNumber;
		unsigned short Flags;
		unsigned short UnitsPerEM;
		unsigned long long Created;
		unsigned long long Modified;
		short Minimum[2];
		short Maximum[2];
		unsigned short MacStyle;
		unsigned short LowestRecPpem;
		short FontDirectionHint;
		short IndexToLocFormat;
		short GlyphDataFormat;

		TTFHeader();
	};
}