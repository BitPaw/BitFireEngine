#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ErrorCode.h"

#include "../../Utility/List.hpp"
#include "../../Utility/ASCIIString.h"

namespace BF
{
	struct File
	{
		private:
		ErrorCode CheckFile();

		public:
		List<unsigned char> Data;

		AsciiString Path;
		AsciiString Extension;

		File(AsciiString& filePath);

		ErrorCode Read();
		ErrorCode Write();

		ErrorCode ReadAsLines(List<AsciiString>& lineList);

		bool DoesFileExist();
		static bool DoesFileExist(AsciiString& filePath);
		static void GetFileExtension(AsciiString& path, AsciiString& extension);
	};
}