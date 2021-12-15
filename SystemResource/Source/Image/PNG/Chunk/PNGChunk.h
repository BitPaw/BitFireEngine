#pragma once

#include "PNGChunkType.h"

namespace BF
{
	struct PNGChunk
	{
		public: 
		bool IsEssential; // Ancillary Bit - Is this chunk not replaceable?.
		bool IsRegisteredStandard; // Private Bit - Is this chunk in the offically registered in any way?  
		bool IsSafeToCopy;  // Can this cunk be modifyed anyhow or does it have a depecdency on the imagedata?

		// [4-byte] Giving the number of bytes in the chunk's data field. The length counts only the data field, not itself, the chunk type code, or the CRC. Zero is a valid length. Although encoders and decoders should treat the length as unsigned, its value must not exceed 231 bytes. 
		unsigned int Lengh;

		unsigned char ChunkTypeRaw[4];

		// [4-byte] uppercase and lowercase ASCII letters (A-Z and a-z, or 65-90 and 97-122 decimal).
		PNGChunkType ChunkType;

		// The data bytes appropriate to the chunk type, if any. This field can be of zero length. 
		unsigned char* ChunkData;

		// A 4-byte CRC (Cyclic Redundancy Check) calculated on the preceding bytes in the chunk, including the chunk type code and chunk data fields, but not including the length field. The CRC is always present, even for chunks containing no data. See CRC algorithm. 
		
		bool CRCOK; 
		unsigned int CRC;
		

		void Check();

		PNGChunk();	
	};
}