#include "FileStream.h"

#include <cassert>
#include <string>
#include "File.h"

BF::FileStream::FileStream()
{
}

BF::FileStream::FileStream(size_t dataSize)
{
	Data = (Byte*)malloc(DataSize * sizeof(Byte));
	DataSize = dataSize;
}

BF::FileStream::~FileStream()
{
	free(Data);
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const char* filePath, FilePersistence filePersistence)
{
	size_t fullSize = -1;
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read);

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	fseek(file.FileMarker, 0, SEEK_END);
	DataSize = ftell(file.FileMarker);
	rewind(file.FileMarker);
	//fseek(file, 0, SEEK_SET);

	Data = (Byte*)malloc(DataSize * sizeof(Byte));

	if (!Data)
	{
		return BF::FileActionResult::OutOfMemory;
	}

	//Data[fullSize] = '\0'; // Termiate

	size_t readBytes = fread(Data, 1u, DataSize, file.FileMarker);
	size_t overAllocatedBytes = DataSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.	

	assert(readBytes == DataSize);

	if (readBytes != DataSize)
	{
		memset(&Data[readBytes], 0, DataSize - readBytes);

		DataSize = readBytes;
	}

	result = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const wchar_t* filePath, FilePersistence filePersistence)
{
	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const char* filePath, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator, FilePersistence filePersistence)
{
	size_t fullSize = -1;
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read);

	if (result != FileActionResult::Successful)
	{
		return result;
	}	

	fseek(file.FileMarker, 0, SEEK_END);
	bufferSize = ftell(file.FileMarker);
	rewind(file.FileMarker);

	fullSize = bufferSize * sizeof(Byte);

	if (bufferSize)
	{
		++fullSize;
	}

	Byte* data = (Byte*)malloc(fullSize);

	if (!data)
	{
		return BF::FileActionResult::OutOfMemory;
	}

	if (bufferSize)
	{
		data[fullSize - 1] = '\0';
	}

	*targetBuffer = data;

	//Data[fullSize] = '\0'; // Termiate

	size_t readBytes = fread(data, 1u, bufferSize, file.FileMarker);
	size_t overAllocatedBytes = bufferSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.	

	assert(readBytes == bufferSize);

	if (readBytes != bufferSize)
	{
		memset(&data[readBytes], 0, bufferSize - readBytes);

		bufferSize = readBytes;
	}

	result = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::WriteToDisk(const char* filePath, FilePersistence filePersistence)
{
	File file(filePath);
	FileActionResult fileActionResult = file.Open(filePath, FileOpenMode::Write);

	if (fileActionResult != FileActionResult::Successful)
	{
		return fileActionResult;
	}

	size_t writtenBytes = fwrite(Data, sizeof(char), DataSize, file.FileMarker);

	fileActionResult = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::WriteToDisk(const wchar_t* filePath, FilePersistence filePersistence)
{
	return FileActionResult();
}