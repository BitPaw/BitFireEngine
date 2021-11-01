#pragma once

namespace BF
{
	struct AVIHeader
	{
		public:
		unsigned int MicroSecPerFrame; // frame display rate (or 0)
		unsigned int MaxBytesPerSec; // max. transfer rate
		unsigned int PaddingGranularity; // pad to multiples of this
		// size;
		unsigned int Flags; // the ever-present flags
		unsigned int TotalFrames; // # frames in file
		unsigned int InitialFrames;
		unsigned int Streams;
		unsigned int SuggestedBufferSize;
		unsigned int Width;
		unsigned int Height;
		unsigned int Reserved[4];
	};
}