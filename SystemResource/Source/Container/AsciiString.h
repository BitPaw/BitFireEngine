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

		bool _isReferenceToOtherString;

		public:
		AsciiString();
		AsciiString(const char* string);
		AsciiString(const char* string, unsigned int size);
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
	
		char operator==(const char* string);

		void SetAsReference(AsciiString& string);
		void SetAsReference(const char* stringAdress);
		void SetAsReference(const char* stringAdress, unsigned int size);
		void ReSize(unsigned int size);
		void Delete();
		unsigned int Size();
		unsigned int SizeInBytes();
		bool Empty();

		void AttachToBack(char character);
		void AttachToBack(AsciiString& string);

		//---<Convert>---
		float ToFloat();
		static float ToFloat(const char* string);
		int ToInt();
		static int ToInt(const char* string);
		bool ToBool();
		static int ToBool(const char* string);
		//---------------

		unsigned int Count(char character);
		unsigned int CountUnique(char character);

		void Replace(char from, char to);
		void ReplaceWhiteSpaceInQuotes(char key, bool revert);
		void Remove(char character);
		void RemoveWhiteSpace();

		void PonterMoveBy(int offset);
		void PointerMoveToFirstChar(char character);

		bool IsCharacterInBetween(char target, char curroundedChar);
		bool IsCharacterInBetween(char target, char curroundedChar, unsigned int startIndex);

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
		unsigned int FindFirst(AsciiString& string);
		unsigned int FindFirst(AsciiString& string, unsigned int beginIndex);
		unsigned int FindFirst(AsciiString& string, unsigned int beginIndex, unsigned int endIndex);

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