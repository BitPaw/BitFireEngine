#pragma once

#include <cstddef>

#include "Endian.h"

#define Byte unsigned char

namespace BF
{
	struct ByteStream
	{
		public:
		Byte* Data;
		size_t DataSize;
		size_t DataCursorPosition;

		ByteStream();
		ByteStream(Byte* data, size_t dataSize);


		void DataSet(Byte* data, size_t dataSize, size_t cursorPosition = 0);

		void CursorToBeginning();


		unsigned int ReadNextLineInto(char* exportBuffer);

		void SkipEndOfLineCharacters();

		void Read(bool& value);
		void Read(char& value);
		void Read(unsigned char& value);
		void Read(short& value, Endian endian);
		void Read(unsigned short& value, Endian endian);
		void Read(int& value, Endian endian);
		void Read(unsigned int& value, Endian endian);
		void Read(unsigned long long& value, Endian endian);
		void Read(void* value, size_t length);
		bool ReadAndCompare(const Byte* value, size_t length);
		bool ReadAndCompare(const char* value, size_t length);
		bool ReadAndCompare(void* value, size_t length);

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
	};
}