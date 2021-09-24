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

		static unsigned char HuffmanFixedCodeLength(unsigned short literalValue);
		//static unsigned short
	};
}