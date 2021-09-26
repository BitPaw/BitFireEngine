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
