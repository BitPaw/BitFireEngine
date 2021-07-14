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
		unsigned int _currentCursorPosition;

		public:
		List<unsigned char> Data;

		AsciiString Path;
		AsciiString Extension;

		File(char* filePath);
		File(AsciiString& filePath);

		ErrorCode Read();
		static ErrorCode Read(char* filePath, char** buffer);
		static ErrorCode Read(char* filePath, char** buffer, unsigned int maxSize);
		ErrorCode Write();
		static ErrorCode Write(char* filePath, char* content);
		ErrorCode ReadNextLineInto(char* exportBuffer);

		ErrorCode ReadAsLines(List<AsciiString>& lineList);

		bool DoesFileExist();
		static bool DoesFileExist(AsciiString& filePath);
		static void GetFileExtension(AsciiString& path, AsciiString& extension);

		int CountAmountOfLines();

		void CursorToBeginning();

		void Remove();
		static void Remove(AsciiString& filePath);
		void ReName(AsciiString& name);

		void ExtractAndSave(AsciiString& filePath, unsigned int start, unsigned int length);
		static void ExtractAndSave(AsciiString& filePath, void* data, unsigned int length);
	};
}