#include "PNG.h"

#include "../../File/File.h"

#include "../../Compression/ZLib.h"
#include "../../Container/BitStreamHusk.h"
#include "../../Container/ByteStreamHusk.h"

void BF::PNG::Load(const char* filePath)
{
    PNGChunk chunk;
    File file(filePath);
    file.Read();
    ByteStreamHusk byteStream
    (
        reinterpret_cast<unsigned char*>(file.Data),
        file.Size
    );      

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
        chunk.Lengh = byteStream.ExtractIntegerAndMove(Endian::Big);
        chunk.ChunkTypeBlock.Value = byteStream.ExtractDoubleWord();
        chunk.ChunkTypeBlock.Type = PNGChunkType::Custom;
        
        // Parse Chunk Type
        {
            PNGChunkType& chunkType = chunk.ChunkTypeBlock.Type;
            unsigned char& byteA = chunk.ChunkTypeBlock.Value.ByteData[0];
            unsigned char& byteB = chunk.ChunkTypeBlock.Value.ByteData[1];
            unsigned char& byteC = chunk.ChunkTypeBlock.Value.ByteData[2];
            unsigned char& byteD = chunk.ChunkTypeBlock.Value.ByteData[3];
            switch (byteA)
            {
                case 'I':
                {
                    if (byteB == 'H' && byteC == 'D' && byteD == 'R') chunkType = PNGChunkType::ImageHeader;
                    if (byteB == 'D' && byteC == 'A' && byteD == 'T') chunkType = PNGChunkType::ImageData;
                    if (byteB == 'E' && byteC == 'N' && byteD == 'D') chunkType = PNGChunkType::ImageEnd;
                    break;
                }

                case 'i':
                {
                    if (byteB == 'C' && byteC == 'C' && byteD == 'P') chunkType = PNGChunkType::EmbeddedICCProfile; // iCCP
                    if (byteB == 'T' && byteC == 'X' && byteD == 't') chunkType = PNGChunkType::Transparency; // iTXt
                    break;
                }

                case 's':
                {
                    if (byteB == 'B' && byteC == 'I' && byteD == 'T') chunkType = PNGChunkType::SignificantBits; // sBIT
                    if (byteB == 'R' && byteC == 'G' && byteD == 'B') chunkType = PNGChunkType::StandardRGBColorSpace; // sRGB
                    break;
                }

                case 't':
                {
                    if (byteB == 'R' && byteC == 'N' && byteD == 'S') chunkType = PNGChunkType::Transparency; // tRNS
                    if (byteB == 'E' && byteC == 'X' && byteD == 't') chunkType = PNGChunkType::Transparency; // tEXt
                    if (byteB == 'I' && byteC == 'M' && byteD == 'E') chunkType = PNGChunkType::LastModificationTime; // tIME
                    break;
                }

                default:
                {
                    if (byteA == 'P' && byteB == 'L' && byteC == 'T' && byteD == 'E') chunkType = PNGChunkType::Palette;

                    if (byteA == 'c' && byteB == 'H' && byteC == 'R' && byteD == 'M') chunkType = PNGChunkType::PrimaryChromaticities; // cHRM
                    if (byteA == 'g' && byteB == 'A' && byteC == 'M' && byteD == 'A') chunkType = PNGChunkType::ImageGamma; // gAMA
                    if (byteA == 'b' && byteB == 'K' && byteC == 'G' && byteD == 'D') chunkType = PNGChunkType::BackgroundColor; // bKGD
                    if (byteA == 'h' && byteB == 'I' && byteC == 'S' && byteD == 'T') chunkType = PNGChunkType::PaletteHistogram; // hIST   
                    if (byteA == 'p' && byteB == 'H' && byteC == 'Y' && byteD == 's') chunkType = PNGChunkType::PhysicalPixelDimensions; //pHYs
                    if (byteA == 's' && byteB == 'P' && byteC == 'L' && byteD == 'T') chunkType = PNGChunkType::Transparency; // sPLT    
                    if (byteA == 'z' && byteB == 'T' && byteC == 'X' && byteD == 't') chunkType = PNGChunkType::Transparency; // zTXt

                    break;
                }
            }
        }

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

                switch (colorType)
                {
                    case 0:
                        ColorType = PNGColorType::Grayscale;
                        break;

                    case 2:
                        ColorType = PNGColorType::Truecolor;
                        break;

                    case 3:
                        ColorType = PNGColorType::IndexedColor;
                        break;

                    case 4:
                        ColorType = PNGColorType::GrayscaleWithAlphaChannel;
                        break;

                    case 6:
                        ColorType = PNGColorType::TruecolorWithAlphaChannel;
                        break;
                }

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
                List<unsigned char>* compressedBytes = new List<unsigned char>(chunk.Lengh);

                byteStream.CopyBytesAndMove(&(*compressedBytes)[0], chunk.Lengh);
                
                CompressedData.Add(compressedBytes);           
                
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

    File::Write(filePath, data, fileLength);
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
        File::ExtractAndSave(compressedFilePath, &(*data)[0], data->Size());

        ZLib::Decompress(&compressedFilePath[0], &unCompressedFilePath[0]);

        File zlibDecompressedFile(unCompressedFilePath);
        zlibDecompressedFile.Read();

        File::Remove(compressedFilePath);
        File::Remove(unCompressedFilePath);    

        for (size_t i = 0; i < zlibDecompressedFile.Size; )
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
