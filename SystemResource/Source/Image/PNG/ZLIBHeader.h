#pragma once

#include "ZLIBCompressionLevel.h"
#include "ZLIBCompressionMethod.h"

namespace BF
{
	struct ZLIBHeader
	{
		private:
		static inline ZLIBCompressionLevel ConvertCompressionLevel(unsigned char compressionLevel);
		static inline unsigned char ConvertCompressionLevel(ZLIBCompressionLevel compressionLevel);

		static inline ZLIBCompressionMethod ConvertCompressionMethod(unsigned char compressionMethod);
		static inline unsigned char ConvertCompressionMethod(ZLIBCompressionMethod compressionMethod);

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

		ZLIBHeader();

		void Parse(unsigned char* data, unsigned int length);
	};
}