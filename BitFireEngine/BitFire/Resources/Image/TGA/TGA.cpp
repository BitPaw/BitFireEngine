#include "TGA.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Utility/ByteStreamHusk.h"

BF::TGA::TGA()
{
	ImageIDLengh = 0;
	ColorPaletteType = 0;
	ImageDataType = TGAImageDataType::NoImageDataIsPresent;

	ColorPaletteChunkEntryIndex = 0;
	ColorPaletteChunkSize = 0;
	ColorPaletteEntrySizeInBits = 0;

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
	ByteStreamHusk byteSteam((unsigned char*)&bytes[0], bytes.Size());
	
	unsigned char imageTypeValue;
	unsigned char pixelDepth;

	//---[ Parse Header ]-------------------------------
	ImageIDLengh = byteSteam.ExtractByteAndMove();
	ColorPaletteType = byteSteam.ExtractByteAndMove();
	imageTypeValue = byteSteam.ExtractByteAndMove();

	ColorPaletteChunkEntryIndex = byteSteam.ExtractShortAndMove(EndianType::Little);
	ColorPaletteChunkSize = byteSteam.ExtractShortAndMove(EndianType::Little);
	ColorPaletteEntrySizeInBits = byteSteam.ExtractByteAndMove();

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
	if (ImageIDLengh > 0)
	{
		ImageID.ReSize(ImageIDLengh);

		unsigned char* destination = &ImageID[0];
		unsigned char* source = &byteSteam.StartAdress[byteSteam.CurrentPosition];

		memcpy(destination, source, ImageIDLengh);

		byteSteam.CurrentPosition += ImageIDLengh;
	}
	//----------------------------------

	//---[Parse Color-Palette]----------
	if (ColorPaletteChunkSize > 0)
	{
		byteSteam.CurrentPosition += ColorPaletteChunkSize;
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

	//---[ Extension Area ]--------------------------------------------------------
	unsigned short extensionSize = byteSteam.ExtractShortAndMove(EndianType::Little);

	return;

	if (extensionSize != 495u)
	{
		throw "Inavlid ExtensionSize";
	}

	byteSteam.CurrentPosition += extensionSize;
	//-----------------------------------------------------------	
}

void BF::TGA::Save(AsciiString& filePath)
{
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