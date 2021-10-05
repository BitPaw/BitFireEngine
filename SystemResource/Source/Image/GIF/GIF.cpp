#include "GIF.h"

BF::GIF::GIF()
{

}

BF::ResourceLoadingResult BF::GIF::Load(const char* filePath)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::GIF::Save(const char* filePath)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::GIF::ConvertTo(Image& image)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::GIF::ConvertFrom(Image& image)
{
    return ResourceLoadingResult::Successful;
}
