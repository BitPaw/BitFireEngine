#include "BMP.h"

#include "../../../Utility/Word.h"
#include "../../../Utility/DoubleWord.h"
#include "../../../Utility/ByteStreamHusk.h"
#include "../../File/File.h"

BF::BMP::BMP()
{
	InformationHeaderType = BMPInformationHeaderType::UnkownOrInvalid;
	InformationHeader = nullptr;
}

BF::BMP::~BMP()
{
	if (InformationHeader != nullptr)
	{
		//delete InformationHeader;
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

void BF::BMP::Load(AsciiString& filePath)
{
    File file(filePath);
    file.Read();
    ByteStreamHusk byteStream((unsigned char*)&file.Data[0], file.Data.Size());
    int dip = 0; 

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
    SizeOfFile = byteStream.ExtractIntegerAndMove(EndianType::Little);
    ReservedBlock = byteStream.ExtractIntegerAndMove(EndianType::Little);
    DataOffset = byteStream.ExtractIntegerAndMove(EndianType::Little);
    //-------------------------------------------------------------------------

    //---[ DIP ]---------------------------------------------------------------
    unsigned char result = byteStream.ExtractIntegerAndMove(EndianType::Little);

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
            bitMapInfoHeader->Width = byteStream.ExtractIntegerAndMove(EndianType::Little);
            bitMapInfoHeader->Height = byteStream.ExtractIntegerAndMove(EndianType::Little);
            bitMapInfoHeader->NumberOfColorPlanes = byteStream.ExtractShortAndMove(EndianType::Little);
            bitMapInfoHeader->NumberOfBitsPerPixel = byteStream.ExtractShortAndMove(EndianType::Little);
            bitMapInfoHeader->CompressionMethod = byteStream.ExtractIntegerAndMove(EndianType::Little);
            bitMapInfoHeader->ImageSize = byteStream.ExtractIntegerAndMove(EndianType::Little);
            bitMapInfoHeader->HorizontalResolution = byteStream.ExtractIntegerAndMove(EndianType::Little);
            bitMapInfoHeader->VerticalResolution = byteStream.ExtractIntegerAndMove(EndianType::Little);
            bitMapInfoHeader->NumberOfColorsInTheColorPalette = byteStream.ExtractIntegerAndMove(EndianType::Little);
            bitMapInfoHeader->NumberOfImportantColorsUsed = byteStream.ExtractIntegerAndMove(EndianType::Little);

            InformationHeader = bitMapInfoHeader;


            // Copy Data (Make a bit redundant data)
            Width = bitMapInfoHeader->Width;
            Height = bitMapInfoHeader->Height;

            dip = bitMapInfoHeader->NumberOfBitsPerPixel;
        }

        break;
    }
    //-----------------------------------------------------------    

    //---[ Pixel Data ]--------------------------------------------------------    
    unsigned int pixelIndex = 0;
    unsigned int width = Width;
    unsigned int size = width * Height * 3;
    unsigned int length = byteStream.DataLength;
    unsigned int neededRows = Math::Ceiling((dip * width) / (32.0f)) * 4;
    unsigned int paddingSize = neededRows % 4; // <--  hardcoded
    unsigned int rowIndex = 0;
     const unsigned int rowWidth = width * 3;

    PixelData.ReSize(size);

    printf("Width=%i Rows size=%u padding=%u\n", width, neededRows, paddingSize);

    while (!byteStream.IsAtEnd())
    {
        bool ifPixelData = rowIndex < rowWidth;

        if (ifPixelData)
        {
            unsigned char blue = byteStream.ExtractByteAndMove();
            unsigned char green = byteStream.ExtractByteAndMove();
            unsigned char red = byteStream.ExtractByteAndMove();

            rowIndex += 3;

            PixelData[pixelIndex++] = red;
            PixelData[pixelIndex++] = green;
            PixelData[pixelIndex++] = blue;

            //printf("[Pixel][%05u/%05u] Pixel: ", rowIndex, size);
            //printf("%03u %03u %03u\n", red, green, blue);
        }
        else
        {
            for (unsigned int i = 0; i < paddingSize; i++)
            {
                rowIndex++;

                printf("[Pixel][%05u/%05u] Pixel: ", rowIndex, size);
            }

            rowIndex = 0;
        }
    }
}

void BF::BMP::Save(AsciiString& filePath)
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
    image.PixelData.ReSize(pixelDataSize);
    
    destination = &image.PixelData[0];
    
    memcpy(destination, source, pixelDataSize);
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