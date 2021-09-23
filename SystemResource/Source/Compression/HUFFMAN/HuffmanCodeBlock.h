#pragma once

namespace BF
{
	struct HuffmanCodeBlock
	{
		public:
		unsigned short NumberOfLiteralValues;
		unsigned char NumberOfDistanceCodes;
		unsigned char NumberOfCodeLengthCodes;
	};
}