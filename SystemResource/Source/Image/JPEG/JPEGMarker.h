#pragma once

// First Key
#define PNGMarkerStartKey 0xFF

// Secondary Key
#define PNGMarkerInvalid 0xFF
#define PNGMarkerUnkownTypeCHANGETHIS 0xC2
#define PNGMarkerStartOfScan 0xDA
#define PNGMarkerStartOfImage 0xD8
#define PNGMarkerEndOfImage 0xD9
#define PNGMarkerDefineQuantizationTable 0xDB
#define PNGMarkerStartOfFrame 0xC0
#define PNGMarkerDefineHuffmanTable 0xC4
#define PNGMarkerHeaderFileInfo 0xE0

namespace BF
{
	enum class JPEGMarker
	{
		MarkerInvalid,

		StartOfImage,

		HeaderFileInfo,

		StartOfFrame,

		DefineQuantizationTable,
		DefineHuffmanTable,
	
		StartOfScan,

		EndOfImage
	};

	JPEGMarker ConvertJPEGMarker(unsigned char jpegMarker[2]);
	void ConvertJPEGMarker(unsigned char target[2], JPEGMarker jpegMarker);
}