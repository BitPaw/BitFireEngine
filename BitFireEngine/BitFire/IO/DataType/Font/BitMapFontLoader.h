#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "BitMapFont.h"

class BitMapFontLoader
{
private:
	static const unsigned int _bufferSize;
	static const char* _characterLineSyntax;

public:
	static BitMapFont* LoadFont(std::string filePath);
	static void SaveFont(std::string filePath, BitMapFont* bitMapFont);
	static std::string PrintCharacterLine(BitMapFontCharacter* character);
};