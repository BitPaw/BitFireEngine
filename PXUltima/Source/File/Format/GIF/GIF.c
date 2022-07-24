#include "GIF.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <Math/Math.h>

#define GIFHeader {'G','I','F'}
#define GIFVersionA {'8','7','a'}
#define GIFVersionB {'8','9','a'}
#define GIFEOF 0x3B

ActionResult GIFLoad(GIF* gif, const void* data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;

    MemorySet(gif, sizeof(GIF), 0);
    ParsingStreamConstruct(&parsingStream, data, dataSize);
    *dataRead = 0;

    // Check Header
    {
        const char versionA[3] = GIFVersionA;
        const char versionB[3] = GIFVersionB;
        const char headerTag[3] = GIFHeader;
        char version[3] = { '#','#','#' };

        const unsigned char validHeader = ParsingStreamReadAndCompare(&parsingStream, headerTag, sizeof(headerTag));

        ParsingStreamReadD(&parsingStream, version, sizeof(version));

        const unsigned char validVersion =
            version[0] == versionA[0] &&
            version[1] == versionA[1] &&
            version[2] == versionA[2]
            ||
            version[0] == versionB[0] &&
            version[1] == versionB[1] &&
            version[2] == versionB[2];

        if(!validHeader)
        {
            return ResultInvalidHeaderSignature;
        }

        if(!validVersion)
        {
            return ResultInvalidVersion;
        }
    }

    // Logical Screen Descriptor.
    {
        ParsingStreamReadSU(&parsingStream, &gif->Width, EndianLittle);
        ParsingStreamReadSU(&parsingStream, &gif->Height, EndianLittle);

        unsigned char packedFields = 0;

        ParsingStreamReadCU(&parsingStream, &packedFields);
        ParsingStreamReadCU(&parsingStream, &gif->BackgroundColorIndex);
        ParsingStreamReadCU(&parsingStream, &gif->PixelAspectRatio);

        gif->GlobalColorTableSize = packedFields & 0b00000111;
        gif->IsSorted = (packedFields & 0b00001000) >> 3;
        gif->ColorResolution = (packedFields & 0b01110000) >> 4;
        gif->IsGlobalColorTablePresent = (packedFields & 0b10000000) >> 7;

        if(gif->IsGlobalColorTablePresent)
        {
            //---<Image Descriptor>--------------------------------------------

            // 3 x 2^(Size of Global Color Table+1).
            size_t size = 3 * MathPowerOfTwo(gif->GlobalColorTableSize + 1); // ???

            GIFImageDescriptor imageDescriptor;

            unsigned char packedFields = 0;

            ParsingStreamReadCU(&parsingStream, &imageDescriptor.Separator);
            ParsingStreamReadCU(&parsingStream, &imageDescriptor.LeftPosition, EndianLittle);
            ParsingStreamReadCU(&parsingStream, &imageDescriptor.TopPosition, EndianLittle);
            ParsingStreamReadCU(&parsingStream, &imageDescriptor.Width, EndianLittle);
            ParsingStreamReadCU(&parsingStream, &imageDescriptor.Height, EndianLittle);
            ParsingStreamReadCU(&parsingStream, &packedFields);

            imageDescriptor.LocalColorTableSize = (packedFields & 0b00000111);
            imageDescriptor.Reserved = (packedFields & 0b00011000) >> 3;
            imageDescriptor.SortFlag = (packedFields & 0b00100000) >> 5;
            imageDescriptor.InterlaceFlag = (packedFields & 0b01000000) >> 6;
            imageDescriptor.LocalColorTableFlag = (packedFields & 0b10000000) >> 7;

            if(imageDescriptor.LocalColorTableFlag)
            {
                //---<Local Color Table>---------------------------------------

                //-------------------------------------------------------------
            }

            //-----------------------------------------------------------------       
        }
    }

    //---<Table Based Image Data>--------------------------------------

    //-----------------------------------------------------------------


    return ResultSuccessful;
}
