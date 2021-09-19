#include "TGA.h"
#include "../../File/File.h"
#include "../../Types/Endian.h"
#include "../../Container/ByteStreamHusk.h"
#include <cassert>

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

	ImageIDSize = 0;
	ImageID = nullptr; 
	ColorMapDataSize = 0;
	ColorMapData = nullptr;
	ImageDataSize = 0;
	ImageData = nullptr;
}

BF::TGA::~TGA()
{
	free(ImageID);
	free(ColorMapData);
	free(ImageData);
}

void BF::TGA::Load(const char* filePath)
{
	unsigned int footerEntryIndex = 0;
	unsigned char imageIDLengh = 0;
	unsigned short colorPaletteChunkEntryIndex = 0;
	unsigned short colorPaletteChunkSize = 0;
	unsigned char colorPaletteEntrySizeInBits = 0;
	unsigned char imageTypeValue = 0;
	unsigned char pixelDepth = 0;
	unsigned int extensionOffset = 0;
	unsigned int developerAreaOffset = 0;
	unsigned int firstFieldAfterHeader = 0;
	File file(filePath);
	ResourceLoadingResult loadingResult = file.ReadFromDisk();

	if (loadingResult != ResourceLoadingResult::Successful)
	{
		return;
	}

	//---[ Parse Header ]-------------------------------
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

	switch (imageTypeValue)
	{
		case 0:
			ImageDataType = TGAImageDataType::NoImageDataIsPresent;
			break;

		case 1:
			ImageDataType = TGAImageDataType::UncompressedColorMapped;
			break;

		case 2:
			ImageDataType = TGAImageDataType::UncompressedTrueColor;
			break;

		case 3:
			ImageDataType = TGAImageDataType::UncompressedBlackAndWhite;
			break;

		case 9:
			ImageDataType = TGAImageDataType::RunLengthEncodedColorMapped;
			break;

		case 10:
			ImageDataType = TGAImageDataType::RunLengthEncodedTrueColor;
			break;

		case 11:
			ImageDataType = TGAImageDataType::RunLengthEncodedBlackAndWhite;
			break;

		default:
			throw "Invalid image Type";
	}

	switch (pixelDepth)
	{
		case 1:
			PixelDepth = TGABitsPerPixel::X1;
			break;

		case 8:
			PixelDepth = TGABitsPerPixel::X8;
			break;

		case 15:
			PixelDepth = TGABitsPerPixel::X15;
			break;

		case 16:
			PixelDepth = TGABitsPerPixel::X16;
			break;

		case 24:
			PixelDepth = TGABitsPerPixel::X24;
			break;

		case 32:
			PixelDepth = TGABitsPerPixel::X32;
			break;

		default:
			PixelDepth = TGABitsPerPixel::Invalid;
	}

	//----------------------------------------------------

	//---[Parse Image ID]--------------
	if (imageIDLengh > 0)
	{
		ImageIDSize = imageIDLengh;
		ImageID = (unsigned char*)malloc(ImageIDSize);

		file.Read(ImageID, ImageIDSize);
	}
	//----------------------------------

	//---[Parse Color-Palette]----------
	if (colorPaletteChunkSize > 0)
	{
		file.DataCursorPosition += colorPaletteChunkSize;
	}
	//--------------------------------

	//---[ ImageData ]------------------
	{
		ImageDataSize = Width * Height * (pixelDepth / 8);
		ImageData = (unsigned char*)malloc(ImageDataSize);

		file.Read(ImageData, ImageDataSize);
	}
	//-----------------------------------------------------------------
	

	// Check end of file if the file is a Version 2.0 file.
	{
		const unsigned int stringLengh = 18;
		unsigned int compareLength = stringLengh;
		unsigned char lastCharacter = file.Data[file.DataSize-1];
		char* string = &file.Data[file.DataSize - stringLengh];
		bool isTGAVersionTwo = false;
		
		if (lastCharacter == '.')
		{
			compareLength--;
			string++;
		}

		footerEntryIndex = file.DataSize - 26u;

		isTGAVersionTwo = memcmp("TRUEVISION-XFILE.", string, compareLength-1) == 0; // Is this string at this address?;

		if (!isTGAVersionTwo) // Is this a TGA v.1.0 file?
		{
			return; // Parsing finished. There should be no more data to parse. End of file.
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
	if (extensionOffset > 0 && false) // TODO: Disabled -> some wierd errors 
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
}

void BF::TGA::Save(const char* filePath)
{
	const char footer[18] = "TRUEVISION-XFILE.";
	File file(filePath, 500);

	unsigned int fileLength = 500;
	char* data = (char*)malloc(fileLength * sizeof(char));
	ByteStreamHusk byteStreamHusk(data, fileLength);


	byteStreamHusk.InsertArrayAndMove((void*)footer, 8);

	// Data Stuff

	file.WriteToDisk();
}

void BF::TGA::Convert(Image& image)
{	
	ImageFormat imageFormat = ImageFormat::Unkown;
	unsigned int pixelDataLengh = -1;
	unsigned int bytesPerPixel = -1;
	unsigned char* newImageData = nullptr;

	switch (PixelDepth)
	{
		case TGABitsPerPixel::X1:
		{
			imageFormat = ImageFormat::AlphaMaskBinary;			
			break;
		}
		case TGABitsPerPixel::X8:
		{
			imageFormat = ImageFormat::AlphaMaskBinary;
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
			imageFormat = ImageFormat::BGR;
			bytesPerPixel = 3;
			break;
		}
		case TGABitsPerPixel::X32:
		{
			imageFormat = ImageFormat::BGRA;
			bytesPerPixel = 4;
			break;
		}
	}

	pixelDataLengh = Width * Height * bytesPerPixel;
	newImageData = (unsigned char*)malloc(pixelDataLengh);

	if (newImageData == nullptr)
	{
		return;
	}	

	image.Type = ImageType::Texture2D;
	image.Format = imageFormat;
	image.Height = Height;
	image.Width = Width;
	image.PixelData = newImageData;
	image.PixelDataSize = pixelDataLengh;

	memcpy(newImageData, ImageData, pixelDataLengh);
}