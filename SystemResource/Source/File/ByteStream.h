#pragma once

#include <cstddef>

#include "Endian.h"

#include <Container/ClusterShort.h>
#include <Container/ClusterInt.h>
#include <Container/ClusterLongLong.h>

#ifndef Byte
#define Byte unsigned char
#endif

namespace BF
{
	struct ByteStream
	{
		public:
		//---------------------------------------------------------------------
		Byte* Data;
		size_t DataSize;
		size_t DataCursorPosition;
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		ByteStream();
		ByteStream(Byte* data, const size_t dataSize);

		// WARNING! If this constructor is used, guarantee that it will only be "read".
		// A write operation will be illegal to do, a crash may accur. 
		ByteStream(const Byte* data, const size_t dataSize);

		size_t ReadPossibleSize() const;
		bool IsAtEnd() const;

		void DataSet(const Byte* data, const size_t dataSize, const size_t cursorPosition = 0);
		
		void CursorToBeginning();
		Byte* CursorCurrentAdress();
		void CursorAdvance(const size_t steps);
		void CursorRewind(const size_t steps);
		void CursorToEnd();


		unsigned int ReadNextLineInto(char* exportBuffer);

		void SkipEndOfLineCharacters();
		void SkipLine();

		void Read(bool& value);
		void Read(char& value);
		void Read(unsigned char& value);
		void Read(short& value, const Endian endian);
		void Read(unsigned short& value, const Endian endian);
		void Read(int& value, const  Endian endian);
		void Read(unsigned int& value, const Endian endian);
		void Read(unsigned long long& value, const  Endian endian);
		void Read(void* value, const size_t length);
		void ReadUntil(char* value, const size_t length, const char character);
		void ReadUntil(wchar_t* value, const size_t length, const wchar_t character);

		// Additional check how many bytes are read.
		// Slower version of Read(), this function can't fail.
		size_t ReadSafe(Byte* value, const size_t length);

		bool ReadAndCompare(const Byte* value, const size_t length);
		bool ReadAndCompare(const char* value, const size_t length);
		bool ReadAndCompare(const char value);
		bool ReadAndCompare(const void* value, const size_t length);
		bool ReadAndCompare(const unsigned int value);

		void Write(const bool value);
		void Write(const char value);
		void Write(const unsigned char value);
		void Write(const short value, const Endian endian);
		void Write(const unsigned short value, const Endian endian);
		void Write(const int value, const Endian endian);
		void Write(const unsigned int value, const Endian endian);
		void Write(const long long value, const Endian endian);
		void Write(const unsigned long long value, const Endian endian);
		void Write(const char* value, const size_t length);
		void Write(const unsigned char* value, const size_t length);
		void Write(const void* value, const size_t length);
		size_t Write(const char* format, ...);
	};
}