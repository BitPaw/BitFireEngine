#pragma once

#include "TTFSubtableFormat0.h"
#include "TTFSubtableFormat2.h"

namespace BF
{
	struct TTFKerningSubtable
	{
		public:
		unsigned short Version;// 	Kern subtable version number
		unsigned short Length;// 	Length of the subtable, in bytes(including this header).
		//unsigned short Coverage;// 	What type of information is contained in this table.

		unsigned char Horizontal;// 	0 	1 	1 if table has horizontal data, 0 if vertical.
		unsigned char Minimum;// 	1 	1 	If this bit is set to 1, the table has minimum values.If set to 0, the table has kerning values.
		unsigned char Cross;// - stream 	2 	1 	If set to 1, kerning is perpendicular to the flow of the text.
		unsigned char Override;//	3 	1 	If this bit is set to 1 the value in this table should replace the value currently being accumulated.
		unsigned char Reserved;// 	4 - 7 	4 	Reserved.This should be set to zero.
		unsigned char Format;// 	8 - 15 	8 	Format of the subtable.Only formats 0 and 2 have been defined.Formats 1 and 3 through 255 are reserved for future use.
	
		TTFSubtableFormat0 SubtableFormat0;
		TTFSubtableFormat2 SubtableFormat2;

		TTFKerningSubtable();

		void ParseCoverageValue(unsigned short coverage);
	};
}
