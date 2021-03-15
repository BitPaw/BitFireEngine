#include "FNTLoader.h"

void BF::FNTLoader::ParseInfoLine(ASCIIString& line, FNTInfo& fntInfo)
{
	List<ASCIIString> lines;
	const char token = '=';

	line.Splitt(' ', lines);

	ASCIIString face = lines[1];
	ASCIIString size = lines[2];
	ASCIIString bold = lines[3];
	ASCIIString italic = lines[4];
	ASCIIString charset = lines[5];
	ASCIIString unicode = lines[6];
	ASCIIString stretchH = lines[7];
	ASCIIString smooth = lines[8];
	ASCIIString aa = lines[9];
	ASCIIString padding = lines[10];
	ASCIIString spacing = lines[11];

	lines.DeleteAll();

	//----------------------------------------------------------------------------
	face.Splitt(token, lines);
	face = lines[1];
	lines.DeleteAll();

	size.Splitt(token, lines);
	size = lines[1];
	lines.DeleteAll();

	bold.Splitt(token, lines);
	bold = lines[1];
	lines.DeleteAll();

	italic.Splitt(token, lines);
	italic = lines[1];
	lines.DeleteAll();

	charset.Splitt(token, lines);
	charset = lines[1];
	lines.DeleteAll();

	unicode.Splitt(token, lines);
	unicode = lines[1];
	lines.DeleteAll();

	stretchH.Splitt(token, lines);
	stretchH = lines[1];
	lines.DeleteAll();

	smooth.Splitt(token, lines);
	smooth = lines[1];
	lines.DeleteAll();

	aa.Splitt(token, lines);
	aa = lines[1];
	lines.DeleteAll();

	padding.Splitt(token, lines);
	padding = lines[1];
	lines.DeleteAll();

	spacing.Splitt(token, lines);
	spacing = lines[1];
	lines.DeleteAll();
	//----------------------------------------------------------------------------

	fntInfo.Name = face;
	fntInfo.Size = size.ToInt();
	fntInfo.Bold = bold.ToBool();
	fntInfo.Italic = aa.ToBool();
	fntInfo.CharSet = charset;
	fntInfo.Unicode = unicode.ToBool();
	fntInfo.StretchH = stretchH.ToInt();
	fntInfo.Smooth = smooth.ToInt();
	fntInfo.Supersampling = aa.ToBool();
	// bitMapFontInfo.CharacterPadding = padding;
	//bitMapFontInfo.SpacerOffset = spacing;
}

void BF::FNTLoader::ParseCommonDataLine(ASCIIString& line, FNTCommonData& fntCommonData)
{
	List<ASCIIString> lines;
	const char token = '=';

	line.Splitt(' ', lines);

	ASCIIString lineHeight = lines[1];
	ASCIIString base = lines[2];
	ASCIIString scaleW = lines[3];
	ASCIIString scaleH = lines[4];
	ASCIIString pages = lines[5];
	ASCIIString packed = lines[6];

	//----------------------------------------------------------------------------
	lineHeight.Splitt(token, lines);
	lineHeight = lines[1];
	lines.DeleteAll();

	base.Splitt(token, lines);
	base = lines[1];
	lines.DeleteAll();

	scaleW.Splitt(token, lines);
	scaleW = lines[1];
	lines.DeleteAll();

	scaleH.Splitt(token, lines);
	scaleH = lines[1];
	lines.DeleteAll();

	pages.Splitt(token, lines);
	pages = lines[1];
	lines.DeleteAll();

	packed.Splitt(token, lines);
	packed = lines[1];
	lines.DeleteAll();
	//----------------------------------------------------------------------------

	fntCommonData.LineHeight = lineHeight.ToInt();
	fntCommonData.Base = base.ToInt();
	fntCommonData.ScaleWidth = scaleW.ToInt();
	fntCommonData.ScaleHeight = scaleH.ToInt();
	fntCommonData.AmountOfPages = pages.ToInt();
	fntCommonData.Packed = packed.ToBool();
}

void BF::FNTLoader::ParsePageLine(ASCIIString& line, FNTPage& fntPage)
{
	List<ASCIIString> lines;
	const char token = '\"';
	unsigned int start = 0;
	unsigned int stop = 0;
	unsigned int cutlengh = 0;

	line.Splitt(' ', lines);

	ASCIIString pageIDText(lines[1]);
	ASCIIString pageFileNameText(lines[2]);

	lines.DeleteAll();

	pageIDText.Splitt('=', lines);
	pageIDText.Copy(lines[1]);
	fntPage.PageID = pageIDText.ToInt();

	lines.DeleteAll();

	start = pageFileNameText.FindFirst(token) + 1;
	stop = pageFileNameText.FindLast(token);
	
	pageFileNameText.Cut(start, stop, fntPage.PageFileName);
}

unsigned int BF::FNTLoader::ParseCharacterCountLine(ASCIIString& line)
{
	List<ASCIIString> lines;	
	line.Splitt('=', lines);
	ASCIIString pageIDText = lines[1];
	lines.DeleteAll();

	unsigned int count = pageIDText.ToInt();

	return count;
}

void BF::FNTLoader::ParseCharacterLine(ASCIIString& line, FNTCharacter& fntCharacter)
{
	const char token = '=';
	unsigned int start = 0;
	unsigned int stop = 0;
	unsigned int cutlengh = 0;
	List<ASCIIString> lines;
	List<ASCIIString> charIDText;
	List<ASCIIString> charXText;
	List<ASCIIString> charYText;
	List<ASCIIString> charWidthText;
	List<ASCIIString> charHeightText;
	List<ASCIIString> charXOffsetText;
	List<ASCIIString> charYOffsetText;
	List<ASCIIString> charXAdvanceText;
	List<ASCIIString> charPageText;
	List<ASCIIString> charChanelText;

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


	fntCharacter.ID = charIDText[1].ToInt();

	fntCharacter.Position.Set
	(
		charXText[1].ToInt(), 
		charYText[1].ToInt()
	);
	
	fntCharacter.Size.Set
	(
		charWidthText[1].ToInt(), 
		charHeightText[1].ToInt()
	);

	fntCharacter.Offset.Set
	(
		charXOffsetText[1].ToInt(), 
		charYOffsetText[1].ToInt()
	);	
	
	fntCharacter.XAdvance = charXAdvanceText[1].ToInt();
	fntCharacter.Page = charPageText[1].ToInt();
	fntCharacter.Chanal = charChanelText[1].ToInt();
}

BF::FNT* BF::FNTLoader::LoadFromFile(ASCIIString& path)
{
	TextFile textFile(path);
	FileLoader::ReadTextFile(textFile, true);
	List<FNTCommand> commandList;
	FNT* bitMapFont = new FNT();
	unsigned int amountOfLines = textFile.Lines.Size();


	bitMapFont->FontPages.ReSize(1);
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
			ASCIIString* line = &textFile.Lines[i];
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
		bitMapFont->FontPages[0].Characters.ReSize(characterCounter);
	}



	// Parse
	unsigned int pageCounter = 0;
	unsigned int charCounter = 0;

	for (unsigned int i = 0; i < amountOfLines; i++)
	{
		ASCIIString& line = textFile.Lines[i];
		FNTCommand currentCommand = commandList[i];

		switch (currentCommand)
		{
			case FNTCommand::Info:
				//bitMapFont->FontInfo = ParseInfoLine(line);
				break;

			case FNTCommand::Common:
				//bitMapFont->FontCommon = ParseCommonDataLine(line);
				break;

			case FNTCommand::Page:
			{
				FNTPage& currentPage = bitMapFont->FontPages[pageCounter];

				ParsePageLine(line, currentPage);

				pageCounter++;
			}


			break;

			case FNTCommand::Chars:
				// Ignore?
				// ParseCharacterCountLine(line);
				break;

			case FNTCommand::Char:
			{
				FNTCharacter character;
				
				ParseCharacterLine(line, character);
				FNTPage* page = &bitMapFont->FontPages[character.Page];

				// ERROR!
				page->Characters[charCounter++] = character;


				break;
			}

			case FNTCommand::Invalid:
			default:
				// Do nothing
				break;
		}
	}

	return bitMapFont;
}