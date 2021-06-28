#include "AsciiString.h"

BF::AsciiString::AsciiString()
{
	_data = nullptr;
	_size = 0;

	_isReferenceToOtherString = false;
}

BF::AsciiString::AsciiString(const char* string)
{
	char* currentAdress = (char*)string;
	_size = 1;

	while (*(currentAdress++) != '\0') _size++;

	SetAsReference((char*)string, _size);
}

BF::AsciiString::AsciiString(const char* string, unsigned int size)
{
	SetAsReference((char*)string, size);
}

BF::AsciiString::AsciiString(std::string& stdstring) : AsciiString()
{
	Copy(stdstring);
}

BF::AsciiString::AsciiString(char character) : AsciiString()
{
	Copy(character);
}


BF::AsciiString::AsciiString(AsciiString& string) : AsciiString()
{
	Copy(string);
}

BF::AsciiString::~AsciiString()
{
	Delete();
}

char& BF::AsciiString::operator[](unsigned int value)
{
	return _data[value];
}

BF::AsciiString& BF::AsciiString::operator+(const char* text)
{
	//AttachToBack(string);

	return *this;
}

BF::AsciiString& BF::AsciiString::operator+(AsciiString& string)
{
	AttachToBack(string);

	return *this;
}

BF::AsciiString& BF::AsciiString::operator=(const char* string)
{
	Copy(string);

	return *this;
}

BF::AsciiString& BF::AsciiString::operator=(std::string& string)
{
	Copy(string);

	return *this;
}

bool BF::AsciiString::operator==(const char* string)
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

void BF::AsciiString::SetAsReference(AsciiString& string)
{
	SetAsReference(&string[0], string.Size());
}

void BF::AsciiString::SetAsReference(char* stringAdress, unsigned int size)
{
	_isReferenceToOtherString = true;
	_data = stringAdress;
	_size = size;
}

void BF::AsciiString::ReSize(unsigned int size)
{
	_size = size + 1;
	_data = (char*)realloc(_data, _size);

	if (_data != nullptr)
	{
		memset(_data, '\0', _size * sizeof(char));
	}	
}

void BF::AsciiString::Delete()
{
	bool hasData = _data != nullptr;
	bool hasAllocatedSpace = !_isReferenceToOtherString;
	bool shouldBeDeleted = hasData && hasAllocatedSpace;

	if (shouldBeDeleted)
	{
		delete[] _data;
		_data = nullptr;
		_size = 0;
	}
}

unsigned int BF::AsciiString::Size()
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

unsigned int BF::AsciiString::SizeInBytes()
{
	return sizeof(char) * Size();
}

bool BF::AsciiString::Empty()
{
	return _size == 0;
}

void BF::AsciiString::AttachToBack(char character)
{
	AsciiString characterCaontainer;
	characterCaontainer.SetAsReference(&character, 2);
	
	AttachToBack(characterCaontainer);
}

void BF::AsciiString::AttachToBack(AsciiString& string)
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
	char* startA = _data;
	char* startB = &string[0];
	char* insertionPoint = 0;

	if (_isReferenceToOtherString) // If the String is just a reference, create a new string to manipulate
	{
		startA = new char[stringCLengh+1]; // create space
		memcpy(startA, _data, _size); // Copy old referenced string to new location
		_isReferenceToOtherString = false; // its no longer a reference

		_data = startA;
	}
	else
	{
		_data = (char*)realloc(_data, byteLenghC);
	}	
	
	insertionPoint = _data + byteLenghA; // Move to the next insertion point (After A).
	
	memcpy(insertionPoint, startB, byteLenghB); // Attach content from B after the A part.

	_data[stringCLengh - 1] = '\0'; // Add c-string style endmarker.	
	_size = stringCLengh; // Update new size.
}

float BF::AsciiString::ToFloat()
{
	return std::strtof(&_data[0], 0);
}

int BF::AsciiString::ToInt()
{
	return std::strtol(&_data[0], 0, 10);
}

bool BF::AsciiString::ToBool()
{
	return ToInt() == 0;
}

unsigned int BF::AsciiString::Count(char character)
{
	unsigned int size = Size();
	unsigned int numberOfChars = 0; 

	for (unsigned int i = 0; i < size; i++)
	{
		numberOfChars += _data[i] == character;
	}

	return numberOfChars;
}

unsigned int BF::AsciiString::CountUnique(char character)
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

void BF::AsciiString::Replace(char from, char to)
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

void BF::AsciiString::Remove(char character)
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

void BF::AsciiString::RemoveWhiteSpace()
{
	const char whiteSpace = ' ';

	Remove(whiteSpace);
}

bool BF::AsciiString::IsCharacterInBetween(char target, char curroundedChar)
{
	return IsCharacterInBetween(target, curroundedChar, 0);
}

bool BF::AsciiString::IsCharacterInBetween(char target, char curroundedChar, unsigned int startIndex)
{
	unsigned int leftFoundIndex = FindFirst(curroundedChar, startIndex);
	unsigned int rightFoundIndex = FindFirst(curroundedChar, leftFoundIndex);
	unsigned int targetIndex = FindFirst(target, leftFoundIndex, rightFoundIndex);

	return targetIndex != -1;
}

char BF::AsciiString::GetFirstNonEmpty()
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

void BF::AsciiString::MergeRepeatingCharacters(char character)
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

void BF::AsciiString::MergeRepeatingWhiteSpace()
{
	const char whiteSpace = ' ';

	MergeRepeatingCharacters(whiteSpace);
}

void BF::AsciiString::ToLowerCase()
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

void BF::AsciiString::ToUpperCase()
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

bool BF::AsciiString::Compare(AsciiString& string)
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

bool BF::AsciiString::CompareIgnoreCase(const char* string)
{
	AsciiString bfString(string);

	return CompareIgnoreCase(bfString);
}

bool BF::AsciiString::CompareIgnoreCase(AsciiString& string)
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

void BF::AsciiString::Splitt(char seperator, List<AsciiString>& stringList)
{
	const unsigned int length = Size();
	const unsigned int tokenCounter = CountUnique(seperator);	
	unsigned int size = tokenCounter + 1; // If you cut, you have two elements
	unsigned int dynamicIndex = 0;

	unsigned int cutStartIndex = 0;
	unsigned int seperatorIndex = -1;
	unsigned int cutEndIndex = length;

	if (length < 3)
	{
		return;
	}

	// Create new space
	stringList.ReSize(size);

	for (unsigned int i = 0; i < size; i++)
	{
		AsciiString& segment = stringList[dynamicIndex];		
		
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

void BF::AsciiString::Cut(unsigned int startPosition, AsciiString& cuttedString)
{
	Cut(startPosition, Size(), cuttedString);
}

void BF::AsciiString::Cut(unsigned int startPosition, unsigned int endPosition, AsciiString& cuttedString)
{	
	if (startPosition >= endPosition || endPosition == 0)
	{
		throw "Invalid lengh";
	}

	unsigned int cuttedStringSize = endPosition - startPosition;
	unsigned int cuttedStringByteSize = cuttedStringSize * sizeof(char);
	char* startAdress = _data + startPosition;

	cuttedString.ReSize(cuttedStringSize);	 

	memcpy(&cuttedString[0], startAdress, cuttedStringByteSize);
}

unsigned int BF::AsciiString::FindFirst(char character)
{
	return FindFirst(character, 0, Size());
}

unsigned int BF::AsciiString::FindFirst(char character, unsigned int beginIndex)
{
	return FindFirst(character, beginIndex, Size());
}

unsigned int BF::AsciiString::FindFirst(char character, unsigned int beginIndex, unsigned int endIndex)
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

unsigned int BF::AsciiString::FindFirst(AsciiString& string)
{
	return FindFirst(string, 0, Size());
}

unsigned int BF::AsciiString::FindFirst(AsciiString& string, unsigned int beginIndex)
{
	return FindFirst(string, beginIndex, Size());
}

unsigned int BF::AsciiString::FindFirst(AsciiString& string, unsigned int beginIndex, unsigned int endIndex)
{
	unsigned int searchPoolStringSize = Size();
	unsigned int tokenSize = string.Size();
	char searchToken = string[0];
	unsigned int searchIndex = FindFirst(searchToken, beginIndex, endIndex);

	if (searchIndex == -1)
	{
		return -1;
	}

	if (searchIndex + tokenSize <= searchPoolStringSize)
	{
		char* tokenAdress = &string[0];
		char* searchPoolAdress = &_data[searchIndex];

		if (memcmp(searchPoolAdress, tokenAdress, tokenSize) == 0)
		{
			return searchIndex;
		}
	}

	return -1;
}

unsigned int BF::AsciiString::FindLast(char character)
{
	return FindLast(character, 0, Size());
}

unsigned int BF::AsciiString::FindLast(char character, unsigned int beginIndex)
{
	return FindLast(character, beginIndex, Size());
}

unsigned int BF::AsciiString::FindLast(char character, unsigned int beginIndex, unsigned int endIndex)
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

void BF::AsciiString::Copy(const char* string)
{	
	unsigned int stringSize = 0;

	while (string[stringSize] != '\0')
	{
		stringSize++;
	}

	Copy(string, stringSize);
}

void BF::AsciiString::Copy(const char* string, unsigned int lengh)
{
	unsigned int sizeInBytes = lengh * sizeof(char);

	ReSize(lengh);

	memcpy(_data, string, sizeInBytes);
}

void BF::AsciiString::Copy(std::string& stdstring)
{
	Copy(stdstring.c_str(), stdstring.length());
}

void BF::AsciiString::Copy(char character)
{
	char* string = static_cast<char*>(&character);

	Copy(string);
}

void BF::AsciiString::Copy(AsciiString& string)
{
	//unsigned int index = string.FindFirst('\0');

	//index = index == -1 ? string.Size() : index - 1;

	Copy(&string[0], string.Size());
}