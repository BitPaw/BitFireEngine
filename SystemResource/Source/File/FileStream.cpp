#include "FileStream.h"

#include <cassert>
#include <string>
#include "File.h"

#include <Hardware/Memory/Memory.h>

BF::FileStream::FileStream()
{
	_fileHandle = 0;
	_fileMappingHandle = 0;
	_fileLocation = FileLocation::Invalid;
}

BF::FileStream::FileStream(const size_t dataSize)
{
	_fileHandle = 0;
	_fileMappingHandle = 0;
	_fileLocation = FileLocation::Invalid;

	DataSize = dataSize;
	Data = Memory::Allocate<Byte>(dataSize);
}

BF::FileStream::~FileStream()
{

	switch(_fileLocation)
	{
		case FileLocation::MappedFromDisk:
			UnmapFromVirtualMemory();
			break;

		case  FileLocation::CachedFromDisk:
			Memory::Release(Data, DataSize);
			break;
	}
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const char* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read, FileCachingMode::Sequential);

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	result = file.ReadFromDisk(&Data, DataSize, addNullTerminator);

	if (result != FileActionResult::Successful)
	{
		file.Close();
		return result;
	}

	result = file.Close();

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	_fileLocation = FileLocation::CachedFromDisk;

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::ReadFromDisk(const wchar_t* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read, FileCachingMode::Sequential);

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	result = file.ReadFromDisk(&Data, DataSize, addNullTerminator);

	if (result != FileActionResult::Successful)
	{
		file.Close();
		return result;
	}

	result = file.Close();

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	_fileLocation = FileLocation::CachedFromDisk;

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::MapToVirtualMemory(const char* filePath)
{


	return FileActionResult::Invalid;
}

BF::FileActionResult BF::FileStream::MapToVirtualMemory(const wchar_t* filePath)
{
	void** adress = (void**)&Data;
	const bool x = Memory::VirtualMemoryFileMap(filePath, _fileHandle, _fileMappingHandle, adress, DataSize);

	_fileLocation = FileLocation::MappedFromDisk;

	return FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::UnmapFromVirtualMemory()
{
	void** adress = (void**)&Data;
	const bool x = Memory::VirtualMemoryFileUnmap(_fileHandle, _fileMappingHandle, adress, DataSize);

	return FileActionResult::Successful;
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

	Byte* dataBuffer = Memory::Allocate<Byte>(bufferSize);

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

BF::FileActionResult BF::FileStream::ReadFromDisk(const wchar_t* filePath, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read);

	if (result != FileActionResult::Successful)
	{
		return result;
	}	

	//result = ReadFromDisk(file.FileMarker, targetBuffer, bufferSize, addNullTerminator);

	file.ReadFromDisk(targetBuffer, bufferSize, addNullTerminator);

	result = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::FileStream::WriteToDisk(const char* filePath, FilePersistence filePersistence)
{
	File file;
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
	File file;
	FileActionResult fileActionResult = file.Open(filePath, FileOpenMode::Write);

	if(fileActionResult != FileActionResult::Successful)
	{
		return fileActionResult;
	}

	size_t writtenBytes = fwrite(Data, sizeof(char), DataSize, file.FileMarker);

	fileActionResult = file.Close();

	return BF::FileActionResult::Successful;
}