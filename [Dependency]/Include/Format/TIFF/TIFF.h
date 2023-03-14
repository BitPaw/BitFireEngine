#ifndef QOIInclude
#define QOIInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <Format/Image.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum TIFFType_
	{
		TIFFTypeInvalid,

		TIFFTypeByteSigned,
		TIFFTypeByteUnsigned,
		TIFFTypeByteCustom,

		TIFFTypeShortSigned,
		TIFFTypeShortUnsigned,

		TIFFTypeLongSigned,
		TIFFTypeLongUnsigned,

		TIFFTypeRationalSigned,
		TIFFTypeRationalUnsigned,

		TIFFTypeFloat,
		TIFFTypeDouble,

		TIFFTypeASCII
	}
	TIFFType;

	typedef enum TIFFTagType_
	{
		TIFFTagTypeInvalid,
		TIFFTagTypeUnkown,
		TIFFTagNewSubFileType,
		TIFFTagSubfileType,
		TIFFTagImageWidth,
		TIFFTagImageLength,
		TIFFTagBitsPerSample,
		TIFFTagCompression,
		TIFFTagPhotometricInterpretation,
		TIFFTagThreshholding,//	263
		TIFFTagCellWidth,//264
		TIFFTagCellLength,//265
		TIFFTagFillOrder,//266
		TIFFTagDocumentName,//269
		TIFFTagImageDescription,//270
		TIFFTagMake,//271
		TIFFTagModel,//272
		TIFFTagStripOffsets,//273
		TIFFTagOrientation,//274
		TIFFTagSamplesPerPixel,//	277
		TIFFTagRowsPerStrip,//278
		TIFFTagStripByteCounts,//279
		TIFFTagMinSampleValue,//280
		TIFFTagMaxSampleValue,//281
		TIFFTagXResolution,//282
		TIFFTagYResolution,//283
		TIFFTagPlanarConfiguration,//284
		TIFFTagPageName,//285
		TIFFTagXPosition,//286
		TIFFTagYPosition,//287
		TIFFTagFreeOffsets,//288
		TIFFTagFreeByteCounts,//289
		TIFFTagGrayResponseUnit,//290
		TIFFTagGrayResponseCurve,//291
		TIFFTagT4Options,//292
		TIFFTagT6Options,//293
		TIFFTagResolutionUnit,//296
		TIFFTagPageNumber,//297
		TIFFTagTransferFunction,//301
		TIFFTagSoftware,//305
		TIFFTagDateTime,//306
		TIFFTagArtist,//315
		TIFFTagHostComputer,//316
		TIFFTagPredictor,//317
		TIFFTagWhitePoint,//318
		TIFFTagPrimaryChromaticities,//319
		TIFFTagColorMap,//320
		TIFFTagHalftoneHints,//321
		TIFFTagTileWidth,//322
		TIFFTagTileLength,//323
		TIFFTagTileOffsets,//324
		TIFFTagTileByteCounts,//325
		TIFFTagInkSet,//332
		TIFFTagInkNames,//333
		TIFFTagNumberOfInks,//	334
		TIFFTagDotRange,//336
		TIFFTagTargetPrinter,//	337
		TIFFTagExtraSamples,//338
		TIFFTagSampleFormat,//339
		TIFFTagSMinSampleValue,//340
		TIFFTagSMaxSampleValue,//341
		TIFFTagTransferRange,//342
		TIFFTagJPEGProc,//512
		TIFFTagJPEGInterchangeFormat,//513
		TIFFTagJPEGInterchangeFormatLngth,//514
		TIFFTagJPEGRestartInterval,//515
		TIFFTagJPEGLosslessPredictors,//	517
		TIFFTagJPEGPointTransforms,//518
		TIFFTagJPEGQTables,//519
		TIFFTagJPEGDCTables,//520
		TIFFTagJPEGACTables,//521
		TIFFTagYCbCrCoefficients,//529
		TIFFTagYCbCrSubSampling,//530
		TIFFTagYCbCrPositioning,//531
		TIFFTagReferenceBlackWhite,//	532
		TIFFTagCopyright//	33432
	}
	TIFFTagType;


	typedef enum TIFFColorFormat_
	{
		TIFFColorInvalid,
		TIFFColorMonochromeWhiteIsZero,
		TIFFColorMonochromeBlackIsZero,
		TIFFColorRGB,
		TIFFColorRGBPalette,
		TIFFColorTransparencyMask,
		TIFFColorCMYK,
		TIFFColorYCbCr,
		TIFFColorCIELab
	}
	TIFFColorFormat;

	typedef enum TIFFCompression_
	{
		TIFFCompressionInvalid,
		TIFFCompressionUncompressed,
		TIFFCompressionCCITT1D,
		TIFFCompressionGroup3Fax,
		TIFFCompressionGroup4Fax,
		TIFFCompressionLZW,
		TIFFCompressionJPEGCompression,
		TIFFCompressionPackBits
	}
	TIFFCompression;


	typedef struct TIFFHeader_
	{
		Endian Endianness;
		unsigned short Version;
		unsigned int OffsetToIFD;
	}
	TIFFHeader;

	typedef struct TIFFPage_
	{
		unsigned short NumberOfTags;
		void* TagData;
		unsigned int OffsetToNextIFD;
	}
	TIFFPage;





	typedef struct TIFFTag_
	{
		unsigned short TypeID;
		TIFFTagType Type;
		unsigned short DataTypeID;
		TIFFType DataType;
		unsigned int NumberOfValues;
		unsigned int DataOffset;
	}
	TIFFTag;

	// Tag Image File Format
	typedef struct TIFF_
	{
		unsigned int Width;
		unsigned int Height;

		TIFFColorFormat PhotometricInterpretation;
		TIFFCompression Compression;
		unsigned short SamplesPerPixel;
		unsigned short BitsPerSample[4];
	}
	TIFF;



	PXPrivate TIFFType TIFFTypeFromID(const unsigned char tiffTypeID);
	PXPrivate TIFFTagType TIFFTagTypeFromID(const unsigned short tiffTagTypeID);
	PXPrivate TIFFCompression TIFFCompressionFromID(const unsigned short tiffCompressionID);
	PXPrivate TIFFColorFormat TIFFColorFormatFromID(const unsigned short tiffColorFormatID);

	PXPublic PXSize TIFFFilePredictSize(const PXSize width, const PXSize height, const PXSize bbp);

	PXPublic PXActionResult TIFFParse(TIFF* const tiff, PXDataStream* const dataStream);
	PXPublic PXActionResult TIFFParseToImage(Image* const image, PXDataStream* const dataStream);

	PXPublic PXActionResult TIFFSerializeFromImage(const Image* const image, PXDataStream* const dataStream);

#ifdef __cplusplus
}
#endif

#endif