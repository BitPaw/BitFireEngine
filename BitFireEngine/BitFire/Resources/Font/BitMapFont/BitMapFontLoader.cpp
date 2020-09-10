#include "BitMapFontLoader.h"

BitMapFontInfo BitMapFontLoader::ParseInfoLine(std::string line)
{
	BitMapFontInfo bitMapFontInfo;
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

BitMapFontCommonData BitMapFontLoader::ParseCommonDataLine(std::string line)
{
	BitMapFontCommonData bitMapFontCommonData;
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

BitMapFontPage BitMapFontLoader::ParsePageLine(std::string line)
{
	BitMapFontPage bitMapFontPage;
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

unsigned int BitMapFontLoader::ParseCharacterCountLine(std::string line)
{
	line = StringSplitter::CutInHalfAndTakeRightValue(line, '=');
	unsigned int count = stoi(line);

	return count;
}

BitMapFontCharacter BitMapFontLoader::ParseCharacterLine(std::string line)
{
	BitMapFontCharacter character;
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

BitMapFont BitMapFontLoader::LoadBitMapFont(std::string path)
{
	TextFile textFile = FileLoader::ReadTextFile(path, true);
	BF::List<BitMapFontCommand> commandList;
	BitMapFont bitMapFont;	
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
			BitMapFontCommand currentCommand;
			char firstCharacter = line.size() <= 0 ? ' ' : line.at(0);

			switch (firstCharacter)
			{
			case commandInfo:
				currentCommand = BitMapFontCommand::Info;
				break;
			case commandPage:
				currentCommand = BitMapFontCommand::Page;
				break;

			case commandC:
				firstCharacter = line.at(1);

				switch (firstCharacter)
				{
				case commandCommon:
					currentCommand = BitMapFontCommand::Common;
					break;

				case commandH:
					firstCharacter = line.at(4);

					switch (firstCharacter)
					{
					case commandNone:
						currentCommand = BitMapFontCommand::Char;
						characterCounter++;
						break;

					case commandS:
						currentCommand = BitMapFontCommand::Chars;
						break;

					default:
						currentCommand = BitMapFontCommand::Invalid;
						break;
					}
					break;

				default:
					currentCommand = BitMapFontCommand::Invalid;
					break;
				}

				break;

			default:
				currentCommand = BitMapFontCommand::Invalid;
				break;
			}

			commandList[currentCommandIndex++] = currentCommand;
		}

		//bitMapFont.Characters.reserve(characterCounter);
	}

	// Parse
	for (unsigned int i = 0; i < amountOfLines; i++)
	{
		std::string line = textFile.Lines[i];
		BitMapFontCommand currentCommand = commandList[i];

		switch (currentCommand)
		{
		case BitMapFontCommand::Info:
			bitMapFont.FontInfo = ParseInfoLine(line);
			break;

		case BitMapFontCommand::Common:
			bitMapFont.FontCommon = ParseCommonDataLine(line);
			break;

		case BitMapFontCommand::Page:
			bitMapFont.FontPages.push_back(ParsePageLine(line));
			break;

		case BitMapFontCommand::Chars:
			// Ignore?
			// ParseCharacterCountLine(line);
			break;

		case BitMapFontCommand::Char:
		{
			BitMapFontCharacter character = ParseCharacterLine(line);
			BitMapFontPage* page = &bitMapFont.FontPages[character.Page];

			page->Characters.push_back(character);
			break;
		}		

		case BitMapFontCommand::Invalid:
		default:
			// Do nothing
			break;
		}
	}

	return bitMapFont;
}