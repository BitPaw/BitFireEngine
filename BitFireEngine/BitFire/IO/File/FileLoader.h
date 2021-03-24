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
		static bool DoesFileExist(AsciiString& filePath);

		static void ReadFileAsBytes(AsciiString& filePath, AsciiString& byteString);
		static void WriteFileAsBytes(AsciiString& filePath, AsciiString& byteString);

		static void ReadCompleteFile(AsciiString& filePath, AsciiString& fileContent);
		static void ReadFileByLines(AsciiString& filePath, List<AsciiString>& stringList);

		static void ReadTextFile(TextFile& textFile);
		static void ReadTextFile(TextFile& textFile, const bool splittLines);

		static void GetFileExtension(AsciiString& fileName, AsciiString& extension);
	};
}