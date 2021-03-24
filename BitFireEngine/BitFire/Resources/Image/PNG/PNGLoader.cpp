#include "PNGLoader.h"
#include "../../../Utility/DoubleWord.h"
#include "../../Compression/Huffman/HuffmanCodeFixed.h"
#include "../../Compression/Deflate/DeflateCompressedBlock.h"
#include "../../Compression/ZLIB/ZLibHeader.h"
#include "../../../Utility/BitStreamHusk.h"
#include "../../../Utility/RingBuffer.hpp"
#include "../../../Utility/ByteStreamHusk.h"

unsigned char BF::PNGLoader::FilterTypePeath(unsigned char leftCell, unsigned char aboveCell, unsigned char upperCell)
{
    unsigned char p = leftCell + aboveCell - upperCell;
    unsigned char pa = abs(p - leftCell);
    unsigned char pb = abs(p - aboveCell);
    unsigned char pc = abs(p - upperCell);

    if (pa <= pb && pa <= pc)
    {
        return leftCell;
    }
    else if (pb <= pc)
    {
        return aboveCell;
    }
    else
    {
        return upperCell;
    }
}

BF::PNGChunkType BF::PNGLoader::ParseChunkType(DoubleWord& doubleWord)
{
    unsigned char& byteA = doubleWord.ByteA;
    unsigned char& byteB = doubleWord.ByteB;
    unsigned char& byteC = doubleWord.ByteC;
    unsigned char& byteD = doubleWord.ByteD;
  
      


    switch (byteA)
    {
        case 'I':
        {
            if (byteB == 'H' && byteC == 'D' && byteD == 'R') return PNGChunkType::ImageHeader;
            if (byteB == 'D' && byteC == 'A' && byteD == 'T') return PNGChunkType::ImageData;
            if (byteB == 'E' && byteC == 'N' && byteD == 'D') return PNGChunkType::ImageEnd;
            break;
        }

        case 'i':
        {
            if (byteB == 'C' && byteC == 'C' && byteD == 'P') return PNGChunkType::EmbeddedICCProfile; // iCCP
            if (byteB == 'T' && byteC == 'X' && byteD == 't') return PNGChunkType::Transparency; // iTXt
            break;
        }

        case 's':
        {
            if (byteB == 'B' && byteC == 'I' && byteD == 'T') return PNGChunkType::SignificantBits; // sBIT
            if (byteB == 'R' && byteC == 'G' && byteD == 'B') return PNGChunkType::StandardRGBColorSpace; // sRGB
            break;
        }

        case 't':
        {
            if (byteB == 'R' && byteC == 'N' && byteD == 'S') return PNGChunkType::Transparency; // tRNS
            if (byteB == 'E' && byteC == 'X' && byteD == 't') return PNGChunkType::Transparency; // tEXt
            if (byteB == 'I' && byteC == 'M' && byteD == 'E') return PNGChunkType::LastModificationTime; // tIME
            break;
        }

        default:
        {
            if (byteA == 'P' && byteB == 'L' && byteC == 'T' && byteD == 'E') return PNGChunkType::Palette;

            if (byteA == 'c' && byteB == 'H' && byteC == 'R' && byteD == 'M') return PNGChunkType::PrimaryChromaticities; // cHRM
            if (byteA == 'g' && byteB == 'A' && byteC == 'M' && byteD == 'A') return PNGChunkType::ImageGamma; // gAMA
            if (byteA == 'b' && byteB == 'K' && byteC == 'G' && byteD == 'D') return PNGChunkType::BackgroundColor; // bKGD
            if (byteA == 'h' && byteB == 'I' && byteC == 'S' && byteD == 'T') return PNGChunkType::PaletteHistogram; // hIST   
            if (byteA == 'p' && byteB == 'H' && byteC == 'Y' && byteD == 's') return PNGChunkType::PhysicalPixelDimensions; //pHYs
            if (byteA == 's' && byteB == 'P' && byteC == 'L' && byteD == 'T') return PNGChunkType::Transparency; // sPLT    
            if (byteA == 'z' && byteB == 'T' && byteC == 'X' && byteD == 't') return PNGChunkType::Transparency; // zTXt

            break;
        }
    } 

    return PNGChunkType::Custom;
}

BF::PNG* BF::PNGLoader::LoadFromFile(AsciiString& filePath)
{
    PNG* png = new PNG();

    LoadFromFile(filePath, *png);

    return png;
}

void BF::PNGLoader::LoadFromFile(AsciiString& filePath, PNG& png)
{   
    AsciiString bytes;
    FileLoader::ReadFileAsBytes(filePath, bytes);

    unsigned char* startAdress = reinterpret_cast<unsigned char*>(&bytes[0]);
    ByteStreamHusk byteStream(startAdress + 8, bytes.Size() -8);

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
        unsigned int chunkLengh = byteStream.ExtractIntegerAndMove();
        unsigned int crc;        
        DoubleWord chunkTypeDword = byteStream.ExtractDoubleWord();
        PNGChunkType chunkType = ParseChunkType(chunkTypeDword);
        
        //----------------------------------------------------------

        printf("| PNG Chunk Type: %c%c%c%c Size: %3u   |\n", chunkTypeDword.ByteA, chunkTypeDword.ByteB, chunkTypeDword.ByteC, chunkTypeDword.ByteD, chunkLengh);

        //---Get Chunk Data------------------------------------------
        switch (chunkType)
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
  
                png.Header.Width = byteStream.ExtractIntegerAndMove(); 
                png.Header.Height = byteStream.ExtractIntegerAndMove();

                png.Header.BitDepth = byteStream.ExtractByteAndMove();
                colorType = byteStream.ExtractByteAndMove();
                png.Header.CompressionMethod = byteStream.ExtractByteAndMove();
                png.Header.FilterMethod = byteStream.ExtractByteAndMove();
                png.Header.InterlaceMethod = byteStream.ExtractByteAndMove();

                switch (colorType)
                {
                    case 0: 
                        png.Header.ColorType = PNGColorType::Grayscale; 
                        break;

                    case 2:
                        png.Header.ColorType = PNGColorType::Truecolor; 
                        break;

                    case 3: 
                        png.Header.ColorType = PNGColorType::IndexedColor; 
                        break;

                    case 4: 
                        png.Header.ColorType = PNGColorType::GrayscaleWithAlphaChannel; 
                        break;

                    case 6: 
                        png.Header.ColorType = PNGColorType::TruecolorWithAlphaChannel; 
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
                png.Palette.Red = byteStream.ExtractByteAndMove();
                png.Palette.Green = byteStream.ExtractByteAndMove();
                png.Palette.Blue = byteStream.ExtractByteAndMove();

                break;
            }
            case PNGChunkType::ImageData:
            {
                bool finished = false;
                unsigned int dataLengh = chunkLengh - 6;
                unsigned int pixelDataIndex = 0;
                unsigned char* startingAdress = reinterpret_cast<unsigned char*>(&byteStream.StartAdress[byteStream.CurrentPosition]); 
                BitStreamHusk bitStream(startingAdress, dataLengh);       
          
                ZLibHeader& zlibHeader = png.zlib;
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
                byteStream.CurrentPosition += chunkLengh-4;

                zlibHeader.Adeler32CheckValue = byteStream.ExtractIntegerAndMove();
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
                    chunkLengh,
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
                png.ImageGamma.Gamma = byteStream.ExtractIntegerAndMove();

                break;
            }
            case PNGChunkType::PrimaryChromaticities:
            {
                png.PrimaryChromaticities.White.X = byteStream.ExtractIntegerAndMove();
                png.PrimaryChromaticities.White.Y = byteStream.ExtractIntegerAndMove();
                png.PrimaryChromaticities.Red.X = byteStream.ExtractIntegerAndMove();
                png.PrimaryChromaticities.Red.Y = byteStream.ExtractIntegerAndMove();
                png.PrimaryChromaticities.Green.X = byteStream.ExtractIntegerAndMove();
                png.PrimaryChromaticities.Green.Y = byteStream.ExtractIntegerAndMove();
                png.PrimaryChromaticities.Blue.X = byteStream.ExtractIntegerAndMove();
                png.PrimaryChromaticities.Blue.Y = byteStream.ExtractIntegerAndMove();
                break;
            }
            case PNGChunkType::StandardRGBColorSpace:
            {
                png.StandardRGBColorSpace.RenderingIntent = byteStream.ExtractByteAndMove();
                break;
            }
            case PNGChunkType::EmbeddedICCProfile:
            case PNGChunkType::TextualData:
            case PNGChunkType::CompressedTextualData:
            case PNGChunkType::InternationalTextualData:
            case PNGChunkType::BackgroundColor:
            case PNGChunkType::PhysicalPixelDimensions:
            {
                png.PhysicalPixelDimensions.PixelsPerUnitXAxis = byteStream.ExtractIntegerAndMove();
                png.PhysicalPixelDimensions.PixelsPerUnitYAxis = byteStream.ExtractIntegerAndMove();
                png.PhysicalPixelDimensions.UnitSpecifier = byteStream.ExtractByteAndMove();

                break;
            }
            case PNGChunkType::SignificantBits:
            {
                unsigned int byteLength = 0;
                unsigned int result = 0;

                switch (png.Header.ColorType)
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

                png.SignificantBits.Data = result;

                break;
            }
            case PNGChunkType::SuggestedPalette:
            case PNGChunkType::PaletteHistogram:
            case PNGChunkType::LastModificationTime:
            case PNGChunkType::Custom:
            default:
            {
                byteStream.CurrentPosition += chunkLengh;
                break;
            }
        }
        //---------------------------------------------------------------

        crc = byteStream.ExtractIntegerAndMove();
    }


    printf
    (
        "+----------------------------------+\n"
    );
}

void BF::PNGLoader::PNGToImage(PNG& png, Image& image)
{
    PNGHeader& header = png.Header;
    unsigned int width = header.Width;
    unsigned int height = header.Height;

    image.Information.Format = ImageFormatMode::RGBA;
    image.Resize(width, height);

    for (size_t y = 0; y < width; y++)
    {      
        for (size_t x = 0; x < height; x++)
        {            
            image.PixelData[x + (y * header.Width) + 0] = Math::RandomeNumber() % 255;
            image.PixelData[x + (y * header.Width) + 1] = Math::RandomeNumber() % 255;
            image.PixelData[x + (y * header.Width) + 2] = Math::RandomeNumber() % 255;
            image.PixelData[x + (y * header.Width) + 3] = 0xFF;
        }
    }
}

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