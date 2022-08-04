#ifndef ImageInclude
#define ImageInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
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
		unsigned char* PixelData;
	}
	Image;

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

	extern void ImageResize(Image* image, const ImageDataFormat format, const size_t width, const size_t height);
	extern void ImageFlipHorizontal(Image* image);
	extern void ImageFlipVertical(Image* image);
	extern void ImageRemoveColor(Image* image, unsigned char red, unsigned char green, unsigned char blue);

	//extern void ImageFillRandome();
	//extern void ImageFormatChange(ImageDataFormat imageFormat);


#ifdef __cplusplus
}
#endif

#endif