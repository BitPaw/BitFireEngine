#pragma once

#include "ZLIBHeader.h"
#include "../../Algorithm/Adler32.h"

namespace BF
{
	struct ZLIB
	{
		public:
		ZLIBHeader Header;

		size_t CompressedDataSize;
		unsigned char* CompressedData;

		Adler32 AdlerChecksum;

		ZLIB(unsigned char* inputData, size_t inputDataSize);

		void Parse(unsigned char* inputData, size_t inputDataSize);
	};
}