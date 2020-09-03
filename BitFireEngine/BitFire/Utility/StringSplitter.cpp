#include "StringSplitter.h"

StringSplitter::StringSplitter()
{

}

StringSplitter StringSplitter::Split(std::string content, char splitToken)
{
	unsigned int tokenCounter = 0;
	const unsigned int length = content.length();
	unsigned int offset = 0;
	StringSplitter ss;

	bool isTokeUniqe = false;

	// Count
	for (unsigned int i = 0; i < length; i++)
	{
		if (content[i] == splitToken)
		{
			if (i+1 >= length) // If there is no character after, its uniqe
			{
				isTokeUniqe = true;
			}
			else
			{
				if (content[i+1] != splitToken) // Is token uniqe?
				{
					isTokeUniqe = true;
				}
			}		
		}

		if (isTokeUniqe)
		{
			tokenCounter++;
			isTokeUniqe = false;
		}
	}
	tokenCounter++;

	ss.NumberOfLines = 0;
	ss.Lines = new std::string[tokenCounter];


	// do stuff
	{
		unsigned int cutStart;
		unsigned int cutPoint;
		std::string segment;

		for (unsigned int i = 0; i < tokenCounter; i++)
		{
			cutStart = offset;
			cutPoint = content.find(splitToken, offset);

			offset = cutPoint + 1;

			segment = content.substr(cutStart, cutPoint - cutStart);

			if (segment.empty())
			{
				i--;
			}
			else
			{
				ss.Lines[ss.NumberOfLines++] = segment;
			}
		}
	}

	return ss;
}

StringSplitter StringSplitter::Split(std::string content, std::string splitTokens)
{	
	StringSplitter ss;

	return ss;

	const unsigned char removerKey = '\xFF';
	unsigned int tokenCounter = 0;
	const unsigned int length = content.length();
	unsigned int offset = 0;


	unsigned int startIndex = 0;
	unsigned int stopIndex = startIndex + 1;

	// Count
	for (unsigned int i = 0; i < length; i++)
	{	
		std::string target = content.substr(startIndex, stopIndex);

		if (target.compare(splitTokens) == 0)
		{
			tokenCounter++;

			content[startIndex] = removerKey;
			content[stopIndex] = removerKey;
		}

		startIndex++;
		stopIndex = startIndex + 1;

		if (stopIndex >= length)
		{
			break;
		}		
	}
	tokenCounter++;

	ss.NumberOfLines = tokenCounter;
//	ss.Lines.reserve(tokenCounter);

	for (unsigned int i = 0; i < tokenCounter; i++)
	{
		unsigned int cutStart = offset;
		unsigned int cutPoint = content.find(removerKey, offset);

		offset = cutPoint + 2;

		std::string segment = content.substr(cutStart, cutPoint - cutStart);

	//	ss.Lines.push_back(segment);
	}

	return ss;
}

std::string StringSplitter::CutInHalfAndTakeRightValue(std::string content, char splitToken)
{
	unsigned int startIndex = content.find(splitToken) + 1;
	content = content.substr(startIndex);

	return content;
}
