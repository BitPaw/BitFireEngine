#if !defined(TextInclude)
#define TextInclude

#include <stddef.h>

#define MakeLetterCaseLower(character) (character | 0b00100000)
#define MakeLetterCaseUpper(character) (character & 0b11011111)
#define CompareLetterCaseIgnore(a, b) (MakeLetterCaseLower(a) == b) || (MakeLetterCaseUpper(a) == b)
#define UnicodeToASCII(wc) (wc <= 0xFF ? (char)wc : '?')

#define TextUnkownLength -1
#define TextIndexNotFound -1

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct ParsingTokenA_
	{
		const char* String;
		const char** Value;
	}
	ParsingTokenA;

	typedef enum TextFormat_
	{
		TextFormatInvalid,

		// 1 Byte__ per character, range from 0 to 255
		TextFormatASCII,

		// 2 Bytes per character, range from 0 to 65535
		TextFormatUNICODE,

		// Variable length of characters, 1 to 4 Bytes
		TextFormatUTF8,
		TextFormatUTF16
	}
	TextFormat;

	typedef struct Text_
	{
		TextFormat Format;
		size_t SizeInCharacters;
		size_t SizeInBytes;

		union
		{
			char* TextA;
			wchar_t* TextW;
			void* TextData;
		};
	}
	Text;

	extern size_t TextFromIntA(const int number,  char* string, const size_t dataSize);
	extern size_t TextFromIntW(const int number,  wchar_t* string, const size_t dataSize);
	extern size_t TextFromBoolA(const unsigned char number,  char* string, const size_t dataSize);
	extern size_t TextFromBoolW(const unsigned char number,  wchar_t* string, const size_t dataSize);
	extern size_t TextFromFloatA(const float number,  char* string, const size_t dataSize);
	extern size_t TextFromFloatW(const float number,  wchar_t* string, const size_t dataSize);
	extern size_t TextFromDoubleA(const double number,  char* string, const size_t dataSize);
	extern size_t TextFromDoubleW(const double number,  wchar_t* string, const size_t dataSize);
	extern size_t TextFromBinaryDataA(const void* data, const size_t dataSize, char* string, const size_t stringSize);

	extern size_t TextToIntA(const char* string, const size_t dataSize, int* number);
	extern size_t TextToIntW(const wchar_t* string, const size_t dataSize, int* number);
	extern size_t TextToBoolA(const char* string, const size_t dataSize, unsigned char* number);
	extern size_t TextToBoolW(const wchar_t* string, const size_t dataSize, unsigned char* number);
	extern size_t TextToFloatA(const char* string, const size_t dataSize, float* number);
	extern size_t TextToFloatW(const wchar_t* string, const size_t dataSize, float* number);
	extern size_t TextToDoubleA(const char* string, const size_t dataSize, double* number);
	extern size_t TextToDoubleW(const wchar_t* string, const size_t dataSize, double* number);

	extern size_t TextAppendW(wchar_t* const dataString, const size_t dataStringSize, const wchar_t* const appaendString, const size_t appaendStringSize);

	extern size_t TextClearA(char* string, const size_t stringSize);
	extern size_t TextClearW(wchar_t* string, const size_t stringSize);

	extern size_t TextLengthA(const char* string, const size_t stringSize);
	extern size_t TextLengthW(const wchar_t* string, const size_t stringSize);

	extern size_t TextLengthUntilA(const char* string, const size_t stringSize, const char character);
	extern size_t TextLengthUntilW(const wchar_t* string, const size_t stringSize, const wchar_t character);

	extern size_t TextCopyA(const char* source, const size_t sourceLength, char* destination, const size_t destinationLength);
	extern size_t TextCopyAW(const char* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength);
	extern size_t TextCopyWA(const wchar_t* source, const size_t sourceLength, char* destination, const size_t destinationLength);
	extern size_t TextCopyW(const wchar_t* source, const size_t sourceLength, wchar_t* destination, const size_t destinationLength);

	extern size_t TextCountUntilA(const char* text, const size_t textSize, const char target, const char stopAt);
	extern size_t TextCountUntilW(const wchar_t* text, const size_t textSize, const wchar_t target, const wchar_t stopAt);

	extern char TextCompareA(const char* a, const size_t aSize, const char* b, const size_t bSize);
	extern char TextCompareAW(const char* a, const size_t aSize, const wchar_t* b, const size_t bSize);
	extern char TextCompareW(const wchar_t* a, const size_t aSize, const wchar_t* b, const size_t bSize);
	extern char TextCompareWA(const wchar_t* a, const size_t aSize, const char* b, const size_t bSize);

	extern char TextCompareIgnoreCaseA(const char* a, const size_t aSize, const char* b, const size_t bSize);
	extern char TextCompareIgnoreCaseW(const wchar_t* a, const size_t aSize, const wchar_t* b, const size_t bSize);
	extern char TextCompareIgnoreCaseAW(const char* a, const size_t aSize, const wchar_t* b, const size_t bSize);
	extern char TextCompareIgnoreCaseWA(const wchar_t* a, const size_t aSize, const char* b, const size_t bSize);

	extern char* TextFindPositionA(const char* data, size_t dataSize, const char* target, size_t targetSize);

	extern size_t TextFindFirstA(const char* string, const size_t dataSize, const char character);
	extern size_t TextFindLastA(const char* string, const size_t dataSize, const char character);
	extern size_t TextFindLastW(const wchar_t* string, const size_t dataSize, const wchar_t character);

	extern void TextTerminateBeginFromFirstA(char* string, const size_t dataSize, const char character);

	extern void TextParseA(const char* buffer, const size_t bufferSize, const char* syntax, ...);

	extern void TextParseFindAllA(const char* string, const size_t stringSize, const ParsingTokenA* parsingTokenList, const size_t parsingTokenListSize);

#ifdef __cplusplus
}
#endif

#endif
