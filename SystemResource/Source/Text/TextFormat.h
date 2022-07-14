#pragma once

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

	TextFormat ConvertTextFormat(const unsigned char textFormatID);
	unsigned char ConvertTextFormat(const TextFormat textFormat);
}