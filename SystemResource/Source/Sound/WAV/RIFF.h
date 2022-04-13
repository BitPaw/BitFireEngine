#pragma once

#include <File/Cluster4Byte.h>

namespace BF
{
	// Resource Interchange File Format. 
	struct RIFF
	{
		public:
		Cluster4Byte ChunkID;
		unsigned int ChunkSize;
		char Format[4];

		RIFF();
	};
}