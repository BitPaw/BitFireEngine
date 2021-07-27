#include "FNT.h"
#include "../../File/File.h"
#include "FNTCommand.h"

BF::FNTCharacter* BF::FNT::GetCharacterPosition(unsigned char character)
{
	FNTPage* page = &FontPages[0];
	unsigned int size = page->Characters.Size();

	for (unsigned int i = 0; i < size; i++)
	{
		FNTCharacter* bitMapFontCharacter = &page->Characters[i];
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
	//Name = "[N/A]";
	Size = 70;
	Bold = false;
	Italic = false;
	//CharSet = "";
	Unicode = false;
	StretchH = 100;
	Smooth = 1;
	Supersampling = 1;
	CharacterPadding[0] = 0;
	CharacterPadding[1] = 0;
	CharacterPadding[2] = 0;
	CharacterPadding[3] = 0;
	SpacerOffset[0] = 0;
	SpacerOffset[1] = 0;

	LineHeight = 95;
	Base = 71;
	ScaleWidth = 512;
	ScaleHeight = 512;
	AmountOfPages = 1;
	Packed = false;
}

void BF::FNT::Load(const char* filePath)
{
	AsciiString dataString;
	AsciiString referenceSting;
	FNTPage* currentPage = nullptr;
	File file(filePath);
	char currentCursor[1048];
	char textCharacter[30];
	int pageCounter = 0;

	file.Read();

	char hasCommas = 0;
	bool stopFlag = false;
	int characterCounter = 0;
	int dynamicIndex = 0;

	// HARD CODED
	FontPages.ReSize(1);
	//----

	while (true)
	{
		ErrorCode errorCode = file.ReadNextLineInto(currentCursor);

		if (errorCode == ErrorCode::Empty)
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

			memset(Name, 0, 30);
			memset(CharSet, 0, 10);

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
			//AsciiString extrectfileName(); // face="SegoeþScript"

			referenceSting.SetAsReference(textName);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			referenceSting.ReplaceWhiteSpaceInQuotes('\xFE', true);

			memcpy(Name, &referenceSting[1], referenceSting.Size() - 2);

			referenceSting.SetAsReference(textCharSet);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			referenceSting.ReplaceWhiteSpaceInQuotes('\xFE', true);

			memcpy(CharSet, &referenceSting[1], referenceSting.Size() - 2);

			referenceSting.SetAsReference(size);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Size = referenceSting.ToInt();

			referenceSting.SetAsReference(bold);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Bold = referenceSting.ToBool();

			referenceSting.SetAsReference(italic);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Italic = referenceSting.ToBool();

			referenceSting.SetAsReference(unicode);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Unicode = referenceSting.ToBool();

			referenceSting.SetAsReference(stretchH);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			StretchH = referenceSting.ToInt();

			referenceSting.SetAsReference(smooth);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Smooth = referenceSting.ToBool();

			referenceSting.SetAsReference(aa);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Supersampling = referenceSting.ToBool();

			if (scannedObjects == 13)
			{
				referenceSting.SetAsReference(outlineThickness);
				referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
				OutlineThickness = referenceSting.ToInt();
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
			LineHeight = referenceSting.ToInt();

			referenceSting.SetAsReference(base);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Base = referenceSting.ToInt();

			referenceSting.SetAsReference(scaleW);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			ScaleWidth = referenceSting.ToInt();

			referenceSting.SetAsReference(scaleH);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			ScaleHeight = referenceSting.ToInt();

			referenceSting.SetAsReference(pages);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			AmountOfPages = referenceSting.ToInt();

			referenceSting.SetAsReference(packed);
			referenceSting.PonterMoveBy(referenceSting.FindFirst('=') + 1);
			Packed = referenceSting.ToBool();
		}

		if (isPageLine)
		{
			char textPageID[12];
			char imageFileName[30];

			currentPage = &FontPages[pageCounter++];

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

			currentPage->Characters.ReSize(numberOfChars);
		}

		if (isCharacterDeclareLine)
		{
			FNTCharacter& character = currentPage->Characters[characterCounter++];
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
}
/*
void BF::FNT::Load(AsciiString& filePath)
{
	List<FNTCommand> commandList;
	List<AsciiString> lineList;
	File file(filePath);
	unsigned int amountOfLines;

	file.ReadAsLines(lineList);

	amountOfLines = lineList.Size();

	FontPages.ReSize(1);

	commandList.ReSize(amountOfLines);

	// Raw-Parse (Counting)
	{
		unsigned int currentCommandIndex = 0;
		unsigned int characterCounter = 0;

		const unsigned char commandInfo = 'i';
		const unsigned char commandPage = 'p';
		const unsigned char commandCommon = 'o';

		const unsigned char commandNone = ' ';
		const unsigned char commandC = 'c';
		const unsigned char commandH = 'h';
		const unsigned char commandS = 's';

		for (unsigned int i = 0; i < amountOfLines; i++)
		{
			AsciiString* line = &lineList[i];
			FNTCommand currentCommand;
			char firstCharacter = line->Empty() ? ' ' : (*line)[0];

			switch (firstCharacter)
			{
				case commandInfo:
					currentCommand = FNTCommand::Info;
					break;
				case commandPage:
					currentCommand = FNTCommand::Page;
					break;

				case commandC:
					firstCharacter = (*line)[1];

					switch (firstCharacter)
					{
						case commandCommon:
							currentCommand = FNTCommand::Common;
							break;

						case commandH:
							firstCharacter = (*line)[4];

							switch (firstCharacter)
							{
								case commandNone:
									currentCommand = FNTCommand::Char;
									characterCounter++;
									break;

								case commandS:
									currentCommand = FNTCommand::Chars;
									break;

								default:
									currentCommand = FNTCommand::Invalid;
									break;
							}
							break;

						default:
							currentCommand = FNTCommand::Invalid;
							break;
					}

					break;

				default:
					currentCommand = FNTCommand::Invalid;
					break;
			}

			commandList[currentCommandIndex++] = currentCommand;
		}


		//bitMapFont.Characters.reserve(characterCounter);

		// BUG! static to 0
		FontPages[0].Characters.ReSize(characterCounter);
	}

	// Parse
	{
		unsigned int pageCounter = 0;
		unsigned int charCounter = 0;

		for (unsigned int i = 0; i < amountOfLines; i++)
		{
			AsciiString& line = lineList[i];
			FNTCommand& currentCommand = commandList[i];

			switch (currentCommand)
			{
			case FNTCommand::Info:
			{
				List<AsciiString> lines;
				AsciiString face;
				AsciiString size;
				AsciiString bold;
				AsciiString italic;
				AsciiString charset;
				AsciiString unicode;
				AsciiString stretchH;
				AsciiString smooth;
				AsciiString aa;
				AsciiString padding;
				AsciiString spacing;
				const char token = '=';
				unsigned int lineIndex = 1;

				line.Splitt(' ', lines);

				{
					AsciiString& line = lines[1];

					unsigned int commas = line.Count('\"');

					if (commas == 1)
					{
						face.Copy(lines[lineIndex++]);
						face.AttachToBack(' ');
						face.AttachToBack(lines[lineIndex++]);
						face.Remove('\"');
					}
					else
					{
						face = lines[lineIndex++];
					}
				}

				size.Copy(lines[lineIndex++]);
				bold.Copy(lines[lineIndex++]);
				italic.Copy(lines[lineIndex++]);
				charset.Copy(lines[lineIndex++]);
				unicode.Copy(lines[lineIndex++]);
				stretchH.Copy(lines[lineIndex++]);
				smooth.Copy(lines[lineIndex++]);
				aa.Copy(lines[lineIndex++]);
				padding.Copy(lines[lineIndex++]);
				spacing.Copy(lines[lineIndex++]);

				lines.DeleteAll();

				//----------------------------------------------------------------------------
				face.Splitt(token, lines);
				face.Copy(lines[1]);
				lines.DeleteAll();

				size.Splitt(token, lines);
				size.Copy(lines[1]);
				lines.DeleteAll();

				bold.Splitt(token, lines);
				bold.Copy(lines[1]);
				lines.DeleteAll();

				italic.Splitt(token, lines);
				italic.Copy(lines[1]);
				lines.DeleteAll();

				charset.Splitt(token, lines);
				charset.Copy(lines[1]);
				lines.DeleteAll();

				unicode.Splitt(token, lines);
				unicode.Copy(lines[1]);
				lines.DeleteAll();

				stretchH.Splitt(token, lines);
				stretchH.Copy(lines[1]);
				lines.DeleteAll();

				smooth.Splitt(token, lines);
				smooth.Copy(lines[1]);
				lines.DeleteAll();

				aa.Splitt(token, lines);
				aa.Copy(lines[1]);
				lines.DeleteAll();

				padding.Splitt(token, lines);
				padding.Copy(lines[1]);
				lines.DeleteAll();

				spacing.Splitt(token, lines);
				spacing.Copy(lines[1]);
				lines.DeleteAll();
				//----------------------------------------------------------------------------

				//Name.Copy(face);

				Size = size.ToInt();
				Bold = bold.ToBool();
				Italic = aa.ToBool();
				//CharSet.Copy(charset);
				Unicode = unicode.ToBool();
				StretchH = stretchH.ToInt();
				Smooth = smooth.ToInt();
				Supersampling = aa.ToBool();
				// bitMapFontInfo.CharacterPadding = padding;
				//bitMapFontInfo.SpacerOffset = spacing;
				break;
			}

			case FNTCommand::Common:
			{
				//bitMapFont->FontCommon = ParseCommonDataLine(line);
				List<AsciiString> lines;
				AsciiString lineHeight;
				AsciiString base;
				AsciiString scaleW;
				AsciiString scaleH;
				AsciiString pages;
				AsciiString packed;
				const char token = '=';

				line.Splitt(' ', lines);

				lineHeight.Copy(lines[1]);
				base.Copy(lines[2]);
				scaleW.Copy(lines[3]);
				scaleH.Copy(lines[4]);
				pages.Copy(lines[5]);
				packed.Copy(lines[6]);

				//----------------------------------------------------------------------------
				lineHeight.Splitt(token, lines);
				lineHeight.Copy(lines[1]);
				lines.DeleteAll();

				base.Splitt(token, lines);
				base.Copy(lines[1]);
				lines.DeleteAll();

				scaleW.Splitt(token, lines);
				scaleW.Copy(lines[1]);
				lines.DeleteAll();

				scaleH.Splitt(token, lines);
				scaleH.Copy(lines[1]);
				lines.DeleteAll();

				pages.Splitt(token, lines);
				pages.Copy(lines[1]);
				lines.DeleteAll();

				packed.Splitt(token, lines);
				packed.Copy(lines[1]);
				lines.DeleteAll();
				//----------------------------------------------------------------------------

				LineHeight = lineHeight.ToInt();
				Base = base.ToInt();
				ScaleWidth = scaleW.ToInt();
				ScaleHeight = scaleH.ToInt();
				AmountOfPages = pages.ToInt();
				Packed = packed.ToBool();
				break;
			}

			case FNTCommand::Page:
			{
				FNTPage& currentPage = FontPages[pageCounter];

				//ParsePageLine(line, currentPage);
				List<AsciiString> lines;
				const char token = '\"';
				unsigned int start = 0;
				unsigned int stop = 0;
				unsigned int cutlengh = 0;

				line.Splitt(' ', lines);

				AsciiString pageIDText(lines[1]);
				AsciiString pageFileNameText(lines[2]);

				lines.DeleteAll();

				pageIDText.Splitt('=', lines);
				pageIDText.Copy(lines[1]);
				FontPages[0].PageID = pageIDText.ToInt();

				lines.DeleteAll();

				start = pageFileNameText.FindFirst(token) + 1;
				stop = pageFileNameText.FindLast(token);

				//pageFileNameText.Cut(start, stop, FontPages[0].PageFileName);

				pageCounter++;
				break;
			}

			case FNTCommand::Chars:
			{
				// Ignore?
				// ParseCharacterCountLine(line);
				List<AsciiString> lines;
				line.Splitt('=', lines);
				AsciiString pageIDText = lines[1];
				lines.DeleteAll();

				unsigned int count = pageIDText.ToInt();

				break;
			}

			case FNTCommand::Char:
			{
				FNTCharacter fontCharacter;

				//-------------
				const char token = '=';
				unsigned int start = 0;
				unsigned int stop = 0;
				unsigned int cutlengh = 0;
				List<AsciiString> lines;
				List<AsciiString> charIDText;
				List<AsciiString> charXText;
				List<AsciiString> charYText;
				List<AsciiString> charWidthText;
				List<AsciiString> charHeightText;
				List<AsciiString> charXOffsetText;
				List<AsciiString> charYOffsetText;
				List<AsciiString> charXAdvanceText;
				List<AsciiString> charPageText;
				List<AsciiString> charChanelText;

				line.MergeRepeatingWhiteSpace();

				line.Splitt(' ', lines);

				lines[1].Splitt(token, charIDText);
				lines[2].Splitt(token, charXText);
				lines[3].Splitt(token, charYText);
				lines[4].Splitt(token, charWidthText);
				lines[5].Splitt(token, charHeightText);
				lines[6].Splitt(token, charXOffsetText);
				lines[7].Splitt(token, charYOffsetText);
				lines[8].Splitt(token, charXAdvanceText);
				lines[9].Splitt(token, charPageText);
				lines[10].Splitt(token, charChanelText);


				fontCharacter.ID = charIDText[1].ToInt();

				fontCharacter.Position[0] = charXText[1].ToInt();
				fontCharacter.Position[1] = charYText[1].ToInt();

				fontCharacter.Size[0] = charWidthText[1].ToInt();
				fontCharacter.Size[1] = charHeightText[1].ToInt();

				fontCharacter.Offset[0] = charXOffsetText[1].ToInt();
				fontCharacter.Offset[1] = charYOffsetText[1].ToInt();


				fontCharacter.XAdvance = charXAdvanceText[1].ToInt();
				fontCharacter.Page = charPageText[1].ToInt();
				fontCharacter.Chanal = charChanelText[1].ToInt();
				//----------

				FNTPage& page = FontPages[fontCharacter.Page];

				// ERROR!
				page.Characters[charCounter++] = fontCharacter;


				break;
			}

			case FNTCommand::Invalid:
			default:
				// Do nothing
				break;
			}
		}
	}
}
*/

void BF::FNT::Save(const char* filePath)
{
	char fileBuffer[16384];
	char* currentCursorIndex = fileBuffer;
	int characterWritten = 0;

	characterWritten = sprintf
	(
		currentCursorIndex,
		"info face=\"%s\" size=%i bold=%i italic=%i charset=%s unicode=%i stretchH=%i smooth=%i aa=%i padding=%i,%i,%i,%i spacing=%i,%i\n",
		Name,
		Size,
		Bold,
		Italic,
		CharSet,
		Unicode,
		StretchH,
		Smooth,
		Supersampling,
		CharacterPadding[0],
		CharacterPadding[1],
		CharacterPadding[2],
		CharacterPadding[3],
		SpacerOffset[0],
		SpacerOffset[1]
	);

	currentCursorIndex += characterWritten;


	characterWritten = sprintf
	(
		currentCursorIndex,
		"common lineHeight=%i base=%i scaleW=%i scaleH=%i pages=%i packed=%i\n",
		LineHeight,
		Base,
		ScaleWidth,
		ScaleHeight,
		AmountOfPages,
		Packed
	);

	currentCursorIndex += characterWritten;

	for (unsigned int i = 0; i < AmountOfPages; i++)
	{
		FNTPage& page = FontPages[i];
		int amountOfCharacters = page.Characters.Size();

		characterWritten = sprintf
		(
			currentCursorIndex,
			"page id=%i file=\"%s\"\n"
			"chars count=%i",
			page.PageID,
			page.PageFileName,
			page.Characters
		);

		currentCursorIndex += characterWritten;

		for (size_t i = 0; i < amountOfCharacters; i++)
		{
			FNTCharacter& character = page.Characters[i];

			characterWritten = sprintf
			(
				currentCursorIndex,
				"char id=%i x=%i y=%i width=%i height=%i xoffset=%i yoffset=%i xadvance=%i page=%i chnl=%i\n",
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

			currentCursorIndex += characterWritten;
		}
	}

	File::Write(&filePath[0], fileBuffer);
}

void BF::FNT::Convert(Font& font)
{
	unsigned int amountOfResources = FontPages.Size();

	strcpy(font.Name, Name);

	font.AdditionalResourceListSize = amountOfResources;
	font.CharacterSize = Size;
	font.SizeBetweenLines = LineHeight;
	font.AdditionalResourceList = new char[amountOfResources, 30];

	for (size_t i = 0; i < amountOfResources; i++)
	{
		FNTPage& page = FontPages[i];
		char* pageFileName = page.PageFileName;
		char* string = &font.AdditionalResourceList[i];

		strcpy(string, pageFileName);
	}
}

void BF::FNT::PrintData()
{
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Font (%s) : %s\n", &CharSet[0], &Name[0]);
	printf(" +-------------------------------------------------------------------------+\n");
	printf(" | Size     : %4u | Smooth  : %3u |\n", Size, Smooth);
	printf(" | Bold     : %4s | AA      : %3u |\n", Bold ? "Yes" : "No", Supersampling);
	printf
	(
		" | Italic   : %4s | Padding : %u,%u,%u,%u |\n",
		Italic ? "Yes" : "No",
		CharacterPadding[0],
		CharacterPadding[1],
		CharacterPadding[2],
		CharacterPadding[3]

	);
	printf(" | unicode  : %4s | Spacing : %u,%u |\n", Unicode ? "Yes" : "No", SpacerOffset[0], SpacerOffset[1]);
	printf(" | stretchH : %4u | Outline : %3u |\n", StretchH, OutlineThickness);


	for (unsigned int pageIndex = 0; pageIndex < FontPages.Size(); pageIndex++)
	{
		FNTPage* page = &FontPages[pageIndex];

		//printf(" |          |       |       |       |       |       |       |       |\n");
		printf("\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Page <%u/%u> %s\n", pageIndex + 1, FontPages.Size(), &page->PageFileName[0]);
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
		printf(" | Letter   | X-Pos | Y-Pos | Width | Height| X-Off | Y-Off | X-Step|\n");
		printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");

		for (unsigned int characterIndex = 0; characterIndex < page->Characters.Size(); characterIndex++)
		{
			FNTCharacter* character = &page->Characters[characterIndex];

			printf
			(
				" | %3u -> %c | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f |\n",
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