#include "Text.h"

#include <cstring>
#include <cassert>

#define MakeLetterCaseLower(character) (character | 0b00100000)
#define MakeLetterCaseUpper(character) (character & 0b11011111)
#define CompareLetterCaseIgnore(a, b) (MakeLetterCaseLower(a) == b) || (MakeLetterCaseUpper(a) == b)

inline wchar_t BF::Text::AsciiToUnicode(char character)
{
	return (wchar_t)character;
}

inline char BF::Text::UnicodeToAscii(wchar_t character)
{
	const bool isToBig = character > 255u;
	const char result = (!isToBig * character) + (isToBig * '?');

	return result;
}

size_t BF::Text::AsciiToUnicode(const char* input, const size_t inputSize, wchar_t* output, const  size_t outputSize)
{
	size_t i = 0;

	for (; (i < inputSize) && (input[i] != '\0') && (i < outputSize); ++i)
	{
		output[i] = input[i];
	}

	output[i] = L'\0';

	return i;
}

size_t BF::Text::UnicodeToAscii(const wchar_t* input, const size_t inputSize, char* output, const size_t outputSize)
{
	size_t i = 0;

	for (; (i < inputSize) && (output[i] != L'\0') && (i < outputSize); ++i)
	{
		output[i] = AsciiToUnicode(input[i]);
	}

	output[i] = '\0';

	return i;
}

void BF::Text::Clear(char* string, const size_t stringSize)
{
	memset(string, 0, sizeof(char) * stringSize);
}

void BF::Text::Clear(wchar_t* string, const size_t stringSize)
{
	memset(string, 0, sizeof(wchar_t) * stringSize);
}

size_t BF::Text::Length(const char* string)
{
	size_t index = 0;

	for (; (string[index] != '\0'); ++index);

	return index;
}

size_t BF::Text::Length(const wchar_t* string)
{
	size_t index = 0;

	for (; (string[index] != L'\0'); ++index);

	return index;
}

size_t BF::Text::Copy(char* destination, const char* source, const size_t stringSize)
{
	size_t i = 0;

	assert(destination);
	assert(source);

	for (; (i < stringSize) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

size_t BF::Text::Copy(char* destination, const wchar_t* source, const size_t stringSize)
{
	size_t i = 0;

	assert(destination);
	assert(source);

	for (; (i < stringSize) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

size_t BF::Text::Copy(wchar_t* destination, const char* source, const size_t stringSize)
{
	size_t i = 0;

	for (; (i < stringSize) && (source[i] != '\0'); ++i)
	{
		destination[i] = AsciiToUnicode(source[i]);
	}

	destination[i] = '\0';

	return i;
}

size_t BF::Text::Copy(wchar_t* destination, const wchar_t* source, const size_t stringSize)
{
	// lstrcpyW(Path, filePath);

	size_t i = 0;

	for (; (i < stringSize) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	return i;
}

int BF::Text::Compare(const char* a, const char* b, const size_t stringSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
		samecounter += a[index] == b[index];

	return index == samecounter;
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
	int samecounter = 0;

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
	int samecounter = 0;
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
	int samecounter = 0;
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
	int samecounter = 0;
	bool wasLastLetterSame = true;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0') && wasLastLetterSame; ++index)
	{
		wasLastLetterSame = CompareLetterCaseIgnore(a[index], (wchar_t)b[index]);
		samecounter += wasLastLetterSame;
	}

	return index == samecounter;
}