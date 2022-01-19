#include "HuffmanTree.h"
#include "HuffmanSymbol.h"
#include "HuffmanNumberCode.h"



/* a symbol value too big to represent any valid symbol, to indicate reading disallowed huffman bits combination,
which is possible in case of only 0 or 1 present symbols. */
#define INVALIDSYMBOL 65535u
#define NUM_DEFLATE_CODE_SYMBOLS 288
#define NUM_DISTANCE_SYMBOLS 32

#define LODEPNG_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define LODEPNG_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define LODEPNG_ABS(x) ((x) < 0 ? -(x) : (x))

int BF::HuffmanTree::GenerateFromLengths(const unsigned int* bitlen, size_t numcodes, size_t maxbitlen)
{
	// HuffmanTree_makeFromLengths()
	lengths = (unsigned int*)malloc(numcodes * sizeof(unsigned int));
	memcpy(lengths, bitlen, numcodes * sizeof(unsigned int));
	this->numcodes = NUM_DEFLATE_CODE_SYMBOLS;
	this->maxbitlen = 15;
	//-----------

	//------------------------------------ HuffmanTree_makeFromLengths2()
	unsigned int* blcount = (unsigned int*)malloc((maxbitlen + 1) * sizeof(unsigned int));
	unsigned int* nextcode = (unsigned int*)malloc((maxbitlen + 1) * sizeof(unsigned int));
	unsigned error = 0;

	codes = (unsigned int*)malloc(numcodes * sizeof(unsigned int));
	
	
	if (!codes || !blcount || !nextcode) error = 83; /*alloc fail*/

	if (!error)
	{
		for (size_t n = 0; n != maxbitlen + 1; n++) blcount[n] = nextcode[n] = 0;
		/*step 1: count number of instances of each code length*/
		for (size_t bits = 0; bits != numcodes; ++bits) ++blcount[lengths[bits]];
		/*step 2: generate the nextcode values*/
		for (size_t bits = 1; bits <= maxbitlen; ++bits)
		{
			nextcode[bits] = (nextcode[bits - 1] + blcount[bits - 1]) << 1u;
		}
		/*step 3: generate all the codes*/
		for (size_t n = 0; n != numcodes; ++n)
		{
			if (lengths[n] != 0)
			{
				codes[n] = nextcode[lengths[n]]++;
				/*remove superfluous bits from the code*/
				codes[n] &= ((1u << lengths[n]) - 1u);
			}
		}
	}

	free(blcount);
	free(nextcode);
	//-------------------------------------------------


	// HuffmanTree_makeTable()
	static const unsigned headsize = 1u << FIRSTBITS; /*size of the first table*/
	static const unsigned mask = (1u << FIRSTBITS) /*headsize*/ - 1u;
	size_t numpresent, pointer, size; /*total table size*/
	unsigned* maxlens = (unsigned*)malloc(headsize * sizeof(unsigned));
	if (!maxlens) return 83; /*alloc fail*/

	/* compute maxlens: max total bit length of symbols sharing prefix in the first table*/
	memset(maxlens, 0, headsize * sizeof(*maxlens));
	for (size_t i = 0; i < numcodes; i++)
	{
		unsigned int symbol = codes[i];
		unsigned int l = lengths[i];
		unsigned int index;
		if (l <= FIRSTBITS) continue; /*symbols that fit in first table don't increase secondary table size*/
		/*get the FIRSTBITS MSBs, the MSBs of the symbol are encoded first. See later comment about the reversing*/
		index = reverseBits(symbol >> (l - FIRSTBITS), FIRSTBITS);
		maxlens[index] = LODEPNG_MAX(maxlens[index], l);
	}
	/* compute total table size: size of first table plus all secondary tables for symbols longer than FIRSTBITS */
	size = headsize;
	for (size_t i = 0; i < headsize; ++i)
	{
		size_t l = maxlens[i];

		if (l > FIRSTBITS)
		{
			size += (1u << (l - FIRSTBITS));
		}
	}
	table_len = (unsigned char*)malloc(size * sizeof(*table_len));
	table_value = (unsigned short*)malloc(size * sizeof(*table_value));
	if (!table_len || !table_value)
	{
		free(maxlens);
		/* freeing tree->table values is done at a higher scope */
		return 83; /*alloc fail*/
	}
	/*initialize with an invalid length to indicate unused entries*/
	for (size_t i = 0; i < size; ++i) table_len[i] = 16;

	/*fill in the first table for long symbols: max prefix size and pointer to secondary tables*/
	pointer = headsize;
	for (size_t i = 0; i < headsize; ++i)
	{
		size_t l = maxlens[i];

		if (l <= FIRSTBITS) continue;

		table_len[i] = l;
		table_value[i] = pointer;
		
		pointer += (1u << (l - FIRSTBITS));
	}

	free(maxlens);

	/*fill in the first table for short symbols, or secondary table for long symbols*/
	numpresent = 0;
	for (size_t i = 0; i < numcodes; ++i)
	{
		unsigned l = lengths[i];
		unsigned symbol = codes[i]; /*the huffman bit pattern. i itself is the value.*/
		/*reverse bits, because the huffman bits are given in MSB first order but the bit reader reads LSB first*/
		unsigned reverse = reverseBits(symbol, l);
		if (l == 0) continue;
		numpresent++;

		if (l <= FIRSTBITS)
		{
			/*short symbol, fully in first table, replicated num times if l < FIRSTBITS*/
			unsigned num = 1u << (FIRSTBITS - l);
		
			for (size_t j = 0; j < num; ++j)
			{
				/*bit reader will read the l bits of symbol first, the remaining FIRSTBITS - l bits go to the MSB's*/
				unsigned index = reverse | (j << l);
				if (table_len[index] != 16) return 55; /*invalid tree: long symbol shares prefix with short symbol*/
				table_len[index] = l;
				table_value[index] = i;
			}
		}
		else
		{
			/*long symbol, shares prefix with other long symbols in first lookup table, needs second lookup*/
			/*the FIRSTBITS MSBs of the symbol are the first table index*/
			unsigned index = reverse & mask;
			unsigned maxlen = table_len[index];
			/*log2 of secondary table length, should be >= l - FIRSTBITS*/
			unsigned tablelen = maxlen - FIRSTBITS;
			unsigned start = table_value[index]; /*starting index in secondary table*/
			unsigned num = 1u << (tablelen - (l - FIRSTBITS)); /*amount of entries of this symbol in secondary table*/
	
			if (maxlen < l) return 55; /*invalid tree: long symbol shares prefix with short symbol*/
			for (size_t j = 0; j < num; ++j)
			{
				unsigned reverse2 = reverse >> FIRSTBITS; /* l - FIRSTBITS bits */
				unsigned index2 = start + (reverse2 | (j << (l - FIRSTBITS)));
				table_len[index2] = l;
				table_value[index2] = i;
			}
		}
	}

	if (numpresent < 2)
	{
		/* In case of exactly 1 symbol, in theory the huffman symbol needs 0 bits,
		but deflate uses 1 bit instead. In case of 0 symbols, no symbols can
		appear at all, but such huffman tree could still exist (e.g. if distance
		codes are never used). In both cases, not all symbols of the table will be
		filled in. Fill them in with an invalid symbol value so returning them from
		huffmanDecodeSymbol will cause error. */
		for (size_t i = 0; i < size; ++i)
		{
			if (table_len[i] == 16)
			{
				/* As length, use a value smaller than FIRSTBITS for the head table,
				and a value larger than FIRSTBITS for the secondary table, to ensure
				valid behavior for advanceBits when reading this symbol. */
				table_len[i] = (i < headsize) ? 1 : (FIRSTBITS + 1);
				table_value[i] = INVALIDSYMBOL;
			}
		}
	}
	else
	{
		/* A good huffman tree has N * 2 - 1 nodes, of which N - 1 are internal nodes.
		If that is not the case (due to too long length codes), the table will not
		have been fully used, and this is an error (not all bit combinations can be
		decoded): an oversubscribed huffman tree, indicated by error 55. */
		for (size_t i = 0; i < size; ++i)
		{
			if (table_len[i] == 16) return 55;
		}
	}
	//----------------------------

	return 0;
}

unsigned int BF::HuffmanTree::GenerateDynamicTree(BitStreamHusk& bitStreamHusk, HuffmanTree& treeLength, HuffmanTree& treeDistance)
{
#define NUM_CODE_LENGTH_CODES 19

	/*the order in which "code length alphabet code lengths" are stored as specified by deflate, out of this the huffman
tree of the dynamic huffman tree lengths is generated*/
	const unsigned char CLCL_ORDER[NUM_CODE_LENGTH_CODES]= { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

	/*make sure that length values that aren't filled in will be 0, or a wrong tree will be generated*/
	unsigned error = 0;
	unsigned n, HLIT, HDIST, HCLEN;

	/*see comments in deflateDynamic for explanation of the context and these variables, it is analogous*/
	unsigned* bitlen_ll = 0; /*lit,len code lengths*/
	unsigned* bitlen_d = 0; /*dist code lengths*/
	/*code length code lengths ("clcl"), the bit lengths of the huffman tree used to compress bitlen_ll and bitlen_d*/
	unsigned* bitlen_cl = 0;
	HuffmanTree tree_cl; /*the code tree for code length codes (the huffman tree for compressed huffman trees)*/

	//if (!ensureBits17(reader, 14)) return 49; /*error: the bit pointer is or will go past the memory*/

	HuffmanNumberCode huffmanNumberCode;
	huffmanNumberCode.NumberOfLiteralCodes = bitStreamHusk.ExtractBitsAndMove(5) + 257u;
	huffmanNumberCode.NumberOfDistanceCodes = bitStreamHusk.ExtractBitsAndMove(5) + 1u;
	huffmanNumberCode.NumberOfLengthCodes = bitStreamHusk.ExtractBitsAndMove(4) + 4u;

	HLIT = huffmanNumberCode.NumberOfLiteralCodes;
	HDIST = huffmanNumberCode.NumberOfDistanceCodes;
	HCLEN = huffmanNumberCode.NumberOfLengthCodes;

	/*number of literal/length codes + 257. Unlike the spec, the value 257 is added to it here already*/
	//HLIT =  readBits(reader, 5) + 257;
	/*number of distance codes. Unlike the spec, the value 1 is added to it here already*/
	//HDIST = readBits(reader, 5) + 1;
	/*number of code length codes. Unlike the spec, the value 4 is added to it here already*/
	//HCLEN = readBits(reader, 4) + 4;

	bitlen_cl = (unsigned*)malloc(NUM_CODE_LENGTH_CODES * sizeof(unsigned));
	if (!bitlen_cl) return 83 /*alloc fail*/;

	//HuffmanTree_init(&tree_cl);

	while (!error)
	{
		/*read the code length codes out of 3 * (amount of code length codes) bits*/
		/*if (lodepng_gtofl(reader->bp, HCLEN * 3, reader->bitsize))
		{
			throw(50); /*error: the bit pointer is or will go past the memory* /
		}*/
		for (size_t index = 0; index != HCLEN; ++index)
		{
			//ensureBits9(reader, 3); /*out of bounds already checked above */
			bitlen_cl[CLCL_ORDER[index]] = bitStreamHusk.ExtractBitsAndMove(3);
		}
		for (size_t index = HCLEN; index != NUM_CODE_LENGTH_CODES; ++index)
		{
			bitlen_cl[CLCL_ORDER[index]] = 0;
		}

		error = tree_cl.GenerateFromLengths(bitlen_cl, NUM_CODE_LENGTH_CODES, 7);
		if (error) break;

		/*now we can use this tree to read the lengths for the tree that this function will return*/
		bitlen_ll = (unsigned int*)malloc(NUM_DEFLATE_CODE_SYMBOLS * sizeof(unsigned int));
		bitlen_d = (unsigned int*)malloc(NUM_DISTANCE_SYMBOLS * sizeof(unsigned int));
		if (!bitlen_ll || !bitlen_d) throw(83 /*alloc fail*/);
		memset(bitlen_ll, 0, NUM_DEFLATE_CODE_SYMBOLS * sizeof(*bitlen_ll));
		memset(bitlen_d, 0, NUM_DISTANCE_SYMBOLS * sizeof(*bitlen_d));

		/*i is the current symbol we're reading in the part that contains the code lengths of lit/len and dist codes*/
		
		for (size_t i = 0; i < HLIT + HDIST; )
		{
			unsigned code;
			//ensureBits25(reader, 22); /* up to 15 bits for huffman code, up to 7 extra bits below*/
			code =  huffmanDecodeSymbol(bitStreamHusk, tree_cl);
			if (code <= 15) /*a length code*/
			{
				if (i < HLIT) bitlen_ll[i] = code;
				else bitlen_d[i - HLIT] = code;
				++i;
			}
			else if (code == 16) /*repeat previous*/
			{
				unsigned replength = 3; /*read in the 2 bits that indicate repeat length (3-6)*/
				unsigned value; /*set value to the previous code*/

				if (i == 0) throw(54); /*can't repeat previous if i is 0*/

				replength += bitStreamHusk.ExtractBitsAndMove(2);

				if (i < HLIT + 1) value = bitlen_ll[i - 1];
				else value = bitlen_d[i - HLIT - 1];
				/*repeat this value in the next lengths*/
				for (n = 0; n < replength; ++n)
				{
					if (i >= HLIT + HDIST) throw(13); /*error: i is larger than the amount of codes*/
					if (i < HLIT) bitlen_ll[i] = value;
					else bitlen_d[i - HLIT] = value;
					++i;
				}
			}
			else if (code == 17) /*repeat "0" 3-10 times*/
			{
				unsigned replength = 3; /*read in the bits that indicate repeat length*/
				replength += bitStreamHusk.ExtractBitsAndMove(3);

				/*repeat this value in the next lengths*/
				for (n = 0; n < replength; ++n)
				{
					if (i >= HLIT + HDIST) throw(14); /*error: i is larger than the amount of codes*/

					if (i < HLIT) bitlen_ll[i] = 0;
					else bitlen_d[i - HLIT] = 0;
					++i;
				}
			}
			else if (code == 18) /*repeat "0" 11-138 times*/
			{
				unsigned replength = 11; /*read in the bits that indicate repeat length*/
				replength += bitStreamHusk.ExtractBitsAndMove(7);

				/*repeat this value in the next lengths*/
				for (n = 0; n < replength; ++n)
				{
					if (i >= HLIT + HDIST) throw(15); /*error: i is larger than the amount of codes*/

					if (i < HLIT) bitlen_ll[i] = 0;
					else bitlen_d[i - HLIT] = 0;
					++i;
				}
			}
			else /*if(code == INVALIDSYMBOL)*/
			{
				throw(16); /*error: tried to read disallowed huffman symbol*/
			}
			/*check if any of the ensureBits above went out of bounds*/
			/*if (reader->bp > reader->bitsize)
			{
				/*return error code 10 or 11 depending on the situation that happened in huffmanDecodeSymbol
				(10=no endcode, 11=wrong jump outside of tree)*/
				/* TODO: revise error codes 10,11,50: the above comment is no longer valid * /
				throw(50); /*error, bit pointer jumps past memory* /
			}*/ 
		}
		if (error) break;

		if (bitlen_ll[256] == 0) throw(64); /*the length of the end code 256 must be larger than 0*/

		/*now we've finally got HLIT and HDIST, so generate the code trees, and the function is done*/
	
		error = treeLength.GenerateFromLengths(bitlen_ll, NUM_DEFLATE_CODE_SYMBOLS, 15);
		if (error) break;
		error = treeDistance.GenerateFromLengths(bitlen_d, NUM_DISTANCE_SYMBOLS, 15);

		break; /*end of error-while*/
	}

	free(bitlen_cl);
	free(bitlen_ll);
	free(bitlen_d);
	
	return error;
}

int BF::HuffmanTree::lodepng_gtofl(size_t a, size_t b, size_t c)
{
	size_t d;
	if (lodepng_addofl(a, b, &d)) return 1;
	return d > c;
}

int BF::HuffmanTree::lodepng_addofl(size_t a, size_t b, size_t* result)
{
	*result = a + b; /* Unsigned addition is well defined and safe in C90 */
	return *result < a;
}

unsigned int BF::HuffmanTree::huffmanDecodeSymbol(BitStreamHusk& reader, HuffmanTree& codetree)
{
	HuffmanSymbol huffmanSymbol;
	huffmanSymbol.Code = reader.ExtractBits(FIRSTBITS);
	huffmanSymbol.Length = codetree.table_len[huffmanSymbol.Code];
	huffmanSymbol.Value = codetree.table_value[huffmanSymbol.Code];

	bool finished = huffmanSymbol.Length <= FIRSTBITS;

	if (finished)
	{
		reader.Move(huffmanSymbol.Length);

		return huffmanSymbol.Value;
	}
	else
	{
		reader.Move(FIRSTBITS);

		unsigned int extraBitsToRead = huffmanSymbol.Length - FIRSTBITS;
		unsigned int extraBits = reader.ExtractBits(extraBitsToRead);
		unsigned int index2 = huffmanSymbol.Value + extraBits;		
		unsigned int moveBits = codetree.table_len[index2] - FIRSTBITS;
		unsigned int result = codetree.table_value[index2];

		reader.Move(moveBits);

		return result;
	}
}

BF::HuffmanTree::HuffmanTree()
{
	codes = 0;
	lengths = 0;
	maxbitlen = 0;
	numcodes = 0;
	table_len = 0;
	table_value = 0;
}

unsigned BF::HuffmanTree::reverseBits(unsigned bits, unsigned num)
{
	/*TODO: implement faster lookup table based version when needed*/
	unsigned i, result = 0;
	for (i = 0; i < num; i++) result |= ((bits >> (num - i - 1u)) & 1u) << i;
	return result;
}

void BF::HuffmanTree::GenerateFixedLiteralLengthTree()
{
	//------------------------------------------- generateFixedLitLenTree()			
	const unsigned int maxbitlen = 15;
	const size_t numcodes = NUM_DEFLATE_CODE_SYMBOLS;
	unsigned int bitlen[numcodes];
	unsigned int i = 0;
	

	/*288 possible codes: 0-255=literals, 256=endcode, 257-285=lengthcodes, 286-287=unused*/
	for (i = 0; i <= 143; ++i) bitlen[i] = 8;
	for (i = 144; i <= 255; ++i) bitlen[i] = 9;
	for (i = 256; i <= 279; ++i) bitlen[i] = 7;
	for (i = 280; i <= 287; ++i) bitlen[i] = 8;
	//---------------------------------------------------------------------------

	GenerateFromLengths(bitlen, numcodes, maxbitlen);
}

void BF::HuffmanTree::GenerateFixedDistanceTree()
{
	const unsigned int maxbitlen = 15;
	const size_t numcodes = NUM_DISTANCE_SYMBOLS;
	unsigned int bitlen[numcodes];

	/*there are 32 distance codes, but 30-31 are unused*/
	for (size_t i = 0; i < numcodes; i++)
	{
		bitlen[i] = 5;
	}

	GenerateFromLengths(bitlen, numcodes, maxbitlen);
}
