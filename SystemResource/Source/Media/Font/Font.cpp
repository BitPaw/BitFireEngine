#include "Font.h"

#include "FNT/FNT.h"
#include "OTF/OTF.h"
#include "TTF/TTF.h"

#include <File/File.h>

BF::FileActionResult BF::Font::Load(const wchar_t* filePath)
{
    FontFormat fontFormat = FileFormatPeek(filePath);

    if (!File::DoesFileExist(filePath))
    {
        return FileActionResult::FileNotFound;
    }

    switch (fontFormat)
    {
        case FontFormat::FormatFNT:
        {
            // TODO: this is pointer for no reason. I use it at another place -> No delete needed
            FNT* fnt = new FNT();
            fnt->Load(filePath);
            fnt->ConvertTo(*this);
            break;
        }
        case FontFormat::FormatOFT:
        {
            OTF otf;
            otf.Load(filePath);
            otf.ConvertTo(*this);
            break;
        }
        case FontFormat::FormatTTF:
        {
            TTF ttf;
            ttf.Load(filePath);
            ttf.ConvertTo(*this);
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
            fnt.ConvertFrom(*this);
            fnt.Save(filePath);
            break;
        }       
        case BF::FontFormat::FormatOFT:
        {
            OTF otf;
            otf.ConvertFrom(*this);
            otf.Save(filePath);
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

BF::FontFormat BF::Font::FileFormatPeek(const wchar_t* filePath)
{
    FilePath file(filePath);

    if (file.ExtensionEquals("FNT")) return FontFormat::FormatFNT;
    if (file.ExtensionEquals("OTF")) return FontFormat::FormatOFT;
    if (file.ExtensionEquals("TTF")) return FontFormat::FormatTTF;

    return FontFormat::Unkown;
}

size_t BF::Font::FullSizeInMemory()
{
    return sizeof(*this);
}