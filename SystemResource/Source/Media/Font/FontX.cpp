#include "FontX.h"

ActionResult BF::FontX::Load(const char* filePath)
{
    return FontLoadA(this, filePath);
}

ActionResult BF::FontX::Load(const wchar_t* filePath)
{
    return FontLoadW(this, filePath);
}

ActionResult BF::FontX::Load(const unsigned char* fileData, const size_t fileDataSize, const FontFileFormat fontFormat)
{
    return FontLoadD(this, fontFormat, fileData, fileDataSize);   
}

size_t BF::FontX::FullSizeInMemory()
{
    return sizeof(*this);
}