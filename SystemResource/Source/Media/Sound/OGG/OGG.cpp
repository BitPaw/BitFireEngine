#include "OGG.h"

#include <File/File.h>
#include <Media/Sound/OGG/OGGPage.h>
#include <Hardware/Memory/Memory.h>

#define OGGHeaderSignature { 'O','g','g','S' }

#define OGGHeaderTypeContinuation 0x01
#define OGGHeaderTypeBeginningOfStream 0x02
#define OGGHeaderTypeEndOfStream 0x04

enum class OGGHeaderType
{
	Invalid,

	Continuation,
	Beginning,
	End
};

BF::FileActionResult BF::OGG::Load(const char* filePath)
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

BF::FileActionResult BF::OGG::Load(const wchar_t* filePath)
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

BF::FileActionResult BF::OGG::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);

	while(!dataStream.IsAtEnd())
	{
		OGGPage page;	

		//Check OGG Header
		{
			// Header tag does exist multible times.
			// You can refocus it when the file is corrupted.
			const Byte headerSignature[] = OGGHeaderSignature;
			const size_t headerSignatureSize = sizeof(headerSignature);
			const bool validHeaderSignature = dataStream.ReadAndCompare(headerSignature, headerSignatureSize);

			if(!validHeaderSignature)
			{
				printf("Chunk Index missing!\n");
				return FileActionResult::InvalidHeaderSignature;
			}
		}

		dataStream.Read(page.Version);
		dataStream.Read(page.HeaderType);
		dataStream.Read(page.GranulePosition, Endian::Little);
		dataStream.Read(page.SerialNumber, Endian::Little);
		dataStream.Read(page.SequenceNumber, Endian::Little);
		dataStream.Read(page.CRC32CheckSum, Endian::Little);
		dataStream.Read(page.PageSegments);

		Byte segmentSizeList[0xFF];

		printf
		(
			"|         | %7s | %4s | %8s | %6s | %7s | %11s | %4s |\n"
			"|  Chunk  | %7i | %4i | %8zi | %6i | %7i | %11i | %4i |\n",
		
			"Version", 
			"Type",
			"Position",
			"Serial",
			"Sequenc",
			"CRC",
			"Page",

			page.Version,
			page.HeaderType,
			page.GranulePosition,
			page.SerialNumber,
			page.SequenceNumber,
			page.CRC32CheckSum,
			page.PageSegments
		);

		for(size_t i = 0; i < page.PageSegments; ++i)
		{
			dataStream.Read(segmentSizeList[i]);		

			printf
			(
				"| Segment | %3i/%3i | %3i Bytes %-45s |\n",
				i+1,
				page.PageSegments,
				segmentSizeList[i],
				""
			);		
		}

		for(size_t i = 0; i < page.PageSegments; ++i)
		{
			Byte x = segmentSizeList[i];

			for(size_t i = 0; i < x; i++)
			{
				Byte* currentPos = dataStream.CursorCurrentAdress() + i;

				char print = (*currentPos >= ' ' && *currentPos <= '~') ? *currentPos : '.';

				printf("%c", print);				

				if(((i+1) % 64u) == 0)
				{
					printf("\n");
				}
			}		

			printf("\n");

			dataStream.CursorAdvance(x);
		}
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::OGG::Save(const wchar_t* filePath)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::OGG::ConvertTo(Sound& sound)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::OGG::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}