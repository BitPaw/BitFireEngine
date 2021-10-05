#include "Font.h"

#include "FNT/FNT.h"
#include "OTF/OTF.h"
#include "TTF/TTF.h"

#include "../File/File.h"

BF::FileActionResult BF::Font::Load(const char* filePath)
{
    File file(filePath);
    FontFormat fontFormat = FileFormatPeek(filePath);

    if (!file.DoesFileExist())
    {
        return FileActionResult::FileNotFound;
    }

    switch (fontFormat)
    {
    case FontFormat::FNT:
    {
        FNT* fnt = new FNT();
        fnt->Load(filePath);
        fnt->Convert(*this);
        break;
    }

    case FontFormat::OFT:
    {
        OTF otf;

        break;
    }

    case FontFormat::TTF:
    {
        TTF ttf;
        break;
    }

    case FontFormat::Unkown:
    default:
        return FileActionResult::FormatNotSupported;
    }

    return FileActionResult::Successful;
}

BF::FontFormat BF::Font::FileFormatPeek(const char* filePath)
{
    File file(filePath);
    AsciiString fileExtensionAS(file.Extension);

    bool isFNT = fileExtensionAS.CompareIgnoreCase("fnt");
    bool isOTF = fileExtensionAS.CompareIgnoreCase("otf");
    bool isTTF = fileExtensionAS.CompareIgnoreCase("ttf");

    if (isFNT) return FontFormat::FNT;
    if (isOTF) return FontFormat::OFT;
    if (isTTF) return FontFormat::TTF;

    return FontFormat::Unkown;
}