#include "Text.h"

#include <Memory/Memory.h>
#include <Math/Math.h>

#include <stdarg.h> 

#define PXTextAssertEnable 1

#if PXTextAssertEnable
#include <assert.h>
#endif

size_t TextToIntA(const char* string, const size_t dataSize, int* number)
{
	int accumulator = 0;
	size_t index = 0;
	unsigned char isNegative = 0;

	if(!string)
	{
		return 0;
	}

	if(string[0] == '-')
	{
		index++;
		isNegative = 1u;
	}

	while(string[index] != '\0')
	{
		char character = string[index];
		char isValidCharacter = (character >= '0' && character <= '9');
		int numberElement = character - '0';

		if(!isValidCharacter)
		{
			break;
		}

		accumulator *= 10; // "Shft number to left" Example 12 -> 120
		accumulator += numberElement; // ASCII character to actual number.

		++index;
	}

	if(isNegative)
	{
		accumulator *= -1;
	}

	*number = accumulator;

	return index;
}

size_t TextToIntW(const wchar_t* string, const size_t dataSize, int* number)
{
	size_t index = 0;
	unsigned char isNegative = 0;
	int accumulator = 0;

	if(!string)
	{
		return 0;
	}

	if(string[0] == '-')
	{
		index++;
		isNegative = 1u;
	}

	while(string[index] != '\0')
	{
		char character = string[index];
		char isValidCharacter = (character >= '0' && character <= '9');
		int numberElement = character - '0';

		if(!isValidCharacter)
		{
			break;
		}

		accumulator *= 10; // "Shft number to left" Example 12 -> 120
		accumulator += numberElement; // ASCII character to actual number.

		++index;
	}

	if(isNegative)
	{
		accumulator *= -1;
	}

	*number = accumulator;

	return index;
}

size_t TextToBoolA(const char* string, const size_t dataSize, unsigned char* number)
{
	switch(string[0])
	{
		default:
		case '0':
		case 'F':
		case 'f':
			*number = 0;
			break;

		case '1':
		case 'T':
		case 't':
			*number = 1u;
			break;
	}

	return 1u;
}

size_t TextToBoolW(const wchar_t* string, const size_t dataSize, unsigned char* number)
{
	return 0;
}

size_t TextToFloatA(const char* string, const size_t dataSize, float* number)
{
	double x = 0;

	const size_t readBytes = TextToDoubleA(string, dataSize, &x);

	*number = (float)x;

	return readBytes;
}

size_t TextToFloatW(const wchar_t* string, const size_t dataSize, float* number)
{
	return 0;
}

size_t TextToDoubleA(const char* string, const size_t dataSize, double* number)
{
	int accumulator = 0;
	size_t digitsAfterDot = 1;
	size_t index = 0;
	unsigned char isNegative = 0;
	unsigned char isWholeNumberChunk = 1;

	if(!string)
	{
		return 0;
	}

	if(string[0] == '-')
	{
		index++;
		isNegative = 1;
	}

	for(; string[index] != '\0'; ++index)
	{
		const char character = string[index];
		const unsigned char isDot = character == '.';
		const unsigned char isValidCharacter = (character >= '0' && character <= '9') || isDot;
		const int numberElement = character - '0';

		if(!isValidCharacter)
		{
			break;
		}

		// Trigger when we switch to after dot
		if(isDot && isWholeNumberChunk)
		{
			isWholeNumberChunk = 0;
			continue;
		}

		accumulator *= 10; // "Shft number to left" Example 12 -> 120
		accumulator += numberElement; // ASCII character to actual number.

		if(!isWholeNumberChunk)
		{
			digitsAfterDot *= 10;
		}
	}

	if(isNegative)
	{
		accumulator *= -1;
	}

	//double stdResult = std::strtof(string, 0); // STD Method

	// Calculate
	{
		const double a = accumulator;
		const double b = digitsAfterDot;
		const double c = a / b;

		*number = c;
	}

	return index;
}

size_t TextToDoubleW(const wchar_t* string, const size_t dataSize, double* number)
{
	return 0;
}

size_t TextClearA(char* string, const size_t stringSize)
{
	MemorySet(string, stringSize * sizeof(char), 0x00);

	return stringSize;
}

size_t TextClearW(wchar_t* string, const size_t stringSize)
{
	MemorySet(string, stringSize * sizeof(wchar_t), 0x00);

	return stringSize;
}

size_t TextLengthA(const char* string, const size_t stringSize)
{
	size_t index = 0;

	for(; (string[index] != '\0'); ++index);

	return index;
}

size_t TextLengthW(const wchar_t* string)
{
	size_t index = 0;

	for(; (string[index] != L'\0'); ++index);

	return index;
}

size_t TextLengthUntilA(const char* string, const size_t stringSize, const char character)
{
	size_t index = 0;

	for(; (index < stringSize) && (string[index] != '\0') && (string[index] != character); ++index);

	return index;
}

size_t TextLengthUntilW(const wchar_t* string, const size_t stringSize, const wchar_t character)
{
	return 0;
}

size_t TextCopyA(const char* source, const size_t sourceLength, char* destination, const size_t destinationLength)
{
	const size_t minLength = MathMinimum(sourceLength, destinationLength);
	size_t i = 0;

#if PXTextAssertEnable
	assert(destination);
	assert(source);
#endif	

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

size_t TextCopyAW(const char* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength)
{
	const size_t minLength = MathMinimum(sourceLength, destinationLength);
	size_t i = 0;

#if PXTextAssertEnable
	assert(destination);
	assert(source);
#endif	

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

size_t TextCopyWA(const wchar_t* source, const size_t sourceLength, char* destination, const size_t destinationLength)
{
	const size_t minLength = MathMinimum(sourceLength, destinationLength);
	size_t i = 0;

#if PXTextAssertEnable
	assert(destination);
	assert(source);
#endif	

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = UnicodeToASCII(source[i]);
	}

	destination[i] = '\0';

	return i;
}

size_t TextCopyW(const wchar_t* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength)
{
	const size_t minLength = MathMinimum(sourceLength, destinationLength);
	size_t i = 0;

#if PXTextAssertEnable
	assert(destination);
	assert(source);
#endif	

	for(; (i < minLength) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

size_t TextCountUntilA(const char* text, const size_t textSize, const char target, const char stopAt)
{
	size_t samecounter = 0;

	for(size_t index = 0; (index < textSize) && (text[index] != '\0' && text[index] != stopAt); ++index)
		samecounter += target == text[index];

	return samecounter;
}

size_t TextCountUntilW(const wchar_t* text, const size_t textSize, const wchar_t target, const wchar_t stopAt)
{
	size_t samecounter = 0;

	for(size_t index = 0; (index < textSize) && (text[index] != '\0' && text[index] != stopAt); ++index)
		samecounter += target == text[index];

	return samecounter;
}

char TextCompareA(const char* a, const size_t aSize, const char* b, const size_t bSize)
{
	const size_t textSize = MathMinimum(aSize, bSize);

	size_t index = 0;
	size_t samecounter = 0;

	for(; (index < textSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	if(index < textSize) // Still in range but encountered an \0 in a or b 
	{
		samecounter += a[index] == b[index]; // One of them is \0, check this too
		++index; // keep for comparsion
	}

	return (index == samecounter);
}

char TextCompareAW(const char* a, const size_t aSize, const wchar_t* b, const size_t bSize)
{
	const size_t textSize = MathMinimum(aSize, bSize);

	size_t index = 0;
	size_t samecounter = 0;

	for(; (index < textSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	return (index == samecounter);
}

char TextCompareW(const wchar_t* a, const size_t aSize, const wchar_t* b, const size_t bSize)
{
	const size_t textSize = MathMinimum(aSize, bSize);

	size_t index = 0;
	size_t samecounter = 0;

	for(; (index < textSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	return (index == samecounter);
}

char TextCompareWA(const wchar_t* a, const size_t aSize, const char* b, const size_t bSize)
{
	const size_t textSize = MathMinimum(aSize, bSize);

	size_t index = 0;
	size_t samecounter = 0;

	for(; (index < textSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	return (index == samecounter);
}

char TextCompareIgnoreCaseA(const char* a, const size_t aSize, const char* b, const size_t bSize)
{
	const size_t textSize = MathMinimum(aSize, bSize);

	size_t index = 0;
	size_t samecounter = 0;
	unsigned char wasLastLetterSame = 1;

	for(; (index < textSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore(a[index], b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}

char TextCompareIgnoreCaseW(const wchar_t* a, const size_t aSize, const wchar_t* b, const size_t bSize)
{
	const size_t textSize = MathMinimum(aSize, bSize);

	size_t index = 0;
	size_t samecounter = 0;
	unsigned char wasLastLetterSame = 1;

	for(; (index < textSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore(a[index], b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}

char TextCompareIgnoreCaseAW(const char* a, const size_t aSize, const wchar_t* b, const size_t bSize)
{
	const size_t textSize = MathMinimum(aSize, bSize);

	size_t index = 0;
	size_t samecounter = 0;
	unsigned char wasLastLetterSame = 1;

	for(; (index < textSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore((wchar_t)a[index], b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}

char TextCompareIgnoreCaseWA(const wchar_t* a, const size_t aSize, const char* b, const size_t bSize)
{
	size_t index = 0;
	size_t samecounter = 0;
	unsigned char wasLastLetterSame = 1;

	for(; (index < aSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore(a[index], (wchar_t)b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}

char* TextFindPositionA(const char* data, size_t dataSize, const char* target, size_t targetSize)
{
	const char* source = 0;
	unsigned char found = 0;

	for(size_t i = 0; (data[i] != '\0') && (i + targetSize) < dataSize && !found; i++)
	{
		source = data + i;
		found = TextCompareA(source, targetSize-i, target, targetSize);
	}

	return (char*)(found * (size_t)source);
}

size_t TextFindFirstA(const char* string, const size_t dataSize, const char character)
{
	size_t i = 0;

	for(unsigned char found = 0; (string[i] != '\0') && i < dataSize && !found; ++i)
	{
		found = character == string[i];
	}

	--i;

	return i;
}

size_t TextFindLastA(const char* string, const size_t dataSize, const char character)
{
	unsigned char found = 0;
	size_t i = TextLengthA(string, dataSize);

	for(; i > 0 && !found; --i)
	{
		found = character == string[i];
	}

	++i;
	
	return found ? i+1 : TextIndexNotFound;
}

size_t TextFindLastW(const wchar_t* string, const size_t dataSize, const wchar_t character)
{
	unsigned char found = 0;
	size_t i = TextLengthW(string, dataSize);

	for(; i > 0 && !found; --i)
	{
		found = character == string[i];
	}

	return found ? i+1 : TextIndexNotFound;
}

void TextTerminateBeginFromFirstA(char* string, const size_t dataSize, const char character)
{
	size_t index = TextFindFirstA(string, dataSize, character);

	if(index != -1)
	{
		string[index] = '\0';
	}
}

void TextParseA(const char* buffer, const size_t bufferSize, const char* syntax, ...)
{
	va_list args;
	va_start(args, syntax);

	size_t offsetData = 0;

	for(size_t commandIndex = 0; syntax[commandIndex] != '\0'; ++commandIndex)
	{
		const char commandKey = syntax[commandIndex];
		//const bool commandIsNumber = commandKey == 'i' || commandKey == 'f' || commandKey == 'u';

		size_t offsetLength = offsetData;

		// Get length until new block
		{
			while(offsetLength < bufferSize)
			{
				const char symbol = buffer[offsetLength];
				const unsigned char stop = symbol == '\n' || symbol == '\0' || symbol == ' ';
				//const bool skip = symbol == '\n'; 	if(commandIsNumber && current == '/' || current == ' ' || finished)

				if(stop)
				{
					break; // End of string
				}

				++offsetLength;
			}
		}

		switch(commandKey)
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

				const size_t readBytes = TextCopyA(source, offsetLength, destination, -1);

				offsetData += readBytes;

				break;
			}
			case 'i':
			case 'd':
			case 'u':
			{
				int* i = va_arg(args, int*);
				const char* source = buffer + offsetData;

				const size_t readBytes = TextToIntA(source, offsetLength, i);

				assert(readBytes);

				offsetData += readBytes;

				break;
			}
			case 'f':
			{
				float* number = va_arg(args, float*);
				const char* source = buffer + offsetData;

				const size_t readBytes = TextToFloatA(source, offsetLength, number);

				assert(readBytes);

				offsetData += readBytes;

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
			const unsigned char stop = !(symbol == ' ' || symbol == '\0');

			if(stop)
			{
				break;
			}

			++offsetData;
		}
	}

	va_end(args);
}

void TextParseFindAllA(const char* string, const size_t stringSize, const ParsingTokenA* parsingTokenList, const size_t parsingTokenListSize)
{
	unsigned char finished = 0;
	unsigned char foundItem = 0;
	size_t foundTargets = 0;

	for(size_t i = 0; (i < stringSize) && (string[i] != '\0') && !finished; ++i)
	{
		foundItem = 0;

		for(size_t t = 0; (t < parsingTokenListSize) && (string[i] != ' ') && !foundItem; t++)
		{
			const ParsingTokenA* parsingToken = &parsingTokenList[t];
			const char* targetString = parsingToken->String;
			const size_t targetStringSize = TextLengthA(targetString, -1);
			const char* sourceString = string + i;

			foundItem = TextCompareA(sourceString, stringSize, targetString, targetStringSize); // Compare whole word

			if(foundItem)
			{
				size_t lengthTag = TextLengthUntilA(sourceString, stringSize, '=');
				const char* valueString = sourceString + lengthTag + 1;

				i += lengthTag + 1;

				(*parsingToken->Value) = valueString;

				for(; (string[i] != '\0') && string[i] != ' '; i++); // Skip data	

				++foundTargets;
			}
		}

		finished = foundTargets == parsingTokenListSize;
	}
}