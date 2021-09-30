#include "TIFF.h"

BF::TIFF::TIFF()
{

}

BF::ResourceLoadingResult BF::TIFF::Load(const char* filePath)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::TIFF::Save(const char* filePath)
{
    return ResourceLoadingResult::Successful;
}

void BF::TIFF::ConvertTo(Image& image)
{
}
