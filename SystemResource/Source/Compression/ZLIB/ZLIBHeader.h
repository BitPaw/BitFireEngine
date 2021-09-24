#pragma once

#include "ZLIBCompressionLevel.h"
#include "ZLIBCompressionMethod.h"

namespace BF
{
	struct ZLIBHeader
	{
		private:
	

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
		bool DicttionaryPresent; // 1 Bit
		ZLIBCompressionLevel CompressionLevel; // 2 Bits	


		size_t DataSize;
		char Data[2000];

		ZLIBHeader();

		void Parse(unsigned char* data, unsigned int length);
	};
}