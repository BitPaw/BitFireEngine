#include "PNG.h"

#include "../../File/FileStream.h"
#include "../../Compression/ZLIB/ZLIBHeader.h"

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
        const unsigned char pngFileHeader[8] = { 137u, 'P', 'N', 'G', '\r', '\n', 26u, '\n' }; //  137, 80, 78, 71, 13, 10, 26, 10
        unsigned char expectedHeader[8];

        fileStream.Read(expectedHeader, 8u);

        bool isValidHeader = memcmp(pngFileHeader, expectedHeader, 8u) == 0;

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
        unsigned char chunkTypeBuffer[4];

        fileStream.Read(chunk.Lengh, Endian::Big);
        fileStream.Read(chunkTypeBuffer, 4u);

        chunk.ChunkTypeBlock.Set(chunkTypeBuffer);        
     
        //---Get Chunk Data------------------------------------------
        switch (chunk.ChunkTypeBlock.Type)
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
                fileStream.Read(Palette[0]); // Red 	1 byte
                fileStream.Read(Palette[1]); // Green 1 byte
                fileStream.Read(Palette[2]); // Blue 	1 byte

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

    // Fetch data
    while (!parseFinished)
    {
        PNGChunk chunk;
        unsigned char chunkTypeBuffer[4];

        fileStream.Read(chunk.Lengh, Endian::Big);
        fileStream.Read(chunkTypeBuffer, 4u);

        chunk.ChunkTypeBlock.Set(chunkTypeBuffer);

        //---Get Chunk Data------------------------------------------
        switch (chunk.ChunkTypeBlock.Type)
        {
            default:
            {
                fileStream.DataCursorPosition += chunk.Lengh;
                break;
            }
            case PNGChunkType::ImageData:
            {
                ZLIBHeader& ZLIBHeader = ZLIBHeaderList[imageDataIndex++];

                ZLIBHeader.Parse((unsigned char*)fileStream.Data + fileStream.DataCursorPosition, chunk.Lengh);

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
        const unsigned char pngFileHeader[8] = { 137u, 'P', 'N', 'G', '\r', '\n', 26u, '\n' };

        fileStream.Write((void*)pngFileHeader, 8u);
    }

    // Header
    {
        unsigned char colorType = ConvertColorType(ColorType);

        fileStream.Write(13u, Endian::Big);
        fileStream.Write((void*)"IHDR", 4u);

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
    unsigned char* pixelData = image.PixelData;
    unsigned int width = Width;
	unsigned int height = Height;
    unsigned int pIndex = 0;

	image.Format = ImageDataFormat::RGBA;
	image.Resize(width, height);
	

    for (size_t i = 0; i < ZLIBHeaderListSize; i++)
    {
        ZLIBHeader& zlibHeader = ZLIBHeaderList[i];
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::PNG::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}

void BF::PNG::PrintData()
{
    const char* colorType;
    const char* compressionMethod;
    const char* filterMethod;
    const char* interlaceMethod;

    switch (ColorType)
    {
        case PNGColorType::Grayscale:
            colorType = "Grayscale";
            break;
        case PNGColorType::Truecolor:
            colorType = "Truecolor";
            break;
        case PNGColorType::IndexedColor:
            colorType = "Indexed Color";
            break;
        case PNGColorType::GrayscaleWithAlphaChannel:
            colorType = "Grayscale with AlphaChannel";
            break;
        case PNGColorType::TruecolorWithAlphaChannel:
            colorType = "Truecolor with AlphaChannel";
            break;

        default:
            colorType = "Error";
            break;
    }

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
