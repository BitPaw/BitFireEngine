#pragma once

#include <string>
#include <iostream>

class StringSplitter
{
private:
	StringSplitter();

public:
	unsigned char SplitToken;
	unsigned int NumberOfLines;
	std::string* Lines;

	static StringSplitter Split(std::string content, char splitToken);
	static StringSplitter Split(std::string content, std::string splitTokens);
	static std::string CutInHalfAndTakeRightValue(std::string content, char splitToken);
};