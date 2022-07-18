#include "BMP.h"

#include <cassert>

#include <File/File.h>
#include <Math/Math.h>

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
    MemoryRelease(PixelData, PixelDataSize);
}

BF::FileActionResult BF::BMP::Load(const char* filePath)
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

BF::FileActionResult BF::BMP::Load(const wchar_t* filePath)
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

BF::FileActionResult BF::BMP::Load(const unsigned char* fileData, const size_t fileDataSize)
{
    ByteStream dataStream(fileData, fileDataSize);

    //---[ Parsing Header ]----------------------------------------------------
    {
        ClusterInt byteCluster;
        unsigned int sizeOfFile = 0;
        unsigned int reservedBlock = 0;
        unsigned int dataOffset = 0;

        dataStream.Read(byteCluster.Data, 2u);
        dataStream.Read(sizeOfFile, EndianLittle);
        dataStream.Read(reservedBlock, EndianLittle);
        dataStream.Read(dataOffset, EndianLittle);

        Type = ConvertBMPType(byteCluster.Value);

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
        dataStream.Read(InfoHeader.HeaderSize, EndianLittle);

        InfoHeaderType = ConvertBMPInfoHeaderType(InfoHeader.HeaderSize);

        switch(InfoHeaderType)
        {
            case BMPInfoHeaderType::BitMapInfoHeader:
            {
                dataStream.Read(InfoHeader.Width, EndianLittle);
                dataStream.Read(InfoHeader.Height, EndianLittle);
                dataStream.Read(InfoHeader.NumberOfColorPlanes, EndianLittle);
                dataStream.Read(InfoHeader.NumberOfBitsPerPixel, EndianLittle);
                dataStream.Read(InfoHeader.CompressionMethod, EndianLittle);
                dataStream.Read(InfoHeader.ImageSize, EndianLittle);
                dataStream.Read(InfoHeader.HorizontalResolution, EndianLittle);
                dataStream.Read(InfoHeader.VerticalResolution, EndianLittle);
                dataStream.Read(InfoHeader.NumberOfColorsInTheColorPalette, EndianLittle);
                dataStream.Read(InfoHeader.NumberOfImportantColorsUsed, EndianLittle);

                break;
            }
            case BMPInfoHeaderType::OS21XBitMapHeader:
            case BMPInfoHeaderType::OS22XBitMapHeader:
            {
                dataStream.Read((unsigned short&)InfoHeader.Width, EndianLittle);
                dataStream.Read((unsigned short&)InfoHeader.Height, EndianLittle);
                dataStream.Read(InfoHeader.NumberOfColorPlanes, EndianLittle);
                dataStream.Read(InfoHeader.NumberOfBitsPerPixel, EndianLittle);

                if(InfoHeaderType == BMPInfoHeaderType::OS22XBitMapHeader)
                {
                    unsigned short paddingBytes = 0; // Padding.Ignored and should be zero

                    dataStream.Read(InfoHeader.HorizontalandVerticalResolutions, EndianLittle);
                    dataStream.Read(paddingBytes, EndianLittle);
                    dataStream.Read(InfoHeader.DirectionOfBits, EndianLittle);
                    dataStream.Read(InfoHeader.halftoningAlgorithm, EndianLittle);

                    dataStream.Read(InfoHeader.HalftoningParameterA, EndianLittle);
                    dataStream.Read(InfoHeader.HalftoningParameterB, EndianLittle);
                    dataStream.Read(InfoHeader.ColorEncoding, EndianLittle);
                    dataStream.Read(InfoHeader.ApplicationDefinedByte, EndianLittle);
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

    PixelData = Memory::Allocate<Byte__>(PixelDataSize);

    //---[ Pixel Data ]--------------------------------------------------------
    const size_t dataRowSize = InfoHeader.Width * (InfoHeader.NumberOfBitsPerPixel / 8);
    const size_t fullRowSize = MathFloor((InfoHeader.NumberOfBitsPerPixel * InfoHeader.Width + 31) / 32.0f) * 4;
    const int paddingSUM = (int)fullRowSize - (int)dataRowSize;
    const size_t padding = MathAbsolute(paddingSUM);
    size_t amountOfRows = PixelDataSize / fullRowSize;
    size_t pixelDataOffset = 0;

    while(amountOfRows-- > 0)
    {
        unsigned char* data = PixelData + pixelDataOffset;

        assert(pixelDataOffset <= PixelDataSize);

        dataStream.Read(data, dataRowSize);

        pixelDataOffset += dataRowSize;
        dataStream.DataCursor += padding; // Move data, row + padding(padding can be 0)
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BMP::Save(const wchar_t* filePath)
{
    File file;

    // Open file
    {
        const FileActionResult openResult = file.Open(filePath, FileOpenMode::Write);
        const bool sucessful = openResult == FileActionResult::Successful;

        if(!sucessful)
        {
            return openResult;
        }
    }

    // Write header
    {
        unsigned int fileSize = InfoHeader.Width * InfoHeader.Height * 3 + 54u;

        file.Write("BM", 2u);
        file.Write(fileSize, EndianLittle);
        file.Write(0u, EndianLittle);
        file.Write(54u, EndianLittle);
    }

    //------<Windows-Header>-----------
    file.Write(InfoHeader.HeaderSize, EndianLittle);
    file.Write(InfoHeader.Width, EndianLittle);
    file.Write(InfoHeader.Height, EndianLittle);
    file.Write(InfoHeader.NumberOfColorPlanes, EndianLittle);
    file.Write(InfoHeader.NumberOfBitsPerPixel, EndianLittle);
    file.Write(InfoHeader.CompressionMethod, EndianLittle);
    file.Write(InfoHeader.ImageSize, EndianLittle);
    file.Write(InfoHeader.HorizontalResolution, EndianLittle);
    file.Write(InfoHeader.VerticalResolution, EndianLittle);
    file.Write(InfoHeader.NumberOfColorsInTheColorPalette, EndianLittle);
    file.Write(InfoHeader.NumberOfImportantColorsUsed, EndianLittle);

    file.Write(PixelData, PixelDataSize);

    // Close file
    {
        const FileActionResult closeResult = file.Close();
        const bool sucessful = closeResult == FileActionResult::Successful;

        if(!sucessful)
        {
            return closeResult;
        }
    }

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

    MemoryCopy(PixelData, PixelDataSize, image.PixelData, image.PixelDataSize);

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

    MemoryCopy(PixelData, PixelDataSize, image.PixelData, image.PixelDataSize);

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
