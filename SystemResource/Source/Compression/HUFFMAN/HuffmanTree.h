#pragma once

#include <stdlib.h>
#include <string.h>

#include "../../Container/BitStreamHusk.h"

/* amount of bits for first huffman table lookup (aka root bits), see HuffmanTree_makeTable and huffmanDecodeSymbol.*/
/* values 8u and 9u work the fastest */
#define FIRSTBITS 9u

namespace BF
{
	struct HuffmanTree
	{
		public:
		unsigned int* codes; /*the huffman codes (bit patterns representing the symbols)*/
		unsigned int* lengths; /*the lengths of the huffman codes*/
		unsigned int maxbitlen; /*maximum number of bits a single code can get*/
		unsigned int numcodes; /*number of symbols in the alphabet = number of codes*/

		/* for reading only */
		unsigned char* table_len; /*length of symbol from lookup table, or max length if secondary lookup needed*/
		unsigned short* table_value; /*value of symbol from lookup table, or pointer to secondary table if needed*/
		
		HuffmanTree();

		static unsigned reverseBits(unsigned bits, unsigned num);

		void GenerateFixedLiteralLengthTree();
		void GenerateFixedDistanceTree();

		int GenerateFromLengths(const unsigned int* bitlen, size_t numcodes, unsigned maxbitlen);

		static unsigned int GenerateDynamicTree(BitStreamHusk& bitStreamHusk, HuffmanTree& treeLength, HuffmanTree& treeDistance);

		/* Safely check if a + b > c, even if overflow could happen. */
		static int lodepng_gtofl(size_t a, size_t b, size_t c);
		static int lodepng_addofl(size_t a, size_t b, size_t* result);



		static unsigned int huffmanDecodeSymbol(BitStreamHusk& reader, HuffmanTree& codetree);
		
	};
}