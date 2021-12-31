#include "FileStream.h"

#include <cassert>
#include <string>
#include "File.h"

BF::FileStream::FileStream()
{
}

BF::FileStream::FileStream(size_t dataSize)
{
	DataSize = dataSize;
	Data = (Byte*)malloc(DataSize * sizeof(Byte));
}

BF::FileStream::~FileStream()
{
	free(Data);
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const char* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read);

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	result = ReadFromDisk(file.FileMarker, &Data, DataSize, addNullTerminator);

	result = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const wchar_t* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read);

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	result = ReadFromDisk(file.FileMarker, &Data, DataSize, addNullTerminator);

	result = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::ReadFromDisk(FILE* file, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator)
{
	fseek(file, 0, SEEK_END); // Jump to end of file
	bufferSize = ftell(file); // Get current 'data-cursor' position

	if (!bufferSize) // If no bytes in file, exit.
	{
		return FileActionResult::FileEmpty;
	}

	rewind(file); // Jump to the begining of the file

	if (addNullTerminator)
	{
		++bufferSize;
	}

	Byte* dataBuffer = (Byte*)malloc(bufferSize * sizeof(Byte));	

	if (!dataBuffer) // If malloc failed
	{
		return BF::FileActionResult::OutOfMemory;
	}

	*targetBuffer = dataBuffer;

	if (addNullTerminator)
	{
		dataBuffer[bufferSize - 1] = '\0';
		--bufferSize;
	}	

	size_t readBytes = fread(dataBuffer, 1u, bufferSize, file);
	size_t overAllocatedBytes = bufferSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.	

	assert(bufferSize == readBytes);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const char* filePath, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read);

	if (result != FileActionResult::Successful)
	{
		return result;
	}	

	result = ReadFromDisk(file.FileMarker, targetBuffer, bufferSize, addNullTerminator);

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