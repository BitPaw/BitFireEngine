#include "FNT.h"

#include <stdio.h>

#include <Text/Text.h>
#include <Memory/Memory.h>
#include <File/ParsingStream.h>

FNTCharacter* FNTGetCharacter(FNT* fnt, const wchar_t character)
{
	if(fnt->FontPageListSize == 0)
	{
		return 0;
	}

	for (size_t pageIndex = 0; pageIndex < fnt->FontPageListSize; ++pageIndex)
	{
		const FNTPage* page = &fnt->FontPageList[pageIndex];

		for (size_t i = 0; i < page->CharacteListSize; ++i)
		{
			const FNTCharacter* bitMapFontCharacter = &page->CharacteList[i];
			const unsigned char target = bitMapFontCharacter->ID;
			const unsigned char isSameCharacter = target == character;

			if (isSameCharacter)
			{
				return bitMapFontCharacter;
			}
		}
	}

	return 0;
}

ActionResult FNTParse(FNT* fnt, const void* fileData, const size_t fileDataSize, size_t* readBytes)
{
	ParsingStream parsingStream;
	FNTPage* currentPage = 0;
	size_t characterIndex = 0;

	ParsingStreamConstruct(&parsingStream, fileData, fileDataSize);
	MemorySet(fnt, sizeof(FNT), 0);
	*readBytes = 0;

	while(!ParsingStreamIsAtEnd(&parsingStream))
	{
		const unsigned char* currentPosition = ParsingStreamCursorPosition(&parsingStream);
		const size_t currentReadableBytes = ParsingStreamRemainingSize(&parsingStream);
		const FNTLineType lineType = PeekLineType(currentPosition, currentReadableBytes);

		switch(lineType)
		{		
			case FNTLineInfo:
			{
				const char parsingData[] = "face=\0size=\0bold=\0italic\0charset=\0unicode=\0stretchH=\0smooth=\0aa=\0padding=\0spacing=\0";
				const char* indexPosition[11];
				const ParsingTokenA parsingTokenList[] =
				{
					{parsingData + 0, &indexPosition[0]},
					{parsingData + 6, &indexPosition[1]},
					{parsingData + 12, &indexPosition[2]},
					{parsingData + 18, &indexPosition[3]},
					{parsingData + 25, &indexPosition[4]},
					{parsingData + 34, &indexPosition[5]},
					{parsingData + 43, &indexPosition[6]},
					{parsingData + 53, &indexPosition[7]},
					{parsingData + 61, &indexPosition[8]},
					{parsingData + 65, &indexPosition[9]},
					{parsingData + 74, &indexPosition[10]}
				};
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingTokenA);

				ParsingStreamCursorAdvance(&parsingStream, 5u);
							
				TextParseFindAllA
				(
					ParsingStreamCursorPosition(&parsingStream),
					ParsingStreamRemainingSize(&parsingStream),
					parsingTokenList,
					values
				);

				TextCopyA(indexPosition[0] + 1, FontNameSize, fnt->Info.Name, FontNameSize);
				TextToIntA(indexPosition[1], 5, &fnt->Info.Size);
				TextToBoolA(indexPosition[2], 5, &fnt->Info.Bold);
				TextToBoolA(indexPosition[3], 5, &fnt->Info.Italic);
				TextCopyA(indexPosition[4] + 1, CharSetNameSize, fnt->Info.CharSet, CharSetNameSize);
				TextToBoolA(indexPosition[5], 5, &fnt->Info.Unicode);
				TextToIntA(indexPosition[6], 5, &fnt->Info.StretchH);
				TextToBoolA(indexPosition[7], 5, &fnt->Info.Smooth);
				TextToBoolA(indexPosition[8], 5, &fnt->Info.Supersampling);

				TextTerminateBeginFromFirstA(fnt->Info.Name, FontNameSize, '\"');
				TextTerminateBeginFromFirstA(fnt->Info.CharSet, CharSetNameSize, '\"');

				break;
			}
			case FNTLineCommon:
			{
				const char parsingData[] = "lineHeight=\0base=\0scaleW=\0scaleH=\0pages=\0packed=\0";
				const char* indexPosition[6];
				const ParsingTokenA parsingTokenList[] =
				{
					{parsingData + 0, &indexPosition[0]},
					{parsingData + 12, &indexPosition[1]},
					{parsingData + 18, &indexPosition[2]},
					{parsingData + 26, &indexPosition[3]},
					{parsingData + 34, &indexPosition[4]},
					{parsingData + 41, &indexPosition[5]}
				};
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingTokenA);

				ParsingStreamCursorAdvance(&parsingStream, 6u);

				TextParseFindAllA
				(
					ParsingStreamCursorPosition(&parsingStream),
					ParsingStreamRemainingSize(&parsingStream),
					parsingTokenList,
					values
				);

				const size_t readableSize = ParsingStreamRemainingSize(&parsingStream);

				TextToIntA(indexPosition[0], readableSize, &fnt->CommonData.LineHeight);
				TextToIntA(indexPosition[1], readableSize, &fnt->CommonData.Base);
				TextToIntA(indexPosition[2], readableSize, &fnt->CommonData.ScaleWidth);
				TextToIntA(indexPosition[3], readableSize, &fnt->CommonData.ScaleHeight);
				TextToIntA(indexPosition[4], readableSize, &fnt->CommonData.AmountOfPages);
				TextToBoolA(indexPosition[5], readableSize, &fnt->CommonData.Packed);

				// Allocate
				{
					const size_t size = fnt->CommonData.AmountOfPages;
					const size_t sizeInBytes = sizeof(FNTPage) * size;
					FNTPage* pageList = MemoryAllocateClear(sizeInBytes);					

					fnt->FontPageListSize = size;
					fnt->FontPageList = pageList;

					currentPage = pageList;
				}

				break;
			}
			case FNTLinePage:
			{
				const char parsingData[] = "id=\0file=";
				const char* indexPosition[2];
				const ParsingTokenA parsingTokenList[] =
				{
					{parsingData + 0, &indexPosition[0]},
					{parsingData + 4, &indexPosition[1]}
				};
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingTokenA);

				ParsingStreamCursorAdvance(&parsingStream, 5u);

				TextParseFindAllA
				(
					ParsingStreamCursorPosition(&parsingStream),
					ParsingStreamRemainingSize(&parsingStream),
					parsingTokenList,
					values
				);

				TextToIntA(indexPosition[0], 5, &currentPage->PageID);
				TextCopyA
				(
					indexPosition[1] + 1,
					ParsingStreamRemainingSize(&parsingStream),
					currentPage->PageFileName,
					FNTPageFileNameSize - 1
				);

				TextTerminateBeginFromFirstA(currentPage->PageFileName, FNTPageFileNameSize, '\"');

				break;
			}
			case FNTLineCharacterCount:
			{
				const char countText[] = "count=";

				ParsingStreamCursorAdvance(&parsingStream, 6u);

				char* count = TextFindPositionA
				(
					ParsingStreamCursorPosition(&parsingStream),
					ParsingStreamRemainingSize(&parsingStream),
					countText, 
					sizeof(countText) - 1
				);

				// Allocate
				{
					int size = 0;

					TextToIntA
					(
						count + sizeof(countText) - 1,
						ParsingStreamRemainingSize(&parsingStream) - sizeof(countText),
						&size
					);

					const size_t sizeInBytes = sizeof(FNTCharacter) * size;

					currentPage->CharacteListSize = size;
					currentPage->CharacteList = MemoryAllocateClear(sizeInBytes);
				}				

				characterIndex = 0;

				break;
			}
			case FNTLineCharacterDefinition:
			{
				const unsigned char acessCharacterOutofBounce = characterIndex >= currentPage->CharacteListSize;

				if(acessCharacterOutofBounce)
				{
					const size_t sizeCurrent = currentPage->CharacteListSize * sizeof(FNTPage);
					const size_t sizeNew = currentPage->CharacteListSize * sizeof(FNTPage) + 1;

					FNTCharacter* characteListR = MemoryReallocateClear(currentPage->CharacteList, sizeCurrent, sizeNew);
					const unsigned char adresschanged = characteListR != currentPage->CharacteList;

					if(!characteListR)
					{
						// Error, out of memeory
					}

					currentPage->CharacteListSize++;
					currentPage->CharacteList = characteListR;
				}

				FNTCharacter* character = &currentPage->CharacteList[characterIndex++];

				const char parsingData[] = "id=\0x=\0y=\0width=\0height=\0xoffset=\0yoffset=\0xadvance=\0page=\0chnl=";
				const char* indexPosition[10];
				const ParsingTokenA parsingTokenList[] =
				{
					{parsingData + 0, &indexPosition[0]},
					{parsingData + 4, &indexPosition[1]},
					{parsingData + 7, &indexPosition[2]},
					{parsingData + 10, &indexPosition[3]},
					{parsingData + 17, &indexPosition[4]},
					{parsingData + 25, &indexPosition[5]},
					{parsingData + 34, &indexPosition[6]},
					{parsingData + 43, &indexPosition[7]},
					{parsingData + 53, &indexPosition[8]},
					{parsingData + 59, &indexPosition[9]}
				};
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingTokenA);

				ParsingStreamCursorAdvance(&parsingStream, 5u);

				TextParseFindAllA
				(
					ParsingStreamCursorPosition(&parsingStream),
					ParsingStreamRemainingSize(&parsingStream),
					parsingTokenList,
					values
				);

				TextToIntA(indexPosition[0], 5, &character->ID);
				TextToFloatA(indexPosition[1], 5, &character->Position[0]);
				TextToFloatA(indexPosition[2], 5, &character->Position[1]);
				TextToFloatA(indexPosition[3], 5, &character->Size[0]);
				TextToFloatA(indexPosition[4], 5, &character->Size[1]);
				TextToFloatA(indexPosition[5], 5, &character->Offset[0]);
				TextToFloatA(indexPosition[6], 5, &character->Offset[1]);
				TextToIntA(indexPosition[7], 5, &character->XAdvance);
				TextToIntA(indexPosition[8], 5, &character->Page);
				TextToIntA(indexPosition[9], 5, &character->Chanal);

				break;
			}
		}

		ParsingStreamSkipLine(&parsingStream);
	}

	*readBytes = parsingStream.DataCursor;

	return ResultSuccessful;
}

FNTLineType PeekLineType(const void* line, const size_t fileDataSize)
{
	const unsigned char* data = line;
	const unsigned char isCommonLine = data[0] == 'c' && data[1] == 'o' && data[2] == 'm' && data[3] == 'm' && data[4] == 'o' && data[5] == 'n' && data[6] == ' ';
	const unsigned char isCharacterCountLine = data[0] == 'c' && data[1] == 'h' && data[2] == 'a' && data[3] == 'r' && data[4] == 's' && data[5] == ' ';
	const unsigned char isCharacterDeclareLine = data[0] == 'c' && data[1] == 'h' && data[2] == 'a' && data[3] == 'r' && data[4] == ' ';
	const unsigned char isInfoLine = data[0] == 'i' && data[1] == 'n' && data[2] == 'f' && data[3] == 'o' && data[4] == ' ';
	const unsigned char isPageLine = data[0] == 'p' && data[1] == 'a' && data[2] == 'g' && data[3] == 'e' && data[4] == ' ';

	unsigned code =
		isCommonLine * 1 +
		isCharacterCountLine * 2 +
		isCharacterDeclareLine * 3 +
		isInfoLine * 4 +
		isPageLine * 5;

	switch(code)
	{
		case 1:
			return FNTLineCommon;

		case 2:
			return FNTLineCharacterCount;

		case 3:
			return FNTLineCharacterDefinition;

		case 4:
			return FNTLineInfo;

		case 5:
			return FNTLinePage;

		default:
			return FNTLineUnkown;
	}

	return ResultSuccessful;
}

void FNTPrtinf(const FNT* fnt)
{
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Font (%s) : %s\n", &fnt->Info.CharSet[0], &fnt->Info.Name[0]);
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Size     : %4u | Smooth  : %3u |\n", fnt->Info.Size, fnt->Info.Smooth);
	printf(" | Bold     : %4s | AA      : %3u |\n", fnt->Info.Bold ? "Yes" : "No", fnt->Info.Supersampling);
	printf
	(
		" | Italic   : %4s | Padding : %u,%u,%u,%u |\n",
		fnt->Info.Italic ? "Yes" : "No",
		fnt->Info.CharacterPadding[0],
		fnt->Info.CharacterPadding[1],
		fnt->Info.CharacterPadding[2],
		fnt->Info.CharacterPadding[3]

	);
	printf(" | unicode  : %4s | Spacing : %u,%u |\n", fnt->Info.Unicode ? "Yes" : "No", fnt->Info.SpacerOffset[0], fnt->Info.SpacerOffset[1]);
	printf(" | stretchH : %4u | Outline : %3u |\n", fnt->Info.StretchH, fnt->Info.OutlineThickness);


	for(unsigned int pageIndex = 0; pageIndex < fnt->FontPageListSize; pageIndex++)
	{
		FNTPage* page = &fnt->FontPageList[pageIndex];

		//printf(" |          |       |       |       |       |       |       |       |\n");
		printf("\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Page <%zu/%zu> %s\n", pageIndex + 1, fnt->FontPageListSize, page->PageFileName);
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Letter   | X-Pos | Y-Pos | Width | Height| X-Off | Y-Off | X-Step|\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");

		for(unsigned int characterIndex = 0; characterIndex < page->CharacteListSize; characterIndex++)
		{
			FNTCharacter* character = &page->CharacteList[characterIndex];

			printf
			(
				" | %3i -> %c | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5i |\n",
				character->ID,
				character->ID,
				character->Position[0],
				character->Position[1],
				character->Size[0],
				character->Size[1],
				character->Offset[0],
				character->Offset[1],
				character->XAdvance
			);
		}

		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
	}
}
