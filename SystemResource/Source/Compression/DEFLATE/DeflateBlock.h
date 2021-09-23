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
		DeflateBlock(unsigned char value);

		void Set(unsigned char value);
	};
}