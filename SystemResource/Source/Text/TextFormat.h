#pragma once

#define TextFormatInvalid 0xFF
#define TextFormatASCII 0x01
#define TextFormatUNICODE 0x02
#define TextFormatUTF8 0x03

namespace BF
{
	enum class TextFormat
	{
		Invalid,

		// 1 Byte__ per character, range from 0 to 255
		TextASCII,
		
		// 2 Bytes per character, range from 0 to 65535
		TextUNICODE,

		// Variable length of characters, 1 to 4 Bytes
		TextUTF8,
		TextUTF16
	};
}