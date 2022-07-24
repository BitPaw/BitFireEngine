#ifndef TGAInclude
#define TGAInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum TGAColorType_
	{
		NoColorMap,
		ColorMapPresent,
		Reserverd,
		Custom
	}
	TGAColorType;

	typedef enum TGABitsPerPixel_
	{
		Invalid,

		X1,
		X8,
		X15,
		X16,
		X24,
		X32
	}
	TGABitsPerPixel;

	typedef enum TGAImageDataType_
	{
		UnkownImageDataType,

		NoImageDataIsPresent, // 0
		UncompressedColorMapped, // 1
		UncompressedTrueColor, // 2
		UncompressedBlackAndWhite, // 3 (grayscale) image
		RunLengthEncodedColorMapped,  // 9
		RunLengthEncodedTrueColor, // 10
		RunLengthEncodedBlackAndWhite // 11 (grayscale) image 
	}
	TGAImageDataType;

	typedef struct TGA_
	{
		//---[Header]----------------------	
		unsigned char ColorPaletteType;
		TGAImageDataType ImageDataType;

		unsigned short OriginX;
		unsigned short OriginY;
		unsigned short Width;
		unsigned short Height;
		TGABitsPerPixel PixelDepth;
		unsigned char ImageDescriptor;
		//---------------------------------

		//---[Image specification]---------
		size_t ImageInformationSize;
		char ImageInformation[255]; // Optional field containing identifying information
		size_t ColorMapDataSize;
		unsigned char* ColorMapData; // Look-up table containing color map data
		size_t ImageDataSize;
		unsigned char* ImageData; // Stored according to the image descriptor 	
		//----------------------------------


		//---- Versiion 2.0 only----------------
		// Extension Area
		char AuthorName[41]; // Name of the author. If not used, bytes should be set to NULL (\0) or spaces 
		char AuthorComment[324]; // A comment, organized as four lines, each consisting of 80 characters plus a NULL 

		unsigned short DateTimeMonth;// Date and time at which the image was created 
		unsigned short JobTimeDay;
		unsigned short JobTimeYear;
		unsigned short JobTimeHour;
		unsigned short JobTimeMinute;
		unsigned short JobTimeSecond;

		char JobID[41];
		unsigned short JobTimeHours; // spent creating the file (for billing, etc.) 
		unsigned short JobTimeMinutes;
		unsigned short JobTimeSeconds;
		char SoftwareName[41]; // The application that created the file. 
		unsigned short VersionNumber;
		char SoftwareVersion;
		unsigned int BackGroundColor;
		unsigned short PixelAspectRatioCounter;
		unsigned short PixelAspectRatioDenominator;
		unsigned short GammaCounter;
		unsigned short GammaDenominator;

		unsigned int ColorCorrectionOffset; // Number of bytes from the beginning of the file to the color correction table if present
		unsigned int PostagestampOffset; // Number of bytes from the beginning of the file to the postage stamp image if present
		unsigned int ScanlineOffset; // Number of bytes from the beginning of the file to the scan lines table if present 
		unsigned char AttributesType; // Specifies the alpha channel
		//-------------------------------
	}
	TGA;

	extern ActionResult TGAParse(TGA* tga, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif