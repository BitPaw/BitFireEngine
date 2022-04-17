#pragma once

#include <File/ByteCluster.h>

#include "RIFFFormat.h"

#include <cstddef>
#include <File/Endian.h>
#include <File/FileStream.h>


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
	
		void Parse(FileStream& fileStream);
	};
}