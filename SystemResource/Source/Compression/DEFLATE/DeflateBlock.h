#pragma once

#include "DeflateEncodingMethod.h"
#include "../../Container/BitStreamHusk.h"

namespace BF
{
	struct DeflateBlock
	{
		public:
		bool IsLastBlock;
		DeflateEncodingMethod EncodingMethod;

		DeflateBlock();

		void Parse(BitStreamHusk& bitStream);

		void Inflate(BitStreamHusk& bitStream, unsigned char* dataOut, size_t& dataOutSize);
		//void Deflalate(size_t& dataCursor, unsigned char* dataIn, size_t dataInSize, unsigned char* dataOut, size_t& dataOutSize);
	};
}