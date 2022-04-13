#pragma once

namespace BF
{
	// Format header
	struct FMT
	{
		public:
		char ChunkID[4];
		unsigned int ChunkSize;
		unsigned short AudioFormat;
		unsigned short NumerOfChannels;
		unsigned int SampleRate;
		unsigned int ByteRate;
		unsigned short BlockAllign;
		unsigned short BitsPerSample;

		FMT();
	};
}