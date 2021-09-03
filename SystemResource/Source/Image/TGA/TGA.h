#pragma once

#include "../../Container/AsciiString.h"
#include "../../Container/List.hpp"
#include "TGAImageDataType.h"
#include "../Image.h"
#include "TGABitsPerPixel.h"

namespace BF
{
	// Truevision Advanced Raster Graphics Array
	struct TGA
	{
		public:	
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
		unsigned int ImageIDSize;
		unsigned char* ImageID; // Optional field containing identifying information
		unsigned int ColorMapDataSize;
		unsigned char* ColorMapData; // Look-up table containing color map data
		unsigned int ImageDataSize;
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

		TGA();
		~TGA();

		void Load(const char* filePath);
		void Save(const char* filePath);
		void Convert(Image& image);
	};
}



