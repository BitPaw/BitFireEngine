#include "GIF.h"

BF::GIF::GIF()
{

}

BF::FileActionResult BF::GIF::Load(const char* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::GIF::Save(const char* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::GIF::ConvertTo(Image& image)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::GIF::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}
