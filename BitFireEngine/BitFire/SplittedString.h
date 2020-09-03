#pragma once
#include <string>
#include <iostream>

class SplittedString
{
public:
	unsigned char SplitToken;
	unsigned int NumberOfLines;
	std::string* Lines;

	SplittedString(std::string* lines, unsigned int numberOfLines, unsigned char splitToken);

	static SplittedString Split(std::string line, char splitToken);
};

