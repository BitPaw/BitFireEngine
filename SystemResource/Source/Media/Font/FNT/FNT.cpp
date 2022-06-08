#include "FNT.h"
#include "FNTCommand.h"
#include "FNTLineType.h"

#include <File/File.h>
#include <Text/Text.h>
#include <File/ParsingToken.h>
#include <Hardware/Memory/Memory.h>

#define InfoLineFace "face"
#define InfoLineSizzeText "size"
#define InfoLineScaleWText "scaleW"
#define InfoLineBoldText "bold"
#define InfoLineItalicText "italic"
#define InfoLineCharsetText "charset"
#define InfoLineUnicodeText "unicode"
#define InfoLineStretchHText "stretchH"
#define InfoLineSmoothText "smooth"
#define InfoLineAAText "aa"
#define InfoLinePaddingText "padding"
#define InfoLineSpacingText "spacing"
#define InfoLineOutlineThicknessText "xxxxx"

BF::FNTCharacter* BF::FNT::GetCharacterPosition(const unsigned char character)
{
	if (FontPageListSize == 0)
	{
		return nullptr;
	}

	const FNTPage& page = FontPageList[0];

	for (size_t i = 0; i < page.CharacteListSize; i++)
	{
		const FNTCharacter& bitMapFontCharacter = page.CharacteList[i];
		const unsigned char target = bitMapFontCharacter.ID;
		const bool isSameCharacter = target == character;

		if (isSameCharacter)
		{
			return &(FNTCharacter&)bitMapFontCharacter;
		}
	}

	return nullptr;
}

BF::FNT::FNT()
{
	FontPageListSize = 0;
	FontPageList = 0;
}

BF::FNT::~FNT()
{
	delete[] FontPageList;
}

BF::FileActionResult BF::FNT::Load(const char* filePath)
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

BF::FileActionResult BF::FNT::Load(const wchar_t* filePath)
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

BF::FileActionResult BF::FNT::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);
	FNTPage* currentPage = nullptr;
	size_t characterIndex = 0;

	while(!dataStream.IsAtEnd())
	{
		const Byte* currentPosition = dataStream.CursorCurrentAdress();
		FNTLineType lineType = ConvertFNTLineType(currentPosition);

		switch(lineType)
		{
			case BF::FNTLineType::Info:
			{
				const char parsingData[] = "face=\0size=\0bold=\0italic\0charset=\0unicode=\0stretchH=\0smooth=\0aa=\0padding=\0spacing=\0";
				const char* indexPosition[11];
				const ParsingToken parsingTokenList[] =
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
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingToken);

				dataStream.CursorAdvance(5u);

				Text::FindAll
				(
					(char*)dataStream.CursorCurrentAdress(),
					dataStream.ReadPossibleSize(),
					parsingTokenList, 
					values
				);

				Text::Copy(indexPosition[0] + 1, FontNameSize, Info.Name, FontNameSize);
				Text::ToInt(indexPosition[1], 5, Info.Size);
				Text::ToBool(indexPosition[2], 5, Info.Bold);
				Text::ToBool(indexPosition[3], 5, Info.Italic);
				Text::Copy(indexPosition[4] + 1, CharSetNameSize, Info.CharSet, CharSetNameSize);
				Text::ToBool(indexPosition[5], 5, Info.Unicode);
				Text::ToInt(indexPosition[6], 5, Info.StretchH);
				Text::ToBool(indexPosition[7], 5, Info.Smooth);
				Text::ToBool(indexPosition[8], 5, Info.Supersampling);

				// TODO: Implement! Soemthing like "Find ',' ?"
				//Text::ToInt(padding + sizeof(paddingText), bufferSize - sizeof(paddingText), Info.CharacterPadding);
				//Text::ToInt(spacing + sizeof(spacingText), bufferSize - sizeof(spacingText), Info.SpacerOffset);
				//Text::ToInt(outlineThickness + sizeof(outlineThicknessText), bufferSize - sizeof(outlineThicknessText), Info.OutlineThickness);

				Text::TerminateBeginFromFirst(Info.Name, FontNameSize, '\"');
				Text::TerminateBeginFromFirst(Info.CharSet, CharSetNameSize, '\"');

				break;
			}
			case BF::FNTLineType::Common:
			{
				const char parsingData[] = "lineHeight=\0base=\0scaleW=\0scaleH=\0pages=\0packed=\0";
				const char* indexPosition[6];
				const ParsingToken parsingTokenList[] =
				{
					{parsingData + 0, &indexPosition[0]},
					{parsingData + 12, &indexPosition[1]},
					{parsingData + 18, &indexPosition[2]},
					{parsingData + 26, &indexPosition[3]},
					{parsingData + 34, &indexPosition[4]},
					{parsingData + 41, &indexPosition[5]}
				};
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingToken);

				dataStream.CursorAdvance(6u);

				Text::FindAll
				(
					(char*)dataStream.CursorCurrentAdress(),
					dataStream.ReadPossibleSize(),
					parsingTokenList,
					values
				);

				Text::ToInt(indexPosition[0], dataStream.ReadPossibleSize(), CommonData.LineHeight);
				Text::ToInt(indexPosition[1], dataStream.ReadPossibleSize(), CommonData.Base);
				Text::ToInt(indexPosition[2], dataStream.ReadPossibleSize(), CommonData.ScaleWidth);
				Text::ToInt(indexPosition[3], dataStream.ReadPossibleSize(), CommonData.ScaleHeight);
				Text::ToInt(indexPosition[4], dataStream.ReadPossibleSize(), CommonData.AmountOfPages);
				Text::ToBool(indexPosition[5], dataStream.ReadPossibleSize(), CommonData.Packed);

				FontPageListSize = CommonData.AmountOfPages;
				FontPageList = new FNTPage[FontPageListSize];

				currentPage = FontPageList;

				break;
			}
			case BF::FNTLineType::Page:
			{
				const char parsingData[] = "id=\0file=";
				const char* indexPosition[2];
				const ParsingToken parsingTokenList[] =
				{
					{parsingData + 0, &indexPosition[0]},
					{parsingData + 4, &indexPosition[1]}
				};
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingToken);

				dataStream.CursorAdvance(5u);

				Text::FindAll
				(
					(char*)dataStream.CursorCurrentAdress(),
					dataStream.ReadPossibleSize(),
					parsingTokenList,
					values
				);

				Text::ToInt(indexPosition[0], 5, currentPage->PageID);
				Text::Copy(indexPosition[1] + 1, dataStream.ReadPossibleSize(), currentPage->PageFileName, FNTPageFileNameSize-1);

				Text::TerminateBeginFromFirst(currentPage->PageFileName, FNTPageFileNameSize, '\"');

				break;
			}
			case BF::FNTLineType::CharacterCount:
			{
				const char countText[] = "count=";

				dataStream.CursorAdvance(6u);

				char* count = Text::FindPosition((char*)dataStream.CursorCurrentAdress(), dataStream.ReadPossibleSize(), countText, sizeof(countText) - 1);
				int size = 0;

				Text::ToInt(count + sizeof(countText) - 1, dataStream.ReadPossibleSize() - sizeof(countText), size);

				currentPage->CharacteListSize = size;
				currentPage->CharacteList = new FNTCharacter[size];

				characterIndex = 0;

				break;
			}
			case BF::FNTLineType::CharacterDefinition:
			{			
				const bool acessCharacterOutofBounce = characterIndex >= currentPage->CharacteListSize;

				if(acessCharacterOutofBounce)
				{
					++currentPage->CharacteListSize;

					FNTCharacter* characteListR = Memory::Reallocate(currentPage->CharacteList, currentPage->CharacteListSize);
					const bool adresschanged = characteListR != currentPage->CharacteList;

					if(!characteListR)
					{
						// Error, out of memeory
					}

					currentPage->CharacteList = characteListR;
				}

				FNTCharacter& character = currentPage->CharacteList[characterIndex++];

				const char parsingData[] = "id=\0x=\0y=\0width=\0height=\0xoffset=\0yoffset=\0xadvance=\0page=\0chnl=";
				const char* indexPosition[10];
				const ParsingToken parsingTokenList[] =
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
				const size_t values = sizeof(parsingTokenList) / sizeof(ParsingToken);

				dataStream.CursorAdvance(5u);			

				Text::FindAll
				(
					(char*)dataStream.CursorCurrentAdress(),
					dataStream.ReadPossibleSize(),
					parsingTokenList,
					values
				);				

				Text::ToInt(indexPosition[0], 5, character.ID);			
				Text::ToFloat(indexPosition[1], 5, character.Position[0]);			
				Text::ToFloat(indexPosition[2], 5, character.Position[1]);			
				Text::ToFloat(indexPosition[3], 5, character.Size[0]);				
				Text::ToFloat(indexPosition[4], 5, character.Size[1]);
				Text::ToFloat(indexPosition[5], 5, character.Offset[0]);
				Text::ToFloat(indexPosition[6], 5, character.Offset[1]);			
				Text::ToInt(indexPosition[7], 5, character.XAdvance);
				Text::ToInt(indexPosition[8], 5, character.Page);
				Text::ToInt(indexPosition[9], 5, character.Chanal);

				break;
			}
			case BF::FNTLineType::Unkown:
			default:
			{
				// Ignore
				break;
			}
		}

		dataStream.SkipLine();
	}

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FNT::Save(const wchar_t* filePath)
{
	File file;	

	// Open file
	{
		const FileActionResult openResult = file.Open(filePath, FileOpenMode::Write);
		const bool sucessful = openResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return openResult;
		}
	}

	file.WriteToDisk
	(
		"info face=\"%s\" size=%i bold=%i italic=%i charset=%s unicode=%i stretchH=%i smooth=%i aa=%i padding=%i,%i,%i,%i spacing=%i,%i",
		Info.Name,
		Info.Size,
		Info.Bold,
		Info.Italic,
		Info.CharSet,
		Info.Unicode,
		Info.StretchH,
		Info.Smooth,
		Info.Supersampling,
		Info.CharacterPadding[0],
		Info.CharacterPadding[1],
		Info.CharacterPadding[2],
		Info.CharacterPadding[3],
		Info.SpacerOffset[0],
		Info.SpacerOffset[1]
	);

	file.WriteToDisk
	(
		"\ncommon lineHeight=%i base=%i scaleW=%i scaleH=%i pages=%i packed=%i",
		CommonData.LineHeight,
		CommonData.Base,
		CommonData.ScaleWidth,
		CommonData.ScaleHeight,
		CommonData.AmountOfPages,
		CommonData.Packed
	);

	for(unsigned int i = 0; i < FontPageListSize; i++)
	{
		FNTPage& page = FontPageList[i];

		file.WriteToDisk
		(
			"\npage id=%i file=\"%s\""
			"\nchars count=%zi",
			page.PageID,
			page.PageFileName,
			page.CharacteListSize
		);

		for(size_t i = 0; i < page.CharacteListSize; i++)
		{
			FNTCharacter& character = page.CharacteList[i];

			file.WriteToDisk
			(
				"\nchar id=%i x=%.2f y=%.2f width=%.2f height=%.2f xoffset=%.2f yoffset=%.2f xadvance=%i page=%i chnl=%i",
				character.ID,
				character.Position[0],
				character.Position[1],
				character.Size[0],
				character.Size[1],
				character.Offset[0],
				character.Offset[1],
				character.XAdvance,
				character.Page,
				character.Chanal
			);
		}
	}	

	// Close file
	{
		const FileActionResult closeResult = file.Close();
		const bool sucessful = closeResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return closeResult;
		}
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::FNT::ConvertTo(Font& font)
{
	unsigned int amountOfResources = FontPageListSize;

	//Text::Copy(font.Name, Info.Name, FNTPageFileNameSize);

	font.BitMapFont = this;
	font.AdditionalResourceListSize = amountOfResources;
	font.CharacterSize = Info.Size;
	font.SizeBetweenLines = CommonData.LineHeight;
	font.AdditionalResourceList = Memory::Allocate<char*>(amountOfResources);

	for (size_t i = 0; i < amountOfResources; i++)
	{
		FNTPage& page = FontPageList[i];
		char* pageFileName = page.PageFileName;
		char* string = Memory::Allocate<char>(FNTPageFileNameSize);

		font.AdditionalResourceList[i] = string;

		Text::Copy(pageFileName, FNTPageFileNameSize, string, FNTPageFileNameSize);
	}

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FNT::ConvertFrom(Font& font)
{
	return BF::FileActionResult::Successful;
}

void BF::FNT::PrintData()
{
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Font (%s) : %s\n", &Info.CharSet[0], &Info.Name[0]);
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Size     : %4u | Smooth  : %3u |\n", Info.Size, Info.Smooth);
	printf(" | Bold     : %4s | AA      : %3u |\n", Info.Bold ? "Yes" : "No", Info.Supersampling);
	printf
	(
		" | Italic   : %4s | Padding : %u,%u,%u,%u |\n",
		Info.Italic ? "Yes" : "No",
		Info.CharacterPadding[0],
		Info.CharacterPadding[1],
		Info.CharacterPadding[2],
		Info.CharacterPadding[3]

	);
	printf(" | unicode  : %4s | Spacing : %u,%u |\n", Info.Unicode ? "Yes" : "No", Info.SpacerOffset[0], Info.SpacerOffset[1]);
	printf(" | stretchH : %4u | Outline : %3u |\n", Info.StretchH, Info.OutlineThickness);


	for (unsigned int pageIndex = 0; pageIndex < FontPageListSize; pageIndex++)
	{
		FNTPage& page = FontPageList[pageIndex];

		//printf(" |          |       |       |       |       |       |       |       |\n");
		printf("\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Page <%zu/%zu> %s\n", pageIndex + 1, FontPageListSize, page.PageFileName);
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Letter   | X-Pos | Y-Pos | Width | Height| X-Off | Y-Off | X-Step|\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");

		for (unsigned int characterIndex = 0; characterIndex < page.CharacteListSize; characterIndex++)
		{
			FNTCharacter& character = page.CharacteList[characterIndex];

			printf
			(
				" | %3i -> %c | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5i |\n",
				character.ID,
				character.ID,
				character.Position[0],
				character.Position[1],
				character.Size[0],
				character.Size[1],
				character.Offset[0],
				character.Offset[1],
				character.XAdvance
			);
		}

		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
	}
}