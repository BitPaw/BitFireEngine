#include "Font.h"

#include <File/Format/FNT/FNT.h>

#include "TTF/TTF.h"

#include <File/File.h>

BF::FileActionResult BF::Font::Load(const char* filePath)
{
    File file;

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&file, filePath, MemoryReadOnly);
        const bool sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return FileActionResult::Invalid;
        }
    }

    {
        const FontFormat hint = FileFormatPeek(filePath);
        const FileActionResult fileParsingResult = Load(file.Data, file.DataSize, hint);
        const bool success = fileParsingResult == FileActionResult::Successful;

        if(success)
        {
            return FileActionResult::Successful;
        }

        FileActionResult fileGuessResult = FileActionResult::Invalid;
        unsigned int fileFormatID = 1;

        do
        {
            //const FontFormat fontFormat = ConvertImageFileFormat(fileFormatID);

            //fileGuessResult = Load(file.Data, file.DataSize, fontFormat);

            fileFormatID++;
        }
        while(fileGuessResult == FileActionResult::InvalidHeaderSignature);

        return fileGuessResult;
    }
}

BF::FileActionResult BF::Font::Load(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::Font::Load(const unsigned char* fileData, const size_t fileDataSize, const FontFormat fontFormat)
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

                    return FileActionResult::Successful;
                }
            }

            break;
        }        
        case FontFormat::FormatTTF:
        {
            TTF ttf;

            {
                const FileActionResult fileActionResult = ttf.Load(fileData, fileDataSize);
                const bool sucessful = fileActionResult == FileActionResult::Successful;

                if(sucessful)
                {
                    ttf.ConvertTo(*this);

                    return FileActionResult::Successful;
                }
            }
            break;
        }
        case FontFormat::Unkown:
        default:
        {
            return FileActionResult::FormatNotSupported;
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::Font::Save(const wchar_t* filePath, FontFormat fontFormat)
{
    switch (fontFormat)
    {
        default:
        case BF::FontFormat::Unkown:
        {
            return FileActionResult::FormatNotSupported;
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

    return FileActionResult::Successful;
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