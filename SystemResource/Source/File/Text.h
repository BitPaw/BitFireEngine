#pragma once

#include <cwchar>

namespace BF
{
	struct Text
	{
		public:
		static void AsciiToUnicode(char* input, size_t inputSize, wchar_t* output, size_t outputSize);
		static void UnicodeToAscii(wchar_t* input, size_t inputSize, char* output, size_t outputSize);

		static void Clear(char* string, const size_t stringSize);
		static void Clear(wchar_t* string, const size_t stringSize);

		static void Copy(char* destination, const char* source, const size_t stringSize);
		static void Copy(wchar_t* destination, const wchar_t* source, const size_t stringSize);

		static int Compare(const char* a, const char* b, const size_t stringSize);
		static int Compare(const wchar_t* a, const wchar_t* b, const size_t stringSize);
		static int Compare(const char* a, const wchar_t* b, const size_t stringSize);
		static int Compare(const wchar_t* a, const char* b, const size_t stringSize);
		static int CompareIgnoreCase(const char* a, const char* b, const size_t stringSize);
		static int CompareIgnoreCase(const wchar_t* a, const wchar_t* b, const size_t stringSize);
		static int CompareIgnoreCase(const char* a, const wchar_t* b, const size_t stringSize);
		static int CompareIgnoreCase(const wchar_t* a, const char* b, const size_t stringSize);
	};
}