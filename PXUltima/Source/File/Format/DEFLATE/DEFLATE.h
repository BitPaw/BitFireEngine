#ifndef DeflateInclude
#define DeflateInclude

#include <stddef.h>

#include <Error/ActionResult.h>

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
	}
	DeflateBlock;


	extern DeflateEncodingMethod ConvertToDeflateEncodingMethod(const unsigned char deflateEncodingMethod);
	extern unsigned char ConvertFromDeflateEncodingMethod(const DeflateEncodingMethod deflateEncodingMethod);

	extern int DEFLATEParse(const void* const inputBuffer, const size_t inputBufferSize, void* const outputBuffer, const size_t outputBufferSize, size_t* const outputBufferSizeRead);
	extern int DEFLATESerialize(const void* const inputBuffer, const size_t inputBufferSize, void* const outputBuffer, const size_t outputBufferSize, size_t* const outputBufferSizeWritten);

#ifdef __cplusplus
}
#endif

#endif