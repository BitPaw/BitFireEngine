#include "TIFF.h"

BF::TIFF::TIFF()
{

}

BF::FileActionResult BF::TIFF::Load(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::Save(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::ConvertTo(Image& image)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}