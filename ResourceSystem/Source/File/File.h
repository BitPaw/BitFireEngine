#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ErrorCode.h"
#include "../Container/AsciiString.h"

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

		void Remove();
		static void Remove(AsciiString& filePath);
		void ReName(AsciiString& name);

		void ExtractAndSave(AsciiString& filePath, unsigned int start, unsigned int length);
		static void ExtractAndSave(AsciiString& filePath, void* data, unsigned int length);
	};
}