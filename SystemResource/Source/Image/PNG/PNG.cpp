#include "PNG.h"

#include "../../File/File.h"
#include "../../Compression/ZLIB/ZLIBHeader.h"

BF::PNGColorType BF::PNG::ConvertColorType(unsigned int colorType)
{
    switch (colorType)
    {
        case 0u:
            return PNGColorType::Grayscale;

        case 2u:
            return PNGColorType::Truecolor;

        case 3u:
            return PNGColorType::IndexedColor;

        case 4u:
            return PNGColorType::GrayscaleWithAlphaChannel;

        case 6u:
            return PNGColorType::TruecolorWithAlphaChannel;

        default:
            return PNGColorType::InvalidColorType;
    }
}

unsigned int BF::PNG::ConvertColorType(PNGColorType colorType)
{
    switch (colorType)
    {
        default:
        case BF::PNGColorType::InvalidColorType:
            return -1;

        case BF::PNGColorType::Grayscale:
            return 0u;

        case BF::PNGColorType::Truecolor:
            return 2u;

        case BF::PNGColorType::IndexedColor:
            return 3u;

        case BF::PNGColorType::GrayscaleWithAlphaChannel:
            return 4u;

        case BF::PNGColorType::TruecolorWithAlphaChannel:
            return 6u;
    }
}

BF::ResourceLoadingResult BF::PNG::Load(const char* filePath)
{   
    File file(filePath);
    ResourceLoadingResult resourceLoadingResult = file.ReadFromDisk(); 
    bool parseFinished = false;

    if (resourceLoadingResult != ResourceLoadingResult::Successful)
    {
        return resourceLoadingResult;
    }

    // Check Header
    {
        const unsigned char pngFileHeader[8] = { 137u, 'P', 'N', 'G', '\r', '\n', 26u, '\n' }; //  137, 80, 78, 71, 13, 10, 26, 10
        unsigned char expectedHeader[8];

        file.Read(expectedHeader, 8u);

        bool isValidHeader = memcmp(pngFileHeader, expectedHeader, 8u) == 0;

        if (!isValidHeader)
        {
            return ResourceLoadingResult::FormatNotSupported;
        }
    }
 
    ZLIBHeaderListSize = 0;

    // Fetch data
    while (!parseFinished)
    {
        PNGChunk chunk;
        unsigned char chunkTypeBuffer[4];

        file.Read(chunk.Lengh, Endian::Big);
        file.Read(chunkTypeBuffer, 4u);

        chunk.ChunkTypeBlock.Set(chunkTypeBuffer);        
     
        //---Get Chunk Data------------------------------------------
        switch (chunk.ChunkTypeBlock.Type)
        {
            case PNGChunkType::ImageHeader:
            {
                unsigned char colorType = 0;

                file.Read(Width, Endian::Big); // 4 Bytes
                file.Read(Height, Endian::Big); // 4 Bytes

                file.Read(BitDepth); // 1 Byte
                file.Read(colorType); // 1 Byte
                file.Read(CompressionMethod); // 1 Byte
                file.Read(FilterMethod); // 1 Byte
                file.Read(InterlaceMethod); // 1 Byte
    
                ColorType = ConvertColorType(colorType);

                break;
            }
            case PNGChunkType::Palette:
            {
                file.Read(Palette[0]); // Red 	1 byte
                file.Read(Palette[1]); // Green 1 byte
                file.Read(Palette[2]); // Blue 	1 byte

                break;
            }
            case PNGChunkType::ImageData:
            {                
                ++ZLIBHeaderListSize;
                
                file.DataCursorPosition += chunk.Lengh;

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
                file.Read(Gamma, Endian::Big);

                break;
            }
            case PNGChunkType::PrimaryChromaticities:
            {
                file.Read(CromaWhite[0], Endian::Big);
                file.Read(CromaWhite[1], Endian::Big);
                file.Read(CromaRed[0], Endian::Big);
                file.Read(CromaRed[1], Endian::Big);
                file.Read(CromaGreen[0], Endian::Big);
                file.Read(CromaGreen[1], Endian::Big);
                file.Read(CromaBlue[0], Endian::Big);
                file.Read(CromaBlue[1], Endian::Big);

                break;
            }
            case PNGChunkType::StandardRGBColorSpace:
            {
                file.Read(RenderingIntent);

                break;
            }
            case PNGChunkType::EmbeddedICCProfile:
            case PNGChunkType::TextualData:
            case PNGChunkType::CompressedTextualData:
            case PNGChunkType::InternationalTextualData:
            case PNGChunkType::BackgroundColor:
            case PNGChunkType::PhysicalPixelDimensions:
            {
                file.Read(PixelsPerUnit[0], Endian::Big);
                file.Read(PixelsPerUnit[1], Endian::Big);
                file.Read(UnitSpecifier);

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

                    file.Read(calcbyte);

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
                file.DataCursorPosition += chunk.Lengh;
                break;
            }
        }
        //---------------------------------------------------------------

        file.Read(chunk.CRC, Endian::Big); // 4 Bytes
    }

   

    size_t imageDataIndex = 0;
    ZLIBHeaderList = new ZLIBHeader[ZLIBHeaderListSize];

    if (!ZLIBHeaderList)
    {
        ZLIBHeaderListSize = 0;
        return ResourceLoadingResult::OutOfMemory;
    }

    file.DataCursorPosition = 8u;

    parseFinished = false;

    // Fetch data
    while (!parseFinished)
    {
        PNGChunk chunk;
        unsigned char chunkTypeBuffer[4];

        file.Read(chunk.Lengh, Endian::Big);
        file.Read(chunkTypeBuffer, 4u);

        chunk.ChunkTypeBlock.Set(chunkTypeBuffer);

        //---Get Chunk Data------------------------------------------
        switch (chunk.ChunkTypeBlock.Type)
        {
            default:
            {
                file.DataCursorPosition += chunk.Lengh;
                break;
            }
            case PNGChunkType::ImageData:
            {
                ZLIBHeader& ZLIBHeader = ZLIBHeaderList[imageDataIndex++];

                ZLIBHeader.Parse((unsigned char*)file.Data + file.DataCursorPosition, chunk.Lengh);

                file.DataCursorPosition += chunk.Lengh;

                break;
            }
            case PNGChunkType::ImageEnd:
            {
                parseFinished = true;
                break;
            }
        }

        file.DataCursorPosition += 4u;
    }
}

BF::ResourceLoadingResult BF::PNG::Save(const char* filePath)
{
    size_t fileLength = 500;
    File file(filePath, fileLength);

    // Write Header
    {
        const unsigned char pngFileHeader[8] = { 137u, 'P', 'N', 'G', '\r', '\n', 26u, '\n' };

        file.Write((void*)pngFileHeader, 8u);
    }

    // Header
    {
        unsigned char colorType = ConvertColorType(ColorType);

        file.Write(13u, Endian::Big);
        file.Write((void*)"IHDR", 4u);       

        file.Write(Width, Endian::Big);
        file.Write(Height, Endian::Big);

        file.Write(BitDepth);
        file.Write(colorType);
        file.Write(CompressionMethod);
        file.Write(FilterMethod);
        file.Write(InterlaceMethod);   

        file.Write(0u, Endian::Big);
    }


    //---<>---
    {   
        file.Write(0u, Endian::Big);
        file.Write((void*)"IEND", 4u);
        file.Write(2923585666u, Endian::Big);
    }

    file.WriteToDisk();

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::PNG::ConvertTo(Image& image)
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

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::PNG::ConvertFrom(Image& image)
{
    return ResourceLoadingResult::Successful;
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
