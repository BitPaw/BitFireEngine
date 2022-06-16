#pragma once

#include <cstddef>

#include <File/Endian.h>

namespace BF
{
	// Format header
	struct FMT
	{
		public:
		unsigned int ChunkSize;
		unsigned short AudioFormat;
		unsigned short NumerOfChannels;
		unsigned int SampleRate;
		unsigned int ByteRate;
		unsigned short BlockAllign;
		unsigned short BitsPerSample;

		FMT();

		size_t Parse(const unsigned char* data, const size_t dataSize, const Endian endian);
	};
}