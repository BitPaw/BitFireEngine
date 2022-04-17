#include "GIF.h"

#include "GIFImageDescriptor.h"

#include <File/FileStream.h>
#include <Math/Math.h>

#define GIFHeader {'G','I','F'}
#define GIFVersionA {'8','7','a'}
#define GIFVersionB {'8','9','a'}
#define GIFEOF 0x3B

BF::GIF::GIF()
{

}

BF::FileActionResult BF::GIF::Load(const wchar_t* filePath)
{
    FileStream fileStream;
    FileActionResult loadingResult = fileStream.ReadFromDisk(filePath);

    if (loadingResult != FileActionResult::Successful)
    {
        return loadingResult;
    }

    // Check Header
    {
        const char versionA[3] = GIFVersionA;
        const char versionB[3] = GIFVersionB;
        char headerTag[3] = GIFHeader;
        char version[3] = { '#','#','#' };

        bool validHeader = fileStream.ReadAndCompare(headerTag, sizeof(headerTag));
        fileStream.Read(version, sizeof(version));

        bool validVersion =
            version[0] == versionA[0] &&
            version[1] == versionA[1] &&
            version[2] == versionA[2]
            ||
            version[0] == versionB[0] &&
            version[1] == versionB[1] &&
            version[2] == versionB[2];

        if (!validHeader)
        {
            return FileActionResult::InvalidHeaderSignature;
        }

        if (!validVersion)
        {
            return FileActionResult::InvalidVersion;
        }
    }

    // Logical Screen Descriptor.
    {
        fileStream.Read(Width, Endian::Little);
        fileStream.Read(Height, Endian::Little);

        unsigned char packedFields = 0;

        fileStream.Read(packedFields);
        fileStream.Read(BackgroundColorIndex);
        fileStream.Read(PixelAspectRatio);

        GlobalColorTableSize = packedFields & 0b00000111;
        IsSorted = (packedFields & 0b00001000) >> 3; 
        ColorResolution = (packedFields & 0b01110000) >> 4;
        IsGlobalColorTablePresent = (packedFields & 0b10000000) >> 7;

        if (IsGlobalColorTablePresent)
        {
            //---<Image Descriptor>--------------------------------------------

            // 3 x 2^(Size of Global Color Table+1).
            size_t size = 3 * Math::PowerOfTwo(GlobalColorTableSize + 1); // ???

            GIFImageDescriptor imageDescriptor;

            unsigned char packedFields = 0;

            fileStream.Read(imageDescriptor.Separator);
            fileStream.Read(imageDescriptor.LeftPosition, Endian::Little);
            fileStream.Read(imageDescriptor.TopPosition, Endian::Little);
            fileStream.Read(imageDescriptor.Width, Endian::Little);
            fileStream.Read(imageDescriptor.Height, Endian::Little);
            fileStream.Read(packedFields);

            imageDescriptor.LocalColorTableSize = (packedFields & 0b00000111);
            imageDescriptor.Reserved = (packedFields & 0b00011000) >> 3;
            imageDescriptor.SortFlag = (packedFields & 0b00100000) >> 5;
            imageDescriptor.InterlaceFlag = (packedFields & 0b01000000) >> 6;
            imageDescriptor.LocalColorTableFlag = (packedFields & 0b10000000) >> 7;

            if (imageDescriptor.LocalColorTableFlag)
            {
                //---<Local Color Table>---------------------------------------

                //-------------------------------------------------------------
            }

            //-----------------------------------------------------------------       
        }       
    }

    //---<Table Based Image Data>--------------------------------------
    
    //-----------------------------------------------------------------

    

    return FileActionResult::Successful;
}

BF::FileActionResult BF::GIF::Save(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::GIF::ConvertTo(Image& image)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::GIF::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}
