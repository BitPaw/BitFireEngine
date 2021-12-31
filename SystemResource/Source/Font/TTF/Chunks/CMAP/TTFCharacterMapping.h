#pragma once

#include "EncodingRecord.h"

namespace BF
{
	struct TTFCharacterMapping
	{
		public:
		// Header

		unsigned short Version; // Table version number(0).
		unsigned short NumberOfTables; // Number of encoding tables that follow.
		EncodingRecord* EncodingRecordList;

		TTFCharacterMapping();
	};
}