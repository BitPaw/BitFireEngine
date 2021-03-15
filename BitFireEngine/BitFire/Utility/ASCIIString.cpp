#include "ASCIIString.h"

BF::ASCIIString::ASCIIString()
{
	_data = nullptr;
	_size = 0;
}

BF::ASCIIString::ASCIIString(const char* string) : ASCIIString()
{
	Copy(string);
}

BF::ASCIIString::ASCIIString(std::string& stdstring) : ASCIIString()
{
	Copy(stdstring);
}

BF::ASCIIString::ASCIIString(char character) : ASCIIString()
{
	Copy(character);
}

BF::ASCIIString::ASCIIString(ASCIIString& string) : ASCIIString()
{
	Copy(string);
}

BF::ASCIIString::~ASCIIString()
{
	Delete();
}

char& BF::ASCIIString::operator[](unsigned int value)
{
	return _data[value];
}

BF::ASCIIString& BF::ASCIIString::operator+(const char* text)
{
	//AttachToBack(string);

	return *this;
}


BF::ASCIIString& BF::ASCIIString::operator+(ASCIIString& string)
{
	AttachToBack(string);

	return *this;
}


BF::ASCIIString& BF::ASCIIString::operator=(const char* string)
{
	Copy(string);

	return *this;
}

BF::ASCIIString& BF::ASCIIString::operator=(std::string& string)
{
	Copy(string);

	return *this;
}

bool BF::ASCIIString::operator==(const char* string)
{
	for (int i = 0 ; _data[i] == string[i] ; i++)
	{
		if (_data[i] == '\0' || string[i] == '\0')
		{
			return _data[i] == '\0' && string[i] == '\0';
		}
	}

	return false;
}

void BF::ASCIIString::ReSize(unsigned int size)
{
	_size = size + 1;
	_data = (char*)realloc(_data, _size);

	memset(_data, '\0', _size * sizeof(char));
}

void BF::ASCIIString::Delete()
{
	if (_data != nullptr)
	{
		delete[] _data;
		_data = nullptr;
		_size = 0;
	}
}

unsigned int BF::ASCIIString::Size()
{
	if (_size == 0)
	{
		return 0;
	}
	else
	{
		return _size - 1;
	}   
}

unsigned int BF::ASCIIString::SizeInBytes()
{
	return sizeof(char) * Size();
}

bool BF::ASCIIString::Empty()
{
	return _size == 0;
}

void BF::ASCIIString::AttachToBack(ASCIIString& string)
{
	/*
	A = old Data
	B = additive Data
	C = new Data

	C = A + B
	*/

	unsigned int stringALengh = Size();
	unsigned int stringBLengh = string.Size();
	unsigned int stringCLengh = stringALengh + stringBLengh + 1; // +1 for the '\0' c string style. 
	unsigned int byteLenghA = sizeof(char) * stringALengh;
	unsigned int byteLenghB = sizeof(char) * stringBLengh;
	unsigned int byteLenghC = sizeof(char) * stringCLengh;
	void* startA = _data;
	void* startB = &string[0];
	void* insertionPoint = 0;

	_data = (char*)realloc(startA, byteLenghC);
	
	insertionPoint = (void*)((unsigned int)_data + byteLenghA); // Move to the next insertion point (After A).
	
	memcpy(insertionPoint, startB, byteLenghB); // Attach content from B after the A part.

	_data[stringCLengh - 1] = '\0'; // Add c-string style endmarker.	
	_size = stringCLengh; // Update new size.
}

float BF::ASCIIString::ToFloat()
{
	return std::strtof(&_data[0], 0);
}

int BF::ASCIIString::ToInt()
{
	return std::strtol(&_data[0], 0, 10);
}

bool BF::ASCIIString::ToBool()
{
	return ToInt() == 0;
}

unsigned int BF::ASCIIString::Count(char character)
{
	unsigned int size = Size();
	unsigned int numberOfChars = 0; 

	for (unsigned int i = 0; i < size; i++)
	{
		numberOfChars += _data[i] == character;
	}

	return numberOfChars;
}

unsigned int BF::ASCIIString::CountUnique(char character)
{
	unsigned int size = Size();
	unsigned int numberOfChars = 0;
	bool wasLastChar = false;

	for (unsigned int i = 0; i < size; i++)
	{
		bool isSame = _data[i] == character;

		if (isSame)
		{
			if (!wasLastChar)
			{
				numberOfChars++;
				wasLastChar = true;
			}			
		}
		else
		{		
			wasLastChar = false;
		}
	}

	return numberOfChars;
}

void BF::ASCIIString::Replace(char from, char to)
{
	unsigned int size = Size();

	for (unsigned int i = 0; i < size; i++)
	{
		bool shouldChange = _data[i] == from;

		if (shouldChange)
		{
			_data[i] = to;
		}
	}
}

void BF::ASCIIString::Remove(char character)
{
	unsigned int amoutToRemove = Count(character);
	unsigned int oldSize = _size;
	unsigned int newSize = oldSize - amoutToRemove;
	char* tempText = nullptr;

	if (amoutToRemove == 0)
	{
		return;
	}

	tempText = _data;

	_data = new char[newSize];
	_size = newSize;

	unsigned int dynamicIndex = 0;

	for (unsigned int i = 0; i < oldSize; i++)
	{
		if (tempText[i] != character)
		{
			_data[dynamicIndex++] = tempText[i];
		}
	}

	delete[] tempText;
}

void BF::ASCIIString::RemoveWhiteSpace()
{
	const char whiteSpace = ' ';

	Remove(whiteSpace);
}

char BF::ASCIIString::GetFirstNonEmpty()
{
	unsigned int size = Size();
	unsigned char emptyCharacter = ' ';

	for (unsigned int i = 0; i < size; i++)
	{
		char currentChar = _data[i];
		bool isNotEmpty = currentChar != emptyCharacter;

		if (isNotEmpty)
		{
			return currentChar;
		}
	}

	return emptyCharacter;
}

void BF::ASCIIString::MergeRepeatingCharacters(char character)
{
	const char removerKey = 0xFE;
	unsigned int size = Size();
	bool lastCharWasIdentical = false;

	for (unsigned int i = 0; i < size; i++)
	{
		bool isTarget = _data[i] == character;

		if (isTarget)
		{
			if (lastCharWasIdentical)
			{
				_data[i] = removerKey;
			}
			else
			{
				lastCharWasIdentical = true;
			}
		}
		else
		{
			lastCharWasIdentical = false;
		}
	}

	for (unsigned int i = size-1; i >= 0; i++)
	{
		bool isTarget = _data[i] == character;

		if (isTarget)
		{
			_data[i] = removerKey;
		}
		else
		{
			break;
		}
	}

	Remove(removerKey);
}

void BF::ASCIIString::MergeRepeatingWhiteSpace()
{
	const char whiteSpace = ' ';

	MergeRepeatingCharacters(whiteSpace);
}

void BF::ASCIIString::ToLowerCase()
{
	const char bigA = 'A';
	const char bigZ = 'Z';
	const char smalA = 'a';

	for (unsigned int i = 0; i < _size; i++)
	{
		char character = _data[i];
		bool isSmalLetter = character >= bigA && character <= bigZ;

		_data[i] -= smalA - bigA;
	}
}

void BF::ASCIIString::ToUpperCase()
{
	const char bigA = 'A';
	const char smalA = 'a';
	const char smalZ = 'z';

	for (unsigned int i = 0; i < _size; i++)
	{
		char character = _data[i];
		bool isSmalLetter = character >= smalA && character <= smalZ;

		_data[i] += smalA - bigA;
	}
}

bool BF::ASCIIString::Compare(ASCIIString& string)
{
	const unsigned int targetSize = string.Size();
	const unsigned int sourceSize = Size();

	bool isDifferent = targetSize != sourceSize;

	if (isDifferent)
	{
		return false;
	}	

	for (unsigned int i = 0; i < targetSize; i++)
	{
		const char targetChar = string[i];
		const char sourceChar = _data[i];

		isDifferent = targetChar != sourceChar;

		if (isDifferent)
		{
			return false;
		}
	}

	return true;
}

bool BF::ASCIIString::CompareIgnoreCase(const char* string)
{
	ASCIIString bfString(string);

	return CompareIgnoreCase(bfString);
}

bool BF::ASCIIString::CompareIgnoreCase(ASCIIString& string)
{
	const unsigned int targetSize = string.Size();
	const unsigned int sourceSize = Size();

	bool isDifferent = targetSize != sourceSize;

	if (isDifferent)
	{
		return false;
	}

	for (unsigned int i = 0; i < targetSize; i++)
	{
		const char targetChar = string[i];
		const char sourceChar = _data[i];
		const char bigA = 'A';
		const char bigZ = 'Z';
		const char smalA = 'a';
		const char smalZ = 'z';	

		bool isLetterBig = targetChar >= bigA && targetChar <= bigZ;

		if (isLetterBig)
		{
			char loweredChar = isLetterBig - smalA - bigA;

			isDifferent = !(loweredChar == sourceChar || isLetterBig == sourceChar);
		}
		else
		{
			isDifferent = targetChar != sourceChar;
		}	

		if (isDifferent)
		{
			return false;
		}
	}

	return true;
}

void BF::ASCIIString::Splitt(char seperator, List<ASCIIString>& stringList)
{
	const unsigned int length = Size();
	const unsigned int tokenCounter = CountUnique(seperator);	
	unsigned int size = tokenCounter + 1; // If you cut, you have two elements
	unsigned int dynamicIndex = 0;

	unsigned int cutStartIndex = 0;
	unsigned int seperatorIndex = -1;
	unsigned int cutEndIndex = length;

	// Create new space
	stringList.ReSize(size);

	for (unsigned int i = 0; i < size; i++)
	{
		ASCIIString& segment = stringList[dynamicIndex];		
		
		seperatorIndex = FindFirst(seperator, cutStartIndex);

		if (seperatorIndex == -1)
		{
			cutEndIndex = Size();
		}
		else
		{
			cutEndIndex = seperatorIndex;
		}

		Cut(cutStartIndex, cutEndIndex, segment);

		if (!segment.Empty())
		{
			dynamicIndex++;
		}

		cutStartIndex = cutEndIndex + 1;
	}	
}

void BF::ASCIIString::Cut(unsigned int startPosition, ASCIIString& cuttedString)
{
	Cut(startPosition, Size(), cuttedString);
}

void BF::ASCIIString::Cut(unsigned int startPosition, unsigned int endPosition, ASCIIString& cuttedString)
{	
	if (startPosition >= endPosition || endPosition == 0)
	{
		throw "Invalid lengh";
	}

	unsigned int cuttedStringSize = endPosition - startPosition;
	unsigned int cuttedStringByteSize = cuttedStringSize * sizeof(char);
	void* startAdress = (void*)((unsigned int)_data + startPosition);

	cuttedString.ReSize(cuttedStringSize);	 

	memcpy(&cuttedString[0], startAdress, cuttedStringByteSize);
}

unsigned int BF::ASCIIString::FindFirst(char character)
{
	return FindFirst(character, 0, Size());
}

unsigned int BF::ASCIIString::FindFirst(char character, unsigned int beginIndex)
{
	return FindFirst(character, beginIndex, Size());
}

unsigned int BF::ASCIIString::FindFirst(char character, unsigned int beginIndex, unsigned int endIndex)
{
	unsigned int foundIndex = -1;

	for (unsigned int i = beginIndex; i < endIndex; i++)
	{
		if (_data[i] == character)
		{
			return i;
		}
	}

	return foundIndex;
}

unsigned int BF::ASCIIString::FindLast(char character)
{
	return FindLast(character, 0, Size());
}

unsigned int BF::ASCIIString::FindLast(char character, unsigned int beginIndex)
{
	return FindLast(character, beginIndex, Size());
}

unsigned int BF::ASCIIString::FindLast(char character, unsigned int beginIndex, unsigned int endIndex)
{
	unsigned int foundIndex = -1;

	for (unsigned int i = endIndex; i > beginIndex; i--)
	{
		if (_data[i] == character)
		{
			return i;
		}
	}

	return foundIndex;
}

void BF::ASCIIString::Copy(const char* string)
{	
	unsigned int stringSize = 0;

	while (string[stringSize] != '\0')
	{
		stringSize++;
	}

	Copy(string, stringSize);
}

void BF::ASCIIString::Copy(const char* string, unsigned int lengh)
{
	unsigned int sizeInBytes = lengh * sizeof(char);

	ReSize(lengh);

	memcpy(_data, string, sizeInBytes);
}

void BF::ASCIIString::Copy(std::string& stdstring)
{
	Copy(stdstring.c_str(), stdstring.length());
}

void BF::ASCIIString::Copy(char character)
{
	char* string = static_cast<char*>(&character);

	Copy(string);
}

void BF::ASCIIString::Copy(ASCIIString& string)
{
	//unsigned int index = string.FindFirst('\0');

	//index = index == -1 ? string.Size() : index - 1;

	Copy(&string[0], string.Size());
}