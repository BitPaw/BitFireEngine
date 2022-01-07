#include "FNT.h"
#include "FNTCommand.h"

#include "../../File/FileStream.h"
#include "../../File/File.h"
#include "../../File/Text.h"

BF::FNTCharacter* BF::FNT::GetCharacterPosition(unsigned char character)
{
	FNTPage& page = FontPageList[0];

	for (unsigned int i = 0; i < page.CharacteListSize; i++)
	{
		FNTCharacter* bitMapFontCharacter = &page.CharacteList[i];
		unsigned char target = bitMapFontCharacter->ID;

		bool isSameCharacter = target == character;

		if (isSameCharacter)
		{
			return bitMapFontCharacter;
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

BF::FileActionResult BF::FNT::Load(const wchar_t* filePath)
{
	AsciiString dataString;
	AsciiString referenceSting;
	FNTPage* currentPage = nullptr;

	char currentCursor[2048];
	char textCharacter[120];
	int pageCounter = 0;
	char hasCommas = 0;
	bool stopFlag = false;
	int characterCounter = 0;
	int dynamicIndex = 0;

	FileStream file;
	FileActionResult fileActionResult = file.ReadFromDisk(filePath);

	if (fileActionResult != FileActionResult::Successful)
	{
		return fileActionResult;
	}

	// HARD CODED
	FontPageListSize = 1;
	FontPageList = new FNTPage[FontPageListSize];
	//----

	while (true)
	{
		bool hasLine = file.ReadNextLineInto(currentCursor);

		if (!hasLine)
		{
			break;
		}

		bool isInfoLine = memcmp(currentCursor, "info", 4) == 0;
		bool isCommonLine = memcmp(currentCursor, "common", 6) == 0;
		bool isPageLine = memcmp(currentCursor, "page", 4) == 0;
		bool isCharacterCountLine = memcmp(currentCursor, "chars", 5) == 0;
		bool isCharacterDeclareLine = memcmp(currentCursor, "char ", 5) == 0;

		dataString.SetAsReference(currentCursor);

		if (isInfoLine)
		{
			char textName[20];
			char textCharSet[10];
			char size[20];
			char bold[20];
			char italic[20];
			char unicode[20];
			char stretchH[20];
			char smooth[20];
			char aa[20];
			char padding[20];
			char spacing[20];
			char outlineThickness[20];

			dataString.ReplaceWhiteSpaceInQuotes('\xFE', false);

			memset(Info.Name, 0, 30);
			memset(Info.CharSet, 0, 10);

			//AsciiString::Parse
			int scannedObjects = sscanf
			(
				currentCursor,
				"%s %s %s %s %s %s %s %s %s %s %s %s %s",
				textCharacter,
				textName,
				size,
				bold,
				italic,
				textCharSet,
				unicode,
				stretchH,
				smooth,
				aa,
				padding,
				spacing,
				outlineThickness
			);

			AsciiString reData;

			referenceSting.SetAsReference(textName);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			referenceSting.ReplaceWhiteSpaceInQuotes('\xFE', true);

			memcpy(Info.Name, &referenceSting[1], referenceSting.Size() - 2);

			referenceSting.SetAsReference(textCharSet);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			referenceSting.ReplaceWhiteSpaceInQuotes('\xFE', true);

			memcpy(Info.CharSet, &referenceSting[1], referenceSting.Size() - 2);

			referenceSting.SetAsReference(size);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Info.Size = referenceSting.ToInt();

			referenceSting.SetAsReference(bold);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Info.Bold = referenceSting.ToBool();

			referenceSting.SetAsReference(italic);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Info.Italic = referenceSting.ToBool();

			referenceSting.SetAsReference(unicode);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Info.Unicode = referenceSting.ToBool();

			referenceSting.SetAsReference(stretchH);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Info.StretchH = referenceSting.ToInt();

			referenceSting.SetAsReference(smooth);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Info.Smooth = referenceSting.ToBool();

			referenceSting.SetAsReference(aa);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Info.Supersampling = referenceSting.ToBool();

			if (scannedObjects == 13)
			{
				referenceSting.SetAsReference(outlineThickness);
				referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
				Info.OutlineThickness = referenceSting.ToInt();
			}
		}

		if (isCommonLine)
		{
			char lineHeight[20];
			char base[20];
			char scaleW[20];
			char scaleH[20];
			char pages[20];
			char packed[20];

			int scannedObjects = sscanf
			(
				currentCursor,
				"%s %s %s %s %s %s %s",
				textCharacter,
				lineHeight,
				base,
				scaleW,
				scaleH,
				pages,
				packed
			);

			referenceSting.SetAsReference(lineHeight);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			CommonData.LineHeight = referenceSting.ToInt();

			referenceSting.SetAsReference(base);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			CommonData.Base = referenceSting.ToInt();

			referenceSting.SetAsReference(scaleW);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			CommonData.ScaleWidth = referenceSting.ToInt();

			referenceSting.SetAsReference(scaleH);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			CommonData.ScaleHeight = referenceSting.ToInt();

			referenceSting.SetAsReference(pages);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			CommonData.AmountOfPages = referenceSting.ToInt();

			referenceSting.SetAsReference(packed);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			CommonData.Packed = referenceSting.ToBool();
		}

		if (isPageLine)
		{
			char textPageID[30];
			char imageFileName[40];

			currentPage = &FontPageList[pageCounter++];

			dataString.ReplaceWhiteSpaceInQuotes('\xFE', false);

			int scannedObjects = sscanf(currentCursor, "%s %s %s", textCharacter, textPageID, imageFileName);

			dataString.ReplaceWhiteSpaceInQuotes('\xFE', true);

			referenceSting.SetAsReference(textPageID);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			currentPage->PageID = referenceSting.ToInt();


			AsciiString nameExtract(imageFileName);

			int startIndex = nameExtract.FindFirst('\"') + 1;
			int endIndex = nameExtract.FindLast('\"');
			int length = endIndex - startIndex;

			memcpy(currentPage->PageFileName, &imageFileName[startIndex], length);
			currentPage->PageFileName[length] = '\0';
		}

		if (isCharacterCountLine)
		{
			char count[12];
			int numberOfChars = 0;

			int scannedObjects = sscanf(currentCursor, "%s %s", textCharacter, count);

			referenceSting.SetAsReference(count);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			numberOfChars = referenceSting.ToInt();

			currentPage->CharacteListSize = numberOfChars;
			currentPage->CharacteList = new FNTCharacter[numberOfChars];
		}

		if (isCharacterDeclareLine)
		{
			FNTCharacter& character = currentPage->CharacteList[characterCounter++];
			char textID[20];
			char textX[20];
			char textY[20];
			char textWidth[20];
			char textHeiht[20];
			char textXOffset[20];
			char textYOffset[20];
			char textXAdvance[20];
			char textPage[20];
			char textChanel[20];

			int scannedObjects = sscanf
			(
				currentCursor,
				"%s %s %s %s %s %s %s %s %s %s %s",
				textCharacter,
				textID,
				textX,
				textY,
				textWidth,
				textHeiht,
				textXOffset,
				textYOffset,
				textXAdvance,
				textPage,
				textChanel
			);

			referenceSting.SetAsReference(textID);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.ID = referenceSting.ToInt();

			referenceSting.SetAsReference(textX);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Position[0] = referenceSting.ToFloat();

			referenceSting.SetAsReference(textY);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Position[1] = referenceSting.ToFloat();

			referenceSting.SetAsReference(textWidth);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Size[0] = referenceSting.ToFloat();

			referenceSting.SetAsReference(textHeiht);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Size[1] = referenceSting.ToFloat();

			referenceSting.SetAsReference(textXOffset);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Offset[0] = referenceSting.ToFloat();

			referenceSting.SetAsReference(textYOffset);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Offset[1] = referenceSting.ToFloat();

			referenceSting.SetAsReference(textXAdvance);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.XAdvance = referenceSting.ToFloat();

			referenceSting.SetAsReference(textPage);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Page = referenceSting.ToInt();

			referenceSting.SetAsReference(textChanel);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			character.Chanal = referenceSting.ToInt();

		}
	}

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FNT::Save(const wchar_t* filePath)
{
	int characterWritten = 0;
	
	File file;
	file.Open(filePath, FileOpenMode::Write);

	characterWritten = fprintf
	(
		file.FileMarker,
		"info face=\"%s\" size=%i bold=%i italic=%i charset=%s unicode=%i stretchH=%i smooth=%i aa=%i padding=%i,%i,%i,%i spacing=%i,%i\n",
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

	characterWritten = fprintf
	(
		file.FileMarker,
		"common lineHeight=%i base=%i scaleW=%i scaleH=%i pages=%i packed=%i\n",
		CommonData.LineHeight,
		CommonData.Base,
		CommonData.ScaleWidth,
		CommonData.ScaleHeight,
		CommonData.AmountOfPages,
		CommonData.Packed
	);

	for (unsigned int i = 0; i < FontPageListSize; i++)
	{
		FNTPage& page = FontPageList[i];

		characterWritten = fprintf
		(
			file.FileMarker,
			"page id=%i file=\"%s\"\n"
			"chars count=%zi",
			page.PageID,
			page.PageFileName,
			page.CharacteListSize
		);

		for (size_t i = 0; i < page.CharacteListSize; i++)
		{
			FNTCharacter& character = page.CharacteList[i];

			characterWritten = fprintf
			(
				file.FileMarker,
				"char id=%i x=%f y=%f width=%f height=%f xoffset=%f yoffset=%f xadvance=%i page=%i chnl=%i\n",
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

	FileActionResult closingResult = file.Close();

	return closingResult;
}

BF::FileActionResult BF::FNT::ConvertTo(Font& font)
{
	unsigned int amountOfResources = FontPageListSize;

	Text::Copy(font.Name, Info.Name, FNTPageFileNameSize);

	font.BitMapFont = this;
	font.AdditionalResourceListSize = amountOfResources;
	font.CharacterSize = Info.Size;
	font.SizeBetweenLines = CommonData.LineHeight;
	font.AdditionalResourceList = new char[amountOfResources, 30];

	for (size_t i = 0; i < amountOfResources; i++)
	{
		FNTPage& page = FontPageList[i];
		char* pageFileName = page.PageFileName;
		char* string = &font.AdditionalResourceList[i];

		strcpy(string, pageFileName);
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
				" | %3i -> %c | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5c |\n",
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