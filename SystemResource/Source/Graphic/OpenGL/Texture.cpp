#include "Texture.h"

BF::Texture::Texture()
{
	ID = -1;
	Type = ImageType::Invalid;
    Filter = ImageFilter::Invalid;
    LayoutNear = ImageLayout::Invalid;
    LayoutFar = ImageLayout::Invalid;
    WrapHeight = ImageWrap::Invalid;
    WrapWidth = ImageWrap::Invalid;

    ImageConstruct(&DataImage);
}

void BF::Texture::TextureWrap(ImageWrap wrap)
{
    WrapHeight = wrap;
    WrapWidth = wrap;
}

void BF::Texture::TextureWrap(ImageWrap wrapHeight, ImageWrap wrapWidth)
{
    WrapHeight = wrapHeight;
    WrapWidth = wrapWidth;
}