#pragma once

#include <string>
#include "List.hpp"

namespace BF
{
	class ASCIIString
	{
		private:
		char* _data;
		unsigned int _size;

		public:
		ASCIIString();
		ASCIIString(const char* string);
		ASCIIString(std::string& stdstring);
		ASCIIString(char character);
		ASCIIString(ASCIIString& string);

		~ASCIIString();

		char& operator[](unsigned int value);
		
		ASCIIString& operator+(const char* text);
		ASCIIString& operator+(ASCIIString& string);
		//String& operator+(String& string);

		ASCIIString& operator=(const char* string);
		ASCIIString& operator=(std::string& string);
		//void operator=(String string);
	
		bool operator==(const char* string);

		void ReSize(unsigned int size);
		void Delete();
		unsigned int Size();
		unsigned int SizeInBytes();
		bool Empty();
		void AttachToBack(ASCIIString& string);

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
				
		bool Compare(ASCIIString& string);
		bool CompareIgnoreCase(const char* string);
		bool CompareIgnoreCase(ASCIIString& string);

		void Cut(unsigned int startPosition, ASCIIString& cuttedString);
		void Cut(unsigned int startPosition, unsigned int endPosition, ASCIIString& cuttedString);
		void Splitt(char seperator, List<ASCIIString>& stringList);


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
		void Copy(ASCIIString& string);
	};
}