#ifndef ImageInclude
#define ImageInclude

#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef PXFont_
	typedef struct PXFont_ PXFont; // Avoid inclusion loop
#endif

	typedef enum ImageDataFormat_
	{
		ImageDataFormatInvalid,
		ImageDataFormatAlphaMaskBinary,
		ImageDataFormatAlphaMask,

		// 8-Bit
		ImageDataFormatRGB8,
		ImageDataFormatRGBA8,
		ImageDataFormatBGR8,
		ImageDataFormatBGRA8,

		// 16-Bit
		ImageDataFormatRGB16,
		ImageDataFormatRGBA16,

		ImageDataFormatRGBFloat,
		ImageDataFormatRGBAFloat
	}
	ImageDataFormat;

	typedef struct Image_
	{
		PXSize Width;
		PXSize Height;

		ImageDataFormat Format;

		PXSize PixelDataSize;
		void* PixelData;
	}
	Image;

	typedef  PXActionResult(*ParseToImage)(Image* const image, PXDataStream* dataStream);
	typedef  PXActionResult(*SerializeFromImage)(const Image* const image, PXDataStream* dataStream);

	PXPublic void ImageConstruct(Image* const image);
	PXPublic void ImageDestruct(Image* const image);

	PXPublic PXActionResult ImageLoadA(Image* const image, const PXTextASCII filePath);
	PXPublic PXActionResult ImageLoadW(Image* const image, const PXTextUNICODE filePath);
	PXPublic PXActionResult ImageLoadU(Image* const image, const PXTextUTF8 filePath);
	PXPublic PXActionResult ImageLoadD(Image* const image, PXDataStream* const dataStream, const FileFormatExtension guessedFormat);

	PXPublic PXActionResult ImageSaveA(Image* const image, const PXTextASCII filePath, const FileFormatExtension fileFormat, const ImageDataFormat dataFormat);
	PXPublic PXActionResult ImageSaveW(Image* const image, const PXTextUNICODE filePath, const FileFormatExtension fileFormat, const ImageDataFormat dataFormat);
	PXPublic PXActionResult ImageSaveU(Image* const image, const PXTextUTF8 filePath, const FileFormatExtension fileFormat, const ImageDataFormat dataFormat);
	PXPublic PXActionResult ImageSaveD
	(
		Image* image,
		PXDataStream* const pxDataStream,
		const FileFormatExtension fileFormat,
		const ImageDataFormat dataFormat
	);

	PXPublic PXSize ImageBitDepth(const ImageDataFormat imageDataFormat);
	PXPublic PXSize ImageBytePerPixel(const ImageDataFormat imageDataFormat);
	PXPublic PXSize ImageBitsPerPixel(const ImageDataFormat imageDataFormat);

	PXPublic PXBool ImageResize(Image* const image, const ImageDataFormat format, const PXSize width, const PXSize height);
	PXPublic void ImageFlipHorizontal(Image* image);
	PXPublic void ImageFlipVertical(Image* image);
	PXPublic void ImageRemoveColor(Image* image, unsigned char red, unsigned char green, unsigned char blue);
	PXPublic void ImageFillColorRGBA8(Image* const image, const PXByte red, const PXByte green, const PXByte blue, const PXByte alpha);

	PXPublic void* ImageDataPoint(const Image* const image, const PXSize x, const PXSize y);

	PXPublic PXSize ImagePixelPosition
	(
		const Image* const image,
		const PXSize x,
		const PXSize y
	);
	PXPublic void ImagePixelSetRGB8
	(
		Image* const image,
		const PXSize x,
		const PXSize y,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue
	);

	PXPublic void ImageDrawRectangle
	(
		Image* const image,
		const PXSize x,
		const PXSize y,
		const PXSize width,
		const PXSize height,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue,
		const unsigned char alpha
	);
	PXPublic void ImageDrawTextA
	(
		Image* const image,
		const PXSize x,
		const PXSize y,
		const PXSize width,
		const PXSize height,
		const PXFont* const font,
		const char* text
	);
	PXPublic void ImageDrawTextW
	(
		Image* const image,
		const PXSize x,
		const PXSize y,
		const PXSize width,
		const PXSize height,
		const PXFont* const font,
		const wchar_t* text
	);
	PXPublic void ImageMerge
	(
		Image* const image,
		const PXSize x,
		const PXSize y,
		const PXSize InsertX,
		const PXSize InsertY,
		const PXSize InsertWidth,
		const PXSize InsertHeight,
		const Image* const imageInsert
	);

	//CPublic void ImageFillRandome();
	//CPublic void ImageFormatChange(ImageDataFormat imageFormat);


#ifdef __cplusplus
}
#endif

#endif