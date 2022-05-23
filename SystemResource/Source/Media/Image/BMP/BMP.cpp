#include "BMP.h"

#include <cassert>

#include <File/File.h>
#include <Math/Math.h>

#include <string>
#include <Hardware/Memory/Memory.h>

BF::BMP::BMP()
{
    Type = BMPType::Invalid;
	InfoHeaderType = BMPInfoHeaderType::UnkownOrInvalid;

    PixelDataSize = 0;
    PixelData = 0;
}

BF::BMP::~BMP()
{
    Memory::Release(PixelData, PixelDataSize);
}

BF::FileActionResult BF::BMP::Load(const wchar_t* filePath)
{
    File file; 

    {
        const FileActionResult loadingResult = file.MapToVirtualMemory(filePath);
        const bool success = loadingResult != FileActionResult::Successful;

        if(success)
        {
            return loadingResult;
        }
    }

    //---[ Parsing Header ]----------------------------------------------------
    {
        ByteCluster byteCluster;
        unsigned int sizeOfFile = 0;
        unsigned int reservedBlock = 0;
        unsigned int dataOffset = 0;

        file.Read(byteCluster.Data, 2u);
        file.Read(sizeOfFile, Endian::Little);
        file.Read(reservedBlock, Endian::Little);
        file.Read(dataOffset, Endian::Little);

        Type = ConvertBMPType(byteCluster);

        {
            const bool isValidType = Type != BMPType::Invalid;

            if(!isValidType)
            {
                return FileActionResult::InvalidHeaderSignature;
            }
        }   
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
                return FileActionResult::FormatNotSupported;
            }
        }
    }    
    //-----------------------------------------------------------    

    PixelDataSize = InfoHeader.Width * InfoHeader.Height * (InfoHeader.NumberOfBitsPerPixel / 8);

    PixelData = Memory::Allocate<Byte>(PixelDataSize);

    //---[ Pixel Data ]--------------------------------------------------------    
    const size_t dataRowSize = InfoHeader.Width * (InfoHeader.NumberOfBitsPerPixel / 8);
    const size_t fullRowSize = Math::Floor((InfoHeader.NumberOfBitsPerPixel * InfoHeader.Width + 31) / 32.0f) * 4;
    const size_t padding = Math::Absolute((int)fullRowSize - (int)dataRowSize);
    size_t amountOfRows = PixelDataSize / fullRowSize;
    size_t pixelDataOffset = 0;

    while (amountOfRows-- > 0)
    {
        assert(pixelDataOffset <= PixelDataSize);

        file.Read(PixelData + pixelDataOffset, dataRowSize);

        pixelDataOffset += dataRowSize;
        file.DataCursorPosition += padding; // Move data, row + padding(padding can be 0)
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BMP::Save(const wchar_t* filePath)
{
    unsigned int fileSize = InfoHeader.Width * InfoHeader.Height * 3 + 54u;
    File file;// (fileSize);
 
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

    file.WriteToDisk(filePath);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BMP::ConvertFrom(Image& image)
{
    PixelData = Memory::Allocate<unsigned char>(image.PixelDataSize);

    if (!PixelData)
    {
        return FileActionResult::OutOfMemory;
    }

    PixelDataSize = image.PixelDataSize;

    InfoHeader.Width = image.Width;
    InfoHeader.Height = image.Height;
    InfoHeader.ImageSize = PixelDataSize;

    Memory::Copy(PixelData, image.PixelData, PixelDataSize);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BMP::ConvertTo(Image& image)
{    
    unsigned char* pixelData = Memory::Allocate<unsigned char>(PixelDataSize);

    if (!pixelData)
    {
        return FileActionResult::OutOfMemory;
    }

    image.Format = ImageDataFormat::BGR;
    image.Height = InfoHeader.Height;
    image.Width = InfoHeader.Width;
    image.PixelDataSize = PixelDataSize;
    image.PixelData = pixelData;

    Memory::Copy(image.PixelData, PixelData, image.PixelDataSize);

    //image.FlipHorizontal(); ??
    
    //image.RemoveColor(0,0,0);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BMP::ConvertTo(Image& image, BMP& alphaMap)
{
    size_t pixelDataSize = (PixelDataSize / 3) * 4;
    unsigned char* pixelData = Memory::Allocate<unsigned char>(pixelDataSize);

    if (!pixelData)
    {
        return FileActionResult::OutOfMemory;
    }

    image.Format = ImageDataFormat::BGRA;
    image.Height = InfoHeader.Height;
    image.Width = InfoHeader.Width;
    image.PixelDataSize = pixelDataSize;
    image.PixelData = pixelData;

    size_t imageDataIndex = 0;
    size_t alphaDataIndex = 0;

    for (size_t i = 0; i < pixelDataSize; )
    {
        unsigned char blue = PixelData[imageDataIndex++];
        unsigned char green = PixelData[imageDataIndex++];
        unsigned char red = PixelData[imageDataIndex++];
        unsigned char alpha = alphaMap.PixelData[alphaDataIndex++];
        bool isTansparanetColor = blue == 0xFF && green == 0xFF && red == 0xFF;

        pixelData[i++] = blue;
        pixelData[i++] = green;
        pixelData[i++] = red;
        pixelData[i++] = isTansparanetColor ? 0x00 : 0xFF;
    }

    image.FlipHorizontal();

    return FileActionResult::Successful;
}
