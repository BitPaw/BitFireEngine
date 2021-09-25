#include "BMP.h"

#include "../../File/File.h"

BF::BMP::BMP()
{
    Type = BMPType::UnkownOrInavlid;
    SizeOfFile = -1;
    ReservedBlock = 0;
    DataOffset = -1;

	InfoHeaderType = BMPInfoHeaderType::UnkownOrInvalid;

    PixelDataSize = 0;
    PixelData = 0;
}

BF::BMP::~BMP()
{
    free(PixelData);	
}

BF::ResourceLoadingResult BF::BMP::Load(const char* filePath)
{
    File file(filePath); 
    ResourceLoadingResult resourceLoadingResult = file.ReadFromDisk();

    if (resourceLoadingResult != ResourceLoadingResult::Successful)
    {
        return resourceLoadingResult;
    }

    //-- Parsing Header Tag
    {
        unsigned char type[2];

        file.Read(type, 2u);

        Type = ConvertBMPType(type);
    }

    //---[ Parsing Header ]----------------------------------------------------
    file.Read(SizeOfFile, Endian::Little);
    file.Read(ReservedBlock, Endian::Little);
    file.Read(DataOffset, Endian::Little);
    //-------------------------------------------------------------------------

    //---[ DIP ]---------------------------------------------------------------    
    {
        file.Read(InfoHeader.HeaderSize, Endian::Little);

        InfoHeaderType = ConvertBMPInfoHeaderType(InfoHeader.HeaderSize);

        switch (InfoHeaderType)
        {
            case BMPInfoHeaderType::BitMapInfoHeader:
            {
                file.Read(InfoHeader.Width, Endian::Little);
                file.Read(InfoHeader.Height, Endian::Little);
                file.Read(InfoHeader.NumberOfColorPlanes, Endian::Little);
                file.Read(InfoHeader.NumberOfBitsPerPixel, Endian::Little);
                file.Read(InfoHeader.CompressionMethod, Endian::Little);
                file.Read(InfoHeader.ImageSize, Endian::Little);
                file.Read(InfoHeader.HorizontalResolution, Endian::Little);
                file.Read(InfoHeader.VerticalResolution, Endian::Little);
                file.Read(InfoHeader.NumberOfColorsInTheColorPalette, Endian::Little);
                file.Read(InfoHeader.NumberOfImportantColorsUsed, Endian::Little);

                break;
            }

            case BMPInfoHeaderType::OS21XBitMapHeader:
            case BMPInfoHeaderType::OS22XBitMapHeader:
            {
                file.Read((unsigned short&)InfoHeader.Width, Endian::Little);
                file.Read((unsigned short&)InfoHeader.Height, Endian::Little);
                file.Read(InfoHeader.NumberOfColorPlanes, Endian::Little);
                file.Read(InfoHeader.NumberOfBitsPerPixel, Endian::Little);

                if (InfoHeaderType == BMPInfoHeaderType::OS22XBitMapHeader)
                {               
                    unsigned short paddingBytes = 0; // Padding.Ignored and should be zero                    

                    file.Read(InfoHeader.HorizontalandVerticalResolutions, Endian::Little);
                    file.Read(paddingBytes, Endian::Little);
                    file.Read(InfoHeader.DirectionOfBits, Endian::Little);
                    file.Read(InfoHeader.halftoningAlgorithm, Endian::Little);

                    file.Read(InfoHeader.HalftoningParameterA, Endian::Little);
                    file.Read(InfoHeader.HalftoningParameterB, Endian::Little);
                    file.Read(InfoHeader.ColorEncoding, Endian::Little);
                    file.Read(InfoHeader.ApplicationDefinedByte, Endian::Little);
                }    

                break;
            }
            default:
            {
                // Unkown Header 
                return ResourceLoadingResult::FormatNotSupported;
            }
        }
    }    
    //-----------------------------------------------------------    

    //---[ Pixel Data ]--------------------------------------------------------  
    unsigned int bytesPerPixel = (InfoHeader.NumberOfBitsPerPixel / 8);
    unsigned int pixelDataRowSize = InfoHeader.Width * bytesPerPixel;
    PixelDataSize = pixelDataRowSize * InfoHeader.Height;

    unsigned int paddingSize = pixelDataRowSize % 4;
    unsigned int rowSize = pixelDataRowSize + paddingSize;

    PixelData = (unsigned char*)malloc(PixelDataSize * sizeof(unsigned char));
   
    for (size_t pixelDataOffset = 0 ; file.DataCursorPosition < file.DataSize ; )
    {
        file.Read(PixelData + pixelDataOffset, pixelDataRowSize);

        pixelDataOffset += pixelDataRowSize;
        file.DataCursorPosition += paddingSize; // Move data, row + padding(padding can be 0)
    }
}

BF::ResourceLoadingResult BF::BMP::Save(const char* filePath)
{
    File file(filePath, SizeOfFile);
 
    file.Write("BM", 2u);
    file.Write(SizeOfFile, Endian::Little);
    file.Write(ReservedBlock, Endian::Little);
    file.Write(DataOffset, Endian::Little);

    //------<Windows-Header>-----------
    file.Write(InfoHeader.HeaderSize, Endian::Little);
    file.Write(InfoHeader.Width, Endian::Little);
    file.Write(InfoHeader.Height, Endian::Little);
    file.Write(InfoHeader.NumberOfColorPlanes, Endian::Little);
    file.Write(InfoHeader.NumberOfBitsPerPixel, Endian::Little);
    file.Write(InfoHeader.CompressionMethod, Endian::Little);
    file.Write(InfoHeader.ImageSize, Endian::Little);
    file.Write(InfoHeader.HorizontalResolution, Endian::Little);
    file.Write(InfoHeader.VerticalResolution, Endian::Little);
    file.Write(InfoHeader.NumberOfColorsInTheColorPalette, Endian::Little);
    file.Write(InfoHeader.NumberOfImportantColorsUsed, Endian::Little);

    file.Write(PixelData, PixelDataSize);

    file.WriteToDisk();

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::BMP::ConvertFrom(Image& image)
{
    PixelData = (unsigned char*)malloc(image.PixelDataSize);

    if (!PixelData)
    {
        return ResourceLoadingResult::OutOfMemory;
    }

    PixelDataSize = image.PixelDataSize;

    DataOffset = 54u;
    unsigned int padding = 0;
    unsigned int imageSize = PixelDataSize + padding; 

    SizeOfFile = imageSize + DataOffset;

    InfoHeader.Width = image.Width;
    InfoHeader.Height = image.Height;
    InfoHeader.ImageSize = imageSize;

    memcpy(PixelData, image.PixelData, PixelDataSize);

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::BMP::ConvertTo(Image& image)
{    
    size_t pixelDataSize = InfoHeader.Height * InfoHeader.Width * 3;
    void* pixelData = malloc(PixelDataSize);

    if (!pixelData)
    {
        return ResourceLoadingResult::OutOfMemory;
    }

    image.Format = ImageFormat::BGR;
    image.Height = InfoHeader.Height;
    image.Width = InfoHeader.Width;
    image.PixelDataSize = pixelDataSize;
    image.PixelData = (unsigned char*)pixelData;

    memcpy(image.PixelData, PixelData, image.PixelDataSize);

    image.FlipHorizontal();
    //image.RemoveColor(0,0,0);

    return ResourceLoadingResult::Successful;
}