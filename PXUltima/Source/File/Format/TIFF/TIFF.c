#include "TIFF.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>

#define GIFFormatA {'I','I'}
#define GIFFormatB {'M','M'}

size_t TIFFFilePredictSize(const size_t width, const size_t height, const size_t bbp)
{
    return 0;
}

ActionResult TIFFParse(TIFF* tiff, const void* data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;

    MemorySet(tiff, sizeof(TIFF), 0);
    *dataRead = 0;

    ParsingStreamConstruct(&parsingStream, data, data);

    // Check Header
    {
        const char versionA[2] = GIFFormatA;
        const char versionB[2] = GIFFormatB;
        char headerTag[2];

        ParsingStreamReadD(&parsingStream, headerTag, 2u);

        const unsigned char useBigEndian = headerTag[0] == versionB[0] && headerTag[1] == versionB[1];
        const unsigned char useLittleEndian = headerTag[0] == versionA[0] && headerTag[1] == versionA[1];
        const unsigned char validVersion = useBigEndian != useLittleEndian;

        if(!validVersion)
        {
            return ResultInvalidVersion;
        }
    }

    *dataRead = parsingStream.DataCursor;

    return ResultSuccessful;
}

ActionResult TIFFParseToImage(Image* const image, const void* const data, const size_t dataSize, size_t* dataRead)
{
    return ResultInvalid;
}

ActionResult TIFFSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten)
{
    return ResultInvalid;
}