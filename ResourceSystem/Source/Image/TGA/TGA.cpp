#include "TGA.h"
#include "../../File/File.h"
#include "../../Types/Endian.h"
#include "../../Container/ByteStreamHusk.h"

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

void BF::TGA::Load(const char* filePath)
{
	File file(filePath);
	file.Read();

	ByteStreamHusk byteSteam((unsigned char*)file.Data, file.Size);

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

	colorPaletteChunkEntryIndex = byteSteam.ExtractShortAndMove(Endian::Little);
	colorPaletteChunkSize = byteSteam.ExtractShortAndMove(Endian::Little);
	colorPaletteEntrySizeInBits = byteSteam.ExtractByteAndMove();

	OriginX = byteSteam.ExtractShortAndMove(Endian::Little);
	OriginY = byteSteam.ExtractShortAndMove(Endian::Little);
	Width = byteSteam.ExtractShortAndMove(Endian::Little);
	Height = byteSteam.ExtractShortAndMove(Endian::Little);
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
		ImageID = (unsigned char*)malloc(imageIDLengh);
		ImageIDSize = imageIDLengh;

		unsigned char* source = &byteSteam.StartAdress[byteSteam.CurrentPosition];

		memcpy(ImageID, source, imageIDLengh);

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
		unsigned char* destination = nullptr;
		unsigned char* source = nullptr;

		ImageDataSize = Width * Height * (pixelDepth / 8);
		ImageData = (unsigned char*)malloc(ImageDataSize);

		source = &byteSteam.StartAdress[byteSteam.CurrentPosition];

		memcpy(ImageData, source, ImageDataSize);

		byteSteam.CurrentPosition += ImageDataSize;
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

		isTGAVersionTwo = memcmp(truevisionString, string, compareLength-1) == 0; // Is this string at this address?;

		if (!isTGAVersionTwo) // Is this a TGA v.1.0 file?
		{
			return; // Parsing finished. There should be no more data to parse. End of file.
		}
	}
	
	firstFieldAfterHeader = byteSteam.CurrentPosition;

	//---[ Parse Footer ]--------------------------------------------------------
	byteSteam.CurrentPosition = footerEntryIndex; // Move 26 Bytes before the end. Start of the TGA-Footer.

	extensionOffset = byteSteam.ExtractIntegerAndMove(Endian::Little);
	developerAreaOffset = byteSteam.ExtractIntegerAndMove(Endian::Little);
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

		unsigned short extensionSize = byteSteam.ExtractShortAndMove(Endian::Little);

		if (extensionSize != 495u)
		{
			throw "Inavlid ExtensionSize";
		}

		byteSteam.CopyBytesAndMove(AuthorName, 41u);
		byteSteam.CopyBytesAndMove(AuthorComment, 324u);

		DateTimeMonth = byteSteam.ExtractShortAndMove(Endian::Little);
		JobTimeDay = byteSteam.ExtractShortAndMove(Endian::Little);
		JobTimeYear = byteSteam.ExtractShortAndMove(Endian::Little);
		JobTimeHour = byteSteam.ExtractShortAndMove(Endian::Little);
		JobTimeMinute = byteSteam.ExtractShortAndMove(Endian::Little);
		JobTimeSecond = byteSteam.ExtractShortAndMove(Endian::Little);

		byteSteam.CopyBytesAndMove(JobID, 41u);

		JobTimeHours = byteSteam.ExtractShortAndMove(Endian::Little);
		JobTimeMinutes = byteSteam.ExtractShortAndMove(Endian::Little);
		JobTimeSeconds = byteSteam.ExtractShortAndMove(Endian::Little);

		byteSteam.CurrentPosition += 12;

		byteSteam.CopyBytesAndMove(SoftwareName, 41u);

		VersionNumber = byteSteam.ExtractShortAndMove(Endian::Little);;
		SoftwareVersion = byteSteam.ExtractByteAndMove();

		BackGroundColor = byteSteam.ExtractIntegerAndMove(Endian::Little);
		PixelAspectRatioCounter = byteSteam.ExtractByteAndMove();
		PixelAspectRatioDenominator = byteSteam.ExtractByteAndMove();
		GammaCounter = byteSteam.ExtractByteAndMove();
		GammaDenominator = byteSteam.ExtractByteAndMove();
		ColorCorrectionOffset = byteSteam.ExtractIntegerAndMove(Endian::Little);
		PostagestampOffset = byteSteam.ExtractIntegerAndMove(Endian::Little);
		ScanlineOffset = byteSteam.ExtractIntegerAndMove(Endian::Little);
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

void BF::TGA::Save(const char* filePath)
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
	image.PixelData = (unsigned char*)malloc(pixelDataLengh);
	image.PixelDataSize = pixelDataLengh;

	memset(image.PixelData, 0xFF, pixelDataLengh);

	image.FillRandome();

	for (unsigned int i = 0; i < ImageDataSize; )
	{
		unsigned char blue = ImageData[i++];
		unsigned char green = ImageData[i++];
		unsigned char red = ImageData[i++];

		image.PixelData[dIndex++] = red;
		image.PixelData[dIndex++] = green;
		image.PixelData[dIndex++] = blue;
	}
}