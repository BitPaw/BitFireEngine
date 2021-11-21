#include "HuffmanCodeType.h"

BF::HuffmanCodeType BF::HuffmanCodeTypeFromCode(unsigned short code)
{
	bool isLiteralSymbol = code <= 255u;
	bool isLengthCode = code >= 257u && code <= 285u;
	bool isEndBlock = code == 256u;

	if (isLiteralSymbol)
	{
		return HuffmanCodeType::Literal;
	}

	if (isLengthCode)
	{
		return HuffmanCodeType::Length;
	}

	if (isEndBlock)
	{
		return HuffmanCodeType::EndOfBlock;
	}

	return HuffmanCodeType::InvalidCode;
}
