#ifndef PXLZ77INCLUDE
#define PXLZ77INCLUDE

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	/*
write the lz77-encoded data, which has lit, len and dist codes, to compressed stream using huffman trees.
tree_ll: the tree for lit and len codes.
tree_d: the tree for distance codes.
*/


	typedef struct PXLZ77ESetting
	{
		PXSize Windowsize; /*must be a power of two <= 32768. higher compresses more but is slower. Default value: 2048.*/
		PXSize Minmatch; /*minimum lz77 length. 3 is normally best, 6 can be better for some PNGs. Default: 0*/
		PXSize Nicematch; /*stop searching if >= this length found. Set to 258 for best compression. Default: 128*/
		PXBool Lazymatching; /*use lazy matching: better compression but a bit slower. Default: true*/
	}
	PXLZ77ESetting;

	/*
	
	PXPublic PXActionResult PXLZ77Encode
	(
		//PXDataStream* const pxOutputStream,
		PXDataStream* const pxCacheStream,
		Hash* hash,
		const unsigned char* in,
		PXSize inpos,
		PXSize insize,
		const HuffmanTree* tree_ll,
		const HuffmanTree* tree_d,
		const PXLZ77ESetting* const pxLZ77ESetting
	);
	PXPublic PXActionResult PXLZ77Decode();	*/

#ifdef __cplusplus
}
#endif

#endif