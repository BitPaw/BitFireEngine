#pragma once

#include "RIFFFormat.h"

#include <cstddef>

#include <File/Endian.h>

namespace BF
{
	// Resource Interchange File Format. 
	struct RIFF
	{
		public:
		bool Valid;
		Endian EndianFormat;
		unsigned int ChunkSize;
		RIFFFormat Format;

		RIFF();
	
		size_t Parse(const unsigned char* data, const size_t dataSize);
	};
}