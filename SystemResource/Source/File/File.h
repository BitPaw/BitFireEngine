#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ResourceLoadingResult.hpp"
#include "../Container/AsciiString.h"
#include "../Types/Endian.h"

namespace BF
{
#define FileLineBufferSize 255u

	struct File
	{
		private:
		ResourceLoadingResult CheckFile();

		public:
		char* Data;
		size_t DataSize;
		size_t DataCursorPosition;

		char Path[_MAX_PATH];
		char Drive[_MAX_DRIVE];
		char Directory[_MAX_DIR];
		char FileName[_MAX_FNAME];
		char Extension[_MAX_EXT];

		File(const char* filePath);
		File(const char* filePath, size_t dataSize);	
		~File();

		//---<Utility>--
		bool DoesFileExist();
		int CountAmountOfLines();
		static bool DoesFileExist(const char* filePath);
		static void GetFileExtension(const char* filePath, const char* fileExtension);
		void CursorToBeginning();

		void Remove();
		static void Remove(const char* filePath);
		void ReName(const char* name);

		void Clear();

		void SetFilePath(const char* filePath);
		//---------------------------------------------------------------------

		//---<Cursor>---
		//---------------------------------------------------------------------

		//---<Read>------------------------------------------------------------		
		unsigned int ReadNextLineInto(char* exportBuffer);

		void Read(bool& value);
		void Read(char& value);
		void Read(unsigned char& value);
		void Read(short& value, Endian endian);
		void Read(unsigned short& value, Endian endian);
		void Read(int& value, Endian endian);
		void Read(unsigned int& value, Endian endian);
		void Read(void* value, size_t length);
		ResourceLoadingResult ReadFromDisk();
		static ResourceLoadingResult ReadFromDisk(const char* filePath, char** buffer);
		static ResourceLoadingResult ReadFromDisk(const char* filePath, char** buffer, unsigned int maxSize);
		//---------------------------------------------------------------------

		//---<Write>----------------------------------------------------------------------
		void inline Write(bool value);
		void inline Write(char value);
		void inline Write(short value, Endian endian);
		void inline Write(int value, Endian endian);
		void inline Write(void* value, size_t length);
		ResourceLoadingResult WriteToDisk();
		static ResourceLoadingResult WriteToDisk(const char* filePath, const char* content, unsigned int length);
		//---------------------------------------------------------------------
	};
}