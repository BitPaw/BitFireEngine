#include "TGA.h"

#include <File/File.h>
#include <Hardware/Memory/Memory.h>

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
	MemoryRelease(ColorMapData, ColorMapDataSize);
	MemoryRelease(ImageData, ImageDataSize);
}

BF::FileActionResult BF::TGA::Load(const char* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryReadOnly);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::TGA::Load(const wchar_t* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryReadOnly);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::TGA::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);

	unsigned short colorPaletteChunkEntryIndex = 0;
	unsigned short colorPaletteChunkSize = 0;
	unsigned char colorPaletteEntrySizeInBits = 0;

	size_t footerEntryIndex = 0;
	unsigned int extensionOffset = 0;
	unsigned int developerAreaOffset = 0;
	size_t firstFieldAfterHeader = 0;

	//---[ Parse Header ]-------------------------------
	{
		unsigned char imageIDLengh = 0;
		unsigned char pixelDepth = 0;
		unsigned char imageTypeValue = 0;

		dataStream.Read(imageIDLengh);
		dataStream.Read(ColorPaletteType);
		dataStream.Read(imageTypeValue);

		dataStream.Read(colorPaletteChunkEntryIndex, EndianLittle);
		dataStream.Read(colorPaletteChunkSize, EndianLittle);
		dataStream.Read(colorPaletteEntrySizeInBits);

		dataStream.Read(OriginX, EndianLittle);
		dataStream.Read(OriginY, EndianLittle);
		dataStream.Read(Width, EndianLittle);
		dataStream.Read(Height, EndianLittle);
		dataStream.Read(pixelDepth);
		dataStream.Read(ImageDescriptor);

		ImageInformationSize = imageIDLengh;

		ImageDataType = ConvertImageDataType(imageTypeValue);
		PixelDepth = ConvertPixelDepth(pixelDepth);

		ImageDataSize = Width * Height * (pixelDepth / 8u);
		ImageData = Memory::Allocate<Byte__>(ImageDataSize);
	}
	//----------------------------------------------------

	//---[Parse Image ID]--------------
	if(ImageInformationSize > 0)
	{
		dataStream.Read(ImageInformation, ImageInformationSize);
	}
	//----------------------------------

	//---[Parse Color-Palette]----------
	if(colorPaletteChunkSize > 0)
	{
		dataStream.DataCursor += colorPaletteChunkSize;
	}
	//--------------------------------

	//---[ ImageData ]------------------
	dataStream.Read(ImageData, ImageDataSize);
	//-----------------------------------------------------------------


	// Check end of dataStream if the dataStream is a Version 2.0 dataStream.
	{
		const unsigned int stringLengh = TGAFileIdentifierSize;
		unsigned int compareLength = stringLengh;
		const unsigned char lastCharacter = dataStream.Data[dataStream.DataSize - 1];
		const bool isLastCharacter = lastCharacter == '.';
		Byte__* string = dataStream.Data + (dataStream.DataSize - stringLengh);

		if(isLastCharacter)
		{
			compareLength--;
			string++;
		}

		footerEntryIndex = dataStream.DataSize - (26u - 1u);

		const bool isTGAVersionTwo = MemoryCompare(TGAFileIdentifier, TGAFileIdentifierSize, string, compareLength - 1); // Is this string at this address?;

		if(!isTGAVersionTwo) // Is this a TGA v.1.0 dataStream?
		{
			return FileActionResult::Successful; // Parsing finished. There should be no more data to parse. End of dataStream.
		}
	}

	firstFieldAfterHeader = dataStream.DataCursor;

	//---[ Parse Footer ]--------------------------------------------------------
	dataStream.DataCursor = footerEntryIndex; // Move 26 Bytes before the end. Start of the TGA-Footer.

	dataStream.Read(extensionOffset, EndianLittle);
	dataStream.Read(developerAreaOffset, EndianLittle);
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	if(developerAreaOffset > 0)
	{
		dataStream.DataCursor = developerAreaOffset;// Jump to Developer Block
		// Parse Developer Fields
		// Parse Developer Directory
	}
	//---------------------------------------------------------------------------

	//---[ Extension Area ]--------------------------------------------------------
	if(extensionOffset > 0)
	{
		unsigned short extensionSize = 0;

		dataStream.DataCursor = extensionOffset; // Jump to Extension Header
		dataStream.Read(extensionSize, EndianLittle);

		const bool isExtensionSizeAsExpected = extensionSize == 495u;

		if(!isExtensionSizeAsExpected)
		{
			return FileActionResult::FormatNotAsExpected;
		}

		dataStream.Read(AuthorName, 41u);
		dataStream.Read(AuthorComment, 324u);

		// 12 Bytes
		dataStream.Read(DateTimeMonth, EndianLittle);
		dataStream.Read(JobTimeDay, EndianLittle);
		dataStream.Read(JobTimeYear, EndianLittle);
		dataStream.Read(JobTimeHour, EndianLittle);
		dataStream.Read(JobTimeMinute, EndianLittle);
		dataStream.Read(JobTimeSecond, EndianLittle);

		dataStream.Read(JobID, 41u);

		// 6 Bytes
		dataStream.Read(JobTimeHours, EndianLittle);
		dataStream.Read(JobTimeMinutes, EndianLittle);
		dataStream.Read(JobTimeSeconds, EndianLittle);

		dataStream.DataCursor += 12u;

		dataStream.Read(SoftwareName, 41u);

		dataStream.Read(VersionNumber, EndianLittle);
		dataStream.Read(SoftwareVersion);

		dataStream.Read(BackGroundColor, EndianLittle);
		dataStream.Read(PixelAspectRatioCounter, EndianLittle);
		dataStream.Read(PixelAspectRatioDenominator, EndianLittle);
		dataStream.Read(GammaCounter, EndianLittle);
		dataStream.Read(GammaDenominator, EndianLittle);
		dataStream.Read(ColorCorrectionOffset, EndianLittle);
		dataStream.Read(PostagestampOffset, EndianLittle);
		dataStream.Read(ScanlineOffset, EndianLittle);
		dataStream.Read(AttributesType);

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
	File file;// (fileLength);


	// Data Stuff

	file.WriteToDisk(filePath);

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
	newImageData = Memory::Allocate<unsigned char>(pixelDataLengh);

	if (!newImageData)
	{
		return FileActionResult::OutOfMemory;
	}

	image.Format = imageFormat;
	image.Height = Height;
	image.Width = Width;
	image.PixelData = newImageData;
	image.PixelDataSize = pixelDataLengh;

	MemoryCopy(ImageData, pixelDataLengh, newImageData, pixelDataLengh);
}

BF::FileActionResult BF::TGA::ConvertFrom(Image& image)
{
	return FileActionResult();
}