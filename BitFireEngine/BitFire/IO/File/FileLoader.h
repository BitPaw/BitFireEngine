#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TextFile.h"
#include "FileNotFound.h"
#include "EmptyFileName.h"

#include "../../Utility/List.hpp"
#include "../../Utility/ByteString.h"

namespace BF
{
	class FileLoader
	{
		public:
		static bool DoesFileExist(ASCIIString& filePath);

		static void ReadFileAsBytes(ASCIIString& filePath, ByteString& byteString);
		static void WriteFileAsBytes(ASCIIString& filePath, ByteString& byteString);

		static void ReadCompleteFile(ASCIIString& filePath, ASCIIString& fileContent);
		static void ReadFileByLines(ASCIIString& filePath, List<ASCIIString>& stringList);

		static void ReadTextFile(TextFile& textFile);
		static void ReadTextFile(TextFile& textFile, const bool splittLines);

		static void GetFileExtension(ASCIIString& fileName, ASCIIString& extension);
	};
}