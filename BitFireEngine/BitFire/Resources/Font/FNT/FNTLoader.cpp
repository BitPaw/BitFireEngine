#include "FNTLoader.h"

BF::FNTInfo BF::FNTLoader::ParseInfoLine(std::string line)
{
	FNTInfo bitMapFontInfo;
	StringSplitter ss = StringSplitter::Split(line, ' ');
	const char token = '=';

	std::string face = ss.Lines[1];
	std::string size = ss.Lines[2];
	std::string bold = ss.Lines[3];
	std::string italic = ss.Lines[4];
	std::string charset = ss.Lines[5];
	std::string unicode = ss.Lines[6];
	std::string stretchH = ss.Lines[7];
	std::string smooth = ss.Lines[8];
	std::string aa = ss.Lines[9];
	std::string padding = ss.Lines[10];
	std::string spacing = ss.Lines[11];
	
	face = StringSplitter::CutInHalfAndTakeRightValue(face, token);
	size = StringSplitter::CutInHalfAndTakeRightValue(size, token);
	bold = StringSplitter::CutInHalfAndTakeRightValue(bold, token);
	italic = StringSplitter::CutInHalfAndTakeRightValue(italic, token);
	charset = StringSplitter::CutInHalfAndTakeRightValue(charset, token);
	unicode = StringSplitter::CutInHalfAndTakeRightValue(unicode, token);
	stretchH = StringSplitter::CutInHalfAndTakeRightValue(stretchH, token);
	smooth = StringSplitter::CutInHalfAndTakeRightValue(smooth, token);
	aa = StringSplitter::CutInHalfAndTakeRightValue(aa, token);
	padding = StringSplitter::CutInHalfAndTakeRightValue(padding, token);
	spacing = StringSplitter::CutInHalfAndTakeRightValue(spacing, token);

	bitMapFontInfo.Name = face;
	bitMapFontInfo.Size = stoi(size);
	bitMapFontInfo.Bold = stoi(bold) == 0;
	bitMapFontInfo.Italic = stoi(aa) == 0;
	bitMapFontInfo.CharSet = charset;	
	bitMapFontInfo.Unicode = stoi(unicode) == 0 ? false : true;
	bitMapFontInfo.StretchH = stoi(unicode);
	bitMapFontInfo.Smooth = stoi(smooth);
	bitMapFontInfo.AA = stoi(aa) == 0 ? false : true;
	// bitMapFontInfo.CharacterPadding = padding;
	//bitMapFontInfo.SpacerOffset = spacing;

	return bitMapFontInfo;
}

BF::FNTCommonData BF::FNTLoader::ParseCommonDataLine(std::string line)
{
	FNTCommonData bitMapFontCommonData;
	StringSplitter ss = StringSplitter::Split(line, ' ');
	const char token = '=';

	std::string lineHeight = ss.Lines[1];
	std::string base = ss.Lines[2];
	std::string scaleW = ss.Lines[3];
	std::string scaleH = ss.Lines[4];
	std::string pages = ss.Lines[5];
	std::string packed = ss.Lines[6];

	lineHeight = StringSplitter::CutInHalfAndTakeRightValue(lineHeight, token);
	base = StringSplitter::CutInHalfAndTakeRightValue(base, token);
	scaleW = StringSplitter::CutInHalfAndTakeRightValue(scaleW, token);
	scaleH = StringSplitter::CutInHalfAndTakeRightValue(scaleH, token);
	pages = StringSplitter::CutInHalfAndTakeRightValue(pages, token);
	packed = StringSplitter::CutInHalfAndTakeRightValue(packed, token);

	bitMapFontCommonData.LineHeight = stoi(lineHeight);
	bitMapFontCommonData.Base = stoi(base);
	bitMapFontCommonData.ScaleWidth = stoi(scaleW);
	bitMapFontCommonData.ScaleHeight = stoi(scaleH);
	bitMapFontCommonData.AmountOfPages = stoi(pages);
	bitMapFontCommonData.Packed = stoi(packed) == 0 ? false : true;

	return bitMapFontCommonData;
}

BF::FNTPage BF::FNTLoader::ParsePageLine(std::string line)
{
	FNTPage bitMapFontPage;
	StringSplitter ss = StringSplitter::Split(line, ' ');
	char token;
	unsigned int start = 0;
	unsigned int stop = 0;
	unsigned int cutlengh = 0;

	std::string pageIDText = ss.Lines[1];
	std::string pageFileNameText = ss.Lines[2];

	token = '=';
	pageIDText = StringSplitter::CutInHalfAndTakeRightValue(pageIDText, token);

	token = '\"';
	start = pageFileNameText.find_first_of(token) + 1;
	stop = pageFileNameText.find_last_of(token);
	cutlengh = stop - start;
	pageFileNameText = pageFileNameText.substr(start, cutlengh);

	bitMapFontPage.PageID = std::stoi(pageIDText);
	bitMapFontPage.PageFileName = pageFileNameText;

	return bitMapFontPage;
}

unsigned int BF::FNTLoader::ParseCharacterCountLine(std::string line)
{
	line = StringSplitter::CutInHalfAndTakeRightValue(line, '=');
	unsigned int count = stoi(line);

	return count;
}

BF::FNTCharacter BF::FNTLoader::ParseCharacterLine(std::string line)
{
	FNTCharacter character;
	StringSplitter ss = StringSplitter::Split(line, ' ');

	const char token = '=';
	unsigned int start = 0;
	unsigned int stop = 0;
	unsigned int cutlengh = 0;

	std::string charIDText = ss.Lines[1];
	std::string charXText = ss.Lines[2];
	std::string charYText = ss.Lines[3];
	std::string charWidthText = ss.Lines[4];
	std::string charHeightText = ss.Lines[5];
	std::string charXOffsetText = ss.Lines[6];
	std::string charYOffsetText = ss.Lines[7];
	std::string charXAdvanceText = ss.Lines[8];
	std::string charPageText = ss.Lines[9];
	std::string charChanelText = ss.Lines[10];

	charIDText = StringSplitter::CutInHalfAndTakeRightValue(charIDText, token);
	charXText = StringSplitter::CutInHalfAndTakeRightValue(charXText, token);
	charYText = StringSplitter::CutInHalfAndTakeRightValue(charYText, token);
	charWidthText = StringSplitter::CutInHalfAndTakeRightValue(charWidthText, token);
	charHeightText = StringSplitter::CutInHalfAndTakeRightValue(charHeightText, token);
	charXOffsetText = StringSplitter::CutInHalfAndTakeRightValue(charXOffsetText, token);
	charYOffsetText = StringSplitter::CutInHalfAndTakeRightValue(charYOffsetText, token);
	charXAdvanceText = StringSplitter::CutInHalfAndTakeRightValue(charXAdvanceText, token);
	charPageText = StringSplitter::CutInHalfAndTakeRightValue(charPageText, token);
	charChanelText = StringSplitter::CutInHalfAndTakeRightValue(charChanelText, token);

	character.ID = std::stoi(charIDText);
	character.StartPosition = Point(std::stoi(charXText), std::stoi(charYText));
	character.Size = Point(std::stoi(charWidthText), std::stoi(charHeightText));
	character.Offset = Point(std::stoi(charXOffsetText), std::stoi(charYOffsetText));
	character.XAdvance = std::stoi(charXAdvanceText);
	character.Page = std::stoi(charPageText);
	character.Chanal = std::stoi(charChanelText);

	return character;
}

BF::FNT* BF::FNTLoader::LoadFromFile(std::string path)
{
	TextFile textFile = FileLoader::ReadTextFile(path, true);
	List<FNTCommand> commandList;
	FNT* bitMapFont = new FNT();
	unsigned int amountOfLines = textFile.Lines.Size.Value;

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
			std::string line = textFile.Lines[i];
			FNTCommand currentCommand;
			char firstCharacter = line.size() <= 0 ? ' ' : line.at(0);

			switch (firstCharacter)
			{
			case commandInfo:
				currentCommand = FNTCommand::Info;
				break;
			case commandPage:
				currentCommand = FNTCommand::Page;
				break;

			case commandC:
				firstCharacter = line.at(1);

				switch (firstCharacter)
				{
				case commandCommon:
					currentCommand = FNTCommand::Common;
					break;

				case commandH:
					firstCharacter = line.at(4);

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

	for (unsigned int i = 0; i < amountOfLines; i++)
	{
		std::string line = textFile.Lines[i];
		FNTCommand currentCommand = commandList[i];

		switch (currentCommand)
		{
		case FNTCommand::Info:
			bitMapFont->FontInfo = ParseInfoLine(line);
			break;

		case FNTCommand::Common:
			bitMapFont->FontCommon = ParseCommonDataLine(line);
			break;

		case FNTCommand::Page:
			bitMapFont->FontPages[pageCounter++] = ParsePageLine(line);
			break;

		case FNTCommand::Chars:
			// Ignore?
			// ParseCharacterCountLine(line);
			break;

		case FNTCommand::Char:
		{
			FNTCharacter character = ParseCharacterLine(line);
			FNTPage* page = &bitMapFont->FontPages[character.Page];

			// ERROR!
			page->Characters[character.ID] = character;
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