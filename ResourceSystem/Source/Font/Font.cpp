#include "Font.h"

#include "FNT/FNT.h"
#include "OTF/OTF.h"
#include "TTF/TTF.h"

#include "../File/File.h"

BF::ErrorCode BF::Font::Load(const char* filePath)
{
    File file(filePath);
    FontFormat fontFormat = ParseFontFormat(file.Extension);

    if (!file.DoesFileExist())
    {
        return ErrorCode::FileNotFound;
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
        return ErrorCode::NotSupported;
    }

    return ErrorCode::NoError;
}

BF::FontFormat BF::Font::ParseFontFormat(const char* fileExtension)
{
    AsciiString fileExtensionAS(fileExtension);

    bool isFNT = fileExtensionAS.CompareIgnoreCase("fnt");
    bool isOTF = fileExtensionAS.CompareIgnoreCase("otf");
    bool isTTF = fileExtensionAS.CompareIgnoreCase("ttf");

    if (isFNT) return FontFormat::FNT;
    if (isOTF) return FontFormat::OFT;
    if (isTTF) return FontFormat::TTF;

    return FontFormat::Unkown;
}

bool BF::Font::IsFontFile(const char* fileExtension)
{
    return ParseFontFormat(fileExtension) != FontFormat::Unkown;
}