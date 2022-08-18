#ifndef ImageInclude
#define ImageInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CFont_
	typedef struct CFont_ CFont; // Avoid inclusion loop
#endif

	typedef enum ImageFileFormat_
	{
		ImageFileFormatUnkown,
		ImageFileFormatBitMap,
		ImageFileFormatPNG,
		ImageFileFormatTGA,
		ImageFileFormatJPEG,
		ImageFileFormatTIFF,
		ImageFileFormatGIF
	}
	ImageFileFormat;

	typedef enum ImageDataFormat_
	{
		ImageDataFormatInvalid,
		ImageDataFormatAlphaMaskBinary,
		ImageDataFormatAlphaMask,
		ImageDataFormatRGB,
		ImageDataFormatRGBA,
		ImageDataFormatBGR,
		ImageDataFormatBGRA
	}
	ImageDataFormat;

	typedef struct Image_
	{
		size_t Width;
		size_t Height;

		ImageDataFormat Format;

		size_t PixelDataSize;
		void* PixelData;
	}
	Image;

	typedef ActionResult(*ParseToImage)(Image* const image, void* data, const size_t dataSize, size_t* dataWritten);
	typedef ActionResult(*SerializeFromImage)(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten);

	extern void ImageConstruct(Image* image);
	extern void ImageDestruct(Image* image);

	extern ImageFileFormat ImageGuessFormat(const wchar_t* filePath);

	extern ActionResult ImageLoadA(Image* image, const char* filePath);
	extern ActionResult ImageLoadW(Image* image, const wchar_t* filePath);
	extern ActionResult ImageLoadD(Image* image, const void* data, const size_t dataSize, const ImageFileFormat guessedFormat);

	extern ActionResult ImageSaveA(Image* image, const char* filePath, const ImageFileFormat fileFormat, const ImageDataFormat dataFormat);
	extern ActionResult ImageSaveW(Image* image, const wchar_t* filePath, const ImageFileFormat fileFormat, const ImageDataFormat dataFormat);
	extern ActionResult ImageSaveD
	(
		Image* image, 
		void* data, 
		const size_t dataSize, 
		const ImageFileFormat fileFormat,
		const ImageDataFormat dataFormat
	);

	extern size_t ImageBytePerPixel(const ImageDataFormat imageDataFormat);
	extern size_t ImageBitsPerPixel(const ImageDataFormat imageDataFormat);

	extern void ImageResize(Image* image, const ImageDataFormat format, const size_t width, const size_t height);
	extern void ImageFlipHorizontal(Image* image);
	extern void ImageFlipVertical(Image* image);
	extern void ImageRemoveColor(Image* image, unsigned char red, unsigned char green, unsigned char blue);

	extern void* ImageDataPoint(const Image* const image, const size_t x, const size_t y);

	extern void ImageDrawRectangle
	(
		Image* const image,
		const size_t x,
		const size_t y,
		const size_t width,
		const size_t height,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue,
		const unsigned char alpha
	);
	extern void ImageDrawTextA
	(
		Image* const image,		
		const size_t x,
		const size_t y,
		const size_t width,
		const size_t height,
		const CFont* const font,
		const char* text
	);
	extern void ImageDrawTextW
	(
		Image* const image,
		const size_t x,
		const size_t y,
		const size_t width,
		const size_t height,
		const CFont* const font,
		const wchar_t* text
	);
	extern void ImageMerge
	(
		Image* const image,
		const size_t x,
		const size_t y,
		Image* const imageInsert
	);

	//extern void ImageFillRandome();
	//extern void ImageFormatChange(ImageDataFormat imageFormat);


#ifdef __cplusplus
}
#endif

#endif