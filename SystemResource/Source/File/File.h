#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Endian.h"

#include "../File/FileActionResult.hpp"

#define FileLineBufferSize 255u

namespace BF
{
	struct File
	{
		private:
		FileActionResult CheckFile();

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

		bool Remove();
		static bool Remove(const char* filePath);
		bool ReName(const char* name);

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
		void Read(unsigned long long& value, Endian endian);
		void Read(void* value, size_t length);
		bool ReadAndCompare(const char* value, size_t length);
		bool ReadAndCompare(void* value, size_t length);
		FileActionResult ReadFromDisk();
		static FileActionResult ReadFromDisk(const char* filePath, char** buffer);
		static FileActionResult ReadFromDisk(const char* filePath, char** buffer, unsigned int maxSize);
		//---------------------------------------------------------------------

		//---<Write>----------------------------------------------------------------------
		void Write(bool value);
		void Write(char value);
		void Write(unsigned char value);
		void Write(short value, Endian endian);
		void Write(unsigned short value, Endian endian);
		void Write(int value, Endian endian);
		void Write(unsigned int value, Endian endian);
		void Write(const char* string, size_t length);
		void Write(unsigned long long& value, Endian endian);
		void Write(void* value, size_t length);	
		FileActionResult WriteToDisk();
		static FileActionResult WriteToDisk(const char* filePath, const char* content, unsigned int length);
		//---------------------------------------------------------------------
	};
}