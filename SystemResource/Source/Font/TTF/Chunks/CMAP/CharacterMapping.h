#pragma once

#include "EncodingRecord.h"

namespace BF::TTF::CMAP
{
	struct CharacterMapping
	{
		public:
		// Header

		unsigned short Version; // Table version number(0).
		unsigned short NumberOfTables; // Number of encoding tables that follow.
		EncodingRecord* EncodingRecordList;

		CharacterMapping();
	};
}