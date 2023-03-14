#ifndef HuffmanTreeInclude
#define HuffmanTreeInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>
#include <File/PXDataStream.h>


/* amount of bits for first huffman table lookup (aka root bits), see HuffmanTree_makeTable and huffmanDecodeSymbol.*/
/* values 8u and 9u work the fastest */
#define FIRSTBITS 9u

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum HuffmanCodeType_
	{
		HuffmanCodeInvalid,
		HuffmanCodeLiteral,
		HuffmanCodeLength,
		HuffmanCodeEndOfBlock
	}
	HuffmanCodeType;

	typedef struct HuffmanNumberCode_
	{
		unsigned short NumberOfLiteralCodes;
		unsigned short NumberOfDistanceCodes;
		unsigned short NumberOfLengthCodes;
	}
	HuffmanNumberCode;

	typedef struct HuffmanSymbol_
	{
		unsigned short Code;
		unsigned short Length;
		unsigned short Value;
	}
	HuffmanSymbol;

	typedef enum HuffmanResult_
	{
		HuffmanInvalid,

		HuffmanSucess,



	}HuffmanResult;


	typedef struct HuffmanTree_
	{
		unsigned int* codes; /*the huffman codes (bit patterns representing the symbols)*/
		unsigned int* lengths; /*the lengths of the huffman codes*/
		unsigned int maxbitlen; /*maximum number of bits a single code can get*/
		unsigned int numcodes; /*number of symbols in the alphabet = number of codes*/

		/* for reading only */
		unsigned char* table_len; /*length of symbol from lookup table, or max length if secondary lookup needed*/
		unsigned short* table_value; /*value of symbol from lookup table, or pointer to secondary table if needed*/
	}
	HuffmanTree;


	PXPublic void HuffmanTreeConstruct(HuffmanTree* const huffmanTree);
	PXPublic void HuffmanTreeDestruct(HuffmanTree* const huffmanTree);

	PXPublic HuffmanCodeType HuffmanCodeTypeFromCode(const unsigned short code);


	PXPublic void GenerateFixedLiteralLengthTree(HuffmanTree* huffmanTree);
	PXPublic void HuffmanDistanceTreeGenerateFixed(HuffmanTree* const huffmanTree);

	PXPublic int GenerateFromLengths(HuffmanTree* huffmanTree, const unsigned int* bitlen, PXSize numcodes, PXSize maxbitlen);



	PXPublic unsigned reverseBits(unsigned bits, unsigned num);
	PXPublic unsigned int GenerateDynamicTree(PXDataStream* const dataStream, HuffmanTree* treeLength, HuffmanTree* treeDistance);

	/* Safely check if a + b > c, even if overflow could happen. */
	PXPublic int lodepng_gtofl(PXSize a, PXSize b, PXSize c);
	PXPublic int lodepng_addofl(PXSize a, PXSize b, PXSize* result);
	PXPublic unsigned int HuffmanSymbolDecode(PXDataStream* const dataStream, const HuffmanTree* const codetree);


#ifdef __cplusplus
}
#endif

#endif