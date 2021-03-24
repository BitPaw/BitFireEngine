#pragma once

#include "PNGChunkType.h"
#include "../../../../Utility/List.hpp"

namespace BF
{
	struct PNGChunk
	{
		public:
		// [4-byte] Giving the number of bytes in the chunk's data field. The length counts only the data field, not itself, the chunk type code, or the CRC. Zero is a valid length. Although encoders and decoders should treat the length as unsigned, its value must not exceed 231 bytes. 
		unsigned int Lengh;

		// [4-byte] uppercase and lowercase ASCII letters (A-Z and a-z, or 65-90 and 97-122 decimal).
		unsigned char ChunkType[4];
		PNGChunkType Type;

		// The data bytes appropriate to the chunk type, if any. This field can be of zero length. 
		List<unsigned char> ChunkData;

		/*
				bool IsAncillary();
		bool IsPrivate();
		bool IsReserved();
		bool IsSafeToCopy();
		*/

		// A 4-byte CRC (Cyclic Redundancy Check) calculated on the preceding bytes in the chunk, including the chunk type code and chunk data fields, but not including the length field. The CRC is always present, even for chunks containing no data. See CRC algorithm. 
		unsigned int CRC;

		void Validate();
	};
}