#pragma once

#include "../../../Mathematic/Math.h"
#include "../../../Utility/List.hpp"

namespace BF
{
	struct ZLibHeader
	{
		public:
		unsigned char CompressionMethod;
		unsigned char CompressionInfo;

		bool IsCheckValid;
		unsigned char Check;

		bool HasDictionary;
		unsigned char Level;

		List<unsigned char> DeflateCompressedBlock;

		bool Adeler32CheckValid;
		unsigned char Adeler32CheckValue;

		/*
		Max: 32768 bytes.
		Min: 256 Bytes
		<= 16384 bytes willbe rounded to a power of 2
		2^(CINFO + 8) [+8 because.. documentation]
		*/
		unsigned int LZ77WindowSize;

		ZLibHeader()
		{
			CompressionMethod = 0;
			CompressionInfo = 0;
		
			Check = 0;
			HasDictionary = 0;
			Level = 0;

			Adeler32CheckValue = 0;	

			IsCheckValid = false;
			Adeler32CheckValid = false;
			LZ77WindowSize = 0;
		}

		void FillMissingData()
		{
			unsigned char compressionField = CompressionMethod | CompressionInfo;
			unsigned char flagField = Check | HasDictionary | Level;

			// (CMF*256 + FLG) is a multiple of 31
			IsCheckValid = ((unsigned int)compressionField * 256 + (unsigned int)flagField) % 31 == 0;

			LZ77WindowSize = Math::Power(2, CompressionInfo + 8);
		}
	};
}