#include "TTFVersionType.h"

BF::TTFVersionType BF::ConvertVersionType(unsigned short major, unsigned short minor)
{

	switch (minor)
	{
		case 0:
		{
			switch (major)
			{
				case 1: return TTFVersionType::Version1Dot0;
				case 2: return TTFVersionType::Version2Dot0;
				case 3: return TTFVersionType::Version3Dot0;
			}

			break;
		}
		case 5:
		{
			if (major == 2)
			{
				return TTFVersionType::Version2Dot5;
			}

			break;
		}
	}

	return TTFVersionType::Invalid;
}

void BF::ConvertVersionType(unsigned short& major, unsigned short& minor, TTFVersionType versionType)
{
}
