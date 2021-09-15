#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ResourceLoadingResult.hpp"
#include "../Container/AsciiString.h"

namespace BF
{
#define FileLineBufferSize 255u

	struct File
	{
		private:
		ResourceLoadingResult CheckFile();
		unsigned int _currentCursorPosition;

		public:
		size_t Size;
		char* Data;

		char Path[_MAX_PATH];
		char Drive[_MAX_DRIVE];
		char Directory[_MAX_DIR];
		char FileName[_MAX_FNAME];
		char Extension[_MAX_EXT];

		File(const char* filePath, bool readInstandly = false);
		~File();

		ResourceLoadingResult Read();
		static ResourceLoadingResult Read(const char* filePath, char** buffer);
		static ResourceLoadingResult Read(const char* filePath, char** buffer, unsigned int maxSize);
		ResourceLoadingResult Write();
		static ResourceLoadingResult Write(const char* filePath, const char* content);
		static ResourceLoadingResult Write(const char* filePath, const char* content, unsigned int length);
		unsigned int ReadNextLineInto(char* exportBuffer);

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