#pragma once

#include "PlatformID.h"
#include "EncodingID.h"

namespace BF::TTF::CMAP
{
	struct EncodingRecord
	{
		public:
		PlatformID Platform;
		EncodingID Encoding; // Platform specific.
		unsigned int SubtableOffset;// 	Byte offset from beginning of table to the subtable for this encoding.

		EncodingRecord();
	};
}