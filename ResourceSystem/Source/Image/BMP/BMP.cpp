#include "BMP.h"

#include "../../File/File.h"
#include "../../Container/AsciiString.h"
#include "../../Container/ByteStreamHusk.h"

BF::BMP::BMP()
{
	InformationHeaderType = BMPInformationHeaderType::UnkownOrInvalid;
	InformationHeader = nullptr;
}

BF::BMP::~BMP()
{
	if (InformationHeader != nullptr)
	{
		delete InformationHeader;
	}
}

/*
BF::RGB<unsigned char>* BF::BMP::GetPixel(unsigned int x, unsigned int y)
{
	int width = InformationHeader->Width;
	int height = InformationHeader->Height;
	unsigned int index;
	RGB<unsigned char>* rgb;

	bool flipY = false; // flipüx
	bool flipX = false;

	if (flipX)
	{
		x = width - 1 - x;
	}

	if (flipY)
	{
		y = height - 1 - y;
	}

	index = x * width + y;

	// printf("%u | %u = %u\n", x,y, index);

	rgb = &Pixel[index];

	return rgb;
}*/

void BF::BMP::Load(const char* filePath)
{
    File file(filePath);
    file.Read();
    ByteStreamHusk byteStream((unsigned char*)file.Data, file.Size);
    int bitsPerPixel = 0; 

    //-- Parsing Header Tag
    {
        Word headerTag;

        headerTag.ByteData[0] = byteStream.ExtractByteAndMove();
        headerTag.ByteData[1] = byteStream.ExtractByteAndMove();

        switch (headerTag.ByteData[0])
        {
            case 'B':
                switch (headerTag.ByteData[1])
                {
                    case 'A':
                        Type = BMPType::OS2StructBitmapArray;
                        break;

                    case 'M':
                        Type = BMPType::Windows;
                        break;
                }
                break;

            case 'C':
                switch (headerTag.ByteData[1])
                {
                    case 'I':
                        Type = BMPType::OS2StructColorIcon;
                        break;

                    case 'P':
                        Type = BMPType::OS2ConstColorPointer;
                        break;
                }
                break;

            case 'I':
                if ('C' == headerTag.ByteData[1])
                {
                    Type = BMPType::OS2StructIcon;
                }
                break;

            case 'P':
                if ('C' == headerTag.ByteData[1])
                {
                    Type = BMPType::OS2Pointer;
                }
                break;
            default:
                Type = BMPType::UnkownOrInavlid;
                break;
        }
    }

    //---[ Parsing Header ]----------------------------------------------------
    SizeOfFile = byteStream.ExtractIntegerAndMove(Endian::Little);
    ReservedBlock = byteStream.ExtractIntegerAndMove(Endian::Little);
    DataOffset = byteStream.ExtractIntegerAndMove(Endian::Little);
    //-------------------------------------------------------------------------

    //---[ DIP ]---------------------------------------------------------------
    unsigned char result = byteStream.ExtractIntegerAndMove(Endian::Little);

    // Get Header Version
    {

        //const unsigned char bitMapCoreHeaderSize = 12;
        //const unsigned char os21XBitMapHeaderSize = 12;
        //const unsigned char os22XBitMapHeaderSizeTypeA = 16;
        //const unsigned char os22XBitMapHeaderSizeTypeB = 16;
        const unsigned char bitMapInfoHeaderSize = 40;
        const unsigned char bitMapV2InfoHeaderSize = 52;
        const unsigned char bitMapV3InfoHeaderSize = 56;
        const unsigned char bitMapV4HeaderSize = 108;
        const unsigned char bitMapV5HeaderSize = 124;

        switch (result)
        {
            case 12:
                //type = BitMapInformationHeaderType::BitMapV5Header;
                break;

            case 16:
                //type = BitMapInformationHeaderType::BitMapV5Header;
                break;

            case bitMapInfoHeaderSize:
                InformationHeaderType = BMPInformationHeaderType::BitMapInfoHeader;
                break;

            case bitMapV2InfoHeaderSize:
                InformationHeaderType = BMPInformationHeaderType::BitMapV2InfoHeader;
                break;

            case bitMapV3InfoHeaderSize:
                InformationHeaderType = BMPInformationHeaderType::BitMapV3InfoHeader;
                break;

            case bitMapV4HeaderSize:
                InformationHeaderType = BMPInformationHeaderType::BitMapV4Header;
                break;

            case bitMapV5HeaderSize:
                InformationHeaderType = BMPInformationHeaderType::BitMapV5Header;
                break;

            default:
                InformationHeaderType = BMPInformationHeaderType::UnkownOrInvalid;
                break;
        }

    }

    switch (InformationHeaderType)
    {
        case BMPInformationHeaderType::BitMapInfoHeader:
        {
            BMPInfoHeader* bitMapInfoHeader = new BMPInfoHeader();

            bitMapInfoHeader->HeaderSize = result;
            bitMapInfoHeader->Width = byteStream.ExtractIntegerAndMove(Endian::Little);
            bitMapInfoHeader->Height = byteStream.ExtractIntegerAndMove(Endian::Little);
            bitMapInfoHeader->NumberOfColorPlanes = byteStream.ExtractShortAndMove(Endian::Little);
            bitMapInfoHeader->NumberOfBitsPerPixel = byteStream.ExtractShortAndMove(Endian::Little);
            bitMapInfoHeader->CompressionMethod = byteStream.ExtractIntegerAndMove(Endian::Little);
            bitMapInfoHeader->ImageSize = byteStream.ExtractIntegerAndMove(Endian::Little);
            bitMapInfoHeader->HorizontalResolution = byteStream.ExtractIntegerAndMove(Endian::Little);
            bitMapInfoHeader->VerticalResolution = byteStream.ExtractIntegerAndMove(Endian::Little);
            bitMapInfoHeader->NumberOfColorsInTheColorPalette = byteStream.ExtractIntegerAndMove(Endian::Little);
            bitMapInfoHeader->NumberOfImportantColorsUsed = byteStream.ExtractIntegerAndMove(Endian::Little);

            InformationHeader = bitMapInfoHeader;


            // Copy Data (Make a bit redundant data)
            Width = bitMapInfoHeader->Width;
            Height = bitMapInfoHeader->Height;

            bitsPerPixel = bitMapInfoHeader->NumberOfBitsPerPixel;
        }

        break;
    }
    //-----------------------------------------------------------    

    //---[ Pixel Data ]--------------------------------------------------------    
    unsigned int pixelIndex = 0;
    unsigned int length = byteStream.DataLength;
    unsigned int bytesPerPixel = (bitsPerPixel / 8);
    unsigned int pixelDataRowSize = Width * bytesPerPixel;
    unsigned int pixelDataSize = pixelDataRowSize * Height;

    unsigned int paddingSize = pixelDataRowSize % 4;
    unsigned int rowSize = pixelDataRowSize + paddingSize;
    unsigned int rowIndex = 0;

    PixelData.ReSize(pixelDataSize);

    while (!byteStream.IsAtEnd())
    {
        bool isPixelData = rowIndex < pixelDataRowSize;

        if (isPixelData)
        {
            unsigned char blue = byteStream.ExtractByteAndMove();
            unsigned char green = byteStream.ExtractByteAndMove();
            unsigned char red = byteStream.ExtractByteAndMove();

            rowIndex += 3;

            PixelData[pixelIndex++] = red;
            PixelData[pixelIndex++] = green;
            PixelData[pixelIndex++] = blue;
        }
        else
        {
            byteStream.CurrentPosition += paddingSize;
            rowIndex = 0;        
        }
    }
}

void BF::BMP::Save(const char* filePath)
{
}

void BF::BMP::Convert(Image& image)
{
    unsigned int pixelDataSize = PixelData.Size();
    unsigned char* destination = nullptr;
    unsigned char* source = &PixelData[0];    
  
    image.Format = ImageFormat::RGB;
    image.Height = Height;
    image.Width = Width;    
    image.PixelDataSize = Height * Width * 3;
    image.PixelData = (unsigned char*)malloc(image.PixelDataSize);

    memcpy(image.PixelData, source, image.PixelDataSize);

    //image.FlipHorizontal();
    //image.RemoveColor(0,0,0);
}

void BF::BMP::PrintContent()
{
    printf("[BitMap] (.bmp)");
    printf("Type      : %u\n", Type);
    //printf("SizeOfFile: %i\n", bitMap.Header.SizeOfFile);
   // printf("Unsued    : %i\n", bitMap.Header.ActualSizeOfFile);
   // printf("DataOffset: %i\n", bitMap.Header.DataOffset);

    switch (InformationHeaderType)
    {
        case BMPInformationHeaderType::BitMapInfoHeader:

            BMPInfoHeader* bitMapInfoHeader = (BMPInfoHeader*)(InformationHeader);

            printf("Size : %u\n", bitMapInfoHeader->HeaderSize);
            printf("Width : %i\n", bitMapInfoHeader->Width);
            printf("Height : %i\n", bitMapInfoHeader->Height);
            printf("NumberOfColorPlanes : %u\n", bitMapInfoHeader->NumberOfColorPlanes);
            printf("NumberOfBitsPerPixel : %u\n", bitMapInfoHeader->NumberOfBitsPerPixel);
            printf("CompressionMethod : %u\n", bitMapInfoHeader->CompressionMethod);
            printf("ImageSize : %u\n", bitMapInfoHeader->ImageSize);
            printf("HorizontalResolution : %i\n", bitMapInfoHeader->HorizontalResolution);
            printf("VerticalResolution : %i\n", bitMapInfoHeader->VerticalResolution);
            printf("NumberOfColorsInTheColorPalette : %u\n", bitMapInfoHeader->NumberOfColorsInTheColorPalette);
            printf("NumberOfImportantColorsUsed : %u\n", bitMapInfoHeader->NumberOfImportantColorsUsed);

            break;
    }
}