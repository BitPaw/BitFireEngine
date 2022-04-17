#pragma once

#include "TTFKerningSubtable.h"

namespace BF
{
	struct TTFKerning
	{
		public:
		unsigned short Version;// Table version number(0)
		unsigned short NumberOfSubtables;// Number of subtables in the kerning table.
		TTFKerningSubtable* KerningSubtableList;

		TTFKerning();
		~TTFKerning();
	};
}