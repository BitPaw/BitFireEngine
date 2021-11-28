#pragma once

#include "PlatformID.h"

namespace BF::TTF::CMAP
{
	enum class EncodingID
	{
		Invalid,

		// (platform ID = 0)

		Unicode10,// semantics—deprecated,
		Unicode11,// semantics—deprecated,
		ISOIEC10646,// semantics—deprecated,
		Unicode20BMPOnly,
		Unicode20FullRepertoire,
		UnicodeVariation,// Sequences—for use with subtable format 14,
		Unicodefull,// repertoire—for use with subtable format 13,

		// Macintosh platform (platform ID = 1)

		// (platform ID = 2)

		SevenBitASCII,
		ISO10646,
		ISO8858,

		// Windows platform (platform ID = 3)
		Symbol,
		UnicodeBMP,
		ShiftJIS,
		PRC,
		Big5,
		Wansung,
		Johab,
		Reserved,
		UnicodeFullRepertoire,

		// Custom platform (platform ID = 4) and OTF Windows NT compatibility mapping
		OTFWindowsNTCompatibilityMapping
	};

	EncodingID ConvertEncodingID(PlatformID platformID, unsigned char encodingID);
}