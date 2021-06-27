#pragma once

namespace BF
{
	// DIB header (bitmap information header) - Type / Version
	enum class BMPInformationHeaderType
	{
		UnkownOrInvalid,

		// [12-Bytes] Windows 2.0 or later
		BitMapCoreHeader,

		// [12-Bytes] OS/2 1.x
		OS21XBitMapHeader,

		// [16-Bytes] This variant of the previous header contains only the first 16 bytes and the remaining bytes are assumed to be zero values.
		OS22XBitMapHeader,

		// [40-Bytes] Windows NT, 3.1x or later
		BitMapInfoHeader,

		// [52-Bytes] Undocumented 
		BitMapV2InfoHeader,

		// [56-Bytes] Not officially documented, but this documentation was posted on Adobe's forums,
		BitMapV3InfoHeader,

		// [108-Bytes] Windows NT 4.0, 95 or later 
		BitMapV4Header,

		// [124-Bytes] Windows NT 5.0, 98 or later 
		BitMapV5Header
	};
}