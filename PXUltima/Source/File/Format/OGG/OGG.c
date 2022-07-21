#include "OGG.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>

#define OGGHeaderSignature { 'O','g','g','S' }

#define OGGHeaderTypeContinuation 0x01
#define OGGHeaderTypeBeginningOfStream 0x02
#define OGGHeaderTypeEndOfStream 0x04

ActionResult OGGParse(OGG* ogg, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;

	MemorySet(ogg, sizeof(ogg), 0);
	*dataRead = 0;
	ParsingStreamConstruct(&parsingStream, data, dataSize);

	while(!ParsingStreamIsAtEnd(&parsingStream))
	{
		OGGPage page;

		//Check OGG Header
		{
			// Header tag does exist multible times.
			// You can refocus it when the file is corrupted.
			const unsigned char* headerSignature[] = OGGHeaderSignature;
			const size_t headerSignatureSize = sizeof(headerSignature);
			const unsigned char validHeaderSignature = ParsingStreamReadAndCompare(&parsingStream, headerSignature, headerSignatureSize);

			if(!validHeaderSignature)
			{
				printf("Chunk Index missing!\n");
				return ResultInvalidHeaderSignature;
			}
		}

		ParsingStreamReadCU(&parsingStream, &page.Version);
		ParsingStreamReadCU(&parsingStream, &page.HeaderType);
		ParsingStreamReadIU(&parsingStream, &page.GranulePosition, EndianLittle);
		ParsingStreamReadIU(&parsingStream, &page.SerialNumber, EndianLittle);
		ParsingStreamReadIU(&parsingStream, &page.SequenceNumber, EndianLittle);
		ParsingStreamReadIU(&parsingStream, &page.CRC32CheckSum, EndianLittle);
		ParsingStreamReadCU(&parsingStream, &page.PageSegments);

		unsigned char segmentSizeList[0xFF];

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
			ParsingStreamReadCU(&parsingStream, &segmentSizeList[i]);

			printf
			(
				"| Segment | %3i/%3i | %3i Bytes %-45s |\n",
				i + 1,
				page.PageSegments,
				segmentSizeList[i],
				""
			);
		}

		for(size_t i = 0; i < page.PageSegments; ++i)
		{
			unsigned char x = segmentSizeList[i];

			for(size_t i = 0; i < x; i++)
			{
				unsigned char* currentPos = ParsingStreamCursorPosition(&parsingStream) + i;

				char print = (*currentPos >= ' ' && *currentPos <= '~') ? *currentPos : '.';

				printf("%c", print);

				if(((i + 1) % 64u) == 0)
				{
					printf("\n");
				}
			}

			printf("\n");

			ParsingStreamCursorAdvance(&parsingStream, x);
		}
	}

	*dataRead = parsingStream.DataCursor;

	return ResultSuccessful;
}