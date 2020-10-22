#pragma once

#include <string>

#include "../../Utility/StringSplitter.h"
#include "../../Utility/List.hpp"

namespace BF
{
	class TextFile
	{
	public:
		List<std::string> Lines;

		std::string Path;
		std::string FileName;

		TextFile();
		TextFile(std::string path);

		std::string GetFileExtension();
	};
}