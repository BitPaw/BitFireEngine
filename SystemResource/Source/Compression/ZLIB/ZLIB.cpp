#include "ZLIB.h"

#include "ZLIBHeader.h"

#include <Algorithm/ADLER/Adler32.h>

#include <stdlib.h>

BF::ZLIB::ZLIB(unsigned char* inputData, size_t inputDataSize)
{
    Parse(inputData, inputDataSize);
}

void BF::ZLIB::Parse(unsigned char* inputData, size_t inputDataSize)
{
    const size_t headerSize = 2u;
    const size_t adlerSize = 4u;
    unsigned char compressionFormatByte = inputData[0];
    unsigned char flagByte = inputData[1];
    unsigned int adler32CheckSum =
        (unsigned int)inputData[inputDataSize - 4] << 24 |
        (unsigned int)inputData[inputDataSize - 3] << 16 |
        (unsigned int)inputData[inputDataSize - 2] << 8 |
        (unsigned int)inputData[inputDataSize - 1];

    Header.Parse(compressionFormatByte, flagByte);

    //---<Dictionary Parse>----------------------------------------------------
    if (Header.DictionaryPresent)
    {
        // Parse DICT dictionary identifier 

    }
    //-------------------------------------------------------------------------

    /* Allocate
    if (!(*outputData))
    {
        (*outputData) = (unsigned char*)malloc(zLIBHeader.WindowSize * 4 * sizeof(unsigned char));
    }*/


    CompressedDataSize = inputDataSize - adlerSize;
    CompressedData = inputData + headerSize;

    //AdlerChecksum.;
}

void BF::ZLIB::Serialize(unsigned char* outputData, size_t& outputDataSize)
{
    const size_t headerSize = 2u;
    const size_t adlerSize = 4u;
    unsigned char compressionFormatByte = outputData[0];
    unsigned char flagByte = outputData[1];

    Header.Parse(compressionFormatByte, flagByte);

    //Adler32::

    outputDataSize += headerSize + adlerSize;
}

size_t BF::ZLIB::CalculateExpectedSize(size_t width, size_t height, size_t bpp, PNGInterlaceMethod interlaceMethod)
{
    size_t expected_size = 0;

    switch (interlaceMethod)
    {
        default:
        case BF::PNGInterlaceMethod::Invalid:
            break;

        case BF::PNGInterlaceMethod::NoInterlace:
        {
            // predict output size, to allocate exact size for output buffer to avoid more dynamic allocation.
            // If the decompressed size does not match the prediction, the image must be corrupt.
            expected_size = CalculateRawSizeIDAT(width, height, bpp);
            break;
        }
        case BF::PNGInterlaceMethod::ADAM7Interlace:
        {
            // Adam-7 interlaced: expected size is the sum of the 7 sub-images sizes
            expected_size = 0;
            expected_size += CalculateRawSizeIDAT((width + 7) >> 3, (height + 7) >> 3, bpp);
            if (width > 4) expected_size += CalculateRawSizeIDAT((width + 3) >> 3, (height + 7) >> 3, bpp);
            expected_size += CalculateRawSizeIDAT((width + 3) >> 2, (height + 3) >> 3, bpp);
            if (width > 2) expected_size += CalculateRawSizeIDAT((width + 1) >> 2, (height + 3) >> 2, bpp);
            expected_size += CalculateRawSizeIDAT((width + 1) >> 1, (height + 1) >> 2, bpp);
            if (width > 1) expected_size += CalculateRawSizeIDAT((width + 0) >> 1, (height + 1) >> 1, bpp);
            expected_size += CalculateRawSizeIDAT((width + 0), (height + 0) >> 1, bpp);

            break;
        }           
    }

    return expected_size;
}
