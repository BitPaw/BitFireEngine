#pragma once

#include "TTFVersion.h"

namespace BF
{
	struct TTFOffsetTable
	{
		TTFVersion Version;
		unsigned short NumberOfTables;
		unsigned short SearchRange;
		unsigned short EntrySelctor;
		unsigned short RangeShift;

		TTFOffsetTable();
	};
}