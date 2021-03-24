#pragma once

#include <string>
#include "List.hpp"

namespace BF
{
	class AsciiString
	{
		private:
		char* _data;
		unsigned int _size;

		public:
		AsciiString();
		AsciiString(const char* string);
		AsciiString(std::string& stdstring);
		AsciiString(char character);
		AsciiString(AsciiString& string);

		~AsciiString();

		char& operator[](unsigned int value);
		
		AsciiString& operator+(const char* text);
		AsciiString& operator+(AsciiString& string);
		//String& operator+(String& string);

		AsciiString& operator=(const char* string);
		AsciiString& operator=(std::string& string);
		//void operator=(String string);
	
		bool operator==(const char* string);

		void ReSize(unsigned int size);
		void Delete();
		unsigned int Size();
		unsigned int SizeInBytes();
		bool Empty();
		void AttachToBack(AsciiString& string);

		float ToFloat();
		int ToInt();
		bool ToBool();
		unsigned int Count(char character);
		unsigned int CountUnique(char character);

		void Replace(char from, char to);
		void Remove(char character);
		void RemoveWhiteSpace();

		char GetFirstNonEmpty();

		void MergeRepeatingCharacters(char character);
		void MergeRepeatingWhiteSpace();

		void ToLowerCase();
		void ToUpperCase();
				
		bool Compare(AsciiString& string);
		bool CompareIgnoreCase(const char* string);
		bool CompareIgnoreCase(AsciiString& string);

		void Cut(unsigned int startPosition, AsciiString& cuttedString);
		void Cut(unsigned int startPosition, unsigned int endPosition, AsciiString& cuttedString);
		void Splitt(char seperator, List<AsciiString>& stringList);


		unsigned int FindFirst(char character);
		unsigned int FindFirst(char character, unsigned int beginIndex);
		unsigned int FindFirst(char character, unsigned int beginIndex, unsigned int endIndex);

		unsigned int FindLast(char character);
		unsigned int FindLast(char character, unsigned int beginIndex);
		unsigned int FindLast(char character, unsigned int beginIndex, unsigned int endIndex);
	

		void Copy(const char* string);
		void Copy(const char* string, unsigned int lengh);
		void Copy(std::string& stdstring);
		void Copy(char character);
		void Copy(AsciiString& string);
	};
}