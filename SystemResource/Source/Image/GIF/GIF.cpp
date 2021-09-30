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

void BF::GIF::ConvertTo(Image& image)
{
}
