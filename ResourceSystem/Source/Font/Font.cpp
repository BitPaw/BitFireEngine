#include "Font.h"

#include "FNT/FNT.h"
#include "OTF/OTF.h"
#include "TTF/TTF.h"

#include "../File/File.h"

BF::ErrorCode BF::Font::Load(AsciiString& filePath)
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
        BitMapFont = new FNT();

        break;

        AsciiString x("copy.fnt");

        FNT* fnt = (FNT*)BitMapFont;   

        fnt->Load(&filePath[0]);
        fnt->Convert(*this);

        filePath.AttachToBack(x);

        fnt->Save(filePath);

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

BF::FontFormat BF::Font::ParseFontFormat(AsciiString& fileExtension)
{
    bool isFNT = fileExtension.CompareIgnoreCase("fnt");
    bool isOTF = fileExtension.CompareIgnoreCase("otf");
    bool isTTF = fileExtension.CompareIgnoreCase("ttf");

    if (isFNT) return FontFormat::FNT;
    if (isOTF) return FontFormat::OFT;
    if (isTTF) return FontFormat::TTF;

    return FontFormat::Unkown;
}

bool BF::Font::IsFontFile(AsciiString& fileExtension)
{
    return ParseFontFormat(fileExtension) != FontFormat::Unkown;
}