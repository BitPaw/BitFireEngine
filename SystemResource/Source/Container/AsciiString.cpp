#include "AsciiString.h"
#include <cassert>
#include <cstdarg>

BF::AsciiString::AsciiString()
{
	_data = nullptr;
	_size = 0;

	_isReferenceToOtherString = false;
}

BF::AsciiString::AsciiString(const char* string)
{
	_data = (char*)string;
	_size = 0;

	if (string == nullptr)
	{
		_isReferenceToOtherString = false;	
		return;
	}

	_isReferenceToOtherString = true;

	while (string[_size++] != '\0')
	{
		
	}

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
	if (!_isReferenceToOtherString)
	{
		delete[] _data;
	}
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

int BF::AsciiString::operator==(const char* string)
{
	return strcmp(_data, string);
}

void BF::AsciiString::SetAsReference(AsciiString& string)
{
	SetAsReference(&string[0], string.Size());
}

void BF::AsciiString::SetAsReference(const char* stringAdress)
{
	SetAsReference(stringAdress, -1);
}

void BF::AsciiString::SetAsReference(const char* stringAdress, unsigned int size)
{
	_isReferenceToOtherString = true;
	_data = (char*)stringAdress;
	_size = size;
}

void BF::AsciiString::ReSize(size_t size)
{
	size_t newSize = size + 1;
	char* newData = (char*)realloc(_data, newSize);

	if (!newData)
	{
		return;
	}

	if (_data == nullptr)
	{
		memset(newData, '\0', newSize * sizeof(char));
	}
	else
	{
		newData[size] = '\0';
	}

	_data = newData;
	_size = newSize;
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

	if (_size == -1)
	{
		int index = 0;
		_size = 0;

		while (_data[index++] != '\0') _size++;
	}
	
	return _size - 1;
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
	AsciiString characterCaontainer(&character, 2);
	
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

	size_t stringALengh = Size();
	size_t stringBLengh = string.Size();
	size_t stringCLengh = stringALengh + stringBLengh + 1; // +1 for the '\0' c string style. 
	size_t byteLenghA = sizeof(char) * stringALengh;
	size_t byteLenghB = sizeof(char) * stringBLengh;
	size_t byteLenghC = sizeof(char) * stringCLengh;
	char* startA = _data;
	char* startB = &string[0];
	char* insertionPoint = 0;

	if (_isReferenceToOtherString) // If the String is just a reference, create a new string to manipulate
	{
		startA = (char*)malloc(stringCLengh+1 * sizeof(char)); // create space
		memcpy(startA, _data, _size); // Copy old referenced string to new location
		_isReferenceToOtherString = false; // its no longer a reference

		_data = startA;
	}
	else
	{
		char* newData = (char*)realloc(_data, byteLenghC);

		if (!newData)
		{
			// Error
			return;
		}

		_data = newData;
	}	
	
	insertionPoint = _data + byteLenghA; // Move to the next insertion point (After A).
	
	memcpy(insertionPoint, startB, byteLenghB); // Attach content from B after the A part.

	_data[stringCLengh - 1] = '\0'; // Add c-string style endmarker.	
	_size = stringCLengh; // Update new size.
}

float BF::AsciiString::ToFloat()
{
	return AsciiString::ToFloat(_data);
}

float BF::AsciiString::ToFloat(const char* string)
{	
	int number = 0;
	unsigned int digitsAfterDot = 1;
	bool isWholeNumberChunk = true;

	unsigned int index = 0;
	bool isNegative = false;

	if (string[0] == '-')
	{
		index++;
		isNegative = true;
	}

	for ( ; string[index] != '\0'; index++)
	{
		char character = string[index];
		bool isDot = character == '.';
		bool isValidCharacter = (character >= '0' && character <= '9') || isDot;
		int numberElement = character - '0';

		if (!isValidCharacter)
		{
			break;
		}

		// Trigger when we switch to after dot
		if (isDot && isWholeNumberChunk)
		{
			isWholeNumberChunk = false;
			continue;
		}

		number *= 10; // "Shft number to left" Example 12 -> 120
		number += numberElement; // ASCII character to actual number.

		if (!isWholeNumberChunk)
		{
			digitsAfterDot *= 10;		
		}		
	}

	if (isNegative)
	{
		number *= -1;
	}

	//double stdResult = std::strtof(string, 0); // STD Method
	float result = number / (float)digitsAfterDot;

	return  result;
}

int BF::AsciiString::ToInt()
{
	return AsciiString::ToInt(_data);	
}

int BF::AsciiString::ToInt(const char* string)
{
	int number = 0;
	unsigned int index = 0;
	bool isNegative = false;

	if (string[0] == '-')
	{
		index++;
		isNegative = true;
	}

	for (; string[index] != '\0'; index++)
	{
		char character = string[index];
		char isValidCharacter = (character >= '0' && character <= '9');
		int numberElement = character - '0';

		if (!isValidCharacter)
		{
			break;
		}

		number *= 10; // "Shft number to left" Example 12 -> 120
		number += numberElement; // ASCII character to actual number.
	}

	if (isNegative)
	{
		number *= -1;
	}

	// atoi()
	//std::strtol(&_data[0], 0, 10); // STD Method

	return number;
}

bool BF::AsciiString::ToBool()
{
	return AsciiString::ToBool(_data);
}

bool BF::AsciiString::ToBool(const char* string)
{
	switch (string[0])
	{
		default:
		case '0':
		case 'F':
		case 'f':
			return false;

		case '1':
		case 'T':
		case 't':
			return true;
	}
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

void BF::AsciiString::ReplaceWhiteSpaceInQuotes(char key, bool revert)
{
	int dynamicIndex = 0;

	if (_data == nullptr)
	{
		return;
	}

	while (true)
	{
		char currentChar = _data[dynamicIndex++];
		bool isFirstComma = currentChar == '\"';
		bool endOfString = currentChar == '\0';

		if (endOfString)
		{
			return;
		}

		while (isFirstComma)
		{
			currentChar = _data[dynamicIndex++];
			bool isSecondComma = currentChar == '\"';
			bool isSpace = currentChar == (revert ? key : ' ');

			if (isSpace)
			{
				_data[dynamicIndex - 1] = (revert ? ' ' : key);
			}

			if (isSecondComma)
			{
				return;
			}
		}
	}
}

void BF::AsciiString::Remove(char removerCharacter)
{
	unsigned int size = Size();
	unsigned int amoutToRemove = Count(removerCharacter);
	unsigned int dynamicIndex = 0;
	char resultBuffer[2048];

	if (amoutToRemove == 0)
	{
		return;
	}

	memset(resultBuffer, 0, 2048);

	for (unsigned int i = 0; i < size; i++)
	{
		char character = _data[i];
		bool isRemoverKey = character == removerCharacter;

		if (!isRemoverKey)
		{
			resultBuffer[dynamicIndex++] = character;
		}
	}

	strncpy(_data, resultBuffer, 2048);
}

void BF::AsciiString::RemoveWhiteSpace()
{
	const char whiteSpace = ' ';

	Remove(whiteSpace);
}

void BF::AsciiString::PonterMoveBy(int offset)
{
	_data += offset;
}

void BF::AsciiString::PointerMoveToFirstChar(char character)
{
	while (*_data != '\0' || *_data == character)
	{
		_data++;
	}
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
	char emptyCharacter = ' ';

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

	/*
	* 
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
	}*/

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
	char* sourceText = &this->operator[](0);
	char* targetText = &string[0];
	const unsigned int targetSize = strlen(targetText);
	const unsigned int sourceSize = strlen(sourceText);

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

	cuttedString[cuttedStringByteSize] = '\0';
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
		return (unsigned int)-1;
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

	return (unsigned int)-1;
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
	ReSize(lengh);

	memcpy(_data, (void*)string, lengh);
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
	Copy(&string[0], string.Size());
}

void BF::AsciiString::Parse(char* buffer, const char* syntax, ...)
{
	va_list args;
	va_start(args, syntax);

	int startIndex = 0;
	int stopIndex = 0;
	int command = 0;
	bool finished = false;

	while (!finished)
	{
		char commandKey = syntax[command++];
		bool commandIsNumber = commandKey == 'i' || commandKey == 'f' || commandKey == 'u';

		while (true)
		{
			char current = buffer[stopIndex++];
			finished = current == '\0';

			if (commandIsNumber && current == '/' || current == ' ' || finished)
			{
				break;
			}
		}

		switch (commandKey)
		{
			case 's':
			{
				char* destination = va_arg(args, char*);
				char* source = &buffer[startIndex];
				unsigned int length = stopIndex - startIndex - 1;

				memcpy(destination, source, length);
				destination[length] = '\0';
				break;
			}
			case 'i':
			case 'd':
			case 'u':
			{
				int* i = va_arg(args, int*);
				char* source = &buffer[startIndex];

				*i = BF::AsciiString::ToInt(source);

				break;
			}
			case 'f':
			{
				float* number = va_arg(args, float*);
				char* source = &buffer[startIndex];

				(*number) = AsciiString::ToFloat(source);

				break;
			}
			case 'c':
			{
				char* character = va_arg(args, char*);

				*character = buffer[startIndex];

				break;
			}
			default:
				break;
		}

		startIndex = stopIndex;
	}

	va_end(args);
}