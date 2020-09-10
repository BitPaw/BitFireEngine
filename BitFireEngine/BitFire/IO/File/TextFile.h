#pragma once

#include <string>

#include "../../Utility/StringSplitter.h"
#include "../../Utility/List.h"

class TextFile
{
public:
	BF::List<std::string> Lines;

	std::string Path;
	std::string FileName;

	TextFile();
	TextFile(std::string path);
};