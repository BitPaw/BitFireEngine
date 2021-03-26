#include "PNG.h"

#include "../../../Utility/BitStreamHusk.h"
#include "../../../Utility/ByteStreamHusk.h"
#include "../../../IO/File/FileLoader.h"

void BF::PNG::Load(AsciiString& filePath)
{
    PNGChunk chunk;
    AsciiString bytes;
    FileLoader::ReadFileAsBytes(filePath, bytes);
    ByteStreamHusk byteStream
    (
        reinterpret_cast<unsigned char*>(&bytes[0]) + 8,
        bytes.Size() - 8
    );

    // Check Header
    {
        unsigned int dynamicIndex = 0;
        const unsigned int fileheaderSize = 8;
        const unsigned char fileHeader[fileheaderSize] = { 137, 80, 78, 71, 13, 10, 26, 10 };

        while (dynamicIndex < fileheaderSize)
        {
            unsigned char target = bytes[dynamicIndex];
            unsigned char source = fileHeader[dynamicIndex];
            bool sameValue = target == source;

            if (!sameValue)
            {
                throw std::exception("Inavlid Header / PNG File");
            }

            dynamicIndex++;
        }
    }

    printf
    (
        "+----------------------------------+\n"
        "| Parsing PNG File...              |\n"
        "+----------------------------------+\n"
    );

    // Fetch data
    while (!byteStream.IsAtEnd())
    {
        chunk.Lengh = byteStream.ExtractIntegerAndMove(EndianType::Big);
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

        //----------------------------------------------------------

        printf
        (
            "| PNG Chunk Type: %c%c%c%c Size: %3u B |\n",
            chunk.ChunkTypeBlock.Value.ByteData[0],
            chunk.ChunkTypeBlock.Value.ByteData[1],
            chunk.ChunkTypeBlock.Value.ByteData[2],
            chunk.ChunkTypeBlock.Value.ByteData[3],
            chunk.Lengh
        );

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

                Width = byteStream.ExtractIntegerAndMove(EndianType::Big);
                Height = byteStream.ExtractIntegerAndMove(EndianType::Big);

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
                Palette.Red = byteStream.ExtractByteAndMove();
                Palette.Green = byteStream.ExtractByteAndMove();
                Palette.Blue = byteStream.ExtractByteAndMove();

                break;
            }
            case PNGChunkType::ImageData:
            {
                bool finished = false;
                unsigned int dataLengh = chunk.Lengh - 6;
                unsigned int pixelDataIndex = 0;
                unsigned char* startingAdress = reinterpret_cast<unsigned char*>(&byteStream.StartAdress[byteStream.CurrentPosition]);
                BitStreamHusk bitStream(startingAdress, dataLengh);

                ZLibHeader& zlibHeader = zlib;
                zlibHeader.CompressionMethod = bitStream.ExtractBitsAndMove(4);
                zlibHeader.CompressionInfo = bitStream.ExtractBitsAndMove(4);
                zlibHeader.Check = bitStream.ExtractBitsAndMove(5);
                zlibHeader.HasDictionary = bitStream.ExtractBitsAndMove(1);
                zlibHeader.Level = bitStream.ExtractBitsAndMove(2);

                List<unsigned char>& rawData = zlibHeader.DeflateCompressedBlock;

                rawData.ReSize(dataLengh);

                for (unsigned int i = 0; i < dataLengh; i++)
                {
                    rawData[i] = bitStream.ExtractBitsAndMove(8);
                }

                //---Here could be decompression----      

                //---------------------------------

                // Allignment = ZLIB Chunk - ADLER32
                byteStream.CurrentPosition += chunk.Lengh - 4;

                zlibHeader.Adeler32CheckValue = byteStream.ExtractIntegerAndMove(EndianType::Big);
                zlibHeader.FillMissingData();

                printf
                (
                    "| zlib Header <%u> Bytes: \n"
                    "| - Compression Method %u\n"
                    "| - Compression Info   %u\n"
                    "| - Check              %u, Valid:%s\n"
                    "| - Dictionary         %s\n"
                    "| - Level              %u\n"
                    "| - Window Size        %u\n"
                    "| - Compressed Data    %u Bytes\n"
                    "| - ADLER23            %u, Valid:%s\n",
                    chunk.Lengh,
                    zlibHeader.CompressionMethod,
                    zlibHeader.CompressionInfo,

                    zlibHeader.Check,
                    zlibHeader.IsCheckValid ? "Yes" : "No",
                    zlibHeader.HasDictionary ? "Yes" : "No",
                    zlibHeader.Level,

                    zlibHeader.LZ77WindowSize,

                    dataLengh,

                    zlibHeader.Adeler32CheckValue,
                    zlibHeader.Adeler32CheckValid ? "Yes" : "No"
                );
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
                Gamma = byteStream.ExtractIntegerAndMove(EndianType::Big);

                break;
            }
            case PNGChunkType::PrimaryChromaticities:
            {
                CromaWhite.X = byteStream.ExtractIntegerAndMove(EndianType::Big);
                CromaWhite.Y = byteStream.ExtractIntegerAndMove(EndianType::Big);
                CromaRed.X = byteStream.ExtractIntegerAndMove(EndianType::Big);
                CromaRed.Y = byteStream.ExtractIntegerAndMove(EndianType::Big);
                CromaGreen.X = byteStream.ExtractIntegerAndMove(EndianType::Big);
                CromaGreen.Y = byteStream.ExtractIntegerAndMove(EndianType::Big);
                CromaBlue.X = byteStream.ExtractIntegerAndMove(EndianType::Big);
                CromaBlue.Y = byteStream.ExtractIntegerAndMove(EndianType::Big);
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
                PixelsPerUnit.X = byteStream.ExtractIntegerAndMove(EndianType::Big);
                PixelsPerUnit.Y = byteStream.ExtractIntegerAndMove(EndianType::Big);
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

        chunk.CRC = byteStream.ExtractIntegerAndMove(EndianType::Big);
    }

    printf
    (
        "+----------------------------------+\n"
    );
}

void BF::PNG::Save(AsciiString& filePath)
{
}

void BF::PNG::Convert(Image& image)
{
	unsigned int width = Width * 256;
	unsigned int height = Height * 256;

	image.Format = ImageFormat::RGBA;
	image.Resize(width, height);
	image.FillRandome();
    /*

    do
    {
        // is set if and only if this is the last block of the data set.
        block.IsLastBlock = bitStream.ExtractBitsAndMove(1);

        switch (bitStream.ExtractBitsAndMove(2))
        {
            case 0:
                block.CompressionType = DeflateCompressionType::None;
                break;

            case 1:
                block.CompressionType = DeflateCompressionType::FixedHuffmanCodes;
                break;

            case 2:
                block.CompressionType = DeflateCompressionType::DynamicHuffmanCodes;
                break;

            case 3:
                block.CompressionType = DeflateCompressionType::Reserved;
                break;
        }

        printf("Deflate Header : Last Block: %s, Type:%u\n", block.IsLastBlock ? "Yes" : "No", block.CompressionType);




        switch (block.CompressionType)
        {
            case DeflateCompressionType::None:
            {
                bitStream.SkipBitsToNextByte(); // // skip any remaining bits in current partially processed byte

                // read LENand NLEN(see next section)
                unsigned char numberOfDataBytes = bitStream.ExtractBitsAndMove(2);
                unsigned char numberOfDataBytesCompliment = bitStream.ExtractBitsAndMove(2);

                // copy LEN bytes of data to output
                for (unsigned int i = 0; i < numberOfDataBytes; i++)
                {
                    pixelDataRow[pixelDataIndex++] = bitStream.ExtractBitsAndMove(8);
                }

                break;
            }

            case DeflateCompressionType::DynamicHuffmanCodes:
            {
                // read representation of code trees(see subsection below)

                /*
                  0 - 15: Represent code lengths of 0 - 15
                 16: Copy the previous code length 3 - 6 times. The next 2 bits indicate repeat length
                                (0 = 3, ... , 3 = 6)
                            Example:  Codes 8, 16 (+2 bits 11),
                            16 (+2 bits 10) will expand to
                            12 code lengths of 8 (1 + 6 + 5)
                17: Repeat a code length of 0 for 3 - 10 times.    (3 bits of length)
                18: Repeat a code length of 0 for 11 - 138 times    (7 bits of length)

                DeflateCompressedBlock block;
                block.NrOfLiteralSymboles = bitStream.ExtractBitsAndMove(5) + 257;
                block.NrOfDistanceSymboles = bitStream.ExtractBitsAndMove(5) + 1;
                block.NrOfCodeSymboles = bitStream.ExtractBitsAndMove(4) + 4;
                block.NrOfPrefixCodes = block.NrOfCodeSymboles * 3;

                unsigned char bitlengh = HuffmanCodeFixed::GetBitLengh(block.NrOfLiteralSymboles);
                unsigned char sizeOfPrefixData = block.NrOfPrefixCodes / 3;
                unsigned char* prefixCodes = new unsigned char[sizeOfPrefixData];

                for (unsigned int i = 0; i < sizeOfPrefixData; i++)
                {
                    unsigned char index = HuffmanCodeFixed::TranslateIndex(i);

                    prefixCodes[index] = bitStream.ExtractBitsAndMove(3);
                }

                * /

                // No break
            }

            case DeflateCompressionType::FixedHuffmanCodes:
            {
                while (true) // loop(until end of block code recognized)
                {
                    //decode literal / length value from input stream
                    unsigned int HLIT = bitStream.ExtractBitsAndMove(5);
                    unsigned int HDIST = bitStream.ExtractBitsAndMove(5);
                    unsigned int HCLEN = bitStream.ExtractBitsAndMove(4);



                    if (HLIT < 256) // value < 256
                    {
                        //  copy value(literal byte) to output stream
                        unsigned char choppedLiteralByte = static_cast<unsigned char>(HLIT);

                        ringBuffer.Push(choppedLiteralByte);  // ????
                    }
                    else
                    {
                        if (HLIT == 256) // value = end of block(256)
                        {
                            break;// from loop
                        }
                        else if (257 < HLIT && HLIT < 285)  // (value = 257..285)
                        {
                            unsigned int decodeRunLength = HuffmanCodeFixed::DecodeRunLength(literalValue, bitStream);
                            unsigned int distSym = HuffmanCodeFixed::DecodeNextSymbol(bitStream);
                            unsigned int dist = HuffmanCodeFixed::DecodeDistance(distSym, bitStream);

                            if (dist < 1 || dist > 32768)
                            {
                                throw "Invalid distance";
                            }


                            ringBuffer.Copy(dist, decodeRunLength, ringBufferResult);

                            /*
                            // decode distance from input stream
                            unsigned int distance = HuffmanCodeFixed::GetBitLengh(5);

                            // move backwards distance bytes in the output stream,
                            // and copy length bytes from this position to the output stream.

                            unsigned int movedIndex = pixelDataIndex - distance;
                            * /
                        }
                    }
                }

                break;
            }

            case DeflateCompressionType::Reserved:
                break;
        }
    }
    while (!compressedBlock.IsLastBlock);

*/
}

void BF::PNG::PrintData()
{
	/*
	printf
	(
	    "+---------------------------+\n"
		"| PNG File                  |\n"
		"+---------------------------+\n"
		"| Width             : %5i |\n"
		"| Height            : %5i |\n"
		"| BitDepth          : %5u |\n"
		"| ColorType         : %5u |\n"
		"| CompressionMethod : %5u |\n"
		"| FilterMethod      : %5u |\n"
		"| InterlaceMethod   : %5u |\n"
		"+---------------------------+\n"
		"| Chunks                    |\n"
		"+---------------------------+\n"
		"| Type %4 s Lengh %4 i      |\n",
		Width,
		Height,
		BitDepth,
		ColorType,
		CompressionMethod,
		FilterMethod,
		InterlaceMethod
	);
	/*
	for (unsigned int i = 0; i < ChunkList.Size(); i++)
	{
		PNGChunk* chunk = &ChunkList[i];

		printf
		(
			"| Type %4s Lengh %4i      |\n",
			
			&chunk->ChunkType,
			chunk->Lengh
		);
	}

	printf("+---------------------------+\n");
	*/
}
