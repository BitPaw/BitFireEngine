#pragma once

#include "TTFKerningPair.h"

namespace BF
{
	struct TTFSubtableFormat0
	{
		public:
		unsigned short NumberOfPairs; // This gives the number of kerning pairs in the table.
		unsigned short SearchRange; // The largest power of two less than or equal to the value of nPairs, multiplied by the size in bytes of an entry in the table.
		unsigned short EntrySelector; // This is calculated as log2 of the largest power of two less than or equal to the value of nPairs.This value indicates how many iterations of the search loop will have to be made. (For example, in a list of eight items, there would have to be three iterations of the loop).
		unsigned short RangeShift; // The value of nPairs minus the largest power of two less than or equal to nPairs, and then multiplied by the size in bytes of an entry in the table.

		TTFKerningPair* KerningPairList;

		TTFSubtableFormat0();
		~TTFSubtableFormat0();
	};
}