#include "SplittedString.h"

SplittedString::SplittedString(std::string* lines, unsigned int numberOfLines, unsigned char splitToken)
{
	NumberOfLines = numberOfLines;
	SplitToken = splitToken;
	Lines = lines;
}

SplittedString SplittedString::Split(std::string line, char splitToken)
{    
	unsigned int tokenCounter = 0;
	const size_t length = line.length();
    std::string* lines;

	// Count
	for (size_t i = 0; i < length; i++)
	{
		if (line[i] == splitToken)
		{
			tokenCounter++;
		}
	}

	tokenCounter++;

	lines = new std::string[tokenCounter];
	
	size_t offset = 0;

	for (size_t i = 0; i < tokenCounter; i++)
	{
		size_t cutStart = offset;
		size_t cutPoint = line.find(splitToken, offset);
				
		offset = cutPoint + 1;

		std::string segment = line.substr(cutStart, cutPoint - cutStart);

		lines[i] = segment;
	}

	SplittedString ss(lines, tokenCounter, splitToken);

    return ss;
}
