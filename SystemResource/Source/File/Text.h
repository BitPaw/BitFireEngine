#pragma once

#include <cwchar>

#include "ParsingToken.h"

namespace BF
{
	struct Text
	{
		public:
		static wchar_t AsciiToUnicode(char character);
		static char UnicodeToAscii(wchar_t character);

		static size_t AsciiToUnicode(const char* input, const size_t inputSize, wchar_t* output, const size_t outputSize);
		static size_t UnicodeToAscii(const wchar_t* input, const size_t inputSize, char* output, const size_t outputSize);

		static void Clear(char* string, const size_t stringSize);
		static void Clear(wchar_t* string, const size_t stringSize);

		static size_t Length(const char* string);
		static size_t LengthUntil(const char* string, const size_t stringSize, const char character);
		static size_t Length(const wchar_t* string);

		static size_t Copy(char* destination, const char* source, const size_t stringSize);
		static size_t Copy(char* destination, const wchar_t* source, const size_t stringSize);
		static size_t Copy(wchar_t* destination, const char* source, const size_t stringSize);
		static size_t Copy(wchar_t* destination, const wchar_t* source, const size_t stringSize);

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
		static size_t ToBool(const char* string, const size_t dataSize, bool& number);
		static size_t ToFloat(const char* string, const size_t dataSize, float& number);
		static size_t ToDouble(const char* string, const size_t dataSize, double& number);

		static size_t FindFirst(const char* string, const size_t dataSize, const char character);
		static size_t FindLast(const char* string, const size_t dataSize, const char character);
		static size_t FindLast(const wchar_t* string, const size_t dataSize, const wchar_t character);

		static void TerminateBeginFromFirst(char* string, const size_t dataSize, const char character);



		static void FindAll(const char* string, const size_t stringSize, const ParsingToken* parsingTokenList, const size_t parsingTokenListSize);
	};
}