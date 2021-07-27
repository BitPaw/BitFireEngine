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
		unsigned int _overAllocatedBytes;

		public:
		unsigned int Size;
		char* Data;

		char Path[255];
		char* Extension;

		File(const char* filePath);
		~File();

		ErrorCode Read();
		static ErrorCode Read(const char* filePath, char** buffer);
		static ErrorCode Read(const char* filePath, char** buffer, unsigned int maxSize);
		ErrorCode Write();
		static ErrorCode Write(const char* filePath, const char* content);
		ErrorCode ReadNextLineInto(char* exportBuffer);

		ErrorCode ReadAsLines(List<AsciiString>& lineList);

		bool DoesFileExist();
		static bool DoesFileExist(const char* filePath);
		static void GetFileExtension(AsciiString& path, AsciiString& extension);

		int CountAmountOfLines();

		void CursorToBeginning();

		void Remove();
		static void Remove(const char* filePath);
		void ReName(const char* name);

		void Clear();

		void ExtractAndSave(const char* filePath, unsigned int start, unsigned int length);
		static void ExtractAndSave(const char* filePath, void* data, unsigned int length);
	};
}