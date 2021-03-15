#pragma once

#include "../../Utility/ASCIIString.h"
#include "../../Utility/List.hpp"

namespace BF
{
	class TextFile
	{
		public:
		List<ASCIIString> Lines;

		ASCIIString Path;
		ASCIIString FileExtension;

		TextFile();
		TextFile(ASCIIString& path);

		static void GetFileExtension(ASCIIString& path, ASCIIString& extension);
	};
}