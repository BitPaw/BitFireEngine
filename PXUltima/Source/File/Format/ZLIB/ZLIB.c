#include "ZLIB.h"

#include <Algorithm/ADLER/Adler32.h>
#include <Math/Math.h>
#include <File/BitStream.h>
#include <File/Format/DEFLATE/DeflateBlock.h>

ZLIBCompressionLevel ConvertToCompressionLevel(const unsigned char compressionLevel)
{
    switch(compressionLevel)
    {
        case 0u:
            return ZLIBCompressionLevelFastest;

        case 1u:
            return ZLIBCompressionLevelFast;

        case 2u:
            return ZLIBCompressionLevelDefault;

        case 3u:
            return ZLIBCompressionLevelSlowest;

        default:
            return ZLIBCompressionLevelInvalid;
    }
}

unsigned char ConvertFromCompressionLevel(const ZLIBCompressionLevel compressionLevel)
{
    switch(compressionLevel)
    {
        default:
        case ZLIBCompressionLevelInvalid:
            return -1;

        case ZLIBCompressionLevelDefault:
            return 2u;

        case ZLIBCompressionLevelSlowest:
            return 3u;

        case ZLIBCompressionLevelFast:
            return 1u;

        case ZLIBCompressionLevelFastest:
            return 0u;
    }
}

ZLIBCompressionMethod ConvertToCompressionMethod(const unsigned char compressionMethod)
{
    switch(compressionMethod)
    {
        case 8u:
            return ZLIBCompressionMethodDeflate;

        case 15u:
            return ZLIBCompressionMethodReserved;

        default:
            return ZLIBCompressionMethodInvalid;
    }
}

unsigned char ConvertFromCompressionMethod(const ZLIBCompressionMethod compressionMethod)
{
    switch(compressionMethod)
    {
        default:
        case ZLIBCompressionMethodInvalid:
            return -1;

        case ZLIBCompressionMethodDeflate:
            return 8u;

        case ZLIBCompressionMethodReserved:
            return 15u;
    }
}

ActionResult ZLIBDecompress(const void* const inputData, const size_t inputDataSize, void* const outputData, size_t* const outputDataSize)
{
    BitStream bitStream;
    ZLIB zlib;

    BitStreamConstruct(&bitStream, inputData, inputDataSize);

    const size_t headerSize = 2u;
    const size_t adlerSize = 4u;    

    // Parse header ->     Header.Parse(compressionFormatByte, flagByte);
    {
        unsigned char compressionFormatByte = 0;
        unsigned char flagByte = 0;

        compressionFormatByte = BitStreamReadFullByte(&bitStream);
        flagByte = BitStreamReadFullByte(&bitStream);

        // Valid Check
        {
            unsigned char validFlags = ((unsigned int)compressionFormatByte * 256u + (unsigned int)flagByte) % 31u == 0;

            if(!validFlags)
            {
                return ResultInvalidHeaderSignature;// assert(validFlags);
            }
        }

        //---<Parse First Byte__ - Compression Info>---------------------------------
        {
            unsigned char compressionMethodValue = (compressionFormatByte & 0b00001111);
            zlib.Header.CompressionMethod = ConvertToCompressionMethod(compressionMethodValue);

            zlib.Header.CompressionInfo = (compressionFormatByte & 0b11110000) >> 4;

            // log_2(WindowSize) - 8 = CompressionInfo
            // log_2(32768) - 8 = 7
            // 2^(CompressionInfo + 8)

            const unsigned int isCompressionInfoValid = zlib.Header.CompressionInfo <= 7u;

            if(!isCompressionInfoValid)
            {
                return ResultInvalidVersion;
            }

            //assert(isCompressionInfoValid);

            zlib.Header.WindowSize = MathPower(2, zlib.Header.CompressionInfo + 8);
        }
        //-------------------------------------------------------------------------

        //---<Parse Second Byte__ - Flags>-------------------------------------------
        {
            unsigned char compressionLevelValue = (flagByte & 0b11000000) >> 6;

            zlib.Header.CheckFlag = (flagByte & 0b00011111);
            zlib.Header.DictionaryPresent = ((flagByte & 0b00100000) >> 5) == 1;

            zlib.Header.CompressionLevel = ConvertToCompressionLevel(compressionLevelValue);
        }
        //-------------------------------------------------------------------------        
    }


    //---<Dictionary Parse>----------------------------------------------------
    if(zlib.Header.DictionaryPresent)
    {
        // Parse DICT dictionary identifier 

    }
    //-------------------------------------------------------------------------

    /* Allocate
    if (!(*outputData))
    {
        (*outputData) = (unsigned char*)malloc(zLIBHeader.WindowSize * 4 * sizeof(unsigned char));
    }*/


    zlib.CompressedDataSize = BitStreamRemainingSize(&bitStream) - adlerSize;
    zlib.CompressedData = BitStreamCursorPosition(&bitStream);

    switch(zlib.Header.CompressionMethod)
    {
        case ZLIBCompressionMethodDeflate:
        {
            DeflateBlock deflateBlock;

            do
            {
                DeflateBlockParse(&deflateBlock, &bitStream);
                DeflateBlockInflate(&deflateBlock, &bitStream, outputData, outputDataSize);
            }
            while(!deflateBlock.IsLastBlock);

            break;
        }
        default:
        case ZLIBCompressionMethodReserved:
        case ZLIBCompressionMethodInvalid:
        {
            return ResultFormatInvalid;
        }
    }


    //AdlerChecksum.;
    /*
    unsigned int adler32CheckSum =
        (unsigned int)inputData[dataSize - 4] << 24 +
        (unsigned int)inputData[dataSize - 3] << 16 +
        (unsigned int)inputData[dataSize - 2] << 8 +
        (unsigned int)inputData[dataSize - 1];    
    */

    return ResultSuccessful;
}

ActionResult ZLIBCompress(const void* const inputData, const size_t inputDataSize, void* const outputData, size_t* const outputDataSize)
{
    const size_t headerSize = 2u;
    const size_t adlerSize = 4u;
 /*   unsigned char compressionFormatByte = outputData[0];
    unsigned char flagByte = outputData[1];

    Header.Parse(compressionFormatByte, flagByte);

    //Adler32::

    /* Header
    * 
    *
      //---<Parse First Byte__ - Compression Info>---------------------------------
    {
        unsigned char WindowSizeValue = MathLogarithmusBase2(WindowSize) - 8;
        unsigned char compressionMethodValue = ConvertCompressionMethod(CompressionMethod);

        compressionFormatByte = compressionMethodValue << 4; // 0b11110000
        compressionFormatByte += WindowSizeValue; // 0b00001111
    }
    //-------------------------------------------------------------------------

    //---<Parse Second Byte__ - Flags>-------------------------------------------
    {
        unsigned char compressionLevelValue = ConvertCompressionLevel(CompressionLevel);

        flagByte |= compressionLevelValue << 6;
        flagByte |= DictionaryPresent << 5;
        flagByte |= CheckFlag;
    }
    //-------------------------------------------------------------------------

    * /

    outputDataSize += headerSize + adlerSize;*/

    return ResultInvalid;
}

size_t ZLIBCalculateExpectedSize(size_t width, size_t height, size_t bpp, PNGInterlaceMethod interlaceMethod)
{
    size_t expected_size = 0;

    switch(interlaceMethod)
    {
        default:
        case PNGInterlaceInvalid:
            break;

        case PNGInterlaceNone:
        {
            // predict output size, to allocate exact size for output buffer to avoid more dynamic allocation.
            // If the decompressed size does not match the prediction, the image must be corrupt.
            expected_size = CalculateRawSizeIDAT(width, height, bpp);
            break;
        }
        case PNGInterlaceADAM7:
        {
            // Adam-7 interlaced: expected size is the sum of the 7 sub-images sizes
            expected_size = 0;
            expected_size += CalculateRawSizeIDAT((width + 7) >> 3, (height + 7) >> 3, bpp);
            if(width > 4) expected_size += CalculateRawSizeIDAT((width + 3) >> 3, (height + 7) >> 3, bpp);
            expected_size += CalculateRawSizeIDAT((width + 3) >> 2, (height + 3) >> 3, bpp);
            if(width > 2) expected_size += CalculateRawSizeIDAT((width + 1) >> 2, (height + 3) >> 2, bpp);
            expected_size += CalculateRawSizeIDAT((width + 1) >> 1, (height + 1) >> 2, bpp);
            if(width > 1) expected_size += CalculateRawSizeIDAT((width + 0) >> 1, (height + 1) >> 1, bpp);
            expected_size += CalculateRawSizeIDAT((width + 0), (height + 0) >> 1, bpp);

            break;
        }
    }

    return expected_size;
}

size_t CalculateRawSizeIDAT(unsigned w, unsigned h, unsigned bpp)
{
    /* + 1 for the filter byte, and possibly plus padding bits per line. */
           /* Ignoring casts, the expression is equal to (w * bpp + 7) / 8 + 1, but avoids overflow of w * bpp */
    size_t line = ((size_t)(w / 8u) * bpp) + 1u + ((w & 7u) * bpp + 7u) / 8u;
    return (size_t)h * line;
}
