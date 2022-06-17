#pragma once

#include <cstddef>

namespace BF
{
	struct OGGPage
	{
		unsigned char Version; // Often a zero
		unsigned char HeaderType;
		unsigned long long GranulePosition; // 8 Bytes
		unsigned int SerialNumber;
		unsigned int SequenceNumber;
		unsigned int CRC32CheckSum; // CRC32, is generated using a polynomial value of 0x04C11DB7.
		unsigned char PageSegments;
	};
}
