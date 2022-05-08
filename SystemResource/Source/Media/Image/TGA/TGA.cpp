#include "TGA.h"

#include <cassert>

#include <File/FileStream.h>

#include <string>

#define TGAFileIdentifier "TRUEVISION-XFILE."
#define TGAFileIdentifierSize 18u

BF::TGA::TGA()
{
	ColorPaletteType = 0;
	ImageDataType = TGAImageDataType::NoImageDataIsPresent;

	OriginX = 0;
	OriginY = 0;
	Width = 0;
	Height = 0;
	PixelDepth = TGABitsPerPixel::X1;
	ImageDescriptor = 0;

	ImageInformationSize = 0;
	ColorMapDataSize = 0;
	ColorMapData = nullptr;
	ImageDataSize = 0;
	ImageData = nullptr;
}

BF::TGA::~TGA()
{
	free(ColorMapData);
	free(ImageData);
}

BF::FileActionResult BF::TGA::Load(const wchar_t* filePath)
{
	unsigned short colorPaletteChunkEntryIndex = 0;
	unsigned short colorPaletteChunkSize = 0;
	unsigned char colorPaletteEntrySizeInBits = 0;

	size_t footerEntryIndex = 0;	
	size_t extensionOffset = 0;
	size_t developerAreaOffset = 0;
	size_t firstFieldAfterHeader = 0;
	FileStream file;
	FileActionResult loadingResult = file.ReadFromDisk(filePath);

	if (loadingResult != FileActionResult::Successful)
	{
		return loadingResult;
	}

	//---[ Parse Header ]-------------------------------
	{			
		unsigned char imageIDLengh = 0;
		unsigned char pixelDepth = 0;
		unsigned char imageTypeValue = 0;

		file.Read(imageIDLengh);
		file.Read(ColorPaletteType);
		file.Read(imageTypeValue);

		file.Read(colorPaletteChunkEntryIndex, Endian::Little);
		file.Read(colorPaletteChunkSize, Endian::Little);
		file.Read(colorPaletteEntrySizeInBits);

		file.Read(OriginX, Endian::Little);
		file.Read(OriginY, Endian::Little);
		file.Read(Width, Endian::Little);
		file.Read(Height, Endian::Little);
		file.Read(pixelDepth);
		file.Read(ImageDescriptor);

		ImageInformationSize = imageIDLengh;

		ImageDataType = ConvertImageDataType(imageTypeValue);
		PixelDepth = ConvertPixelDepth(pixelDepth);

		ImageDataSize = Width * Height * (pixelDepth / 8u);
		ImageData = (Byte*)malloc(ImageDataSize * sizeof(Byte));
	}	
	//----------------------------------------------------

	//---[Parse Image ID]--------------
	if (ImageInformationSize > 0)
	{
		file.Read(ImageInformation, ImageInformationSize);
	}
	//----------------------------------

	//---[Parse Color-Palette]----------
	if (colorPaletteChunkSize > 0)
	{
		file.DataCursorPosition += colorPaletteChunkSize;
	}
	//--------------------------------

	//---[ ImageData ]------------------	
	file.Read(ImageData, ImageDataSize);	
	//-----------------------------------------------------------------
	

	// Check end of file if the file is a Version 2.0 file.
	{
		const unsigned int stringLengh = TGAFileIdentifierSize;
		unsigned int compareLength = stringLengh;
		unsigned char lastCharacter = file.Data[file.DataSize-1];
		Byte* string = file.Data + (file.DataSize - stringLengh);
		bool isTGAVersionTwo = false;
		
		if (lastCharacter == '.')
		{
			compareLength--;
			string++;
		}

		footerEntryIndex = file.DataSize - (26u -1u);
		
		isTGAVersionTwo = memcmp(TGAFileIdentifier, string, compareLength-1) == 0; // Is this string at this address?;

		if (!isTGAVersionTwo) // Is this a TGA v.1.0 file?
		{
			return FileActionResult::Successful; // Parsing finished. There should be no more data to parse. End of file.
		}
	}
	
	firstFieldAfterHeader = file.DataCursorPosition;

	//---[ Parse Footer ]--------------------------------------------------------
	file.DataCursorPosition = footerEntryIndex; // Move 26 Bytes before the end. Start of the TGA-Footer.

	file.Read(extensionOffset, Endian::Little);
	file.Read(developerAreaOffset, Endian::Little);
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	if (developerAreaOffset > 0)
	{
		file.DataCursorPosition = developerAreaOffset;// Jump to Developer Block
		// Parse Developer Fields
		// Parse Developer Directory
	}
	//---------------------------------------------------------------------------

	//---[ Extension Area ]--------------------------------------------------------
	if (extensionOffset > 0)
	{
		unsigned short extensionSize = 0;

		file.DataCursorPosition = extensionOffset; // Jump to Extension Header
		file.Read(extensionSize, Endian::Little);

		if (extensionSize != 495u)
		{
			throw "Inavlid ExtensionSize";
		}

		file.Read(AuthorName, 41u);
		file.Read(AuthorComment, 324u);

		// 12 Bytes
		file.Read(DateTimeMonth, Endian::Little);
		file.Read(JobTimeDay, Endian::Little);
		file.Read(JobTimeYear, Endian::Little);
		file.Read(JobTimeHour, Endian::Little);
		file.Read(JobTimeMinute, Endian::Little);
		file.Read(JobTimeSecond, Endian::Little);

		file.Read(JobID, 41u);

		// 6 Bytes
		file.Read(JobTimeHours, Endian::Little); 
		file.Read(JobTimeMinutes, Endian::Little);
		file.Read(JobTimeSeconds, Endian::Little);		

		file.DataCursorPosition += 12u;

		file.Read(SoftwareName, 41u);

		file.Read(VersionNumber, Endian::Little);
		file.Read(SoftwareVersion);

		file.Read(BackGroundColor, Endian::Little);
		file.Read(PixelAspectRatioCounter, Endian::Little);
		file.Read(PixelAspectRatioDenominator, Endian::Little);
		file.Read(GammaCounter, Endian::Little);
		file.Read(GammaDenominator, Endian::Little);
		file.Read(ColorCorrectionOffset, Endian::Little);
		file.Read(PostagestampOffset, Endian::Little);
		file.Read(ScanlineOffset, Endian::Little);
		file.Read(AttributesType);

		/*
	if (ColorCorrectionOffset > 0)
	{
		byteSteam.CurrentPosition += ColorCorrectionOffset;
	}

	if (PostagestampOffset > 0)
	{
		byteSteam.CurrentPosition += PostagestampOffset;
	}

	if (ScanlineOffset > 0)
	{
		byteSteam.CurrentPosition += ScanlineOffset;
	}*/
	}
	//-----------------------------------------------------------		

	return FileActionResult::Successful;
}

BF::FileActionResult BF::TGA::Save(const wchar_t* filePath)
{
	const char footer[18] = TGAFileIdentifier;
	unsigned int fileLength = 500;
	FileStream fileStream(fileLength);


	// Data Stuff

	fileStream.WriteToDisk(filePath);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::TGA::ConvertTo(Image& image)
{	
	ImageDataFormat imageFormat = ImageDataFormat::Invalid;
	size_t pixelDataLengh = 0;
	size_t bytesPerPixel = 0;
	unsigned char* newImageData = nullptr;

	switch (PixelDepth)
	{
		case TGABitsPerPixel::X1:
		{
			imageFormat = ImageDataFormat::AlphaMaskBinary;			
			break;
		}
		case TGABitsPerPixel::X8:
		{
			imageFormat = ImageDataFormat::AlphaMaskBinary;
			bytesPerPixel = 1;
			break;
		}
		case TGABitsPerPixel::X15:
		{
			break;
		}
		case TGABitsPerPixel::X16:
		{
			break;
		}
		case TGABitsPerPixel::X24:
		{
			imageFormat = ImageDataFormat::BGR;
			bytesPerPixel = 3;
			break;
		}
		case TGABitsPerPixel::X32:
		{
			imageFormat = ImageDataFormat::BGRA;
			bytesPerPixel = 4;
			break;
		}
		case TGABitsPerPixel::Invalid:
		{
			return FileActionResult::FormatNotSupported;
		}
	}

	pixelDataLengh = Width * Height * bytesPerPixel;
	newImageData = (unsigned char*)malloc(pixelDataLengh);

	if (newImageData == nullptr)
	{
		return FileActionResult::OutOfMemory;
	}	

	image.Format = imageFormat;
	image.Height = Height;
	image.Width = Width;
	image.PixelData = newImageData;
	image.PixelDataSize = pixelDataLengh;

	memcpy(newImageData, ImageData, pixelDataLengh);
}

BF::FileActionResult BF::TGA::ConvertFrom(Image& image)
{
	return FileActionResult();
}