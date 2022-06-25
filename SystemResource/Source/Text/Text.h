#pragma once

#include <cwchar>

#include <File/ParsingToken.h>

#define MakeLetterCaseLower(character) (character | 0b00100000)
#define MakeLetterCaseUpper(character) (character & 0b11011111)
#define CompareLetterCaseIgnore(a, b) (MakeLetterCaseLower(a) == b) || (MakeLetterCaseUpper(a) == b)
#define UnicodeToASCII(wc) (wc <= 0xFF ? (char)wc : '?') 

namespace BF
{
	struct Text
	{
		public:
		static void Clear(char* string, const size_t stringSize);
		static void Clear(wchar_t* string, const size_t stringSize);

		static size_t Length(const char* string);
		static size_t LengthUntil(const char* string, const size_t stringSize, const char character);
		static size_t Length(const wchar_t* string);

		static size_t Copy(const char* source, const size_t sourceLength, char* destination, const size_t destinationLength);
		static size_t Copy(const char* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength);
		static size_t Copy(const wchar_t* source, const size_t sourceLength, char* destination, const size_t destinationLength);
		static size_t Copy(const wchar_t* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength);

		static int Compare(const char* a, const size_t aSize, const char* b, const size_t bSize);

		static size_t CountUntil(const char* text, const size_t textSize, const char target, const char stopAt);
		static size_t CountUntil(const unsigned char* text, const size_t textSize, const unsigned char target, const unsigned char stopAt);
		static size_t CountUntil(const wchar_t* text, const size_t textSize, const wchar_t target, const wchar_t stopAt);

		static int Compare(const char* a, const char* b, const size_t stringSize);
		static int Compare(const wchar_t* a, const wchar_t* b, const size_t stringSize);
		static int Compare(const char* a, const wchar_t* b, const size_t stringSize);
		static int Compare(const wchar_t* a, const char* b, const size_t stringSize);
		static int CompareIgnoreCase(const char* a, const char* b, const size_t stringSize);
		static int CompareIgnoreCase(const wchar_t* a, const wchar_t* b, const size_t stringSize);
		static int CompareIgnoreCase(const char* a, const wchar_t* b, const size_t stringSize);
		static int CompareIgnoreCase(const wchar_t* a, const char* b, const size_t stringSize);

		static char* FindPosition(const char* data, size_t dataSize, const char* target, size_t targetSize);
		static size_t ToInt(const char* string, const size_t dataSize, int& number);
		static size_t ToInt(const wchar_t* string, const size_t dataSize, int& number);
		static size_t ToBool(const char* string, const size_t dataSize, bool& number);
		static size_t ToFloat(const char* string, const size_t dataSize, float& number);
		static size_t ToDouble(const char* string, const size_t dataSize, double& number);

		static size_t FindFirst(const char* string, const size_t dataSize, const char character);
		static size_t FindLast(const char* string, const size_t dataSize, const char character);
		static size_t FindLast(const wchar_t* string, const size_t dataSize, const wchar_t character);

		static void TerminateBeginFromFirst(char* string, const size_t dataSize, const char character);

		static void Parse(const char* buffer, const size_t bufferSize, const char* syntax, ...);

		static void FindAll(const char* string, const size_t stringSize, const ParsingToken* parsingTokenList, const size_t parsingTokenListSize);
	};
}