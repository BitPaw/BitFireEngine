#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ResourceLoadingResult.hpp"
#include "../Container/AsciiString.h"

namespace BF
{
	struct File
	{
		private:
		ResourceLoadingResult CheckFile();
		unsigned int _currentCursorPosition;

		public:
		unsigned int Size;
		char* Data;

		char Path[255];
		char* Extension;

		File(const char* filePath);
		~File();

		ResourceLoadingResult Read();
		static ResourceLoadingResult Read(const char* filePath, char** buffer);
		static ResourceLoadingResult Read(const char* filePath, char** buffer, unsigned int maxSize);
		ResourceLoadingResult Write();
		static ResourceLoadingResult Write(const char* filePath, const char* content);
		bool ReadNextLineInto(char* exportBuffer);

		ResourceLoadingResult ReadAsLines(List<AsciiString>& lineList);

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