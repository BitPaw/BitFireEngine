#include "BMP.h"

#include "../../File/File.h"
#include <cassert>
#include "../../Math/Math.h"

BF::BMP::BMP()
{
    Type = BMPType::UnkownOrInavlid;
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

    //---[ Parsing Header ]----------------------------------------------------
    {
        unsigned char type[2];
        unsigned int sizeOfFile = 0;
        unsigned int reservedBlock = 0;
        unsigned int dataOffset = 0;

        file.Read(type, 2u);
        file.Read(sizeOfFile, Endian::Little);
        file.Read(reservedBlock, Endian::Little);
        file.Read(dataOffset, Endian::Little);

        Type = ConvertBMPType(type);
    }
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

    PixelDataSize = InfoHeader.Width * InfoHeader.Height * (InfoHeader.NumberOfBitsPerPixel / 8);
    PixelData = (unsigned char*)malloc(PixelDataSize * sizeof(unsigned char));


    //---[ Pixel Data ]--------------------------------------------------------    
    unsigned int dataRowSize = InfoHeader.Width * (InfoHeader.NumberOfBitsPerPixel / 8);
    unsigned int fullRowSize = Math::Floor((InfoHeader.NumberOfBitsPerPixel * InfoHeader.Width + 31) / 32.0f) * 4;
    unsigned int padding = Math::Absolute((int)fullRowSize - (int)dataRowSize);
    unsigned int amountOfRows = PixelDataSize / fullRowSize;
    size_t pixelDataOffset = 0;

    while (amountOfRows-- > 0)
    {
        assert(pixelDataOffset <= PixelDataSize);

        file.Read(PixelData + pixelDataOffset, dataRowSize);

        pixelDataOffset += dataRowSize;
        file.DataCursorPosition += padding; // Move data, row + padding(padding can be 0)
    }

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::BMP::Save(const char* filePath)
{
    unsigned int fileSize = InfoHeader.Width * InfoHeader.Height * 3 + 54u;
    File file(filePath, fileSize);
 
    file.Write("BM", 2u);
    file.Write(fileSize, Endian::Little);
    file.Write(0u, Endian::Little);
    file.Write(54u, Endian::Little);

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

    InfoHeader.Width = image.Width;
    InfoHeader.Height = image.Height;
    InfoHeader.ImageSize = PixelDataSize;

    memcpy(PixelData, image.PixelData, PixelDataSize);

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::BMP::ConvertTo(Image& image)
{    
    void* pixelData = malloc(PixelDataSize);

    if (!pixelData)
    {
        return ResourceLoadingResult::OutOfMemory;
    }

    image.Format = ImageDataFormat::BGR;
    image.Height = InfoHeader.Height;
    image.Width = InfoHeader.Width;
    image.PixelDataSize = PixelDataSize;
    image.PixelData = (unsigned char*)pixelData;

    memcpy(image.PixelData, PixelData, image.PixelDataSize);

    image.FlipHorizontal();
    //image.RemoveColor(0,0,0);

    return ResourceLoadingResult::Successful;
}