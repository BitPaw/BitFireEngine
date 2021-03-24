#include "FontLoader.h"

BF::Font* BF::FontLoader::LoadFontFromFile(AsciiString& filePath)
{
    Font* font = nullptr;
    TextFile textFile(filePath);
    AsciiString fileExtension = textFile.FileExtension;
    FontFormat fontFormat = ParseFontFormat(fileExtension);

    switch (fontFormat)
    {
        case FontFormat::FNT:
        {
            Log::Write(LogMessageType::Event, "[.FNT] BitMapFont File detected.");

            FNT* fnt = FNTLoader::LoadFromFile(filePath);     

            font = fnt;

            break;
        }

        case FontFormat::OFT:
        {
            Log::Write(LogMessageType::Event, "[.OFT] OFT File detected.");

            OTF* otf = OTFLoader::LoadFromFile(filePath);

            font = otf;

            break; 
        }

        case FontFormat::TTF:
        {
            Log::Write(LogMessageType::Event, "[.TTF] TTF File detected.");

            TTF* ttf = TTFLoader::LoadFromFile(filePath);

            font = ttf;

            break;
        }

        case FontFormat::Unkown:
        default:
            throw "Unsuported Type/File";
    }

    return font;
}



BF::FontFormat BF::FontLoader::ParseFontFormat(AsciiString& fileExtension)
{
    bool isFNT = fileExtension.CompareIgnoreCase("fnt");
    bool isOTF = fileExtension.CompareIgnoreCase("otf");
    bool isTTF = fileExtension.CompareIgnoreCase("ttf");

    if (isFNT) return FontFormat::FNT;
    if (isOTF) return FontFormat::OFT;
    if (isTTF) return FontFormat::TTF;

    return FontFormat::Unkown;
}

bool BF::FontLoader::IsFontFile(AsciiString& fileExtension)
{
    return ParseFontFormat(fileExtension) != FontFormat::Unkown;
}

BF::FNT* BF::FontLoader::FNTToFont(Font* font)
{
    return nullptr;
}

BF::OTF* BF::FontLoader::OTFToFont(Font* font)
{
    return nullptr;
}

BF::TTF* BF::FontLoader::TTFToFont(Font* font)
{
    return nullptr;
}

BF::Font* BF::FontLoader::FontToFNT(FNT fnt)
{
    return nullptr;
}

BF::Font* BF::FontLoader::FontToOTF(OTF otf)
{
    return nullptr;
}

BF::Font* BF::FontLoader::FontToTTF(TTF ttf)
{
    return nullptr;
}