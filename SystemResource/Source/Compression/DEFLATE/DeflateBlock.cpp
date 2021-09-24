#include "DeflateBlock.h"

BF::DeflateBlock::DeflateBlock()
{
	IsLastBlock = false;
	EncodingMethod = DeflateEncodingMethod::Invalid;
}

unsigned char BF::DeflateBlock::HuffmanFixedCodeLength(unsigned short literalValue)
{
	if (literalValue <= 143u)
	{
		return 8u;
	}

	if (literalValue <= 255u)
	{
		return 9u;
	}

	if(literalValue <= 279u)
	{
		return 7u;
	}

	if(literalValue <= 287u)
	{
		return 8u;
	}

	return 0;
}
