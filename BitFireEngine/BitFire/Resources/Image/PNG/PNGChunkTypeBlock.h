#pragma once

#include "PNGChunkType.h"
#include "../../../Utility/DoubleWord.h"

namespace BF
{
	struct PNGChunkTypeBlock
	{
		public:
		DoubleWord Value;
		PNGChunkType Type;

		bool IsEssential(); // Ancillary Bit - Is this chunk not replaceable?.
		bool IsRegisteredStandard(); // Private Bit - Is this chunk in the offically registered in any way?  
		bool IsSafeToCopy(); // Can this cunk be modifyed anyhow or does it have a depecdency on the imagedata?
	};
}