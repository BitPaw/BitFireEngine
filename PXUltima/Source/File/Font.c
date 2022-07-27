#include "Font.h"

#include <Memory/Memory.h>
#include <Text/Text.h>
#include <File/File.h>

#include <File/Format/FNT/FNT.h>

void FontConstruct(Font* font)
{
    MemorySet(font, sizeof(Image), 0);
}

void FontDestruct(Font* font)
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

ActionResult FontLoadA(Font* font, const char* filePath)
{
    wchar_t filePathW[PathMaxSize];

    TextCopyAW(filePath, PathMaxSize, filePathW, PathMaxSize);

    ActionResult actionResult = FontLoadW(font, filePathW);

    return actionResult;
}

ActionResult FontLoadW(Font* font, const wchar_t* filePath)
{
    File file;

    FileConstruct(&file);

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, MemoryReadOnly);
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

ActionResult FontLoadD(Font* font, const FontFileFormat guessedFormat, const void* data, const size_t dataSize)
{
    switch(guessedFormat)
    {
        case FontFileFormatFNT:
        {
            // TODO: this is pointer for no reason. I use it at another place -> No delete needed
            FNT fnt;

            FontConstruct(&fnt);

            {
                const ActionResult fileActionResult = FNTParse(&fnt, data, dataSize);
                const unsigned char sucessful = ResultSuccessful == fileActionResult;

                if(!sucessful)
                {
                    //fnt->ConvertTo(*this);

                    return fileActionResult;
                }
            }

            FontDestruct(&fnt);

            break;
        }
        case FontFileFormatTTF:
        {
            /*
            TTF ttf;

            {
                const ActionResult fileActionResult = ttf.Load(fileData, fileDataSize);
                const bool sucessful = fileActionResult == ResultSuccessful;

                if(sucessful)
                {
                    ttf.ConvertTo(*this);

                    return ResultSuccessful;
                }
            }*/
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