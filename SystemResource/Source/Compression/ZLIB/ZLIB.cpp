#include "ZLIB.h"

#include "ZLIBHeader.h"

#include "../DEFLATE/DeflateBlock.h"
#include "../../Algorithm/Adler32.h"

#include <stdlib.h>

void BF::ZLIB::Unpack(unsigned char* inputData, size_t inputDataSize, unsigned char** outputData, size_t& outputDataSize)
{
	ZLIBHeader zLIBHeader(inputData[0], inputData[1]);

    const unsigned int infoBlockSize = 2u;
    const unsigned int adlerBlockSize = 4u;
    const unsigned int subBlockSize = inputDataSize - infoBlockSize - adlerBlockSize;
    unsigned char* subBlockStart = inputData + infoBlockSize;

    unsigned int adler32CheckSum =
        (unsigned int)inputData[inputDataSize - 4] << 24 |
        (unsigned int)inputData[inputDataSize - 3] << 16 |
        (unsigned int)inputData[inputDataSize - 2] << 8 |
        (unsigned int)inputData[inputDataSize - 1];

    //---<Dictionary Parse>----------------------------------------------------
    if (zLIBHeader.DictionaryPresent)
    {
        // Parse DICT dictionary identifier 

    }
    //-------------------------------------------------------------------------

    // Allocate
    if (!(*outputData))
    {
        (*outputData) = (unsigned char*)malloc(zLIBHeader.WindowSize * sizeof(unsigned char));
    }

    //---<Decompress DataBlock>------------------------------------------------
   // unsigned int dataCursor = 0;

    switch (zLIBHeader.CompressionMethod)
    {
        case BF::ZLIBCompressionMethod::Deflate:
        {
            DeflateBlock deflateBlock;

            do
            {
                deflateBlock.Inflate(subBlockStart, subBlockSize, *outputData, outputDataSize);
            }
            while (!deflateBlock.IsLastBlock);

            break;
        }
        default:
        case BF::ZLIBCompressionMethod::Reserved:
        case BF::ZLIBCompressionMethod::Invalid:
        {
            break;
        }
    }
    //-------------------------------------------------------------------------

    //---<ADLER32 Check>------------------------------------------------------- 
    bool isValidCheck = 0;
    //-------------------------------------------------------------------------
}
