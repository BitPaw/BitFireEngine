#include "FontLoader.h"

BF::IFont* BF::FontLoader::LoadFontFromFile(std::string filePath)
{
    IFont* font = nullptr;
    FontFormat fontFormat = FontFormat::Unkown;
    TextFile textFile(filePath);
    std::string fileExtension = textFile.GetFileExtension();

    bool isFNT = fileExtension == "fnt";
    bool isOTF = fileExtension == "otf";
    bool isTTF = fileExtension == "ttf";

    if (isFNT) fontFormat = FontFormat::FNT;
    if (isOTF) fontFormat = FontFormat::OFT;
    if (isTTF) fontFormat = FontFormat::TTF;

    switch (fontFormat)
    {
        case FontFormat::FNT:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.FNT] BitMapFont File detected.");

            FNT* fnt = FNTLoader::LoadFromFile(filePath);

            font = fnt;

            break;
        }

        case FontFormat::OFT:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.OFT] OFT File detected.");

            OTF* otf = OTFLoader::LoadFromFile(filePath);

            font = otf;

            break; 
        }

        case FontFormat::TTF:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.TTF] TTF File detected.");

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