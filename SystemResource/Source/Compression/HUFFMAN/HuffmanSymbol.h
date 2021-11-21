#pragma once

namespace BF
{
	struct HuffmanSymbol
	{
		public:
		unsigned short Code;
		unsigned short Length;
		unsigned short Value;

		HuffmanSymbol();
	};
}