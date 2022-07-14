#include "TextFormat.h"

#define TextFormatInvalid 0xFF
#define TextFormatASCII 0x01
#define TextFormatUNICODE 0x02
#define TextFormatUTF8 0x03
#define TextFormatUTF16 0x04

BF::TextFormat BF::ConvertTextFormat(const unsigned char textFormatID)
{
	switch(textFormatID)
	{
		case TextFormatASCII: return TextFormat::TextASCII;
		case TextFormatUNICODE: return TextFormat::TextUNICODE;
		case TextFormatUTF8: return TextFormat::TextUTF8;
		case TextFormatUTF16: return TextFormat::TextUTF16;

		default: return TextFormat::Invalid;
	}
}

unsigned char BF::ConvertTextFormat(const TextFormat textFormat)
{
	switch(textFormat)
	{
		case BF::TextFormat::Invalid: return TextFormatInvalid;
		case BF::TextFormat::TextASCII:  return TextFormatASCII;
		case BF::TextFormat::TextUNICODE:  return TextFormatUNICODE;
		case BF::TextFormat::TextUTF8:  return TextFormatUTF8;
		case BF::TextFormat::TextUTF16:  return TextFormatUTF16;
	}
}