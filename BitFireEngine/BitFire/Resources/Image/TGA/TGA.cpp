#include "TGA.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Utility/ByteStreamHusk.h"

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
}

void BF::TGA::Load(AsciiString& filePath)
{
	AsciiString bytes;
	FileLoader::ReadFileAsBytes(filePath, bytes);
	ByteStreamHusk byteSteam((unsigned char*)&bytes[0], bytes.Size() -1);

	unsigned int footerEntryIndex = 0;

	/*
	for (size_t i = 0; !byteSteam.IsAtEnd(); i++)
	{
		unsigned char x = byteSteam.ExtractByteAndMove();

		printf("%2X ", x);

		if ((i%32)==0) 
		{
			printf("\n");
		}
	}

	printf("\n");*/

	byteSteam.CurrentPosition = 0;

	unsigned char imageIDLengh = 0;
	unsigned short colorPaletteChunkEntryIndex = 0;
	unsigned short colorPaletteChunkSize = 0;
	unsigned char colorPaletteEntrySizeInBits = 0;
	unsigned char imageTypeValue = 0;
	unsigned char pixelDepth = 0;	

	unsigned int extensionOffset = 0;
	unsigned int developerAreaOffset = 0;
	unsigned int firstFieldAfterHeader = 0;

	//---[ Parse Header ]-------------------------------
	imageIDLengh = byteSteam.ExtractByteAndMove();
	ColorPaletteType = byteSteam.ExtractByteAndMove();
	imageTypeValue = byteSteam.ExtractByteAndMove();

	colorPaletteChunkEntryIndex = byteSteam.ExtractShortAndMove(EndianType::Little);
	colorPaletteChunkSize = byteSteam.ExtractShortAndMove(EndianType::Little);
	colorPaletteEntrySizeInBits = byteSteam.ExtractByteAndMove();

	OriginX = byteSteam.ExtractShortAndMove(EndianType::Little);
	OriginY = byteSteam.ExtractShortAndMove(EndianType::Little);
	Width = byteSteam.ExtractShortAndMove(EndianType::Little);
	Height = byteSteam.ExtractShortAndMove(EndianType::Little);
	pixelDepth = byteSteam.ExtractByteAndMove();
	ImageDescriptor = byteSteam.ExtractByteAndMove();

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
			TGABitsPerPixel::X1;
			break;

		case 8:
			TGABitsPerPixel::X8;
			break;

		case 15:
			TGABitsPerPixel::X15;
			break;

		case 16:
			TGABitsPerPixel::X16;
			break;

		case 24:
			TGABitsPerPixel::X24;
			break;

		case 32:
			TGABitsPerPixel::X32;
			break;
	}

	//----------------------------------------------------

	//---[Parse Image ID]--------------
	if (imageIDLengh > 0)
	{
		ImageID.ReSize(imageIDLengh);

		unsigned char* destination = &ImageID[0];
		unsigned char* source = &byteSteam.StartAdress[byteSteam.CurrentPosition];

		memcpy(destination, source, imageIDLengh);

		byteSteam.CurrentPosition += imageIDLengh;
	}
	//----------------------------------

	//---[Parse Color-Palette]----------
	if (colorPaletteChunkSize > 0)
	{
		byteSteam.CurrentPosition += colorPaletteChunkSize;
	}
	//--------------------------------

	//---[ ImageData ]------------------
	{
		unsigned int pixelDataSize = Width * Height * (pixelDepth / 8);
		unsigned char* destination = nullptr;
		unsigned char* source = nullptr;

		ImageData.ReSize(pixelDataSize);

		destination = &ImageData[0];
		source = &byteSteam.StartAdress[byteSteam.CurrentPosition];

		memcpy(destination, source, pixelDataSize);

		byteSteam.CurrentPosition += pixelDataSize;
	}
	//-----------------------------------------------------------------
	

	// Check end of file if the file is a Version 2.0 file.
	{
		const unsigned int stringLengh = 18;
		unsigned int compareLength = stringLengh;
		unsigned char lastCharacter = byteSteam.StartAdress[byteSteam.DataLength];
		unsigned char* string = &byteSteam.StartAdress[byteSteam.DataLength - stringLengh+1];
		char truevisionString[stringLengh] = "TRUEVISION-XFILE.";
		bool isTGAVersionTwo = false;
		
		if (lastCharacter == '.')
		{
			compareLength--;
			string++;
		}

		footerEntryIndex = byteSteam.DataLength - compareLength + 1 - 8u;

		isTGAVersionTwo = memcmp(truevisionString, string, stringLengh) == 0; // Is this string at this address?;

		if (!isTGAVersionTwo) // Is this a TGA v.1.0 file?
		{
			return; // Parsing finished. There should be no more data to parse. End of file.
		}
	}


	
	firstFieldAfterHeader = byteSteam.CurrentPosition;

	//---[ Parse Footer ]--------------------------------------------------------
	byteSteam.CurrentPosition = footerEntryIndex; // Move 26 Bytes before the end. Start of the TGA-Footer.

	extensionOffset = byteSteam.ExtractIntegerAndMove(EndianType::Little);
	developerAreaOffset = byteSteam.ExtractIntegerAndMove(EndianType::Little);
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	if (developerAreaOffset > 0)
	{
		byteSteam.CurrentPosition = developerAreaOffset;// Jump to Developer Block
		// Parse Developer Fields
		// Parse Developer Directory
	}
	//---------------------------------------------------------------------------

	//---[ Extension Area ]--------------------------------------------------------
	if (extensionOffset > 0)
	{
		byteSteam.CurrentPosition = extensionOffset; // Jump to Extension Header

		unsigned short extensionSize = byteSteam.ExtractShortAndMove(EndianType::Little);

		if (extensionSize != 495u)
		{
			throw "Inavlid ExtensionSize";
		}

		byteSteam.CopyBytesAndMove(AuthorName, 41u);
		byteSteam.CopyBytesAndMove(AuthorComment, 324u);

		DateTimeMonth = byteSteam.ExtractShortAndMove(EndianType::Little);
		JobTimeDay = byteSteam.ExtractShortAndMove(EndianType::Little);
		JobTimeYear = byteSteam.ExtractShortAndMove(EndianType::Little);
		JobTimeHour = byteSteam.ExtractShortAndMove(EndianType::Little);
		JobTimeMinute = byteSteam.ExtractShortAndMove(EndianType::Little);
		JobTimeSecond = byteSteam.ExtractShortAndMove(EndianType::Little);

		byteSteam.CopyBytesAndMove(JobID, 41u);

		JobTimeHours = byteSteam.ExtractShortAndMove(EndianType::Little);
		JobTimeMinutes = byteSteam.ExtractShortAndMove(EndianType::Little);
		JobTimeSeconds = byteSteam.ExtractShortAndMove(EndianType::Little);

		byteSteam.CurrentPosition += 12;

		byteSteam.CopyBytesAndMove(SoftwareName, 41u);

		VersionNumber = byteSteam.ExtractShortAndMove(EndianType::Little);;
		SoftwareVersion = byteSteam.ExtractByteAndMove();

		BackGroundColor = byteSteam.ExtractIntegerAndMove(EndianType::Little);
		PixelAspectRatioCounter = byteSteam.ExtractByteAndMove();
		PixelAspectRatioDenominator = byteSteam.ExtractByteAndMove();
		GammaCounter = byteSteam.ExtractByteAndMove();
		GammaDenominator = byteSteam.ExtractByteAndMove();
		ColorCorrectionOffset = byteSteam.ExtractIntegerAndMove(EndianType::Little);
		PostagestampOffset = byteSteam.ExtractIntegerAndMove(EndianType::Little);
		ScanlineOffset = byteSteam.ExtractIntegerAndMove(EndianType::Little);
		AttributesType = byteSteam.ExtractByteAndMove();

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

void BF::TGA::Save(AsciiString& filePath)
{
	const char footer[18] = "TRUEVISION-XFILE.";
}

void BF::TGA::Convert(Image& image)
{	
	unsigned int pixelDataLengh = Width * Height * 3;
	unsigned int dIndex = 0;

	image.Format = ImageFormat::RGB;
	image.Height = Height;
	image.Width = Width;
	image.PixelData.ReSize(pixelDataLengh);

	for (unsigned int i = 0; i < ImageData.Size(); )
	{
		unsigned int blue = ImageData[i++];
		unsigned int green = ImageData[i++];
		unsigned int red = ImageData[i++];

		image.PixelData[dIndex++] = red;
		image.PixelData[dIndex++] = green;
		image.PixelData[dIndex++] = blue;
	}
}