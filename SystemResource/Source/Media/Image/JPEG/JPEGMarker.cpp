#include "JPEGMarker.h"

BF::JPEGMarker BF::ConvertJPEGMarker(unsigned char jpegMarker[2])
{
	if (jpegMarker[0] != PNGMarkerStartKey)
	{
		return BF::JPEGMarker::MarkerInvalid;
	}

	switch (jpegMarker[1])
	{
		case PNGMarkerUnkownTypeCHANGETHIS:
			return BF::JPEGMarker::MarkerInvalid; // TODO: What is this?

		case PNGMarkerStartOfScan:
			return BF::JPEGMarker::StartOfScan;

		case PNGMarkerStartOfImage:
			return BF::JPEGMarker::StartOfImage;

		case PNGMarkerEndOfImage:
			return BF::JPEGMarker::EndOfImage;

		case PNGMarkerDefineQuantizationTable:
			return BF::JPEGMarker::DefineQuantizationTable;

		case PNGMarkerStartOfFrame:
			return BF::JPEGMarker::StartOfFrame;

		case PNGMarkerDefineHuffmanTable:
			return BF::JPEGMarker::DefineHuffmanTable;

		case PNGMarkerHeaderFileInfo:
			return BF::JPEGMarker::HeaderFileInfo;

		default:
			return BF::JPEGMarker::MarkerInvalid;
	}
}

void BF::ConvertJPEGMarker(unsigned char target[2], JPEGMarker jpegMarker)
{
	unsigned char keyA = PNGMarkerStartKey;
	unsigned char keyB = PNGMarkerInvalid;

	switch (jpegMarker)
	{
		default:
		case BF::JPEGMarker::MarkerInvalid:
		{
			keyB = PNGMarkerInvalid;
			break;
		}
		case BF::JPEGMarker::StartOfImage:
		{
			keyB = PNGMarkerEndOfImage;
			break;
		}
		case BF::JPEGMarker::HeaderFileInfo:
		{
			keyB = PNGMarkerHeaderFileInfo;
			break;
		}
		case BF::JPEGMarker::StartOfFrame:
		{
			keyB = PNGMarkerStartOfFrame;
			break;
		}
		case BF::JPEGMarker::DefineQuantizationTable:
		{
			keyB = PNGMarkerDefineQuantizationTable;
			break;
		}
		case BF::JPEGMarker::DefineHuffmanTable:
		{
			keyB = PNGMarkerDefineHuffmanTable;
			break;
		}
		case BF::JPEGMarker::StartOfScan:
		{
			keyB = PNGMarkerStartOfScan;
			break;
		}
		case BF::JPEGMarker::EndOfImage:
		{
			keyB = PNGMarkerEndOfImage;
			break;
		}			
	}

	target[0] = keyA;
	target[1] = keyB;
}