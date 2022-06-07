#include "OTF.h"

BF::FileActionResult BF::OTF::Load(const char* filePath)
{
    return FileActionResult::Invalid;
}

BF::FileActionResult BF::OTF::Load(const wchar_t* filePath)
{
    return FileActionResult::Invalid;
}

BF::FileActionResult BF::OTF::Load(const unsigned char* fileData, const size_t fileDataSize)
{
    return FileActionResult::Invalid;
}

BF::FileActionResult BF::OTF::Save(const wchar_t* filePath)
{
    return FileActionResult::Invalid;
}

BF::FileActionResult BF::OTF::ConvertTo(Font& font)
{
    return FileActionResult::Invalid;
}

BF::FileActionResult BF::OTF::ConvertFrom(Font& font)
{
    return FileActionResult::Invalid;
}