#pragma once

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