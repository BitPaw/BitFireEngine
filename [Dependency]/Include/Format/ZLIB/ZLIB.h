#ifndef ZLIBInclude
#define ZLIBInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <Format/PNG/PNG.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum ZLIBCompressionLevel_
	{
		ZLIBCompressionLevelInvalid,
		ZLIBCompressionLevelDefault,
		ZLIBCompressionLevelSlowest,
		ZLIBCompressionLevelFast,
		ZLIBCompressionLevelFastest
	}
	ZLIBCompressionLevel;

	typedef enum ZLIBCompressionMethod_
	{
		ZLIBCompressionMethodInvalid,
		ZLIBCompressionMethodDeflate,
		ZLIBCompressionMethodReserved
	}
	ZLIBCompressionMethod;

	typedef struct ZLIBHeader_
	{
		ZLIBCompressionMethod CompressionMethod; // 4 Bits


		/*
		   4 Bits

		For CM = 8, CINFO is the base-2 logarithm of the LZ77 window size, minus eight
		CINFO = 7 indicates a 32K window size).
		Values of CINFO above 7 are not allowed in this version of the specification.
		CINFO is not defined in this specification for CM not equal to 8.
		*/
		unsigned char CompressionInfo;

		PXSize WindowSize;
		unsigned char  CheckFlag; // 5 Bits
		unsigned char PXDictionaryPresent; // 1 Bit
		ZLIBCompressionLevel CompressionLevel; // 2 Bits
	}
	ZLIBHeader;

	typedef struct ZLIB_
	{
		ZLIBHeader Header;

		PXSize CompressedDataSize;
		const unsigned char* CompressedData;

		unsigned int AdlerChecksum;
	}
	ZLIB;

	static ZLIBCompressionLevel ConvertToCompressionLevel(const unsigned char compressionLevel);
	static unsigned char ConvertFromCompressionLevel(const ZLIBCompressionLevel compressionLevel);

	static ZLIBCompressionMethod ConvertToCompressionMethod(const unsigned char compressionMethod);
	static unsigned char ConvertFromCompressionMethod(const ZLIBCompressionMethod compressionMethod);

	PXPublic PXActionResult ZLIBDecompress(PXDataStream* const pxInputSteam, PXDataStream* const pxOutputSteam);
	PXPublic PXActionResult ZLIBCompress(PXDataStream* const pxInputSteam, PXDataStream* const pxOutputSteam);


	PXPublic PXSize ZLIBCalculateExpectedSize(const PXSize width, const PXSize height, const PXSize bpp, const PNGInterlaceMethod interlaceMethod);

	/*in an idat chunk, each scanline is a multiple of 8 bits, unlike the lodepng output buffer,
and in addition has one extra byte per line: the filter byte. So this gives a larger
result than lodepng_get_raw_size. Set h to 1 to get the size of 1 row including filter byte. */
	PXPublic PXSize CalculateRawSizeIDAT(const PXSize w, const PXSize h, const PXSize bpp);

#ifdef __cplusplus
}
#endif

#endif