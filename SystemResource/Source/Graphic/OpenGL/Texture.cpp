#include "Texture.h"

BF::Texture::Texture()
{
	ID = 0;
	Type = ImageType::TextureUnkown;
    Filter = ImageFilter::NoFilter;
    LayoutNear = ImageLayout::Nearest;
    LayoutFar = ImageLayout::Nearest;
    WrapHeight = ImageWrap::NoModification;
    WrapWidth = ImageWrap::NoModification;
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