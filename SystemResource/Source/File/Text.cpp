#include "Text.h"

void BF::Text::AsciiToUnicode(char* input, size_t inputSize, wchar_t* output, size_t outputSize)
{
}

void BF::Text::UnicodeToAscii(wchar_t* input, size_t inputSize, char* output, size_t outputSize)
{
}

void BF::Text::Clear(char* string, const size_t stringSize)
{
	memset(string, 0, sizeof(char) * stringSize);
}

void BF::Text::Clear(wchar_t* string, const size_t stringSize)
{
	memset(string, 0, sizeof(wchar_t) * stringSize);
}

void BF::Text::Copy(char* destination, const char* source, const size_t stringSize)
{
	size_t i = 0;

	for (; (i < stringSize) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';
}

void BF::Text::Copy(wchar_t* destination, const wchar_t* source, const size_t stringSize)
{
	// lstrcpyW(Path, filePath);

	size_t i = 0;

	for (; (i < stringSize) && (source[i] != '\0'); ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';
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
	int samecounter = 0; // counts how many times we detected same characters

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
	{
		// count +1 if a is lowercase or uppercase

		samecounter +=
			(a[index] | 0b00100000) == (wchar_t)b[index] || // lowercase check
			(a[index] & 0b11011111) == (wchar_t)b[index]; // uppercase check


		// a | 0b00100000 -> this exact bit will make the letter lowercase
		// a & 0b11011111 -> "Take all bist exept one"
	}	

	return index == samecounter; // Did we countes as much as we read?
}

int BF::Text::CompareIgnoreCase(const wchar_t* a, const wchar_t* b, const size_t stringSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
	{
		samecounter +=
			(a[index] | 0b00100000) == b[index] ||
			(a[index] & 0b11011111) == b[index];
	}

	return index == samecounter;
}

int BF::Text::CompareIgnoreCase(const char* a, const wchar_t* b, const size_t stringSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
	{
		samecounter +=
			((wchar_t)a[index] | 0b00100000) == b[index] ||
			((wchar_t)a[index] & 0b11011111) == b[index];
	}

	return index == samecounter;
}

int BF::Text::CompareIgnoreCase(const wchar_t* a, const char* b, const size_t stringSize)
{
	size_t index = 0;
	int samecounter = 0;

	for (; (index < stringSize) && (a[index] != '\0') && (b[index] != '\0'); ++index)
	{
		samecounter +=
			(a[index] | 0b00100000) == (wchar_t)b[index] ||
			(a[index] & 0b11011111) == (wchar_t)b[index];
	}

	return index == samecounter;
}