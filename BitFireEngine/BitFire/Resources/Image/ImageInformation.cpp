#include "ImageInformation.h"

BF::ImageInformation::ImageInformation()
{
	Format = ImageFormatMode::RGB;
	Filter = ImageFilterMode::NoFilter;

	LayoutNear = ImageLayout::Nearest;
	LayoutFar = ImageLayout::Nearest;

	WrapHeight = ImageWrap::Repeat;
	WrapWidth = ImageWrap::Repeat;
}
