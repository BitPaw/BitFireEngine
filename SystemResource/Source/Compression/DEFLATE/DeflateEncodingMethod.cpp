#include "DeflateEncodingMethod.h"

BF::DeflateEncodingMethod BF::ConvertDeflateEncodingMethod(unsigned char deflateEncodingMethod)
{
	switch (deflateEncodingMethod)
	{
		case 0b00:
			return DeflateEncodingMethod::LiteralRaw;

		case 0b01:
			return DeflateEncodingMethod::HuffmanStatic;

		case 0b10:
			return DeflateEncodingMethod::HuffmanDynamic;

		case 0b11:
			return DeflateEncodingMethod::Reserverd;

		default:
			return DeflateEncodingMethod::Invalid;
	}
}

const char* BF::DeflateEncodingMethodToString(DeflateEncodingMethod deflateEncodingMethod)
{
	switch (deflateEncodingMethod)
	{
		default:
		case BF::DeflateEncodingMethod::Invalid:
			return "Invalid";

		case BF::DeflateEncodingMethod::LiteralRaw:
			return "Literal Raw";

		case BF::DeflateEncodingMethod::HuffmanStatic:
			return "Huffman Static";

		case BF::DeflateEncodingMethod::HuffmanDynamic:
			return "Huffman Dynamic";

		case BF::DeflateEncodingMethod::Reserverd:
			return "Reserverd";
	}
}
