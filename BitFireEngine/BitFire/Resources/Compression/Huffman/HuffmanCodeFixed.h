#pragma once

#include "../../../Utility/BitStreamHusk.h"

namespace BF
{
	class HuffmanCodeFixed
	{
		public:
        static const unsigned char CodeDistance = 5;
        /*
        Lit Value   Bits    Codes
        ---------   ----    ----------------------------
          0 - 143   8       00110000  through 10111111
        144 - 255   9       110010000 through 111111111
        256 - 279   7       0000000   through 0010111
        280 - 287   8       11000000  through 11000111
        */
		static unsigned char GetBitLengh(unsigned int value);
        static unsigned char TranslateIndex(unsigned char index);

        static unsigned int DecodeRunLength(unsigned int value, BitStreamHusk& bitStream);
        static unsigned int DecodeDistance(unsigned int value, BitStreamHusk& bitStream);
        static unsigned int DecodeNextSymbol(BitStreamHusk& bitStream);


        static unsigned int FindNextLiteralSymbol(BitStreamHusk& bitStream);
        static unsigned int FindNextDistancelSymbol(BitStreamHusk& bitStream);
	};
}