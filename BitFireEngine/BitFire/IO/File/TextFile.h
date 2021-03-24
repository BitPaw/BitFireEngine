#pragma once

#include "../../Utility/AsciiString.h"
#include "../../Utility/List.hpp"

namespace BF
{
	class TextFile
	{
		public:
		List<AsciiString> Lines;

		AsciiString Path;
		AsciiString FileExtension;

		TextFile();
		TextFile(AsciiString& path);

		static void GetFileExtension(AsciiString& path, AsciiString& extension);
	};
}