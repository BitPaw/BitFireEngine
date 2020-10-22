#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TextFile.h"
#include "FileNotFound.h"
#include "EmptyFileName.h"

#include "../../Utility/List.hpp"

namespace BF
{
	class FileLoader
	{
	public:
		static bool DoesFileExist(const std::string filePath);

		static BF::List<unsigned char> ReadFileAsBytes(const std::string filePath);
		static void WriteFileAsBytes(const std::string filePath, const unsigned int size, const unsigned char* data);

		static std::string ReadCompleteFile(const std::string filePath);
		static BF::List<std::string> ReadFileByLines(const std::string filePath);

		static TextFile ReadTextFile(const std::string filePath);
		static TextFile ReadTextFile(const std::string filePath, const bool splittLines);
	};
}