#include "M4A.h"

#include <File/File.h>

BF::FileActionResult BF::M4A::Load(const char* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::M4A::Load(const wchar_t* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::M4A::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);
	
	while(!dataStream.IsAtEnd())
	{
		M4AChunk chunk;

		unsigned int chunkSize = 0;
		ByteCluster typePrimaryID;

		dataStream.Read(chunkSize, Endian::Big);
		dataStream.Read(typePrimaryID.Data, 4u);

		const size_t positionPrediction = dataStream.DataCursorPosition + chunkSize - 8;
		const M4AChunkID typePrimary = ConvertM4AChunkID(typePrimaryID.Value);

		printf
		(
			"[M4A] Chunk (%c%c%c%c) %i Bytes\n",
			typePrimaryID[0],
			typePrimaryID[1],
			typePrimaryID[2],
			typePrimaryID[3],
			chunkSize
		);

		switch(typePrimary)
		{
			case BF::M4AChunkID::FTYP:
			{
				unsigned int sizeB = 0;
				char isoSignature[8]; // isom3gp4

				dataStream.Read(chunk.TypeSub, 4);
				dataStream.Read(sizeB, Endian::Big);
				dataStream.Read(isoSignature, 8u);

				break;
			}		
			case BF::M4AChunkID::MDAT:
				break;
			case BF::M4AChunkID::MOOV:
				break;
			case BF::M4AChunkID::PNOT:
				break;
			case BF::M4AChunkID::UDTA:
				break;
			case BF::M4AChunkID::UUID:
				break;
			case BF::M4AChunkID::MOOF:
				break;
			case BF::M4AChunkID::FREE:
				break;
			case BF::M4AChunkID::SKIP:
				break;
			case BF::M4AChunkID::JP2:
				break;
			case BF::M4AChunkID::WIDE:
				break;
			case BF::M4AChunkID::LOAD:
				break;
			case BF::M4AChunkID::CTAB:
				break;
			case BF::M4AChunkID::IMAP:
				break;
			case BF::M4AChunkID::MATT:
				break;
			case BF::M4AChunkID::KMAT:
				break;
			case BF::M4AChunkID::CLIP:
				break;
			case BF::M4AChunkID::CRGN:
				break;
			case BF::M4AChunkID::SYNC:
				break;
			case BF::M4AChunkID::CHAP:
				break;
			case BF::M4AChunkID::TMCD:
				break;
			case BF::M4AChunkID::SCPT:
				break;
			case BF::M4AChunkID::SSRC:
				break;
			case BF::M4AChunkID::PICT:
				break;

			case BF::M4AChunkID::Invalid:
			default:
			{
				// Unhandled chunk
				break;
			}
		}		

		if(dataStream.DataCursorPosition < positionPrediction)
		{
			const unsigned int offset = positionPrediction - dataStream.DataCursorPosition;

			printf("[M4A] Illegal allignment detected! Moving %i Bytes\n", offset);

			dataStream.DataCursorPosition = positionPrediction;
		}
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::M4A::Save(const wchar_t* filePath)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::M4A::ConvertTo(Sound& sound)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::M4A::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}