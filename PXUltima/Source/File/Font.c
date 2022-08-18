#include "Font.h"

#include <Memory/Memory.h>
#include <Text/Text.h>
#include <File/File.h>

#include <File/Format/FNT/FNT.h>
#include <File/Format/TTF/TTF.h>

#include <File/Image.h>

void FontConstruct(CFont* font)
{
    MemorySet(font, sizeof(CFont), 0);
}

void FontDestruct(CFont* font)
{

}

FontFileFormat FontGuessFormat(const wchar_t* filePath)
{
    wchar_t extension[ExtensionMaxSize];

    FilePathExtensionGetW(filePath, PathMaxSize, extension, ExtensionMaxSize);

    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "FNT", 3u))  return FontFileFormatFNT;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "OTF", 3u))  return FontFileFormatOFT;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "TTF", 4u))  return FontFileFormatTTF;

    return FontFileFormatUnkown;
}

ActionResult FontLoadA(CFont* font, const char* filePath)
{
    wchar_t filePathW[PathMaxSize];

    TextCopyAW(filePath, PathMaxSize, filePathW, PathMaxSize);

    ActionResult actionResult = FontLoadW(font, filePathW);

    return actionResult;
}

ActionResult FontLoadW(CFont* font, const wchar_t* filePath)
{
    File file;

    FileConstruct(&file);
    FontConstruct(font);

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, 0, MemoryReadOnly);
        const unsigned char sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }

    {
        const FontFileFormat hint = FontGuessFormat(filePath);
        const ActionResult fileParsingResult = FontLoadD(font, hint, file.Data, file.DataSize);
        const unsigned char success = fileParsingResult == ResultSuccessful;

        if(success)
        {
            return ResultSuccessful;
        }

        ActionResult fileGuessResult = ResultInvalid;
        unsigned int fileFormatID = 1;

        do
        {
            const ImageFileFormat imageFileFormat = fileGuessResult + fileFormatID;

            fileGuessResult = FontLoadD(font, imageFileFormat, file.Data, file.DataSize);

            fileFormatID++;
        }
        while(fileGuessResult == ResultInvalidHeaderSignature);

        return fileGuessResult;
    }

    FileDestruct(&file);
}

ActionResult FontLoadD(CFont* font, const FontFileFormat guessedFormat, const void* data, const size_t dataSize)
{
    FontConstruct(font);

    switch(guessedFormat)
    {
        case FontFileFormatFNT:
        {
            {
                size_t readBytes = 0;
                const ActionResult fileActionResult = FNTParse(&font->BitMapFont, data, dataSize, &readBytes);
                const unsigned char sucessful = ResultSuccessful == fileActionResult;

                if(!sucessful)
                {
                    return fileActionResult;
                }
            }

            break;
        }
        case FontFileFormatTTF:
        {
            TTF ttf;

            TTFConstruct(&ttf);

            {
                size_t readBytes = 0;
                const ActionResult fileActionResult = TTFParse(&ttf, data, dataSize, &readBytes);
                const unsigned char sucessful = fileActionResult == ResultSuccessful;

                if(sucessful)
                {
                   // ttf.ConvertTo(*this);

                    return ResultSuccessful;
                }
            }

            TTFDestruct(&ttf);

            break;
        }
        case FontFileFormatUnkown:
        default:
        {
            return ResultFormatNotSupported;
        }
    }

    return ResultSuccessful;
}
