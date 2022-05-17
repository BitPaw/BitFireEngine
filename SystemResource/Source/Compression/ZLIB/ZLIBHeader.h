#pragma once

#include <cstddef>

#include "ZLIBCompressionLevel.h"
#include "ZLIBCompressionMethod.h"

namespace BF
{
	struct ZLIBHeader
	{
		public:
		ZLIBCompressionMethod CompressionMethod; // 4 Bits


		/*
		   4 Bits
		   
		For CM = 8, CINFO is the base-2 logarithm of the LZ77 window size, minus eight
		CINFO = 7 indicates a 32K window size).
		Values of CINFO above 7 are not allowed in this version of the specification.
		CINFO is not defined in this specification for CM not equal to 8.
		*/
		unsigned char CompressionInfo; 
	
		size_t WindowSize;
		unsigned char  CheckFlag; // 5 Bits
		bool DictionaryPresent; // 1 Bit
		ZLIBCompressionLevel CompressionLevel; // 2 Bits

		ZLIBHeader();
		ZLIBHeader(unsigned char compressionFormatByte, unsigned char flagByte);
		ZLIBHeader(ZLIBCompressionMethod compressionMethod);

		void Set(unsigned char compressionFormatByte, unsigned char flagByte);
		void Set(ZLIBCompressionMethod compressionMethod);

		void Parse(unsigned char compressionFormatByte, unsigned char flagByte);
		void Serialize(unsigned char& compressionFormatByte, unsigned char& flagByte);		
	};
}