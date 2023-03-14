#ifndef PXTextInclude
#define PXTextInclude

#include <Format/Type.h>

#define MakeLetterCaseLower(character) (character | 0b00100000)
#define MakeLetterCaseUpper(character) (character & 0b11011111)
#define CompareLetterCaseIgnore(a, b) (MakeLetterCaseLower(a) == b) || (MakeLetterCaseUpper(a) == b)
#define UnicodeToASCII(wc) (wc <= 0xFF ? (char)wc : '?')
#define IsEndOfString(c) (c == '\0')
#define IsTab(c) (c == '\t')
#define IsEmptySpace(c) (c == ' ')
#define IsEndOfLineCharacter(c) (c == '\r' || c == '\n')

#define PXTextUnkownLength -1
#define PXTextIndexNotFound -1

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

	typedef enum PXTextFormat_
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
	PXTextFormat;

	typedef struct PXText_
	{
		PXTextFormat Format;
		PXSize SizeInCharacters;
		PXSize SizeInBytes;

		union
		{
			char* TextA;
			wchar_t* TextW;
			void* TextData;
		};
	}
	PXText;

	PXPublic PXSize PXTextFromIntA(const int number,  char* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromIntW(const int number,  wchar_t* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromBoolA(const unsigned char number,  char* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromBoolW(const unsigned char number,  wchar_t* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromFloatA(const float number,  char* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromFloatW(const float number,  wchar_t* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromDoubleA(const double number,  char* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromDoubleW(const double number,  wchar_t* string, const PXSize dataSize);
	PXPublic PXSize PXTextFromBinaryDataA(const void* data, const PXSize dataSize, char* string, const PXSize stringSize);

	PXPublic PXSize PXTextToIntA(const char* string, const PXSize dataSize, int* number);
	PXPublic PXSize PXTextToIntW(const wchar_t* string, const PXSize dataSize, int* number);
	PXPublic PXSize PXTextToBoolA(const char* string, const PXSize dataSize, unsigned char* number);
	PXPublic PXSize PXTextToBoolW(const wchar_t* string, const PXSize dataSize, unsigned char* number);
	PXPublic PXSize PXTextToFloatA(const char* string, const PXSize dataSize, float* number);
	PXPublic PXSize PXTextToFloatW(const wchar_t* string, const PXSize dataSize, float* number);
	PXPublic PXSize PXTextToDoubleA(const char* string, const PXSize dataSize, double* number);
	PXPublic PXSize PXTextToDoubleW(const wchar_t* string, const PXSize dataSize, double* number);

	PXPublic PXSize PXTextFromIntToBinary8U(char* const string, const PXSize dataSize, const PXInt8U number);
	PXPublic PXSize PXTextFromIntToBinary16U(char* const string, const PXSize dataSize, const PXInt16U number);
	PXPublic PXSize PXTextFromIntToBinary32U(char* const string, const PXSize dataSize, const PXInt32U number);
	PXPublic PXSize PXTextFromIntToBinary64U(char* const string, const PXSize dataSize, const PXInt64U number);
	PXPublic PXSize PXTextFromIntToBinary64UR(char* const string, const PXSize dataSize, const PXInt64U number, const unsigned char numberOfDigits);

	PXPublic PXSize PXTextAppendW(wchar_t* const dataString, const PXSize dataStringSize, const wchar_t* const appaendString, const PXSize appaendStringSize);

	PXPublic PXSize PXTextClearA(char* string, const PXSize stringSize);
	PXPublic PXSize PXTextClearW(wchar_t* string, const PXSize stringSize);

	PXPublic PXSize PXTextLengthA(const char* string, const PXSize stringSize);
	PXPublic PXSize PXTextLengthW(const wchar_t* string, const PXSize stringSize);

	PXPublic PXSize PXTextLengthUntilA(const char* string, const PXSize stringSize, const char character);
	PXPublic PXSize PXTextLengthUntilW(const wchar_t* string, const PXSize stringSize, const wchar_t character);

	PXPublic PXSize PXTextCopyA(const char* source, const PXSize sourceLength, char* destination, const PXSize destinationLength);
	PXPublic PXSize PXTextCopyAW(const char* source, const PXSize sourceLength, wchar_t* destination, const PXSize destinationLength);
	PXPublic PXSize PXTextCopyWA(const wchar_t* source, const PXSize sourceLength, char* destination, const PXSize destinationLength);
	PXPublic PXSize PXTextCopyW(const wchar_t* source, const PXSize sourceLength, wchar_t* destination, const PXSize destinationLength);

	PXPublic PXSize PXTextCopyAU(const PXTextASCII source, const PXSize sourceLength, PXTextUTF8 destination, const PXSize destinationLength);
	PXPublic PXSize PXTextCopyWU(const PXTextUNICODE source, const PXSize sourceLength, PXTextUTF8 destination, const PXSize destinationLength);

	PXPublic PXSize PXTextCountA(const char* PXText, const PXSize PXTextSize, const char target);
	PXPublic PXSize PXTextCountW(const wchar_t* PXText, const PXSize PXTextSize, const wchar_t target);

	PXPublic PXSize PXTextCountUntilA(const char* PXText, const PXSize PXTextSize, const char target, const char stopAt);
	PXPublic PXSize PXTextCountUntilW(const wchar_t* PXText, const PXSize PXTextSize, const wchar_t target, const wchar_t stopAt);

	PXPublic PXBool PXTextCompareA(const char* a, const PXSize aSize, const char* b, const PXSize bSize);
	PXPublic PXBool PXTextCompareAW(const char* a, const PXSize aSize, const wchar_t* b, const PXSize bSize);
	PXPublic PXBool PXTextCompareW(const wchar_t* a, const PXSize aSize, const wchar_t* b, const PXSize bSize);
	PXPublic PXBool PXTextCompareWA(const wchar_t* a, const PXSize aSize, const char* b, const PXSize bSize);

	PXPublic char PXTextCompareIgnoreCaseA(const char* a, const PXSize aSize, const char* b, const PXSize bSize);
	PXPublic char PXTextCompareIgnoreCaseW(const wchar_t* a, const PXSize aSize, const wchar_t* b, const PXSize bSize);
	PXPublic char PXTextCompareIgnoreCaseAW(const char* a, const PXSize aSize, const wchar_t* b, const PXSize bSize);
	PXPublic char PXTextCompareIgnoreCaseWA(const wchar_t* a, const PXSize aSize, const char* b, const PXSize bSize);

	PXPublic char* PXTextFindPositionA(const char* data, PXSize dataSize, const char* target, PXSize targetSize);

	PXPublic PXSize PXTextFindFirstA(const char* string, const PXSize dataSize, const char character);
	PXPublic PXSize PXTextFindFirstW(const wchar_t* string, const PXSize dataSize, const wchar_t character);
	PXPublic PXSize PXTextFindLastA(const char* string, const PXSize dataSize, const char character);
	PXPublic PXSize PXTextFindLastW(const wchar_t* string, const PXSize dataSize, const wchar_t character);

	PXPublic void PXTextTerminateBeginFromFirstA(char* string, const PXSize dataSize, const char character);

	PXPublic void PXTextParseA(const char* buffer, const PXSize bufferSize, const char* syntax, ...);

	PXPublic void PXTextParseFindAllA(const char* string, const PXSize stringSize, const ParsingTokenA* parsingTokenList, const PXSize parsingTokenListSize);

#ifdef __cplusplus
}
#endif

#endif
