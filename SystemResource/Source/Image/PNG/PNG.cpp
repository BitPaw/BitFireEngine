#include "PNG.h"

#include "PNGColorCompressor.h"

#include "../../File/FileStream.h"
#include "../../Compression/ZLIB/ZLIBHeader.h"
#include "../../Compression/ADAM7/ADAM7.h"
#include "../../Compression/ZLIB/ZLIB.h"
#include "../../Compression/DEFLATE/DeflateBlock.h"
#include "../../Container/BitStreamHusk.h"

#define PNGHeaderSequenz { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n' }
#define PNGDebugInfo false

unsigned int BF::PNG::BitsPerPixel()
{
    unsigned int numberOfColorChannels = NumberOfColorChannels(ColorType);

    return BitDepth * numberOfColorChannels;
}

BF::FileActionResult BF::PNG::Load(const char* filePath)
{   
    size_t imageDataCounter = 0;
    size_t imageDataChunkCacheSizeUSED = 0;
    size_t imageDataChunkCacheSizeMAX = 0u;
    Byte* imageDataChunkCache = nullptr;

    //---<Parse PNG File>------------------------------------------------------
    {
        FileStream fileStream;
        FileActionResult fileActionResult = fileStream.ReadFromDisk(filePath);
        bool parseFinished = false;

        if (fileActionResult != FileActionResult::Successful)
        {
            return fileActionResult;
        }

        // Allocate Memory for later ImageData Chunks
        imageDataChunkCacheSizeMAX = fileStream.DataSize - 0u;
        imageDataChunkCache = (Byte*)malloc(imageDataChunkCacheSizeMAX * sizeof(Byte));

        //---<Check PNG Header>------------------------------------------------
        {
            const Byte pngFileHeader[8] = PNGHeaderSequenz;
            bool isValidHeader = fileStream.ReadAndCompare(pngFileHeader, 8u);

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
            fileStream.Read(chunk.ChunkTypeRaw, 4u);

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
                    unsigned char colorTypeRaw = 0;
                    unsigned char interlaceMethodRaw = 0;

                    fileStream.Read(Width, Endian::Big); // 4 Bytes
                    fileStream.Read(Height, Endian::Big); // 4 Bytes

                    fileStream.Read(BitDepth); // 1 Byte
                    fileStream.Read(colorTypeRaw); // 1 Byte
                    fileStream.Read(CompressionMethod); // 1 Byte
                    fileStream.Read(FilterMethod); // 1 Byte
                    fileStream.Read(interlaceMethodRaw); // 1 Byte

                    ColorType = ConvertColorType(colorTypeRaw);
                    InterlaceMethod = ConvertPNGInterlaceMethod(interlaceMethodRaw);

                    break;
                }
                case PNGChunkType::Palette:
                {
                    // Red 	1 byte
                    // Green 1 byte
                    // Blue 	1 byte

                    fileStream.Read(Palette, 3u);

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
                    fileStream.Read(CromaWhite[0], Endian::Big);
                    fileStream.Read(CromaWhite[1], Endian::Big);
                    fileStream.Read(CromaRed[0], Endian::Big);
                    fileStream.Read(CromaRed[1], Endian::Big);
                    fileStream.Read(CromaGreen[0], Endian::Big);
                    fileStream.Read(CromaGreen[1], Endian::Big);
                    fileStream.Read(CromaBlue[0], Endian::Big);
                    fileStream.Read(CromaBlue[1], Endian::Big);

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
                    switch (ColorType)
                    {
                        default:
                        case BF::PNGColorType::InvalidColorType:
                            break; // ERROR
                     
                        case BF::PNGColorType::Grayscale:
                        case BF::PNGColorType::GrayscaleWithAlphaChannel:
                        {
                            // 2 Byte
                            fileStream.Read(BackgroundColorGreyScale, Endian::Big);
                            break;
                        }
                        case BF::PNGColorType::Truecolor:
                        case BF::PNGColorType::TruecolorWithAlphaChannel: 
                        {
                            // 2 Byte each RGB
                            fileStream.Read(BackgroundColorRed, Endian::Big);
                            fileStream.Read(BackgroundColorGreen, Endian::Big);
                            fileStream.Read(BackgroundColorBlue, Endian::Big);
                            break;
                        }
                        case BF::PNGColorType::IndexedColor:
                        {
                            // 1 Byte
                            fileStream.Read(BackgroundColorPaletteIndex);
                            break;
                        }   
                    }

                    break;
                }
                case PNGChunkType::PhysicalPixelDimensions:
                {
                    fileStream.Read(PixelsPerUnit[0], Endian::Big);
                    fileStream.Read(PixelsPerUnit[1], Endian::Big);
                    fileStream.Read(UnitSpecifier);

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
                    ColorFrequencyListSize = chunk.Lengh / 2;
                    ColorFrequencyList = (unsigned short*)malloc(ColorFrequencyListSize * sizeof(unsigned short));

                    for (size_t i = 0; i < ColorFrequencyListSize; i++)
                    {
                        fileStream.Read(ColorFrequencyList[i], Endian::Big);
                    }

                    break;
                }
                case PNGChunkType::LastModificationTime:
                {
                    fileStream.Read(Year, Endian::Big);
                    fileStream.Read(Month);
                    fileStream.Read(Day);
                    fileStream.Read(Hour);
                    fileStream.Read(Minute);
                    fileStream.Read(Second);

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
    PixelDataSize = Width * Height * NumberOfColorChannels(ColorType);
    PixelData = (Byte*)malloc(PixelDataSize * sizeof(Byte));   
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
            size_t bitsPerPixel = BitsPerPixel();
            size_t expectedzlibCacheSize = ZLIB::CalculateExpectedSize(Width, Height, bitsPerPixel, InterlaceMethod);
            size_t expectedadam7CacheSize = ADAM7::CaluclateExpectedSize(Width, Height, bitsPerPixel);
            Byte* zlibCache = (Byte*)malloc(expectedzlibCacheSize * sizeof(Byte));
            Byte* adam7Cache = nullptr;

            do
            {           
                deflateBlock.Parse(bitstream);
                deflateBlock.Inflate(bitstream, zlibCache, zlibDataCache);     
            }
            while (!deflateBlock.IsLastBlock);

            adam7Cache = (Byte*)malloc(expectedadam7CacheSize * sizeof(Byte));

            ADAM7::ProcessScanlines(adam7Cache, zlibCache, Width, Height, bitsPerPixel, InterlaceMethod);

            free(zlibCache);

            PNGColorCompressor::Decompress(adam7Cache, PixelData, Width, Height, BitDepth, ColorType);
       
            free(adam7Cache);

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

BF::FileActionResult BF::PNG::Save(const char* filePath)
{
    size_t fileLength = 500;
    FileStream fileStream(fileLength);

    // Write Header
    {
        const Byte pngFileHeader[8] = PNGHeaderSequenz;

        fileStream.Write((void*)pngFileHeader, 8u);
    }

    // Header
    {
        unsigned char colorType = ConvertColorType(ColorType);
        unsigned char interlaceMethod = ConvertPNGInterlaceMethod(InterlaceMethod);

        fileStream.Write(13u, Endian::Big);
        fileStream.Write("IHDR", 4u);

        fileStream.Write(Width, Endian::Big);
        fileStream.Write(Height, Endian::Big);

        fileStream.Write(BitDepth);
        fileStream.Write(colorType);
        fileStream.Write(CompressionMethod);
        fileStream.Write(FilterMethod);
        fileStream.Write(interlaceMethod);

        fileStream.Write(0u, Endian::Big);
    }


    //---<>---
    {   
        fileStream.Write(0u, Endian::Big);
        fileStream.Write("IEND", 4u);
        fileStream.Write(2923585666u, Endian::Big);
    }

    fileStream.WriteToDisk(filePath);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::PNG::ConvertTo(Image& image)
{    
    switch (ColorType)
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
            image.Format = ImageDataFormat::Unkown;           
            break;

        case BF::PNGColorType::TruecolorWithAlphaChannel:
            image.Format = ImageDataFormat::RGBA;
            break;
    }


	image.Resize(Width, Height);

    memcpy(image.PixelData, PixelData, PixelDataSize);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::PNG::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}