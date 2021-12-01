#include "EncodingID.h"

BF::EncodingID BF::ConvertEncodingID(PlatformID platformID, unsigned char encodingID)
{
	switch (platformID)
	{
		case PlatformID::Unicode:
		{
			switch (encodingID)
			{
				case 0: return EncodingID::Unicode10;
				case 1:	return EncodingID::Unicode11;
				case 2:	return EncodingID::ISOIEC10646;
				case 3:	return EncodingID::Unicode20BMPOnly;
				case 4: return EncodingID::Unicode20FullRepertoire;
				case 5: return EncodingID::UnicodeVariation;
				case 6: return EncodingID::UnicodeFullRepertoire;
			}

			break;
		}
		case BF::PlatformID::Macintosh:			
		{
			// ???
			break;
		}
		case BF::PlatformID::ISO:
		{
			switch (encodingID)
			{
				case 0:	return EncodingID::SevenBitASCII;
				case 1:	return EncodingID::ISO10646;
				case 2:	return EncodingID::ISO8858;
			}

			break;
		}
		case BF::PlatformID::Windows:
		{
			switch (encodingID)
			{
				case 0: return EncodingID::Symbol;
				case 1: return EncodingID::UnicodeBMP;
				case 2: return EncodingID::ShiftJIS;
				case 3: return EncodingID::PRC;
				case 4: return EncodingID::Big5;
				case 5: return EncodingID::Wansung;
				case 6: return EncodingID::Johab;
				
				case 7: // fall through
				case 8: // fall through
				case 9: // fall through
					return EncodingID::Reserved;

				case 10: return EncodingID::UnicodeFullRepertoire;
			}

			break;
		}		
		case BF::PlatformID::Custom:
			return EncodingID::OTFWindowsNTCompatibilityMapping;
	}

	return EncodingID::Invalid;
}