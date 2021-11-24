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

    {
        FileStream fileStream;
        FileActionResult fileActionResult = fileStream.ReadFromDisk(filePath);
        bool parseFinished = false;

        if (fileActionResult != FileActionResult::Successful)
        {
            return fileActionResult;
        }

        imageDataChunkCacheSizeMAX = fileStream.DataSize - 0u;
        imageDataChunkCache = (Byte*)malloc(imageDataChunkCacheSizeMAX * sizeof(Byte));

        // Check Header
        {
            const Byte pngFileHeader[8] = PNGHeaderSequenz;
            bool isValidHeader = fileStream.ReadAndCompare(pngFileHeader, 8u);

            if (!isValidHeader)
            {
                return FileActionResult::FormatNotSupported;
            }        
        }

#if PNGDebugInfo
        printf
        (
            "+------+--------------------------------------------+---+---+---+-------+-----+\n"
            "| ID   | Name                                       | E | R | S | Bytes | CRC |\n"
            "+------+--------------------------------------------+---+---+---+-------+-----+\n"
        );
#endif

        // Fetch data
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
                    unsigned char colorType = 0;

                    fileStream.Read(Width, Endian::Big); // 4 Bytes
                    fileStream.Read(Height, Endian::Big); // 4 Bytes

                    fileStream.Read(BitDepth); // 1 Byte
                    fileStream.Read(colorType); // 1 Byte
                    fileStream.Read(CompressionMethod); // 1 Byte
                    fileStream.Read(FilterMethod); // 1 Byte
                    fileStream.Read(InterlaceMethod); // 1 Byte

                    ColorType = ConvertColorType(colorType);

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
                case PNGChunkType::TextualData:
                case PNGChunkType::CompressedTextualData:
                case PNGChunkType::InternationalTextualData:
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

                    SignificantBits = result;

                    break;
                }
                case PNGChunkType::SuggestedPalette:
                case PNGChunkType::PaletteHistogram:
                case PNGChunkType::LastModificationTime:
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
    PixelDataSize = Width * Height * 4u;
    PixelData = (Byte*)malloc(PixelDataSize * sizeof(Byte));  

    size_t zlibDataCache = 0;
    Byte* zlibCache = (Byte*)malloc(imageDataCounter * 10 * 32768 * sizeof(Byte));
    Byte* dataFilder = (Byte*)malloc(PixelDataSize * 2 * sizeof(Byte));
    //-------------------------------------------------------------------------
    

    BitStreamHusk bitstream(imageDataChunkCache, imageDataChunkCacheSizeUSED);
    ZLIB zlib(imageDataChunkCache, imageDataChunkCacheSizeUSED);   
 
    bitstream.CurrentPosition += 2u;

    switch (zlib.Header.CompressionMethod)
    {
        case BF::ZLIBCompressionMethod::Deflate:
        {
            unsigned int bpp = BitsPerPixel();
            DeflateBlock deflateBlock;

            do
            {           
                deflateBlock.Parse(bitstream);
                deflateBlock.Inflate(bitstream, zlibCache, zlibDataCache);       
            }
            while (!deflateBlock.IsLastBlock);

            ADAM7::ProcessScanlines(dataFilder, zlibCache, Width, Height, bpp, InterlaceMethod);

            {
                LodePNGColorMode in;
                LodePNGColorMode out;

                memset(&in, 0, sizeof(LodePNGColorMode));
                memset(&out, 0, sizeof(LodePNGColorMode));

                in.bitdepth = BitDepth;
                in.colortype = LCT_RGBA;

                out.bitdepth = BitDepth;
                out.colortype = LCT_RGBA;

                PNGColorCompressor::Decompress(PixelData, dataFilder, &out, &in, Width, Height);
            }

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

        fileStream.Write(13u, Endian::Big);
        fileStream.Write("IHDR", 4u);

        fileStream.Write(Width, Endian::Big);
        fileStream.Write(Height, Endian::Big);

        fileStream.Write(BitDepth);
        fileStream.Write(colorType);
        fileStream.Write(CompressionMethod);
        fileStream.Write(FilterMethod);
        fileStream.Write(InterlaceMethod);

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
    unsigned int width = Width;
	unsigned int height = Height;
    unsigned int pIndex = 0;
    
	image.Format = ImageDataFormat::RGBA;
	image.Resize(width, height);	

    memcpy(image.PixelData, PixelData, PixelDataSize);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::PNG::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}

void BF::PNG::PrintData()
{
    const char* colorType = PNGColorTypeToString(ColorType);
    const char* compressionMethod;
    const char* filterMethod;
    const char* interlaceMethod;

    switch (CompressionMethod)
    {
        case 0:
        {
            compressionMethod = "None";
            break;
        }
        
        default:
        {
            compressionMethod = "Error";
            break;
        }
    }

    switch (FilterMethod)
    {
        case 0:
        {
            filterMethod = "None";
            break;
        }

        default:
        {
            filterMethod = "Error";
            break;
        }
    }

    switch (InterlaceMethod)
    {
        case 0:
        {
            interlaceMethod = "None";
            break;
        }

        default:
        {
            interlaceMethod = "Error";
            break;
        }
    }

	printf
	(
	    "+---------------------------+\n"
		"| PNG File                  |\n"
		"+---------------------------+\n"
		"| Width             : %5i |\n"
		"| Height            : %5i |\n"
		"| BitDepth          : %5i |\n"
		"| ColorType         : %5s |\n"
		"| CompressionMethod : %5s |\n"
		"| FilterMethod      : %5s |\n"
		"| InterlaceMethod   : %5s |\n"
		"+---------------------------+\n",
		Width,
		Height,
		BitDepth,
        colorType,
        compressionMethod,
        filterMethod,
        interlaceMethod
	);
}
