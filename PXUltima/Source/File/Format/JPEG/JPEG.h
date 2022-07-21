#ifndef JPEGInclude
#define JPEGInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct JPEGFrameComponent_
	{
		unsigned char ID;
		unsigned char Width;
		unsigned char Height;
		unsigned char Key;
	}
	JPEGFrameComponent;

	typedef struct JPEGFrame_
	{
		unsigned short Precusion;
		unsigned short LineNb;
		unsigned char LineSamples;
		unsigned char ComponentListSize;
		JPEGFrameComponent ComponentList[3];
	}
	JPEGFrame;


	typedef struct JPEGFileInfo_
	{
		unsigned short Length;
		char Identifier[5];
		unsigned char VersionMajor;
		unsigned char VersionMinor;
		unsigned char DensityUnits;
		unsigned short DensityX;
		unsigned short DensityY;
		unsigned char ThumbnailX;
		unsigned char ThumbnailY;

		unsigned int ThumbnailDataSize;
		unsigned char* ThumbnailData;
	}
	JPEGFileInfo;

	typedef enum JPEGMarker_
	{
		JPEGMarkerInvalid,
		JPEGMarkerStartOfImage,
		JPEGMarkerHeaderFileInfo,
		JPEGMarkerStartOfFrame,
		JPEGMarkerDefineQuantizationTable,
		JPEGMarkerDefineHuffmanTable,
		JPEGMarkerStartOfScan,
		JPEGMarkerEndOfImage
	}
	JPEGMarker;


	typedef struct JPEGHuffmanTable_
	{
		unsigned char Class;
		unsigned char Destination;
	}JPEGHuffmanTable;


	typedef struct JPEGScanSelector_
	{
		unsigned char Selector;
		unsigned char DC;
		unsigned char ACTable;
	}
	JPEGScanSelector;

	typedef struct JPEGScanStart_
	{
		unsigned char ScanSelectorSize;
		JPEGScanSelector ScanSelector[3];
		unsigned char SpectralSelectFrom;
		unsigned char SpectralSelectTo;
		unsigned char SuccessiveAproximation;
	}
	JPEGScanStart;

	typedef struct JPEG_
	{
		JPEGFileInfo FileInfo;
		size_t HuffmanTableSize;
		JPEGHuffmanTable* HuffmanTable;
		JPEGScanStart ScanStart;

		size_t CompressedImageDataSize;
		unsigned char* CompressedImageData;
	}
	JPEG;


	static JPEGMarker ConvertToJPEGMarker(const unsigned short jpegMarker);
	static unsigned short ConvertFromJPEGMarker(JPEGMarker jpegMarker);

	extern ActionResult JPEGParse(JPEG* jpeg, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif