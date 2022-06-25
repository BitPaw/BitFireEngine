#include "Text.h"

#include <cstring>
#include <cassert>
#include <cstdarg>

#include <Hardware/Memory/Memory.h>

#include <Math/Math.h>


void BF::Text::Clear(char* string, const size_t stringSize)
{
	Memory::Set(string, 0, sizeof(char) * stringSize);
}

void BF::Text::Clear(wchar_t* string, const size_t stringSize)
{
	Memory::Set(string, 0, sizeof(wchar_t) * stringSize);
}

size_t BF::Text::Length(const char* string)
{
	size_t index = 0;

	for (; (string[index] != '\0'); ++index);

	return index;
}

size_t BF::Text::LengthUntil(const char* string, const size_t stringSize, const char character)
{
	size_t index = 0;

	for (; (index < stringSize) && (string[index] != '\0') && (string[index] != character); ++index);

	return index;
}

size_t BF::Text::Length(const wchar_t* string)
{
	size_t index = 0;

	for (; (string[index] != L'\0'); ++index);

	return index;
}

size_t BF::Text::Copy(const char* source, const size_t sourceLength, char* destination, const size_t destinationLength)
{
	const size_t minLength = Math::Minimum(sourceLength, destinationLength);
	size_t i = 0;

	assert(destination);
	assert(source);

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

size_t BF::Text::Copy(const char* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength)
{
	const size_t minLength = Math::Minimum(sourceLength, destinationLength);
	size_t i = 0;

	assert(destination);
	assert(source);

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

size_t BF::Text::Copy(const wchar_t* source, const size_t sourceLength, char* destination, const size_t destinationLength)
{
	const size_t minLength = Math::Minimum(sourceLength, destinationLength);
	size_t i = 0;

	assert(destination);
	assert(source);

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = UnicodeToASCII(source[i]);
	}

	destination[i] = '\0';

	return i;
}

size_t BF::Text::Copy(const wchar_t* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength)
{
	const size_t minLength = Math::Minimum(sourceLength, destinationLength);
	size_t i = 0;

	assert(destination);
	assert(source);

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

int BF::Text::Compare(const char* a, const size_t aSize, const char* b, const size_t bSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < aSize) && (index < bSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	return (index == samecounter) && ((index == aSize) && (index == bSize));
}

size_t BF::Text::CountUntil(const char* text, const size_t textSize, const char target, const char stopAt)
{
	return CountUntil(text, textSize, target, stopAt);
}

size_t BF::Text::CountUntil(const unsigned char* text, const size_t textSize, const unsigned char target, const unsigned char stopAt)
{
	size_t samecounter = 0;

	for(size_t index = 0; (index < textSize) && (text[index] != '\0' && text[index] != stopAt); ++index)
		samecounter += target == text[index];

	return samecounter;
}

size_t BF::Text::CountUntil(const wchar_t* text, const size_t textSize, const wchar_t target, const wchar_t stopAt)
{
	return size_t();
}

int BF::Text::Compare(const char* a, const char* b, const size_t stringSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	return (index == samecounter);
}

int BF::Text::Compare(const wchar_t* a, const wchar_t* b, const size_t stringSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	return index == samecounter;
}

int BF::Text::Compare(const char* a, const wchar_t* b, const size_t stringSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += (wchar_t)a[index] == b[index];	

	return index == samecounter;
}

int BF::Text::Compare(const wchar_t* a, const char* b, const size_t stringSize)
{
	size_t index = 0;
	size_t samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == (wchar_t)b[index];

	return index == samecounter;
}

int BF::Text::CompareIgnoreCase(const char* a, const char* b, const size_t stringSize)
{
	size_t index = 0; // Number of characters that will be read
	size_t counterOfSameCharacters = 0; // counts how many times we detected same characters
	bool wasLastLetterSame = true;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore(a[index], b[index]);
		counterOfSameCharacters += wasLastLetterSame;
	}	

	return index == counterOfSameCharacters; // Did we countes as much as we read?
}

int BF::Text::CompareIgnoreCase(const wchar_t* a, const wchar_t* b, const size_t stringSize)
{
	size_t index = 0;
	size_t samecounter = 0;
	bool wasLastLetterSame = true;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore(a[index], b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}

int BF::Text::CompareIgnoreCase(const char* a, const wchar_t* b, const size_t stringSize)
{
	size_t index = 0;
	size_t samecounter = 0;
	bool wasLastLetterSame = true;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore((wchar_t)a[index], b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}

int BF::Text::CompareIgnoreCase(const wchar_t* a, const char* b, const size_t stringSize)
{
	size_t index = 0;
	size_t samecounter = 0;
	bool wasLastLetterSame = true;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore(a[index], (wchar_t)b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}

char* BF::Text::FindPosition(const char* data, size_t dataSize, const char* target, size_t targetSize)
{
	const char* source = nullptr;
	bool found = false;

	for (size_t i = 0; (data[i] != '\0') && (i + targetSize) < dataSize && !found; i++)
	{
		source = data + i;
		found = Text::Compare(source, target, targetSize);
	}

	return (char*)(found * (size_t)source);
}

size_t BF::Text::ToInt(const char* string, size_t dataSize, int& number)
{
	size_t index = 0;
	bool isNegative = false;	

	number = 0;

	if (!string)
	{
		return 0;
	}

	if (string[0] == '-')
	{
		index++;
		isNegative = true;
	}

	while (string[index] != '\0')
	{
		char character = string[index];
		char isValidCharacter = (character >= '0' && character <= '9');
		int numberElement = character - '0';

		if (!isValidCharacter)
		{
			break;
		}

		number *= 10; // "Shft number to left" Example 12 -> 120
		number += numberElement; // ASCII character to actual number.

		++index;
	}

	if (isNegative)
	{
		number *= -1;
	}

	return index;
}

size_t BF::Text::ToInt(const wchar_t* string, const size_t dataSize, int& number)
{
	size_t index = 0;
	bool isNegative = false;

	number = 0;

	if(!string)
	{
		return 0;
	}

	if(string[0] == '-')
	{
		index++;
		isNegative = true;
	}

	for(; string[index] != '\0'; index++)
	{
		char character = string[index];
		char isValidCharacter = (character >= '0' && character <= '9');
		int numberElement = character - '0';

		if(!isValidCharacter)
		{
			break;
		}

		number *= 10; // "Shft number to left" Example 12 -> 120
		number += numberElement; // ASCII character to actual number.
	}

	if(isNegative)
	{
		number *= -1;
	}

	return index;
}

size_t BF::Text::ToBool(const char* string, size_t dataSize, bool& number)
{
	switch (string[0])
	{
		default:
		case '0':
		case 'F':
		case 'f':
			number = false;
			break;

		case '1':
		case 'T':
		case 't':
			number = true;
			break;
	}

	return 1;
}

size_t BF::Text::ToFloat(const char* string, const size_t dataSize, float& number)
{
	double x = 0;

	size_t readBytes = Text::ToDouble(string, dataSize, x);

	number = (float)x;

	return readBytes;
}

size_t BF::Text::ToDouble(const char* string, const size_t dataSize, double& number)
{
	unsigned int digitsAfterDot = 1;
	bool isWholeNumberChunk = true;

	unsigned int index = 0;
	bool isNegative = false;

	number = 0;

	if (!string)
	{
		return 0;
	}

	if (string[0] == '-')
	{
		index++;
		isNegative = true;
	}

	for (; string[index] != '\0'; index++)
	{
		char character = string[index];
		bool isDot = character == '.';
		bool isValidCharacter = (character >= '0' && character <= '9') || isDot;
		int numberElement = character - '0';

		if (!isValidCharacter)
		{
			break;
		}

		// Trigger when we switch to after dot
		if (isDot && isWholeNumberChunk)
		{
			isWholeNumberChunk = false;
			continue;
		}

		number *= 10; // "Shft number to left" Example 12 -> 120
		number += numberElement; // ASCII character to actual number.

		if (!isWholeNumberChunk)
		{
			digitsAfterDot *= 10;
		}
	}

	if (isNegative)
	{
		number *= -1;
	}

	//double stdResult = std::strtof(string, 0); // STD Method
	number /= (double)digitsAfterDot;

	return index;
}

size_t BF::Text::FindFirst(const char* string, const size_t dataSize, const char character)
{
	size_t i = 0;

	for (bool found = false; (string[i] != '\0') && i < dataSize && !found; ++i)
	{
		found = character == string[i];
	}

	--i;

	return i;
}

size_t BF::Text::FindLast(const char* string, const size_t dataSize, const char character)
{
	bool found = false;
	size_t i = Length(string);

	for (; i > 0 && !found; --i)
	{
		found = character == string[i];
	}

	return i;
}

size_t BF::Text::FindLast(const wchar_t* string, const size_t dataSize, const wchar_t character)
{
	bool found = false;
	size_t i = Length(string);

	for (; i > 0 && !found; --i)
	{
		found = character == string[i];
	}

	i++;

	return i;
}

void BF::Text::TerminateBeginFromFirst(char* string, const size_t dataSize, const char character)
{
	size_t index = FindFirst(string, dataSize, character);

	if (index != -1)
	{
		string[index] = '\0';
	}
}

void BF::Text::Parse(const char* buffer, const size_t bufferSize, const char* syntax, ...)
{
	va_list args;
	va_start(args, syntax);

	size_t offsetData = 0;

	for (size_t commandIndex = 0 ; syntax[commandIndex] != '\0' ; ++commandIndex)
	{
		const char commandKey = syntax[commandIndex];
		//const bool commandIsNumber = commandKey == 'i' || commandKey == 'f' || commandKey == 'u';

		size_t offsetLength = offsetData;

		// Get length until new block
		{
			while(offsetLength < bufferSize)
			{
				const char symbol = buffer[offsetLength];
				const bool stop = symbol == '\n' || symbol == '\0' || symbol == ' ';
				//const bool skip = symbol == '\n'; 	if(commandIsNumber && current == '/' || current == ' ' || finished)

				if(stop)
				{				
					break; // End of string
				}

				++offsetLength;
			}
		}		

		switch (commandKey)
		{
			case '§':
			{
				++offsetData;
				break;
			}
			case 's':
			{
				char* destination = va_arg(args, char*);
				const char* source = buffer + offsetData;

				Memory::Copy(destination, source, offsetLength);
				destination[offsetLength] = '\0';
				break;
			}
			case 'i':
			case 'd':
			case 'u':
			{
				int* i = va_arg(args, int*);
				const char* source = buffer + offsetData;

				offsetData += ToInt(source, offsetLength, *i);

				break;
			}
			case 'f':
			{
				float* number = va_arg(args, float*);
				const char* source = buffer + offsetData;

				offsetData += ToFloat(source, offsetLength, (*number));

				break;
			}
			case 'c':
			{
				char* character = va_arg(args, char*);
				const char* source = buffer + offsetData;

				*character = *source;

				break;
			}
			default:
				break;
		}		

		while(offsetData < bufferSize)
		{
			const char symbol = buffer[offsetData];
			const bool stop = !(symbol == ' ' || symbol == '\0');

			if(stop)
			{
				break;
			}

			++offsetData;
		}
	}

	va_end(args);
}

void BF::Text::FindAll(const char* string, const size_t stringSize, const ParsingToken* parsingTokenList, const size_t parsingTokenListSize)
{
	bool finished = false;
	bool foundItem = false;
	size_t foundTargets = 0;

	for (size_t i = 0; (i < stringSize) && (string[i] != '\0') && !finished; ++i)
	{	
		foundItem = false;

		for (size_t t = 0; (t < parsingTokenListSize) && (string[i] != ' ') && !foundItem; t++)
		{
			const ParsingToken& parsingToken = parsingTokenList[t];
			const char* targetString = parsingToken.String;
			const size_t targetStringSize = Length(targetString);
			const char* sourceString = string + i;		

			foundItem = Compare(sourceString, targetString, targetStringSize); // Compare whole word

			if (foundItem)
			{
				size_t lengthTag = LengthUntil(sourceString, stringSize, '=');
				const char* valueString = sourceString + lengthTag + 1;

				i += lengthTag + 1;				

				(*parsingToken.Value) = valueString;

				for (; (string[i] != '\0') && string[i] != ' '; i++); // Skip data	

				++foundTargets;
			}
		}

		finished = foundTargets == parsingTokenListSize;
	}
}