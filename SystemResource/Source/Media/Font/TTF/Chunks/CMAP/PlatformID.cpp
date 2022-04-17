#include "PlatformID.h"

BF::PlatformID BF::ConvertPlatformID(unsigned char platformID)
{
	switch (platformID)
	{
		case 0:	return BF::PlatformID::Unicode;
		case 1:	return BF::PlatformID::Macintosh;
		case 2:	return BF::PlatformID::ISO;
		case 3:	return BF::PlatformID::Windows;
		case 4:	return BF::PlatformID::Custom;

		default:
			return BF::PlatformID::Invalid;
	}
}