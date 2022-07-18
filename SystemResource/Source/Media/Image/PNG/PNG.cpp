#include "PNG.h"

#include "PNGColorCompressor.h"
#include "Chunk/PNGChunk.h"

#include <File/File.h>
#include <Compression/ZLIB/ZLIB.h>
#include <Compression/ZLIB/ZLIBHeader.h>
#include <Compression/ADAM7/ADAM7.h>
#include <Compression/DEFLATE/DeflateBlock.h>
#include <Container/BitStreamHusk.h>
#include <Algorithm/CRC32/CRC32.h>
#include <Hardware/Memory/Memory.h>

#include <string>

#define PNGHeaderSequenz { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n' }
#define PNGDebugInfo false

BF::PNG::PNG()
{
}

BF::PNG::~PNG()
{
    MemoryRelease(PixelData, PixelDataSize);
}

unsigned int BF::PNG::BitsPerPixel()
{
    unsigned int numberOfColorChannels = NumberOfColorChannels(ImageHeader.ColorType);

    return ImageHeader.BitDepth * numberOfColorChannels;
}

BF::FileActionResult BF::PNG::Load(const char* filePath)
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

BF::FileActionResult BF::PNG::Load(const wchar_t* filePath)
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

BF::FileActionResult BF::PNG::Load(const unsigned char* fileData, const size_t fileDataSize)
{
    ByteStream dataStream(fileData, fileDataSize);

    size_t imageDataCounter = 0;
    size_t imageDataChunkCacheSizeUSED = 0;
    size_t imageDataChunkCacheSizeMAX = 0u;
    Byte__* imageDataChunkCache = nullptr;

    MemorySet(this, 0, sizeof(PNG));

    //---<Parse PNG File>------------------------------------------------------
    {     
        bool parseFinished = false; 

        //---<Check PNG Header>------------------------------------------------
        {
            const Byte__ pngFileHeader[8] = PNGHeaderSequenz;
            const size_t pngFileHeaderSize = sizeof(pngFileHeader);
            const bool isValidHeader = dataStream.ReadAndCompare(pngFileHeader, pngFileHeaderSize);

            if(!isValidHeader)
            {
                return FileActionResult::InvalidHeaderSignature;
            }
        }

        // Allocate Memory for later ImageData Chunks
        imageDataChunkCacheSizeMAX = dataStream.DataSize - 0u;
        imageDataChunkCache = Memory::Allocate<Byte__>(imageDataChunkCacheSizeMAX);

        //---------------------------------------------------------------------

#if PNGDebugInfo
        printf
        (
            "+------+--------------------------------------------+---+---+---+-------+-----+\n"
            "| ID   | Name                                       | E | R | S | Bytes | CRC |\n"
            "+------+--------------------------------------------+---+---+---+-------+-----+\n"
        );
#endif

        // Parse every chunk until finished.
        while(!parseFinished)
        {
            PNGChunk chunk;

            chunk.ChunkData = dataStream.Data + dataStream.DataCursor;

            dataStream.Read(chunk.Lengh, EndianBig);
            dataStream.Read(chunk.ChunkTypeRaw.Data, 4u);

            chunk.Check();

#if PNGDebugInfo
            printf
            (
                "| %c%c%c%c | %-42s | %c | %c | %c | %5i | Yes |\n",
                chunk.ChunkTypeRaw[0],
                chunk.ChunkTypeRaw[1],
                chunk.ChunkTypeRaw[2],
                chunk.ChunkTypeRaw[3],
                ChunkTypeToString(chunk.ChunkType),
                chunk.IsEssential ? 'x' : '-',
                chunk.IsRegisteredStandard ? 'x' : '-',
                chunk.IsSafeToCopy ? 'x' : '-',
                chunk.Lengh
            );
#endif

            //---Get Chunk Data------------------------------------------
            switch(chunk.ChunkType)
            {
                case PNGChunkType::ImageHeader:
                {
                    Byte__ colorTypeRaw = 0;
                    Byte__ interlaceMethodRaw = 0;

                    dataStream.Read(ImageHeader.Width, EndianBig); // 4 Bytes
                    dataStream.Read(ImageHeader.Height, EndianBig); // 4 Bytes

                    dataStream.Read(ImageHeader.BitDepth); // 1 Byte__
                    dataStream.Read(colorTypeRaw); // 1 Byte__
                    dataStream.Read(ImageHeader.CompressionMethod); // 1 Byte__
                    dataStream.Read(ImageHeader.FilterMethod); // 1 Byte__
                    dataStream.Read(interlaceMethodRaw); // 1 Byte__

                    ImageHeader.ColorType = ConvertColorType(colorTypeRaw);
                    ImageHeader.InterlaceMethod = ConvertPNGInterlaceMethod(interlaceMethodRaw);

                    break;
                }
                case PNGChunkType::Palette:
                {
                    // Red 	1 byte
                    // Green 1 byte
                    // Blue 	1 byte

                    dataStream.Read(&Palette, 3u);

                    break;
                }
                case PNGChunkType::ImageData:
                {
                    /*
                    ZLIB zlib(dataStream.Data + dataStream.DataCursor, chunk.Lengh);

                    // Dump content into buffer
                    // There may be multiple IDAT chunks; if so, they shall appear consecutively with no other intervening chunks.
                    // the compressed datastream is then the concatenation of the contents of the data fields of all the IDAT chunks.

                    printf
                    (
                        "| [ZLIB Header]          |\n"
                        "| CompressionMethod : %7s |\n"
                        "| CompressionInfo   : %7i |\n"
                        "| WindowSize        : %7i |\n"
                        "| CheckFlag         : %7i |\n"
                        "| DictionaryPresent : %7i |\n"
                        "| CompressionLevel  : %7s |\n",
                        CompressionMethodToString(zlib.Header.CompressionMethod),
                        zlib.Header.CompressionInfo,
                        zlib.Header.WindowSize,
                        zlib.Header.CheckFlag,
                        zlib.Header.DictionaryPresent,
                        CompressionLevelToString(zlib.Header.CompressionLevel)
                    );

                    printf
                    (
                        "| [DEFLATE]                 |\n"
                        "| IsLastBlock          : %15i |\n"
                        "| EncodingMethod       : %15s |\n"
                        "| BitStreamDataRawSize : %15i |\n",
                        zlib.DeflateData.IsLastBlock,
                        DeflateEncodingMethodToString(zlib.DeflateData.EncodingMethod),
                        zlib.DeflateData.BitStreamDataRawSize
                    );*/


                    //zlib.Unpack(imageDataChunkCache, imageDataChunkCacheSizeUSED);


                    dataStream.Read(imageDataChunkCache + imageDataChunkCacheSizeUSED, chunk.Lengh);
                    imageDataChunkCacheSizeUSED += chunk.Lengh;

                    ++imageDataCounter;

                    break;
                }
                case PNGChunkType::ImageEnd:
                {
                    parseFinished = true;
                    break;
                }
                case PNGChunkType::Transparency:
                {
                    dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkType::ImageGamma:
                {
                    dataStream.Read(Gamma, EndianBig);

                    break;
                }
                case PNGChunkType::PrimaryChromaticities:
                {
                    dataStream.Read(PrimaryChromatics.WhiteX, EndianBig);
                    dataStream.Read(PrimaryChromatics.WhiteY, EndianBig);
                    dataStream.Read(PrimaryChromatics.RedX, EndianBig);
                    dataStream.Read(PrimaryChromatics.RedY, EndianBig);
                    dataStream.Read(PrimaryChromatics.GreenX, EndianBig);
                    dataStream.Read(PrimaryChromatics.GreenY, EndianBig);
                    dataStream.Read(PrimaryChromatics.BlueX, EndianBig);
                    dataStream.Read(PrimaryChromatics.BlueY, EndianBig);

                    break;
                }
                case PNGChunkType::StandardRGBColorSpace:
                {
                    dataStream.Read(RenderingIntent);

                    break;
                }
                case PNGChunkType::EmbeddedICCProfile:
                {
                    dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkType::TextualData:
                {
                    dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkType::CompressedTextualData:
                {
                    // Keyword 	                    1 - 79 bytes(character string)
                    // Null separator 	            1 byte(null character)
                    // Compression method 	        1 byte
                    // Compressed text datastream 	n bytes

                    dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkType::InternationalTextualData:
                {
                    dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkType::BackgroundColor:
                {
                    switch(ImageHeader.ColorType)
                    {
                        default:
                        case BF::PNGColorType::InvalidColorType:
                            break; // ERROR

                        case BF::PNGColorType::Grayscale:
                        case BF::PNGColorType::GrayscaleWithAlphaChannel:
                        {
                            dataStream.Read(BackgroundColor.GreyScale, EndianBig);
                            break;
                        }
                        case BF::PNGColorType::Truecolor:
                        case BF::PNGColorType::TruecolorWithAlphaChannel:
                        {
                            dataStream.Read(BackgroundColor.Red, EndianBig);
                            dataStream.Read(BackgroundColor.Green, EndianBig);
                            dataStream.Read(BackgroundColor.Blue, EndianBig);
                            break;
                        }
                        case BF::PNGColorType::IndexedColor:
                        {
                            dataStream.Read(BackgroundColor.PaletteIndex);
                            break;
                        }
                    }

                    break;
                }
                case PNGChunkType::PhysicalPixelDimensions:
                {
                    dataStream.Read(PhysicalPixelDimension.PixelsPerUnit[0], EndianBig);
                    dataStream.Read(PhysicalPixelDimension.PixelsPerUnit[1], EndianBig);
                    dataStream.Read(PhysicalPixelDimension.UnitSpecifier);

                    break;
                }
                case PNGChunkType::SignificantBits:
                {
                    /*
                    unsigned int byteLength = 0;
                    unsigned int result = 0;

                    switch (ColorType)
                    {
                        case PNGColorType::Grayscale: // single byte,
                            byteLength = 1;
                            break;

                        case PNGColorType::Truecolor: // three bytes,
                        case PNGColorType::IndexedColor:
                            byteLength = 3;
                            break;

                        case PNGColorType::GrayscaleWithAlphaChannel: // two bytes
                            byteLength = 2;
                            break;

                        case PNGColorType::TruecolorWithAlphaChannel: //  four bytes,
                            byteLength = 4;
                            break;
                    }

                    for (unsigned int i = 0; i < byteLength; i++)
                    {
                        char calcbyte;

                        dataStream.Read(calcbyte);

                        result = (result << (i * 8)) | calcbyte;
                    }

                    SignificantBits = result;*/

                    dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkType::SuggestedPalette:
                {
                    dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkType::PaletteHistogram:
                {
                    const size_t listSize = chunk.Lengh / 2;

                    PaletteHistogram.ColorFrequencyListSize = listSize;
                    PaletteHistogram.ColorFrequencyList = Memory::Allocate<unsigned short>(listSize);

                    for(size_t i = 0; i < listSize; i++)
                    {
                        dataStream.Read(PaletteHistogram.ColorFrequencyList[i], EndianBig);
                    }

                    break;
                }
                case PNGChunkType::LastModificationTime:
                {
                    dataStream.Read(LastModificationTime.Year, EndianBig);
                    dataStream.Read(LastModificationTime.Month);
                    dataStream.Read(LastModificationTime.Day);
                    dataStream.Read(LastModificationTime.Hour);
                    dataStream.Read(LastModificationTime.Minute);
                    dataStream.Read(LastModificationTime.Second);

                    break;
                }
                case PNGChunkType::Custom:
                default:
                {
                    dataStream.DataCursor += chunk.Lengh;
                    break;
                }
            }
            //---------------------------------------------------------------

            dataStream.Read(chunk.CRC, EndianBig); // 4 Bytes

            //---<Check CRC>---
            // TODO: Yes
            //-----------------
        }
            }

    //---<Allocate>------------------------------------------------------------
    PixelDataSize = ImageHeader.Width * ImageHeader.Height * NumberOfColorChannels(ImageHeader.ColorType);
    PixelData = Memory::Allocate<Byte__>(PixelDataSize);
    //-------------------------------------------------------------------------    

    BitStreamHusk bitstream(imageDataChunkCache, imageDataChunkCacheSizeUSED);
    ZLIB zlib;

    bitstream.CurrentPosition += zlib.Parse(imageDataChunkCache, imageDataChunkCacheSizeUSED);

    switch(zlib.Header.CompressionMethod)
    {
        case BF::ZLIBCompressionMethod::Deflate:
        {
            DeflateBlock deflateBlock;

            size_t zlibDataCache = 0;
            const size_t bitsPerPixel = BitsPerPixel();
            const size_t expectedzlibCacheSize = ZLIB::CalculateExpectedSize(ImageHeader.Width, ImageHeader.Height, bitsPerPixel, ImageHeader.InterlaceMethod);
            const size_t expectedadam7CacheSize = ADAM7::CaluclateExpectedSize(ImageHeader.Width, ImageHeader.Height, bitsPerPixel);
            Byte__* zlibCache = Memory::Allocate<Byte__>(expectedzlibCacheSize);
            Byte__* adam7Cache = nullptr;

            do
            {
                deflateBlock.Parse(bitstream);
                deflateBlock.Inflate(bitstream, zlibCache, zlibDataCache);
            }
            while(!deflateBlock.IsLastBlock);

            adam7Cache = Memory::Allocate<Byte__>(expectedadam7CacheSize);

            ADAM7::ScanlinesDecode(adam7Cache, zlibCache, ImageHeader.Width, ImageHeader.Height, bitsPerPixel, ImageHeader.InterlaceMethod);

            MemoryRelease(zlibCache, zlibDataCache);

            PNGColorCompressor::Decompress(adam7Cache, PixelData, ImageHeader.Width, ImageHeader.Height, ImageHeader.BitDepth, ImageHeader.ColorType);

            MemoryRelease(adam7Cache, expectedadam7CacheSize);

            break;
        }
        default:
        case BF::ZLIBCompressionMethod::Reserved:
        case BF::ZLIBCompressionMethod::Invalid:
        {
            break;
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::PNG::Save(const wchar_t* filePath)
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

    //---<Signature>---
    {
        const Byte__ pngFileHeader[8] = PNGHeaderSequenz;
        const size_t pngFileHeaderSize = sizeof(pngFileHeader);

        file.Write(pngFileHeader, pngFileHeaderSize);
    }

    //---<IHDR> (Image Header)---
    {
        const unsigned char colorType = ConvertColorType(ImageHeader.ColorType);
        const unsigned char interlaceMethod = ConvertPNGInterlaceMethod(ImageHeader.InterlaceMethod);     
        const unsigned char* chunkStart = file.Data + file.DataCursor;

        file.Write(13u, EndianBig);
        file.Write("IHDR", 4u);

        file.Write(ImageHeader.Width, EndianBig);
        file.Write(ImageHeader.Height, EndianBig);

        file.Write(ImageHeader.BitDepth);
        file.Write(colorType);
        file.Write(ImageHeader.CompressionMethod);
        file.Write(ImageHeader.FilterMethod);
        file.Write(interlaceMethod);

        const unsigned int crc = CRC32::Generate(chunkStart, 13+4);

        file.Write(crc, EndianBig);
    }

    // iCCP
    // sRGB
    // gAMA
    // cHRM
    // PLTE
    // tRNS
    // bKGD
    // pHYs
    // IDAT
    {
   

        // ZLIB comprssion
    }   
     
    // tIME
    // zTXt
    // tEXt

    //---<>---
    {   
        file.Write(0u, EndianBig);
        file.Write("IEND", 4u);
        file.Write(2923585666u, EndianBig);
    }

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

BF::FileActionResult BF::PNG::ConvertTo(Image& image)
{    
    switch (ImageHeader.ColorType)
    {
        case BF::PNGColorType::Grayscale:
            image.Format = ImageDataFormat::AlphaMask;
            break;

        case BF::PNGColorType::Truecolor:
            image.Format = ImageDataFormat::RGB;
            break;

        case BF::PNGColorType::InvalidColorType:
        case BF::PNGColorType::IndexedColor:
        case BF::PNGColorType::GrayscaleWithAlphaChannel:
            image.Format = ImageDataFormat::Invalid;           
            break;

        case BF::PNGColorType::TruecolorWithAlphaChannel:
            image.Format = ImageDataFormat::RGBA;
            break;
    }


	image.Resize(ImageHeader.Width, ImageHeader.Height);

    MemoryCopy(PixelData, PixelDataSize, image.PixelData, image.PixelDataSize);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::PNG::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}