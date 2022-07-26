#include "Font.h"

#include <File/Format/FNT/FNT.h>

#include "TTF/TTF.h"

#include <File/File.h>

ActionResult BF::Font::Load(const char* filePath)
{
    File file;

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&file, filePath, MemoryReadOnly);
        const bool sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return ResultInvalid;
        }
    }

    {
        const FontFormat hint = FileFormatPeek(filePath);
        const ActionResult fileParsingResult = Load(file.Data, file.DataSize, hint);
        const bool success = fileParsingResult == ResultSuccessful;

        if(success)
        {
            return ResultSuccessful;
        }

        ActionResult fileGuessResult = ResultInvalid;
        unsigned int fileFormatID = 1;

        do
        {
            //const FontFormat fontFormat = ConvertImageFileFormat(fileFormatID);

            //fileGuessResult = Load(file.Data, file.DataSize, fontFormat);

            fileFormatID++;
        }
        while(fileGuessResult == ResultInvalidHeaderSignature);

        return fileGuessResult;
    }
}

ActionResult BF::Font::Load(const wchar_t* filePath)
{
    return ResultSuccessful;
}

ActionResult BF::Font::Load(const unsigned char* fileData, const size_t fileDataSize, const FontFormat fontFormat)
{
    switch(fontFormat)
    {
        case FontFormat::FormatFNT:
        {
            // TODO: this is pointer for no reason. I use it at another place -> No delete needed
            FNT* fnt = new FNT();

            {
                const unsigned char fileActionResult = FNTLoad(fnt, fileData, fileDataSize);
                const bool sucessful = fileActionResult == 0;

                if(sucessful)
                {
                    //fnt->ConvertTo(*this);

                    return ResultSuccessful;
                }
            }

            break;
        }        
        case FontFormat::FormatTTF:
        {
            TTF ttf;

            {
                const ActionResult fileActionResult = ttf.Load(fileData, fileDataSize);
                const bool sucessful = fileActionResult == ResultSuccessful;

                if(sucessful)
                {
                    ttf.ConvertTo(*this);

                    return ResultSuccessful;
                }
            }
            break;
        }
        case FontFormat::Unkown:
        default:
        {
            return ResultFormatNotSupported;
        }
    }

    return ResultSuccessful;
}

ActionResult BF::Font::Save(const wchar_t* filePath, FontFormat fontFormat)
{
    switch (fontFormat)
    {
        default:
        case BF::FontFormat::Unkown:
        {
            return ResultFormatNotSupported;
        }
        case BF::FontFormat::FormatFNT:
        {
            FNT fnt;
            //fnt.ConvertFrom(*this);
            //fnt.Save(filePath);
            break;
        }       
        case BF::FontFormat::FormatTTF:
        {
            TTF ttf;
            ttf.ConvertFrom(*this);
            ttf.Save(filePath);
            break;
        }
    }

    return ResultSuccessful;
}

BF::FontFormat BF::Font::FileFormatPeek(const char* filePath)
{
    //FilePath file(filePath);

    //if(file.ExtensionEquals("FNT")) return FontFormat::FormatFNT;
   // if(file.ExtensionEquals("OTF")) return FontFormat::FormatOFT;
    //if(file.ExtensionEquals("TTF")) return FontFormat::FormatTTF;

    return FontFormat::Unkown;
}

BF::FontFormat BF::Font::FileFormatPeek(const wchar_t* filePath)
{
    //FilePath file(filePath);

   // if (file.ExtensionEquals("FNT")) return FontFormat::FormatFNT;
    //if (file.ExtensionEquals("OTF")) return FontFormat::FormatOFT;
   // if (file.ExtensionEquals("TTF")) return FontFormat::FormatTTF;

    return FontFormat::Unkown;
}

size_t BF::Font::FullSizeInMemory()
{
    return sizeof(*this);
}