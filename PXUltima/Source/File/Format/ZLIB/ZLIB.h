#ifndef ZLIBInclude
#define ZLIBInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Format/PNG/PNG.h>

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

		size_t WindowSize;
		unsigned char  CheckFlag; // 5 Bits
		unsigned char DictionaryPresent; // 1 Bit
		ZLIBCompressionLevel CompressionLevel; // 2 Bits
	}
	ZLIBHeader;

	typedef struct ZLIB_
	{
		ZLIBHeader Header;

		size_t CompressedDataSize;
		const unsigned char* CompressedData;

		unsigned int AdlerChecksum;
	}
	ZLIB;

	static ZLIBCompressionLevel ConvertToCompressionLevel(const unsigned char compressionLevel);
	static unsigned char ConvertFromCompressionLevel(const ZLIBCompressionLevel compressionLevel);

	static ZLIBCompressionMethod ConvertToCompressionMethod(const unsigned char compressionMethod);
	static unsigned char ConvertFromCompressionMethod(const ZLIBCompressionMethod compressionMethod);

	extern ActionResult ZLIBDecompress(const void* const inputData, const size_t inputDataSize, void* const outputData, const size_t outputDataSize,size_t* const outputDataSizeRead);
	extern ActionResult ZLIBCompress(const void* const inputData, const size_t inputDataSize, void* const outputData, const size_t outputDataSize, size_t* const outputDataSizeWritten);


	extern size_t ZLIBCalculateExpectedSize(const size_t width, const size_t height, const size_t bpp, const PNGInterlaceMethod interlaceMethod);

	/*in an idat chunk, each scanline is a multiple of 8 bits, unlike the lodepng output buffer,
and in addition has one extra byte per line: the filter byte. So this gives a larger
result than lodepng_get_raw_size. Set h to 1 to get the size of 1 row including filter byte. */
	extern size_t CalculateRawSizeIDAT(const size_t w, const size_t h, const size_t bpp);

#ifdef __cplusplus
}
#endif

#endif