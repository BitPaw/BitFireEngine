#include "JPEG.h"

#include "JPEGMarker.h"
#include "JPEGFrame.h"

#include <cassert>
#include <stdlib.h>

#include <File/File.h>
#include <Hardware/Memory/Memory.h>

BF::JPEG::JPEG()
{
    HuffmanTableSize = 0;
    HuffmanTable = 0;
    CompressedImageDataSize = 0;
    CompressedImageData = 0;
}

BF::FileActionResult BF::JPEG::Load(const char* filePath)
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

BF::FileActionResult BF::JPEG::Load(const wchar_t* filePath)
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

BF::FileActionResult BF::JPEG::Load(const unsigned char* fileData, const size_t fileDataSize)
{
    ByteStream dataStream(fileData, fileDataSize);

    // Check Start of Image
    {
        unsigned char startBlock[2];

        dataStream.Read(startBlock, 2u);

        const JPEGMarker marker = ConvertJPEGMarker(startBlock);
        const bool validStart = marker == JPEGMarker::StartOfImage;

        if(!validStart)
        {
            return FileActionResult::InvalidHeaderSignature;
        }
    }

    while(!dataStream.IsAtEnd())
    {
        unsigned char markerData[2];     

        dataStream.Read(markerData, 2u);

        const JPEGMarker marker = ConvertJPEGMarker(markerData);

        switch(marker)
        {
            default:
            case BF::JPEGMarker::MarkerInvalid:
            {
                unsigned short length = 0;

                dataStream.Read(length, EndianBig);

                dataStream.DataCursor += length - 2;

                break;
            }

            case BF::JPEGMarker::EndOfImage:
            {
                return FileActionResult::Successful;
            }

            case BF::JPEGMarker::StartOfImage:
            {
                // We read the start tag already. Reading it again is not valid.
                return FileActionResult::FormatNotAsExpected;
            }

            case BF::JPEGMarker::StartOfFrame:
            {
                unsigned short length = 0;
                JPEGFrame frame;

                dataStream.Read(length, EndianBig);
                dataStream.Read(frame.Precusion, EndianLittle);
                dataStream.Read(frame.LineNb, EndianLittle);
                dataStream.Read(frame.LineSamples);
                dataStream.Read(frame.ComponentListSize);

                for(size_t i = 0; i < frame.ComponentListSize; ++i)
                {
                    JPEGFrameComponent& frameComponent = frame.ComponentList[i];
                    unsigned char size = 0;

                    dataStream.Read(frameComponent.ID);
                    dataStream.Read(size);
                    dataStream.Read(frameComponent.Key);

                    frameComponent.Width = (unsigned char)((size & 0b11110000) >> 4u);
                    frameComponent.Height = (unsigned char)(size & 0b00001111);
                }

                break;
            }

            case BF::JPEGMarker::DefineQuantizationTable:
            {
                unsigned short length = 0;
                unsigned char chrominance = 0;
                unsigned char buffer[64];

                dataStream.Read(length, EndianBig);
                dataStream.Read(chrominance);

                dataStream.Read(buffer, 64);

                break;
            }

            case BF::JPEGMarker::DefineHuffmanTable:
            {
                unsigned short length = 0;
                JPEGHuffmanTable jpegHuffmanTable;

                dataStream.Read(length, EndianBig);
                dataStream.Read(jpegHuffmanTable.Class);
                dataStream.Read(jpegHuffmanTable.Destination);

                dataStream.DataCursor += (length - 2) - 2;

                break;
            }

            case BF::JPEGMarker::StartOfScan:
            {
                unsigned short length = 0;
                dataStream.Read(length, EndianBig);
                dataStream.Read(ScanStart.ScanSelectorSize);

                for(size_t i = 0; i < ScanStart.ScanSelectorSize; i++)
                {
                    JPEGScanSelector& scanSelector = ScanStart.ScanSelector[i];
                    unsigned char dcacTable = 0;

                    dataStream.Read(scanSelector.Selector);
                    dataStream.Read(dcacTable);

                    scanSelector.DC = (unsigned char)((dcacTable & 0b11110000) >> 4u);
                    scanSelector.ACTable = (unsigned char)(dcacTable & 0b00001111);
                }

                dataStream.Read(ScanStart.SpectralSelectFrom);
                dataStream.Read(ScanStart.SpectralSelectTo);
                dataStream.Read(ScanStart.SuccessiveAproximation);

                CompressedImageDataSize = dataStream.DataSize - dataStream.DataCursor - 2;
                CompressedImageData = Memory::Allocate<unsigned char>(CompressedImageDataSize);

                dataStream.Read(CompressedImageData, CompressedImageDataSize);

                break;
            }
            case BF::JPEGMarker::HeaderFileInfo:
            {
                dataStream.Read(FileInfo.Length, EndianLittle);
                dataStream.Read(FileInfo.Identifier, 5u);
                dataStream.Read(FileInfo.VersionMajor);
                dataStream.Read(FileInfo.VersionMinor);
                dataStream.Read(FileInfo.DensityUnits);
                dataStream.Read(FileInfo.DensityX, EndianLittle);
                dataStream.Read(FileInfo.DensityY, EndianLittle);
                dataStream.Read(FileInfo.ThumbnailX);
                dataStream.Read(FileInfo.ThumbnailY);

                if(FileInfo.ThumbnailX > 0 && FileInfo.ThumbnailY > 0)
                {
                    FileInfo.ThumbnailDataSize = FileInfo.ThumbnailX * FileInfo.ThumbnailY * 3u;
                    FileInfo.ThumbnailData = Memory::Allocate<unsigned char>(FileInfo.ThumbnailDataSize);

                    dataStream.Read(FileInfo.ThumbnailData, FileInfo.ThumbnailDataSize);
                }

                break;
            }
        }
    }
}

BF::FileActionResult BF::JPEG::Save(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::JPEG::~JPEG()
{
    MemoryRelease(CompressedImageData, CompressedImageDataSize);
}

BF::FileActionResult BF::JPEG::ConvertTo(Image& image)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::JPEG::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}
