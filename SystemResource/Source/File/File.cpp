#include "File.h"

#include "../Container/AsciiString.h"
#include <cassert>

BF::FileActionResult BF::File::CheckFile()
{
	if (!DoesFileExist(Path))
	{
		return BF::FileActionResult::FileNotFound;
	}

	return BF::FileActionResult::Successful;
}

BF::File::File(const char* filePath, size_t dataSize)
{
	Data = (char*)malloc(dataSize * sizeof(char));
	DataSize = dataSize;
	DataCursorPosition = 0;

	SetFilePath(filePath);
}

BF::File::File(const char* filePath)
{
	Data = 0;
	DataSize = 0;
	DataCursorPosition = 0;

	SetFilePath(filePath);
}

BF::File::~File()
{
	free(Data);
}

void BF::File::CursorToBeginning()
{
	DataCursorPosition = 0;
}

bool BF::File::Remove()
{
	return BF::File::Remove(Path);
}

bool BF::File::Remove(const char* filePath)
{
	int removeResult = remove(filePath);

	switch (removeResult)
	{
		case 0:
			return true;

		default:
			return false;
	}
}

bool BF::File::ReName(const char* name)
{
	int renameResult = rename(Path, name);

	switch (renameResult)
	{
		case 0:
			return true;

		default:
			return false;
	}
}

void BF::File::Clear()
{
	free(Data);

	DataCursorPosition = 0;
	DataSize = 0;
	Data = nullptr;
}

void BF::File::SetFilePath(const char* filePath)
{
	if (filePath == nullptr)
	{
		Path[0] = '\0';
		Drive[0] = '\0';
		Directory[0] = '\0';
		FileName[0] = '\0';
		Extension[0] = '\0';
		return;
	}

	strcpy_s(Path, _MAX_PATH, filePath);

	_splitpath_s
	(
		filePath,
		Drive, _MAX_DRIVE,
		Directory, _MAX_DIR,
		FileName, _MAX_FNAME,
		Extension, _MAX_EXT
	);

	char buffer[_MAX_EXT];

	memcpy(buffer, Extension, _MAX_EXT);
	memset(Extension, 0, _MAX_EXT);
	strncpy(Extension, buffer+1, _MAX_EXT);

	// Fix stuff
	//AsciiString fileName(Extension);
	//AsciiString extension(Extension);

	//extension.Remove('.');
	//fileName.Remove('/');
}

BF::FileActionResult BF::File::ReadFromDisk()
{
	const unsigned int elementSize = sizeof(char);
	size_t fullSize = -1;
	FILE* file = fopen(Path, "rb");

	if (file == nullptr)
	{
		return BF::FileActionResult::FileNotFound;
	}

	fseek(file, 0, SEEK_END);
	DataSize = ftell(file);
	rewind(file);
	//fseek(file, 0, SEEK_SET);


	fullSize = DataSize * elementSize;
	Data = (char*)malloc(fullSize);	// +1 if text

	if (!Data)
	{
		return BF::FileActionResult::OutOfMemory;
	}

	//Data[fullSize] = '\0'; // Termiate

	size_t readBytes = fread(Data, elementSize, DataSize, file);
	size_t overAllocatedBytes = DataSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.	

	assert(readBytes == DataSize);

	if (readBytes != DataSize)
	{
		memset(&Data[readBytes], 0, DataSize - readBytes);

		DataSize = readBytes;
	}

	int closeResult = fclose(file);

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::ReadFromDisk(const char* filePath, char** buffer)
{
	const unsigned int elementSize = sizeof(char);
	size_t fullSize = -1;
	size_t fileSize = 0;
	FILE* file = fopen(filePath, "rb");

	if (file == nullptr)
	{
		return BF::FileActionResult::FileNotFound;
	}

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	rewind(file);
	//fseek(file, 0, SEEK_SET);


	fullSize = fileSize * elementSize;
	(*buffer) = (char*)malloc(fullSize + 1);

	if (!(*buffer))
	{
		return BF::FileActionResult::OutOfMemory;
	}

	(*buffer)[fullSize] = '\0';

	size_t readBytes = fread((*buffer), elementSize, fileSize, file);
	size_t overAllocatedBytes = fileSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.	

	if (readBytes != fileSize)
	{
		memset(&(*buffer)[readBytes], 0, fileSize - readBytes);

		fileSize = readBytes;
	}

	int closeResult = fclose(file);

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::ReadFromDisk(const char* filePath, char** buffer, unsigned int maxSize)
{
	std::ifstream inputFileStream(filePath, std::ios::binary | std::ios::ate);
	size_t length = inputFileStream.tellg();

	if (length == -1)
	{
		return BF::FileActionResult::FileNotFound;
	}

	if (length > maxSize && maxSize != -1)
	{
		return BF::FileActionResult::OutOfMemory;
	}

	if ((*buffer) == nullptr)
	{
		(*buffer) = new char[length + 1];

		if ((*buffer) == 0)
		{
			return BF::FileActionResult::OutOfMemory;
		}
	}

	inputFileStream.seekg(0, inputFileStream.beg);
	inputFileStream.read(*buffer, length);

	(*buffer)[length] = 0;

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::WriteToDisk()
{
	FILE* file = fopen(Path, "wb");

	if (!file)
	{
		return BF::FileActionResult::FileNotFound;
	}

	size_t writtenBytes = fwrite(Data, sizeof(char), DataSize, file);

	int closeResult = fclose(file);

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::WriteToDisk(const char* filePath, const char* content, unsigned int length)
{
	FILE* file = fopen(filePath, "wb");

	unsigned int resultwrittenBytes = fwrite(content, sizeof(char), length, file);

	int resultCloseResult = fclose(file);

	return BF::FileActionResult::Successful;
}

unsigned int BF::File::ReadNextLineInto(char* exportBuffer)
{
	int length = 0;
	int index = DataCursorPosition;

	while (index < DataSize && Data[index] != '\n' && Data[index] != '\0')
	{
		index = DataCursorPosition + length++;
	}

	if (length <= 1)
	{
		return 0;
	}	

	memcpy(exportBuffer, Data + DataCursorPosition, length);
	exportBuffer[length-1] = '\0';

	DataCursorPosition += length;

	while (Data[DataCursorPosition] == '\n' && DataCursorPosition < DataSize)
	{
		DataCursorPosition++;
	}

	return length;
}

void BF::File::Read(bool& value)
{
	char byte = Data[DataCursorPosition++];

	switch (byte)
	{
		case '1':
		case 1:
			value = true;
			break;

		default:
			value = false;
			break;
	}
}

void BF::File::Read(char& value)
{
	Read((unsigned char&)value);
}

void BF::File::Read(unsigned char& value)
{
	value = Data[DataCursorPosition++];
}

void BF::File::Read(short& value, Endian endian)
{
	Read((unsigned short&)value, endian);
}

void BF::File::Read(unsigned short& value, Endian endian)
{
	unsigned char valueData[2];

	Read(valueData, 2u);

	switch (endian)
	{
		case Endian::Big:
			value =
				(valueData[0] << 8) |
				(valueData[1]);

			break;

		default:
		case Endian::Little:
			value =
				(valueData[0]) |
				(valueData[1] << 8);
			break;
	}

	assert(value < 65408);
}

void BF::File::Read(int& value, Endian endian)
{
	Read((unsigned int&)value, endian);
}

void BF::File::Read(unsigned int& value, Endian endian)
{
	unsigned char valueData[4];

	Read(valueData, 4u);

	switch (endian)
	{
		case Endian::Big:
			value =
				(valueData[0] << 24) |
				(valueData[1] << 16) |
				(valueData[2] << 8) |
				(valueData[3]);

			break;

		default:
		case Endian::Little:
			value =
				(valueData[0]) |
				(valueData[1] << 8) |
				(valueData[2] << 16) |
				(valueData[3] << 24);
			break;
	}
}

void BF::File::Read(unsigned long long& value, Endian endian)
{
	unsigned char valueData[8];

	Read(valueData, 8u);

	switch (endian)
	{
		case Endian::Big:
		{
			value =
				(valueData[0] << 56LL) |
				(valueData[1] << 48LL) |
				(valueData[2] << 40LL) |
				(valueData[3] << 32LL) |
				(valueData[4] << 24LL) |
				(valueData[5] << 16LL) |
				(valueData[6] << 8LL) |
				(valueData[7]);

			break;
		}
		default:
		case Endian::Little:
			value =
				(valueData[0]) |
				(valueData[1] << 8LL) |
				(valueData[2] << 16LL) |
				(valueData[3] << 24LL) |
				(valueData[4] << 32LL) |
				(valueData[5] << 40LL) |
				(valueData[6] << 48LL) |
				(valueData[7] << 56LL);
			break;
	}
}

void BF::File::Read(void* value, size_t length)
{
	memcpy(value, &Data[DataCursorPosition], length);

	DataCursorPosition += length;
}

bool BF::File::ReadAndCompare(const char* value, size_t length)
{
	return ReadAndCompare((void*)value, length);
}

bool BF::File::ReadAndCompare(void* value, size_t length)
{
	bool result = memcmp(value, Data + DataCursorPosition, length) == 0;

	DataCursorPosition += length;

	return result;
}

void BF::File::Write(bool value)
{
	Data[DataCursorPosition++] = value;
}

void BF::File::Write(char value)
{
	Data[DataCursorPosition++] = value;
}

void BF::File::Write(unsigned char value)
{
	Data[DataCursorPosition++] = value;
}

void BF::File::Write(short value, Endian endian)
{
	Write((unsigned short)value, endian);
}

void BF::File::Write(unsigned short value, Endian endian)
{
	unsigned char valueData[2];

	switch (endian)
	{
		case Endian::Big:
		{
			valueData[0] = (value & 0xFF00) >> 8;
			valueData[1] = (value & 0x00FF);
			break;
		}
		default:
		case Endian::Little:
		{
			valueData[0] = (value & 0x00FF);	
			valueData[1] = (value & 0xFF00) >> 8;
			break;
		}
	}

	Write(valueData, 2u);
}

void BF::File::Write(int value, Endian endian)
{
	Write((unsigned int)value, endian);
}

void BF::File::Write(unsigned int value, Endian endian)
{
	unsigned char valueData[4];	

	switch (endian)
	{
		case Endian::Big:
		{
			valueData[0] = (value & 0xFF000000) >> 24;
			valueData[1] = (value & 0x00FF0000) >> 16;
			valueData[2] = (value & 0x0000FF00) >> 8;
			valueData[3] =  value & 0x000000FF;
			break;
		}
		default:
		case Endian::Little:
		{
			valueData[0] =  value & 0x000000FF;
			valueData[1] = (value & 0x0000FF00) >> 8;
			valueData[2] = (value & 0x00FF0000) >> 16;
			valueData[3] = (value & 0xFF000000) >> 24;
			break;
		}
	}

	Write(valueData, 4u);
}

void BF::File::Write(const char* string, size_t length)
{
	Write((void*)string, length);	
}

void BF::File::Write(unsigned long long& value, Endian endian)
{
}

void BF::File::Write(void* value, size_t length)
{
	memcpy(Data + DataCursorPosition, value, length);

	DataCursorPosition += length;
}

bool BF::File::DoesFileExist()
{
	std::ifstream file(Path);
	bool fileExists = file.good();

	file.close();

	return fileExists;
}

bool BF::File::DoesFileExist(const char* filePath)
{
	if (!filePath)
	{
		return false;
	}

    std::ifstream file(filePath);
    bool fileExists = file.good();

    file.close();

    return fileExists;
}

void BF::File::GetFileExtension(const char* filePath, const char* fileExtension)
{
	char dummyBuffer[_MAX_PATH];

	_splitpath_s
	(
		filePath,
		dummyBuffer, _MAX_DRIVE,
		dummyBuffer, _MAX_DIR,
		dummyBuffer, _MAX_FNAME,
		(char*)fileExtension, _MAX_EXT
	);
}
int BF::File::CountAmountOfLines()
{
	int lineCounter = 0;
	int index = 0;

	if (Data == nullptr)
	{
		return 0;
	}

	while (index < DataSize)
	{
		char character = Data[index++];

		if (character == '\n')
		{
			++lineCounter;

			while (Data[index] == '\n')
			{
				++index;
			}
		}		
	}

	return lineCounter;
}