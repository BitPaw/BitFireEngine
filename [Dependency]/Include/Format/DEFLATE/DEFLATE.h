#ifndef DeflateInclude
#define DeflateInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <File/PXDataStream.h>

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
		PXBool IsLastBlock;
		DeflateEncodingMethod EncodingMethod;
	}
	DeflateBlock;

	PXPublic DeflateEncodingMethod ConvertToDeflateEncodingMethod(const PXInt8U deflateEncodingMethod);
	PXPublic PXInt8U ConvertFromDeflateEncodingMethod(const DeflateEncodingMethod deflateEncodingMethod);

	PXPublic PXActionResult DEFLATEParse(PXDataStream* const pxInputStream, PXDataStream* const pxOutputStream);
	PXPublic PXActionResult DEFLATESerialize(PXDataStream* const pxInputStream, PXDataStream* const pxOutputStream);

#ifdef __cplusplus
}
#endif

#endif