#include "ZLIB.h"

#include "ZLIBHeader.h"

#include "../../Algorithm/Adler32.h"

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