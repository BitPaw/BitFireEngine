#include "PlatformID.h"

BF::TTF::CMAP::PlatformID BF::TTF::CMAP::ConvertPlatformID(unsigned char platformID)
{
	switch (platformID)
	{
		case 0:	return BF::TTF::CMAP::PlatformID::Unicode;
		case 1:	return BF::TTF::CMAP::PlatformID::Macintosh;
		case 2:	return BF::TTF::CMAP::PlatformID::ISO;
		case 3:	return BF::TTF::CMAP::PlatformID::Windows;
		case 4:	return BF::TTF::CMAP::PlatformID::Custom;

		default:
			return BF::TTF::CMAP::PlatformID::Invalid;
	}
}