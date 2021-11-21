#pragma once

#include "DeflateEncodingMethod.h"

namespace BF
{
	struct DeflateBlock
	{
		public:
		bool IsLastBlock;
		DeflateEncodingMethod EncodingMethod;

		DeflateBlock();

		void Inflate(unsigned char* dataIn, size_t dataInSize, unsigned char* dataOut, size_t& dataOutSize);
		void Deflalate(unsigned char* dataIn, size_t dataInSize, unsigned char* dataOut, size_t& dataOutSize);
	};
}