#include "TGA.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>

#define TGAFileIdentifier "TRUEVISION-XFILE."
#define TGAFileIdentifierSize 18u

TGABitsPerPixel ConvertToPixelDepth(const unsigned char pixelDepth)
{
	switch(pixelDepth)
	{
		case 1u:
			return TGABitsPerPixelX1;

		case 8u:
			return TGABitsPerPixelX8;

		case 15u:
			return TGABitsPerPixelX15;

		case 16u:
			return TGABitsPerPixelX16;

		case 24u:
			return TGABitsPerPixelX24;

		case 32u:
			return TGABitsPerPixelX32;

		default:
			return TGABitsPerPixelInvalid;
	}
}

unsigned char ConvertFromPixelDepth(const TGABitsPerPixel bitsPerPixel)
{
	switch(bitsPerPixel)
	{
		default:
		case TGABitsPerPixelInvalid:
			return -1;

		case TGABitsPerPixelX1:
			return 1u;

		case TGABitsPerPixelX8:
			return 8u;

		case TGABitsPerPixelX15:
			return 15u;

		case TGABitsPerPixelX16:
			return 16u;

		case TGABitsPerPixelX24:
			return 24u;

		case TGABitsPerPixelX32:
			return 32u;
	}
}

TGAImageDataType ConvertToImageDataType(const unsigned char id)
{
	switch(id)
	{
		case 0u:
			return TGAImageDataNoImageDataIsPresent;

		case 1u:
			return TGAImageDataUncompressedColorMapped;

		case 2u:
			return TGAImageDataUncompressedTrueColor;

		case 3u:
			return TGAImageDataUncompressedBlackAndWhite;

		case 9u:
			return TGAImageDataRunLengthEncodedColorMapped;

		case 10u:
			return TGAImageDataRunLengthEncodedTrueColor;

		case 11u:
			return TGAImageDataRunLengthEncodedBlackAndWhite;

		default:
			return TGAImageDataInvalid;
	}
}

unsigned char ConvertFromImageDataType(const TGAImageDataType imageDataType)
{
	switch(imageDataType)
	{
		default:
		case TGAImageDataInvalid:
			return -1;

		case TGAImageDataNoImageDataIsPresent:
			return 0;

		case TGAImageDataUncompressedColorMapped:
			return 1u;

		case TGAImageDataUncompressedTrueColor:
			return 2u;

		case TGAImageDataUncompressedBlackAndWhite:
			return 3u;

		case TGAImageDataRunLengthEncodedColorMapped:
			return 9u;

		case TGAImageDataRunLengthEncodedTrueColor:
			return 10u;

		case TGAImageDataRunLengthEncodedBlackAndWhite:
			return 11u;
	}
}

size_t TGAFilePredictSize(const size_t width, const size_t height, const size_t bbp)
{
	return 0;
}

ActionResult TGAParse(TGA* tga, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;

	ParsingStreamConstruct(&parsingStream, data, dataSize);
	MemorySet(tga, sizeof(TGA), 0);
	*dataRead = 0;

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

		ParsingStreamReadCU(&parsingStream, &imageIDLengh);
		ParsingStreamReadCU(&parsingStream, &tga->ColorPaletteType);
		ParsingStreamReadCU(&parsingStream, &imageTypeValue);

		ParsingStreamReadCU(&parsingStream, &colorPaletteChunkEntryIndex, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &colorPaletteChunkSize, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &colorPaletteEntrySizeInBits);

		ParsingStreamReadCU(&parsingStream, &tga->OriginX, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &tga->OriginY, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &tga->Width, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &tga->Height, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &pixelDepth);
		ParsingStreamReadCU(&parsingStream, &tga->ImageDescriptor);

		tga->ImageInformationSize = imageIDLengh;

		tga->ImageDataType = ConvertToImageDataType(imageTypeValue);
		tga->PixelDepth = ConvertToPixelDepth(pixelDepth);

		tga->ImageDataSize = tga->Width * tga->Height * (pixelDepth / 8u);
		tga->ImageData = MemoryAllocate(sizeof(unsigned char) * tga->ImageDataSize);
	}
	//----------------------------------------------------

	//---[Parse Image ID]--------------
	if(tga->ImageInformationSize)
	{
		ParsingStreamReadD(&parsingStream, tga->ImageInformation, tga->ImageInformationSize);
	}
	//----------------------------------

	//---[Parse Color-Palette]----------
	if(colorPaletteChunkSize > 0)
	{
		ParsingStreamCursorAdvance(&parsingStream, colorPaletteChunkSize);
	}
	//--------------------------------

	//---[ ImageData ]------------------
	ParsingStreamReadD(&parsingStream, tga->ImageData, tga->ImageDataSize);
	//-----------------------------------------------------------------


	// Check end of dataStream if the dataStream is a Version 2.0 dataStream.
	{
		const unsigned int stringLengh = TGAFileIdentifierSize;
		unsigned int compareLength = stringLengh;
		const unsigned char lastCharacter = parsingStream.Data[parsingStream.DataSize - 1];
		const unsigned char isLastCharacter = lastCharacter == '.';
		unsigned char* string = parsingStream.Data + (parsingStream.DataSize - stringLengh);

		if(isLastCharacter)
		{
			compareLength--;
			string++;
		}

		footerEntryIndex = parsingStream.DataSize - (26u - 1u);

		const unsigned char isTGAVersionTwo = MemoryCompare(TGAFileIdentifier, TGAFileIdentifierSize, string, compareLength - 1); // Is this string at this address?;

		if(!isTGAVersionTwo) // Is this a TGA v.1.0 dataStream?
		{
			return ResultSuccessful; // Parsing finished. There should be no more data to parse. End of dataStream.
		}
	}

	firstFieldAfterHeader = parsingStream.DataCursor;

	//---[ Parse Footer ]--------------------------------------------------------
	parsingStream.DataCursor = footerEntryIndex; // Move 26 Bytes before the end. Start of the TGA-Footer.

	ParsingStreamReadIU(&parsingStream, &extensionOffset, EndianLittle);
	ParsingStreamReadIU(&parsingStream, &developerAreaOffset, EndianLittle);
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	if(developerAreaOffset > 0)
	{
		parsingStream.DataCursor = developerAreaOffset;// Jump to Developer Block
		// Parse Developer Fields
		// Parse Developer Directory
	}
	//---------------------------------------------------------------------------

	//---[ Extension Area ]--------------------------------------------------------
	if(extensionOffset > 0)
	{
		unsigned short extensionSize = 0;

		parsingStream.DataCursor = extensionOffset; // Jump to Extension Header
		ParsingStreamReadSU(&parsingStream,extensionSize, EndianLittle);

		const unsigned char isExtensionSizeAsExpected = extensionSize == 495u;

		if(!isExtensionSizeAsExpected)
		{
			return ResultFormatNotAsExpected;
		}

		ParsingStreamReadD(&parsingStream, tga->AuthorName, 41u);
		ParsingStreamReadD(&parsingStream, tga->AuthorComment, 324u);

		// 12 Bytes
		ParsingStreamReadSU(&parsingStream, &tga->DateTimeMonth, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeDay, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeYear, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeHour, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeMinute, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeSecond, EndianLittle);

		ParsingStreamReadD(&parsingStream, tga->JobID, 41u);

		// 6 Bytes
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeHours, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeMinutes, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->JobTimeSeconds, EndianLittle);

		parsingStream.DataCursor += 12u;

		ParsingStreamReadD(&parsingStream, tga->SoftwareName, 41u);

		ParsingStreamReadSU(&parsingStream, &tga->VersionNumber, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &tga->SoftwareVersion);

		ParsingStreamReadIU(&parsingStream, &tga->BackGroundColor, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->PixelAspectRatioCounter, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->PixelAspectRatioDenominator, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->GammaCounter, EndianLittle);
		ParsingStreamReadSU(&parsingStream, &tga->GammaDenominator, EndianLittle);
		ParsingStreamReadIU(&parsingStream, tga->ColorCorrectionOffset, EndianLittle);
		ParsingStreamReadIU(&parsingStream, tga->PostagestampOffset, EndianLittle);
		ParsingStreamReadIU(&parsingStream, tga->ScanlineOffset, EndianLittle);
		ParsingStreamReadCU(&parsingStream,tga->AttributesType);

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

	return ResultSuccessful;
}

ActionResult TGASerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten)
{
	return ResultInvalid;
}



/*
ActionResult TGA::Save(const wchar_t* filePath)
{
	const char footer[18] = TGAFileIdentifier;
	unsigned int fileLength = 500;
	File file;// (fileLength);


	// Data Stuff

	file.WriteToDisk(filePath);

	return ResultSuccessful;
}

ActionResult TGA::ConvertTo(Image& image)
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
			return ResultFormatNotSupported;
		}
	}

	pixelDataLengh = Width * Height * bytesPerPixel;
	newImageData = Memory::Allocate<unsigned char>(pixelDataLengh);

	if (!newImageData)
	{
		return ResultOutOfMemory;
	}

	image.Format = imageFormat;
	image.Height = Height;
	image.Width = Width;
	image.PixelData = newImageData;
	image.PixelDataSize = pixelDataLengh;

	MemoryCopy(ImageData, pixelDataLengh, newImageData, pixelDataLengh);
}*/