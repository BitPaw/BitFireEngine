#include "PNG.h"

#include "PNGColorCompressor.h"
#include "Chunk/PNGChunk.h"

#include <File/File.h>
#include <Compression/ZLIB/ZLIBHeader.h>
#include <Compression/ADAM7/ADAM7.h>
#include <Compression/ZLIB/ZLIB.h>
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
    Memory::Release(PixelData, PixelDataSize);
}

unsigned int BF::PNG::BitsPerPixel()
{
    unsigned int numberOfColorChannels = NumberOfColorChannels(ImageHeader.ColorType);

    return ImageHeader.BitDepth * numberOfColorChannels;
}

BF::FileActionResult BF::PNG::Load(const wchar_t* filePath)
{   
    size_t imageDataCounter = 0;
    size_t imageDataChunkCacheSizeUSED = 0;
    size_t imageDataChunkCacheSizeMAX = 0u;
    Byte* imageDataChunkCache = nullptr;

    Memory::Set(this, 0, sizeof(PNG));

    //---<Parse PNG File>------------------------------------------------------
    {
        File fileStream;
      
        bool parseFinished = false;

        {
            const FileActionResult fileActionResult = fileStream.MapToVirtualMemory(filePath);
            const bool sucessful = fileActionResult == FileActionResult::Successful;

            if(!sucessful)
            {
                return fileActionResult;
            }
        }     

        // Allocate Memory for later ImageData Chunks
        imageDataChunkCacheSizeMAX = fileStream.DataSize - 0u;
        imageDataChunkCache = Memory::Allocate<Byte>(imageDataChunkCacheSizeMAX);

        //---<Check PNG Header>------------------------------------------------
        {
            const Byte pngFileHeader[8] = PNGHeaderSequenz;
            const size_t pngFileHeaderSize = sizeof(pngFileHeader);
            const bool isValidHeader = fileStream.ReadAndCompare(pngFileHeader, pngFileHeaderSize);

            if (!isValidHeader)
            {
                return FileActionResult::FormatNotSupported;
            }        
        }
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
        while (!parseFinished)
        {
            PNGChunk chunk;

            chunk.ChunkData = fileStream.Data + fileStream.DataCursorPosition;

            fileStream.Read(chunk.Lengh, Endian::Big);
            fileStream.Read(chunk.ChunkTypeRaw.Data, 4u);

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
            switch (chunk.ChunkType)
            {
                case PNGChunkType::ImageHeader:
                {
                    Byte colorTypeRaw = 0;
                    Byte interlaceMethodRaw = 0;

                    fileStream.Read(ImageHeader.Width, Endian::Big); // 4 Bytes
                    fileStream.Read(ImageHeader.Height, Endian::Big); // 4 Bytes

                    fileStream.Read(ImageHeader.BitDepth); // 1 Byte
                    fileStream.Read(colorTypeRaw); // 1 Byte
                    fileStream.Read(ImageHeader.CompressionMethod); // 1 Byte
                    fileStream.Read(ImageHeader.FilterMethod); // 1 Byte
                    fileStream.Read(interlaceMethodRaw); // 1 Byte

                    ImageHeader.ColorType = ConvertColorType(colorTypeRaw);
                    ImageHeader.InterlaceMethod = ConvertPNGInterlaceMethod(interlaceMethodRaw);

                    break;
                }
                case PNGChunkType::Palette:
                {
                    // Red 	1 byte
                    // Green 1 byte
                    // Blue 	1 byte

                    fileStream.Read(&Palette, 3u);

                    break;
                }
                case PNGChunkType::ImageData:
                {
                    /*
                    ZLIB zlib(fileStream.Data + fileStream.DataCursorPosition, chunk.Lengh);

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


                    fileStream.Read(imageDataChunkCache + imageDataChunkCacheSizeUSED, chunk.Lengh);
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
                    fileStream.DataCursorPosition += chunk.Lengh;

                    break;
                }
                case PNGChunkType::ImageGamma:
                {
                    fileStream.Read(Gamma, Endian::Big);

                    break;
                }
                case PNGChunkType::PrimaryChromaticities:
                {
                    fileStream.Read(PrimaryChromatics.WhiteX, Endian::Big);
                    fileStream.Read(PrimaryChromatics.WhiteY, Endian::Big);
                    fileStream.Read(PrimaryChromatics.RedX, Endian::Big);
                    fileStream.Read(PrimaryChromatics.RedY, Endian::Big);
                    fileStream.Read(PrimaryChromatics.GreenX, Endian::Big);
                    fileStream.Read(PrimaryChromatics.GreenY, Endian::Big);
                    fileStream.Read(PrimaryChromatics.BlueX, Endian::Big);
                    fileStream.Read(PrimaryChromatics.BlueY, Endian::Big);

                    break;
                }
                case PNGChunkType::StandardRGBColorSpace:
                {
                    fileStream.Read(RenderingIntent);

                    break;
                }
                case PNGChunkType::EmbeddedICCProfile:
                {
                    fileStream.DataCursorPosition += chunk.Lengh;

                    break;
                }
                case PNGChunkType::TextualData:
                {
                    fileStream.DataCursorPosition += chunk.Lengh;

                    break;
                }
                case PNGChunkType::CompressedTextualData:
                {
                    // Keyword 	                    1 - 79 bytes(character string)
                    // Null separator 	            1 byte(null character)
                    // Compression method 	        1 byte
                    // Compressed text datastream 	n bytes

                    fileStream.DataCursorPosition += chunk.Lengh;

                    break;
                }
                case PNGChunkType::InternationalTextualData:
                {
                    fileStream.DataCursorPosition += chunk.Lengh;

                    break;
                }
                case PNGChunkType::BackgroundColor:
                {
                    switch (ImageHeader.ColorType)
                    {
                        default:
                        case BF::PNGColorType::InvalidColorType:
                            break; // ERROR
                     
                        case BF::PNGColorType::Grayscale:
                        case BF::PNGColorType::GrayscaleWithAlphaChannel:
                        {   
                            fileStream.Read(BackgroundColor.GreyScale, Endian::Big);
                            break;
                        }
                        case BF::PNGColorType::Truecolor:
                        case BF::PNGColorType::TruecolorWithAlphaChannel: 
                        {
                            fileStream.Read(BackgroundColor.Red, Endian::Big);
                            fileStream.Read(BackgroundColor.Green, Endian::Big);
                            fileStream.Read(BackgroundColor.Blue, Endian::Big);
                            break;
                        }
                        case BF::PNGColorType::IndexedColor:
                        {
                            fileStream.Read(BackgroundColor.PaletteIndex);
                            break;
                        }   
                    }

                    break;
                }
                case PNGChunkType::PhysicalPixelDimensions:
                {
                    fileStream.Read(PhysicalPixelDimension.PixelsPerUnit[0], Endian::Big);
                    fileStream.Read(PhysicalPixelDimension.PixelsPerUnit[1], Endian::Big);
                    fileStream.Read(PhysicalPixelDimension.UnitSpecifier);

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

                        fileStream.Read(calcbyte);

                        result = (result << (i * 8)) | calcbyte;
                    }

                    SignificantBits = result;*/

                    fileStream.DataCursorPosition += chunk.Lengh;

                    break;
                }
                case PNGChunkType::SuggestedPalette:
                {
                    fileStream.DataCursorPosition += chunk.Lengh;

                    break;
                }
                case PNGChunkType::PaletteHistogram:
                {
                    const size_t listSize = chunk.Lengh / 2;

                    PaletteHistogram.ColorFrequencyListSize = listSize;
                    PaletteHistogram.ColorFrequencyList = Memory::Allocate<unsigned short>(listSize);

                    for (size_t i = 0; i < listSize; i++)
                    {
                        fileStream.Read(PaletteHistogram.ColorFrequencyList[i], Endian::Big);
                    }

                    break;
                }
                case PNGChunkType::LastModificationTime:
                {
                    fileStream.Read(LastModificationTime.Year, Endian::Big);
                    fileStream.Read(LastModificationTime.Month);
                    fileStream.Read(LastModificationTime.Day);
                    fileStream.Read(LastModificationTime.Hour);
                    fileStream.Read(LastModificationTime.Minute);
                    fileStream.Read(LastModificationTime.Second);

                    break;
                }
                case PNGChunkType::Custom:
                default:
                {
                    fileStream.DataCursorPosition += chunk.Lengh;
                    break;
                }
            }
            //---------------------------------------------------------------

            fileStream.Read(chunk.CRC, Endian::Big); // 4 Bytes

            //---<Check CRC>---
            // TODO: Yes
            //-----------------
        }
    }   

    //---<Allocate>------------------------------------------------------------
    PixelDataSize = ImageHeader.Width * ImageHeader.Height * NumberOfColorChannels(ImageHeader.ColorType);
    PixelData = Memory::Allocate<Byte>(PixelDataSize);   
    //-------------------------------------------------------------------------    

    BitStreamHusk bitstream(imageDataChunkCache, imageDataChunkCacheSizeUSED);
    ZLIB zlib(imageDataChunkCache, imageDataChunkCacheSizeUSED);       

    bitstream.CurrentPosition += 2u;    

    switch (zlib.Header.CompressionMethod)
    {
        case BF::ZLIBCompressionMethod::Deflate:
        {
            DeflateBlock deflateBlock;

            size_t zlibDataCache = 0;
            const size_t bitsPerPixel = BitsPerPixel();
            const size_t expectedzlibCacheSize = ZLIB::CalculateExpectedSize(ImageHeader.Width, ImageHeader.Height, bitsPerPixel, ImageHeader.InterlaceMethod);
            const size_t expectedadam7CacheSize = ADAM7::CaluclateExpectedSize(ImageHeader.Width, ImageHeader.Height, bitsPerPixel);
            Byte* zlibCache = Memory::Allocate<Byte>(expectedzlibCacheSize);
            Byte* adam7Cache = nullptr;

            do
            {           
                deflateBlock.Parse(bitstream);
                deflateBlock.Inflate(bitstream, zlibCache, zlibDataCache);     
            }
            while (!deflateBlock.IsLastBlock);

            adam7Cache = Memory::Allocate<Byte>(expectedadam7CacheSize);

            ADAM7::ScanlinesDecode(adam7Cache, zlibCache, ImageHeader.Width, ImageHeader.Height, bitsPerPixel, ImageHeader.InterlaceMethod);

            Memory::Release(zlibCache, zlibDataCache);

            PNGColorCompressor::Decompress(adam7Cache, PixelData, ImageHeader.Width, ImageHeader.Height, ImageHeader.BitDepth, ImageHeader.ColorType);
       
            Memory::Release(adam7Cache, expectedadam7CacheSize);

            break;
        }
        default:
        case BF::ZLIBCompressionMethod::Reserved:
        case BF::ZLIBCompressionMethod::Invalid:
        {
            break;
        }
    }
}

BF::FileActionResult BF::PNG::Save(const wchar_t* filePath)
{
    size_t fileLength = 500;
    File file;// (fileLength);

    //---<Signature>---
    {
        const char pngFileHeader[8] = PNGHeaderSequenz;
        const size_t pngFileHeaderSize = sizeof(pngFileHeader);

        file.Write(pngFileHeader, pngFileHeaderSize);
    }

    //---<IHDR> (Image Header)---
    {
        unsigned char colorType = ConvertColorType(ImageHeader.ColorType);
        unsigned char interlaceMethod = ConvertPNGInterlaceMethod(ImageHeader.InterlaceMethod);
        unsigned int crc = 0;
        unsigned char* chunkStart = file.Data + file.DataCursorPosition;

        file.Write(13u, Endian::Big);
        file.Write("IHDR", 4u);

        file.Write(ImageHeader.Width, Endian::Big);
        file.Write(ImageHeader.Height, Endian::Big);

        file.Write(ImageHeader.BitDepth);
        file.Write(colorType);
        file.Write(ImageHeader.CompressionMethod);
        file.Write(ImageHeader.FilterMethod);
        file.Write(interlaceMethod);

        crc = CRC32::Generate(chunkStart, 13+4);

        file.Write(crc, Endian::Big);
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
        file.Write(0u, Endian::Big);
        file.Write("IEND", 4u);
        file.Write(2923585666u, Endian::Big);
    }

    file.WriteToDisk(filePath);

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

    Memory::Copy(image.PixelData, PixelData, PixelDataSize);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::PNG::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}