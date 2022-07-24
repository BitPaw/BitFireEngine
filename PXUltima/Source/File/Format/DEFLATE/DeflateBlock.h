#ifndef DeflateBlockInclude
#define DeflateBlockInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/BitStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum DeflateEncodingMethod_
	{
		DeflateEncodingInvalid,
		DeflateEncodingLiteralRaw,
		DeflateEncodingHuffmanStatic,
		DeflateEncodingHuffmanDynamic,
		DeflateEncodingReserverd
	}
	DeflateEncodingMethod;

	typedef struct DeflateBlock_
	{
		unsigned char IsLastBlock;
		DeflateEncodingMethod EncodingMethod;

		//void Parse(BitStreamHusk& bitStream);

		//void Inflate(BitStreamHusk& bitStream, unsigned char* dataOut, size_t& dataOutSize);
		//void Deflalate(size_t& dataCursor, unsigned char* dataIn, size_t dataInSize, unsigned char* dataOut, size_t& dataOutSize);
	}
	DeflateBlock;


	extern DeflateEncodingMethod ConvertToDeflateEncodingMethod(const unsigned char deflateEncodingMethod);

	extern void DeflateBlockParse(DeflateBlock* deflateBlock, BitStream* bitStream);

	extern int DeflateBlockInflate(DeflateBlock* deflateBlock, BitStream* bitStream, void* dataOut, size_t* dataOutSize);
	//void Deflalate(size_t& dataCursor, unsigned char* dataIn, size_t dataInSize, unsigned char* dataOut, size_t& dataOutSize);

#ifdef __cplusplus
}
#endif

#endif