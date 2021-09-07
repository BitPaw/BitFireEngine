#pragma once

namespace BF
{
	// Resource Interchange File Format. 
	struct RIFF
	{
		public:
		char ChunkID[4];
		unsigned int ChunkSize;
		char Format[4];

		RIFF();
		RIFF(unsigned int chunkID, unsigned int chunkSize, unsigned int format);
	};
}