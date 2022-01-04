#pragma once

#include "ZLIBHeader.h"
#include "../../Algorithm/Adler32.h"
#include "../../Image/PNG/Chunk/PNGInterlaceMethod.h"

namespace BF
{
	struct ZLIB
	{
		public:
		ZLIBHeader Header;

		size_t CompressedDataSize;
		unsigned char* CompressedData;

		Adler32 AdlerChecksum;

		ZLIB(unsigned char* inputData, size_t inputDataSize);
		//ZLIB();

		void Parse(unsigned char* inputData, size_t inputDataSize);
		void Serialize(unsigned char* outputData, size_t& outputDataSize);


		static size_t CalculateExpectedSize(size_t width, size_t height, size_t bpp, PNGInterlaceMethod interlaceMethod);

		/*in an idat chunk, each scanline is a multiple of 8 bits, unlike the lodepng output buffer,
and in addition has one extra byte per line: the filter byte. So this gives a larger
result than lodepng_get_raw_size. Set h to 1 to get the size of 1 row including filter byte. */
		static size_t CalculateRawSizeIDAT(unsigned w, unsigned h, unsigned bpp)
		{
			/* + 1 for the filter byte, and possibly plus padding bits per line. */
			/* Ignoring casts, the expression is equal to (w * bpp + 7) / 8 + 1, but avoids overflow of w * bpp */
			size_t line = ((size_t)(w / 8u) * bpp) + 1u + ((w & 7u) * bpp + 7u) / 8u;
			return (size_t)h * line;
		}
	};
}