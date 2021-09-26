#pragma once

#include "PNGChunkType.h"

namespace BF
{
	struct PNGChunkTypeBlock
	{
		public:
		unsigned char Value[4];
		PNGChunkType Type;

		bool IsEssential(); // Ancillary Bit - Is this chunk not replaceable?.
		bool IsRegisteredStandard(); // Private Bit - Is this chunk in the offically registered in any way?  
		bool IsSafeToCopy(); // Can this cunk be modifyed anyhow or does it have a depecdency on the imagedata?


		void Set(unsigned char chunk[4]);

		static inline PNGChunkType ConvertChunkType(unsigned char chunk[4]);
	};
}