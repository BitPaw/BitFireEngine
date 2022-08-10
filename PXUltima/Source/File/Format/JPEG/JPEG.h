#ifndef JPEGInclude
#define JPEGInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Image.h>

#define JPEGQuantizationTableLuminanceIndex 0
#define JPEGQuantizationTableChrominanceIndex 1

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum JPEGMarker_
	{
		JPEGMarkerInvalid,

		JPEGMarkerStartOfFrameHuffmanBaselineDCT, // [0xFFC0] SOF0
		JPEGMarkerStartOfFrameHuffmanSequentialExtendedDCT, // [0xFFC1] SOF1
		JPEGMarkerStartOfFrameHuffmanProgressiveDCT, // [0xFFC2] SOF2
		JPEGMarkerStartOfFrameHuffmanSequentialLossless,// [0xFFC3] SOF3

		JPEGMarkerDefineHuffmanTableList, // [0xFFC4] DHT

		JPEGMarkerStartOfFrameHuffmanDifferentialSequential,// [0xFFC5] SOF5
		JPEGMarkerStartOfFrameHuffmanDifferentialProgressiveDCT,// [0xFFC6] SOF6
		JPEGMarkerStartOfFrameHuffmanDifferentialLosslessSequential,// [0xFFC7] SOF7

		JPEGMarkerStartOfFrameArithmeticJPEGExtension, // [0xFFC8] JPG
		JPEGMarkerStartOfFrameArithmeticExtendedSequentialDCT, // [0xFFC9] SOF09
		JPEGMarkerStartOfFrameArithmeticProgressiveDCT, // [0xFFCA] SOF10
		JPEGMarkerStartOfFrameArithmeticLosslessSequential, // [0xFFCB] SOF11

		JPEGMarkerDefineArithmeticCoding, // [0xFFCC] DAC

		JPEGMarkerStartOfFrameArithmeticDifferentialSequentialDCT, // [0xFFCD] SOF13
		JPEGMarkerStartOfFrameArithmeticDifferentialProgressiveDCT, // [0xFFCE] SOF14
		JPEGMarkerStartOfFrameArithmeticDifferentialLosslessSequential, // [0xFFCF] SOF15

		JPEGMarkerIntervalTerminationRestart0, // [0xFFD0] RST0
		JPEGMarkerIntervalTerminationRestart1, // [0xFFD1] RST1
		JPEGMarkerIntervalTerminationRestart2, // [0xFFD2] RST2
		JPEGMarkerIntervalTerminationRestart3, // [0xFFD3] RST3
		JPEGMarkerIntervalTerminationRestart4, // [0xFFD4] RST4
		JPEGMarkerIntervalTerminationRestart5, // [0xFFD5] RST5
		JPEGMarkerIntervalTerminationRestart6, // [0xFFD6] RST6
		JPEGMarkerIntervalTerminationRestart7, // [0xFFD7] RST7

		JPEGMarkerStartOfImage, // [0xFFD8] SOI
		JPEGMarkerEndOfImage, // [0xFFD9] EOI
		JPEGMarkerStartOfScan, // [0xFFDA] SOS
		JPEGMarkerDefineQuantizationTableList, // [0xFFDB] DQT
		JPEGMarkerDefineNumberOfLines, // [0xFFDC] DNL
		JPEGMarkerDefineRestartInterval, // [0xFFDD] DRI
		JPEGMarkerDefineHierarchicalProgression, // [0xFFDE] DHP
		JPEGMarkerExpandReferenceComponentList, // [0xFFDF] EXP

		JPEGMarkerApplicationSegment00, // [0xFFE0] APP0
		JPEGMarkerApplicationSegment01, // [0xFFE1] APP1
		JPEGMarkerApplicationSegment02, // [0xFFE2] APP2
		JPEGMarkerApplicationSegment03, // [0xFFE3] APP3
		JPEGMarkerApplicationSegment04, // [0xFFE4] APP4
		JPEGMarkerApplicationSegment05, // [0xFFE5] APP5
		JPEGMarkerApplicationSegment06, // [0xFFE6] APP6
		JPEGMarkerApplicationSegment07, // [0xFFE7] APP7
		JPEGMarkerApplicationSegment08, // [0xFFE8] APP8
		JPEGMarkerApplicationSegment09, // [0xFFE9] APP9
		JPEGMarkerApplicationSegment10, // [0xFFEA] APP10
		JPEGMarkerApplicationSegment11, // [0xFFEB] APP11
		JPEGMarkerApplicationSegment12, // [0xFFEC] APP12
		JPEGMarkerApplicationSegment13, // [0xFFED] APP13
		JPEGMarkerApplicationSegment14, // [0xFFEE] APP14
		JPEGMarkerApplicationSegment15, // [0xFFEF] APP15

		JPEGMarkerJPEGExtension00, // [0xFFF0] JPG0
		JPEGMarkerJPEGExtension01, // [0xFFF1] JPG1
		JPEGMarkerJPEGExtension02, // [0xFFF2] JPG2
		JPEGMarkerJPEGExtension03, // [0xFFF3] JPG3
		JPEGMarkerJPEGExtension04, // [0xFFF4] JPG4
		JPEGMarkerJPEGExtension05, // [0xFFF5] JPG5
		JPEGMarkerJPEGExtension06, // [0xFFF6] JPG6
		JPEGMarkerJPEGExtension07, // [0xFFF7] JPG7
		JPEGMarkerJPEGExtension08, // [0xFFF8] JPG8
		JPEGMarkerJPEGExtension09, // [0xFFF9] JPG9
		JPEGMarkerJPEGExtension10, // [0xFFFA] JPG10
		JPEGMarkerJPEGExtension11, // [0xFFFB] JPG11
		JPEGMarkerJPEGExtension12, // [0xFFFC] JPG12
		JPEGMarkerJPEGExtension13, // [0xFFFD] JPG13

		JPEGMarkerComment, // [0xFFFE] COM

		JPEGMarkerTemporary, // [0xFF01] TEM
		JPEGMarkerReserved, // [0xFF02] to [0xFFBF] RES
	}
	JPEGMarker;

	typedef struct JPEGFrameComponent_
	{
		unsigned char ID;
		unsigned char SamplingFactorHorizonal;
		unsigned char SamplingFactorVertical;
		unsigned char QuantizationTableID;
	}
	JPEGFrameComponent;

	typedef struct JPEGFrame_
	{
		unsigned char Precision;
		unsigned short Height;
		unsigned short Width;
		unsigned char ComponentListSize;
		JPEGFrameComponent ComponentList[255];
	}
	JPEGFrame;


	typedef struct JPEGFileInfo_
	{
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



	typedef struct JPEGHuffmanTable_
	{
		unsigned char ID;
		unsigned char Type;
	}JPEGHuffmanTable;


	typedef struct JPEGScanSelector_
	{
		unsigned char ID;
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

		unsigned char QuantizationTable[2][64];

		size_t HuffmanTableSize;
		JPEGHuffmanTable* HuffmanTable;
		JPEGScanStart ScanStart;

		size_t CompressedImageDataSize;
		unsigned char* CompressedImageData;

		size_t CommentSize;
		char* Comment;
	}
	JPEG;


	static JPEGMarker ConvertToJPEGMarker(const unsigned short jpegMarker);
	static unsigned short ConvertFromJPEGMarker(const JPEGMarker jpegMarker);

	extern size_t JPEGFilePredictSize(const size_t width, const size_t height, const size_t bbp);

	extern void JPEGConstruct(JPEG* jpeg);
	extern void JPEGDestruct(JPEG* jpeg);


	extern ActionResult JPEGParseToImage(Image* const image, const void* data, const size_t dataSize, size_t* dataRead);
	extern ActionResult JPEGParse(JPEG* jpeg, const void* data, const size_t dataSize, size_t* dataRead);

	extern ActionResult JPEGSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten);

#ifdef __cplusplus
}
#endif

#endif