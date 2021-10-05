#include "JPEGMarker.h"

BF::JPEGMarker BF::ConvertJPEGMarker(unsigned char jpegMarker[2])
{
	if (jpegMarker[0] != 0xFF)
	{
		return BF::JPEGMarker::MarkerInvalid;
	}

	switch (jpegMarker[1])
	{
		case 0xC2:
			return BF::JPEGMarker::MarkerInvalid; // TODO: What is this?

		case 0xDA: 
			return BF::JPEGMarker::StartOfScan;

		case 0xD8:
			return BF::JPEGMarker::StartOfImage;

		case 0xD9:
			return BF::JPEGMarker::EndOfImage;

		case 0xDB:
			return BF::JPEGMarker::DefineQuantizationTable;

		case 0xC0:
			return BF::JPEGMarker::StartOfFrame;

		case 0xC4:
			return BF::JPEGMarker::DefineHuffmanTable;

		case 0xE0:
			return BF::JPEGMarker::HeaderFileInfo;

		default:
			return BF::JPEGMarker::MarkerInvalid;
	}
}

void BF::ConvertJPEGMarker(unsigned char target[2], JPEGMarker jpegMarker)
{
}
