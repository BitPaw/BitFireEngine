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

				Name.Copy(face);
				Size = size.ToInt();
				Bold = bold.ToBool();
				Italic = aa.ToBool();
				CharSet.Copy(charset);
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

				pageFileNameText.Cut(start, stop, FontPages[0].PageFileName);

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

void BF::FNT::Save(AsciiString& filePath)
{
}

void BF::FNT::Convert(Font& font)
{
	unsigned int amountOfResources = FontPages.Size();

	font.Name.Copy(Name);
	font.CharacterSize = Size;
	font.SizeBetweenLines = LineHeight;
	font.AdditionalResourceList.ReSize(amountOfResources);

	for (size_t i = 0; i < amountOfResources; i++)
	{
		FNTPage& page = FontPages[i];
		AsciiString& string = font.AdditionalResourceList[i];

		string.Copy(page.PageFileName);
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