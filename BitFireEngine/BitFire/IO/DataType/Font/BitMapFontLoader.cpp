#include "BitMapFontLoader.h"

const unsigned int BitMapFontLoader::_bufferSize = 100;
const char* BitMapFontLoader::_characterLineSyntax = "char id=%u x=%.0f y=%.0f width=%.0f height=%.0f xoffset=%.0f yoffset=%.0f xadvance=%u page=0 chnl=0";

BitMapFont* BitMapFontLoader::LoadFont(std::string filePath)
{
	std::ifstream file(filePath);
	std::string line;
	unsigned int lines = 0;
	BitMapFont* bitMapFont;

	while (getline(file, line))
	{
		lines++;
	}

	file.seekg(0, std::ios::beg);

	bitMapFont = new BitMapFont(lines);

	for (size_t i = 0; getline(file, line); i++)
	{
		BitMapFontCharacter* character = &bitMapFont->BitMapFontCharacterList[i];

		sscanf_s
		(
			line.c_str(),
			_characterLineSyntax,
			character->ID,
			character->StartPosition.X,
			character->StartPosition.Y,
			character->Size.X,
			character->Size.Y,
			character->Offset.X,
			character->Offset.Y,
			character->XAdvance
		);
	}

	file.close();

    return bitMapFont;
}

void BitMapFontLoader::SaveFont(std::string filePath, BitMapFont* bitMapFont)
{
	std::ofstream file(filePath);	

	for (size_t i = 0; i < bitMapFont->AmountOfCharacters; i++)
	{
		BitMapFontCharacter* character = &bitMapFont->BitMapFontCharacterList[i];		
		std::string line = BitMapFontLoader::PrintCharacterLine(character);

		file << line << "\n";
	}

	file.close();
}

std::string BitMapFontLoader::PrintCharacterLine(BitMapFontCharacter* character)
{
	char* characterLineBuffer = new char[_bufferSize];	

	// Visual Studio refuses to use this 'unsafe' method.
	// Need to add a PreProcessor "_CRT_SECURE_NO_WARNINGS"
	// Still change this back!
	sprintf
	(
		characterLineBuffer,
		_characterLineSyntax,
		character->ID,
		character->StartPosition.X,
		character->StartPosition.Y,
		character->Size.X,
		character->Size.Y,
		character->Offset.X,
		character->Offset.Y,
		character->XAdvance
	);

	std::string line(characterLineBuffer);

	delete[] characterLineBuffer;

	return line;
}
