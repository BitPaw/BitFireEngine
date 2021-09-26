#pragma once

namespace BF
{
#define HuffmanSymbolEndOfBlock 256u

	struct HuffmanSymbol
	{
		public:
		unsigned short ID; // (3..258)
		unsigned int BackwardDistance; // (1..32.768)
	};
}