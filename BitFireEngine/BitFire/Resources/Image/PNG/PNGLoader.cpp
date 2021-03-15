#include "PNGLoader.h"

BF::PNG* BF::PNGLoader::LoadFromFile(ASCIIString& filePath)
{
    PNG* png = new PNG(); 
        
    // Read Data & Save into png
    {
        ByteString bytes;
            
        FileLoader::ReadFileAsBytes(filePath, bytes);
        unsigned char dynamicIndex = 0;
        unsigned int chunkIndex = 0;
        const unsigned int fileheaderSize = 8;
        const unsigned char fileHeader[fileheaderSize]{ 137, 80, 78, 71, 13, 10, 26, 10 };

        png->ChunkList.ReSize(2);

        // Check Header
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

        // Fetch data
        while (dynamicIndex < bytes.Size())
        {
            PNGChunk* chunk = &png->ChunkList[chunkIndex++];

            if (chunkIndex ==3)
            {
                break;
            }

            unsigned int chunkLengh = ByteString::ToUnsignedInt
            (
                EndianType::Big,
                bytes[dynamicIndex++],
                bytes[dynamicIndex++],
                bytes[dynamicIndex++],
                bytes[dynamicIndex++]
            );

            chunk->Lengh = chunkLengh;

            chunk->ChunkType[0] = bytes[dynamicIndex++];
            chunk->ChunkType[1] = bytes[dynamicIndex++];
            chunk->ChunkType[2] = bytes[dynamicIndex++];
            chunk->ChunkType[3] = bytes[dynamicIndex++];

            // Get Chunk Data
            if (chunkLengh > 0)
            {
                chunk->ChunkData.ReSize(chunkLengh);

                for (unsigned int i = 0; i < chunkLengh; i++)
                {
                    chunk->ChunkData[i] = bytes[dynamicIndex++];
                }
            }

            chunk->CRC = ByteString::ToUnsignedInt
            (
                EndianType::Big,
                bytes[dynamicIndex++],
                bytes[dynamicIndex++],
                bytes[dynamicIndex++],
                bytes[dynamicIndex++]
            );
        }
    }

    /* Compute Chunks
    {
        PNGHeader* header = &png->Header;

        // Check Image Header
        header->Width = ByteString::ToUnsignedInt
        (
            EndianType::Little,
            bytes[dynamicIndex++],
            bytes[dynamicIndex++]
        );

        header->Height = ByteString::ToUnsignedInt
        (
            EndianType::Little,
            bytes[dynamicIndex++],
            bytes[dynamicIndex++]
        );

        header->BitDepth = bytes[dynamicIndex++];
        header->ColorType = bytes[dynamicIndex++];
        header->CompressionMethod = bytes[dynamicIndex++];
        header->FilterMethod = bytes[dynamicIndex++];
        header->InterlaceMethod = bytes[dynamicIndex++];
    }*/

    return png;
}
