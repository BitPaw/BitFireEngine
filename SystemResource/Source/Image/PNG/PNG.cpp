#include "PNG.h"

#include "../../File/FileStream.h"
#include "../../Compression/ZLIB/ZLIBHeader.h"
#include "../../Compression/ADAM7/ADAM7.h"
#include "PNGColorCompressor.h"
#include "../../Compression/ZLIB/ZLIB.h"

#define PNGHeaderSequenz { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n' }

unsigned int BF::PNG::BitsPerPixel()
{
    unsigned int numberOfColorChannels = NumberOfColorChannels(ColorType);

    return BitDepth * numberOfColorChannels;
}

BF::FileActionResult BF::PNG::Load(const char* filePath)
{   
    FileStream fileStream;
    FileActionResult fileActionResult = fileStream.ReadFromDisk(filePath);
    bool parseFinished = false;

    if (fileActionResult != FileActionResult::Successful)
    {
        return fileActionResult;
    }

    // Check Header
    {
        const Byte pngFileHeader[8] = PNGHeaderSequenz;
        bool isValidHeader = fileStream.ReadAndCompare(pngFileHeader, 8u);

        if (!isValidHeader)
        {
            return FileActionResult::FormatNotSupported;
        }
    }
 
    ZLIBHeaderListSize = 0;

    // Fetch data
    while (!parseFinished)
    {
        PNGChunk chunk;

        chunk.ChunkData = fileStream.Data + fileStream.DataCursorPosition;

        fileStream.Read(chunk.Lengh, Endian::Big);
        fileStream.Read(chunk.ChunkTypeRaw, 4u);

        chunk.Check();
     
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
                ++ZLIBHeaderListSize;
                
                fileStream.DataCursorPosition += chunk.Lengh;

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

   

    size_t imageDataIndex = 0;
    ZLIBHeaderList = new ZLIBHeader[ZLIBHeaderListSize];

    if (!ZLIBHeaderList)
    {
        ZLIBHeaderListSize = 0;
        return FileActionResult::OutOfMemory;
    }

    fileStream.DataCursorPosition = 8u;

    parseFinished = false;



    size_t dataIndex = 0;
    PixelDataSize = Width * Height * 4;
    PixelData = (Byte*)malloc(PixelDataSize);

    memset(PixelData, 0xCD, PixelDataSize);

    size_t zlibDataCache = 0;
    unsigned char* zlibCache = nullptr;

    // Fetch data
    while (!parseFinished)
    {
        PNGChunk chunk;

        fileStream.Read(chunk.Lengh, Endian::Big);
        fileStream.Read(chunk.ChunkTypeRaw, 4u);

        chunk.Check();

        //---Get Chunk Data------------------------------------------
        switch (chunk.ChunkType)
        {
            default:
            {
                fileStream.DataCursorPosition += chunk.Lengh;
                break;
            }
            case PNGChunkType::ImageData:
            {
                //ZLIBHeader& zLIBHeader = ZLIBHeaderList[imageDataIndex++];
                unsigned char dataFilder[3000];
                memset(dataFilder, 0xCD, 3000);
    
                unsigned int bpp = BitsPerPixel();
 
                ZLIB::Unpack(fileStream.Data + fileStream.DataCursorPosition, chunk.Lengh, &zlibCache, zlibDataCache);           

                ADAM7::ProcessScanlines(dataFilder, zlibCache, Width, Height, bpp, InterlaceMethod);

                {
                    LodePNGColorMode in;
                    LodePNGColorMode out;

                    memset(&in, 0, sizeof(LodePNGColorMode));
                    memset(&out, 0, sizeof(LodePNGColorMode));

                    in.bitdepth = 8;
                    in.colortype = LCT_RGB;

                    out.bitdepth = 8;
                    out.colortype = LCT_RGBA;

                    PNGColorCompressor::Decompress(PixelData + dataIndex, dataFilder, &out, &in, Width, Height);
                }   

                fileStream.DataCursorPosition += chunk.Lengh;

                break;
            }
            case PNGChunkType::ImageEnd:
            {
                parseFinished = true;
                break;
            }
        }

        fileStream.DataCursorPosition += 4u;
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
