#include "DeflateBlock.h"

BF::DeflateBlock::DeflateBlock()
{
	IsLastBlock = false;
	EncodingMethod = DeflateEncodingMethod::Invalid;
}

BF::DeflateBlock::DeflateBlock(unsigned char value)
{
	Set(value);
}

void BF::DeflateBlock::Set(unsigned char value)
{
	unsigned char encodingMethodValue = (value & 0b110) >> 1;

	IsLastBlock = value & 0b001;

	switch (encodingMethodValue)
	{
		case 0b00:
			EncodingMethod = DeflateEncodingMethod::LiteralRaw;
			break;

		case 0b01:
			EncodingMethod = DeflateEncodingMethod::HuffmanStatic;
			break;

		case 0b10:
			EncodingMethod = DeflateEncodingMethod::HuffmanDynamic;
			break;

		case 0b11:
			EncodingMethod = DeflateEncodingMethod::Reserverd;
			break;

		default:
			EncodingMethod = DeflateEncodingMethod::Invalid;
			break;
	}
}