#include "JPEG.h"

#include "JPEGMarker.h"
#include "JPEGFrame.h"

#include <cassert>
#include <stdlib.h>

#include "../../File/FileStream.h"

BF::JPEG::JPEG()
{
    HuffmanTableSize = 0;
    HuffmanTable = 0;
    CompressedImageDataSize = 0;
    CompressedImageData = 0;
}

BF::FileActionResult BF::JPEG::Load(const char* filePath)
{
    FileStream file;
    FileActionResult FileActionResult = file.ReadFromDisk(filePath);

    if (FileActionResult != FileActionResult::Successful)
    {
        return FileActionResult;
    }

    // Check Start of Image
    {
        unsigned char startBlock[2];
        JPEGMarker marker = JPEGMarker::MarkerInvalid;
        bool validStart = false;

        file.Read(startBlock, 2u);

        marker = ConvertJPEGMarker(startBlock);
        validStart = marker == JPEGMarker::StartOfImage;

        if (!validStart)
        {
            return FileActionResult::FormatNotAsExpected;
        }
    }

    while (true)
    {
        unsigned char markerData[2];
        JPEGMarker marker = JPEGMarker::MarkerInvalid;

        file.Read(markerData, 2u);

        marker = ConvertJPEGMarker(markerData);

        switch (marker)
        {
            default:
            case BF::JPEGMarker::MarkerInvalid:
            {    
                unsigned short length = 0;

                file.Read(length, Endian::Big);

                file.DataCursorPosition += length - 2;

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

                file.Read(length, Endian::Big);
                file.Read(frame.Precusion, Endian::Little);
                file.Read(frame.LineNb, Endian::Little);
                file.Read(frame.LineSamples);
                file.Read(frame.ComponentListSize);
               
                for (size_t i = 0; i < frame.ComponentListSize; i++)
                {
                    JPEGFrameComponent& frameComponent = frame.ComponentList[i];
                    unsigned char size = 0;

                    file.Read(frameComponent.ID);
                    file.Read(size);
                    file.Read(frameComponent.Key);

                    frameComponent.Width = (size & 0b11110000) >> 4;
                    frameComponent.Height = size & 0b00001111;
                }

                break;
            }

            case BF::JPEGMarker::DefineQuantizationTable:
            {
                unsigned short length = 0;
                unsigned char chrominance = 0;
                unsigned char buffer[64];

                file.Read(length, Endian::Big);
                file.Read(chrominance);

                file.Read(buffer, 64);

                break;
            }

            case BF::JPEGMarker::DefineHuffmanTable:
            {
                unsigned short length = 0;
                JPEGHuffmanTable jpegHuffmanTable;

                file.Read(length, Endian::Big);
                file.Read(jpegHuffmanTable.Class);
                file.Read(jpegHuffmanTable.Destination);

                file.DataCursorPosition += (length - 2) - 2;
                
                break;
            }

            case BF::JPEGMarker::StartOfScan:
            {
                unsigned short length = 0;
                file.Read(length, Endian::Big);
                file.Read(ScanStart.ScanSelectorSize);
                
                for (size_t i = 0; i < ScanStart.ScanSelectorSize; i++)
                {
                    JPEGScanSelector& scanSelector = ScanStart.ScanSelector[i];
                    unsigned char dcacTable = 0;

                    file.Read(scanSelector.Selector);
                    file.Read(dcacTable);

                    scanSelector.DC = (dcacTable & 0b11110000) >> 4;
                    scanSelector.ACTable = dcacTable & 0b00001111;
                }

                file.Read(ScanStart.SpectralSelectFrom);
                file.Read(ScanStart.SpectralSelectTo);
                file.Read(ScanStart.SuccessiveAproximation);

                CompressedImageDataSize = file.DataSize - file.DataCursorPosition - 2;
                CompressedImageData = (unsigned char*)malloc(CompressedImageDataSize * sizeof(char));

                file.Read(CompressedImageData, CompressedImageDataSize);

                break;
            }
            case BF::JPEGMarker::HeaderFileInfo:
            {
                file.Read(FileInfo.Length, Endian::Little);
                file.Read(FileInfo.Identifier, 5u);
                file.Read(FileInfo.VersionMajor);
                file.Read(FileInfo.VersionMinor);
                file.Read(FileInfo.DensityUnits);
                file.Read(FileInfo.DensityX, Endian::Little);
                file.Read(FileInfo.DensityY, Endian::Little);
                file.Read(FileInfo.ThumbnailX);
                file.Read(FileInfo.ThumbnailY);
                
                if (FileInfo.ThumbnailX > 0 && FileInfo.ThumbnailY > 0)
                {
                    FileInfo.ThumbnailDataSize = FileInfo.ThumbnailX * FileInfo.ThumbnailY * 3;
                    FileInfo.ThumbnailData = (unsigned char*)malloc(FileInfo.ThumbnailDataSize * sizeof(char));

                    file.Read(FileInfo.ThumbnailData, FileInfo.ThumbnailDataSize);
                }             

                break;
            }                
        }
    }

    return FileActionResult::FormatNotAsExpected;
}

BF::FileActionResult BF::JPEG::Save(const char* filePath)
{
    return FileActionResult::Successful;
}

BF::JPEG::~JPEG()
{
    free(CompressedImageData);
}

BF::FileActionResult BF::JPEG::ConvertTo(Image& image)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::JPEG::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}
