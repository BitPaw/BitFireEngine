#pragma once

#include <cstddef>

namespace BF
{
	enum class XingInfoVersion
	{
		Invalid,

		Info,
		Xing
	};

	struct XingInfo
	{
		XingInfoVersion Version;
		unsigned int NumberOfFrames;
		unsigned int SizeInBytes;
		char TOCBuffer[100];
		unsigned int VBRScale; // 0-100

		size_t Parse(const unsigned char* data, const size_t dataSize);
	};
}