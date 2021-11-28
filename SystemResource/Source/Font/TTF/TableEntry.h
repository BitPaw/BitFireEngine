#pragma once

#include "TableEntryType.h"

namespace BF::TTF
{
	struct TableEntry
	{
		public:
		char TypeRaw[4];
		TableEntryType Type;
		unsigned int CheckSum;
		unsigned int Offset;
		unsigned int Length;

		TableEntry();
	};
}