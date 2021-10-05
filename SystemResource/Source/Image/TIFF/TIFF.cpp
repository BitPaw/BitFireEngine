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

BF::ResourceLoadingResult BF::TIFF::ConvertTo(Image& image)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::TIFF::ConvertFrom(Image& image)
{
    return ResourceLoadingResult::Successful;
}