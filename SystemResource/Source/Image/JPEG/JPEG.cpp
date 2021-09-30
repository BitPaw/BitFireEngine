#include "JPEG.h"

BF::JPEG::JPEG()
{

}

BF::ResourceLoadingResult BF::JPEG::Load(const char* filePath)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::JPEG::Save(const char* filePath)
{
    return ResourceLoadingResult::Successful;
}

void BF::JPEG::ConvertTo(Image& image)
{
}
