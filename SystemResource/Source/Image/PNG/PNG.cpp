#include "PNG.h"

#include "../../File/File.h"

#include "../../Compression/ZLib.h"
#include "../../Container/BitStreamHusk.h"
#include "../../Container/ByteStreamHusk.h"
#include "ZLIBHeader.h"

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

void BF::PNG::Load(const char* filePath)
{
    PNGChunk chunk;
    File file(filePath);
    ResourceLoadingResult resourceLoadingResult = file.ReadFromDisk();
    ByteStreamHusk byteStream(file.Data, file.DataSize);

    if (resourceLoadingResult != ResourceLoadingResult::Successful)
    {
        return;// resourceLoadingResult;
    }

    // Check Header
    {
        const unsigned char pngFileHeader[8] = { 137u, 'P', 'N', 'G', '\r', '\n', 26u, '\n' }; //  137, 80, 78, 71, 13, 10, 26, 10

        bool isValidHeader = memcmp(pngFileHeader, &byteStream.StartAdress[0], 8) == 0;

        byteStream.CurrentPosition += 8u;

        if (!isValidHeader)
        {
            throw std::exception("Inavlid Header / PNG File");
        }
    }
 
    // Fetch data
    while (!byteStream.IsAtEnd())
    {
        unsigned char chunkTypeBuffer[4];

        chunk.Lengh = byteStream.ExtractIntegerAndMove(Endian::Big);

        byteStream.CopyBytesAndMove(chunkTypeBuffer, 4u);

        chunk.ChunkTypeBlock.Set(chunkTypeBuffer);
        
     
        //---Get Chunk Data------------------------------------------
        switch (chunk.ChunkTypeBlock.Type)
        {
            case PNGChunkType::ImageHeader:
            {
                unsigned int colorType;

                /*
                    Width 	4 bytes
                    Height 	4 bytes
                    Bit depth 	1 byte
                    Colour type 	1 byte
                    Compression method 	1 byte
                    Filter method 	1 byte
                    Interlace method 	1 byte
                */

                Width = byteStream.ExtractIntegerAndMove(Endian::Big);
                Height = byteStream.ExtractIntegerAndMove(Endian::Big);

                BitDepth = byteStream.ExtractByteAndMove();
                colorType = byteStream.ExtractByteAndMove();
                CompressionMethod = byteStream.ExtractByteAndMove();
                FilterMethod = byteStream.ExtractByteAndMove();
                InterlaceMethod = byteStream.ExtractByteAndMove();

                ColorType = ConvertColorType(colorType);

                break;
            }
            case PNGChunkType::Palette:
            {
                /*
                Red 	1 byte
                Green 	1 byte
                Blue 	1 byte
                */
                Palette[0] = byteStream.ExtractByteAndMove();
                Palette[1] = byteStream.ExtractByteAndMove();
                Palette[2] = byteStream.ExtractByteAndMove();

                break;
            }
            case PNGChunkType::ImageData:
            {
                unsigned char imageDataBuffer[8512];
                unsigned char compressedData[32768];

                byteStream.CopyBytesAndMove(imageDataBuffer, chunk.Lengh);
                
               // unsigned char adresssss = compressedBytes[0];

               // BitStreamHusk bitStreamHusk(, chunk.Lengh);


                // ZLIB

                unsigned char cmfTag = imageDataBuffer[0];
                ZLIBHeader zlibHedare;
       
                zlibHedare.Parse(imageDataBuffer, chunk.Lengh);

               

                //CompressedData.Add(compressedBytes);           
                
                break;
            }
            case PNGChunkType::ImageEnd:
            {
                // Empty, no data
                break;
            }
            case PNGChunkType::Transparency:
            {


                break;
            }
            case PNGChunkType::ImageGamma:
            {
                // sample = lightoutgamma ???
                Gamma = byteStream.ExtractIntegerAndMove(Endian::Big);

                break;
            }
            case PNGChunkType::PrimaryChromaticities:
            {
                CromaWhite[0] = byteStream.ExtractIntegerAndMove(Endian::Big);
                CromaWhite[1] = byteStream.ExtractIntegerAndMove(Endian::Big);
                CromaRed[0] = byteStream.ExtractIntegerAndMove(Endian::Big);
                CromaRed[1] = byteStream.ExtractIntegerAndMove(Endian::Big);
                CromaGreen[0] = byteStream.ExtractIntegerAndMove(Endian::Big);
                CromaGreen[1] = byteStream.ExtractIntegerAndMove(Endian::Big);
                CromaBlue[0] = byteStream.ExtractIntegerAndMove(Endian::Big);
                CromaBlue[1] = byteStream.ExtractIntegerAndMove(Endian::Big);
                break;
            }
            case PNGChunkType::StandardRGBColorSpace:
            {
                RenderingIntent = byteStream.ExtractByteAndMove();
                break;
            }
            case PNGChunkType::EmbeddedICCProfile:
            case PNGChunkType::TextualData:
            case PNGChunkType::CompressedTextualData:
            case PNGChunkType::InternationalTextualData:
            case PNGChunkType::BackgroundColor:
            case PNGChunkType::PhysicalPixelDimensions:
            {
                PixelsPerUnit[0] = byteStream.ExtractIntegerAndMove(Endian::Big);
                PixelsPerUnit[1] = byteStream.ExtractIntegerAndMove(Endian::Big);
                UnitSpecifier = byteStream.ExtractByteAndMove();

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
                    result = (result << (i * 8)) | byteStream.ExtractByteAndMove();
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
                byteStream.CurrentPosition += chunk.Lengh;
                break;
            }
        }
        //---------------------------------------------------------------

        chunk.CRC = byteStream.ExtractIntegerAndMove(Endian::Big);
    }
}

void BF::PNG::Save(const char* filePath)
{
    unsigned int fileLength = 500;
    char* data = (char*)malloc(fileLength * sizeof(char));
    ByteStreamHusk byteStreamHusk(data, fileLength);

    const unsigned char pngFileHeader[8] = { 137u, 'P', 'N', 'G', '\r', '\n', 26u, '\n' };

    byteStreamHusk.InsertArrayAndMove((void*)pngFileHeader, 8);

    // Data Stuff

    File::WriteToDisk(filePath, data, fileLength);
}

void BF::PNG::Convert(Image& image)
{
    PrintData();
    unsigned char* pixelData = image.PixelData;
    auto compressedDataRow = CompressedData[0];
	unsigned int width = Width;
	unsigned int height = Height;
    unsigned int pIndex = 0;

	image.Format = ImageFormat::RGBA;
	image.Resize(width, height);
	//image.FillRandome();

    const char* compressedFilePath = "zlibCompressed_TempDump.bin";
    const char* unCompressedFilePath = "zlibUncompressed_TempDump.bin";

    while (compressedDataRow != nullptr)
    {
        List<unsigned char>* data = compressedDataRow->Element;
        //File::ExtractAndSave(compressedFilePath, &(*data)[0], data->Size());

        ZLib::Decompress(&compressedFilePath[0], &unCompressedFilePath[0]);

        File zlibDecompressedFile(unCompressedFilePath);
        zlibDecompressedFile.ReadFromDisk();

        File::Remove(compressedFilePath);
        File::Remove(unCompressedFilePath);    

        for (size_t i = 0; i < zlibDecompressedFile.DataSize; )
        {
            i++;

            for (size_t w = 0; w < Width; w++)
            {
                pixelData[pIndex++] = zlibDecompressedFile.Data[i++];
                pixelData[pIndex++] = zlibDecompressedFile.Data[i++];
                pixelData[pIndex++] = zlibDecompressedFile.Data[i++];
                pixelData[pIndex++] = zlibDecompressedFile.Data[i++];
                //printf("%2x %2x %2x %2x\n", UncompressedPixelData[pIndex - 4], UncompressedPixelData[pIndex - 3], UncompressedPixelData[pIndex - 2], UncompressedPixelData[pIndex - 1]);
            }
        }

        compressedDataRow = compressedDataRow->Next;
    }     
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
