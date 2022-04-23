#include "File.h"

#include "../Container/AsciiString.h"

#include <Text/Text.h>
#include <Hardware/Memory/Memory.h>

BF::File::File()
{
	FileHandle = 0;
}

BF::FileActionResult BF::File::Open(const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
{
	return File::Open(FileHandle, filePath, fileOpenMode, fileCachingMode);
}

BF::FileActionResult BF::File::Open(FileHandleType& fileHandle, const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
{
#if defined(OSUnix)
	const char* readMode = nullptr;

	switch (fileOpenMode)
	{
		case BF::FileOpenMode::Read:
			readMode = FileReadMode;
			break;

		case BF::FileOpenMode::Write:
			readMode = FileWriteMode;
			break;
	}

	assert(readMode != nullptr);

	// Use this somewhere here
	// int posix_fadvise(int fd, off_t offset, off_t len, int advice);
	// int posix_fadvise64(int fd, off_t offset, off_t len, int advice);

	FileMarker = fopen(filePath, readMode);

	return FileMarker ? FileActionResult::Successful : FileActionResult::FileOpenFailure;

#elif defined(OSWindows)
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;
	//SECURITY_ATTRIBUTES securityAttributes = 0;
	DWORD dwCreationDisposition = 0;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = 0;

	switch (fileOpenMode)
	{
		case FileOpenMode::Read:
		{
			dwCreationDisposition = OPEN_EXISTING;
			dwDesiredAccess = GENERIC_READ;
			break;
		}
		case  FileOpenMode::Write:
		{
			dwCreationDisposition = CREATE_ALWAYS;
			dwDesiredAccess = GENERIC_WRITE;
			break;
		}
	}

	dwFlagsAndAttributes |= ConvertFileCachingMode(fileCachingMode);

	fileHandle = CreateFileA
	(
		filePath,
		dwDesiredAccess,
		dwShareMode,
		nullptr,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);

	bool successful = fileHandle != INVALID_HANDLE_VALUE;

	return successful ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
#endif
}

BF::FileActionResult BF::File::Open(const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
{
	return File::Open(FileHandle, filePath, fileOpenMode, fileCachingMode);
}

BF::FileActionResult BF::File::Open(FileHandleType& fileHandle, const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
{
#if defined(OSUnix)
	char filePathA[PathMaxSize];

	Text::Copy(filePathA, filePath, PathMaxSize);
	File::Open(filePathA, fileOpenMode);

	return FileMarker ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
#elif defined(OSWindows)
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;
	//SECURITY_ATTRIBUTES securityAttributes = 0;
	DWORD dwCreationDisposition = 0;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = nullptr;

	switch (fileOpenMode)
	{
		case FileOpenMode::Read:
		{
			dwCreationDisposition = OPEN_EXISTING;
			dwDesiredAccess = GENERIC_READ;
			break;
		}
		case  FileOpenMode::Write:
		{
			dwCreationDisposition = CREATE_ALWAYS;
			dwDesiredAccess = GENERIC_WRITE;
			break;
		}
	}

	dwFlagsAndAttributes |= ConvertFileCachingMode(fileCachingMode);

	fileHandle = CreateFileW
	(
		filePath,
		dwDesiredAccess,
		dwShareMode,
		nullptr,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);

	bool successful = fileHandle != INVALID_HANDLE_VALUE;

	return successful ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
#endif
}

BF::FileActionResult BF::File::Close()
{
	return File::Close(FileHandle);
}

BF::FileActionResult BF::File::Close(FileHandleType& fileHandle)
{
#if defined(OSUnix)
	int closeResult = fclose(FileMarker);

	switch (closeResult)
	{
		case 0:
			return FileActionResult::Successful;

		default:
			return FileActionResult::FileCloseFailure;
}
#elif defined(OSWindows)
	bool successful = CloseHandle(fileHandle);

	fileHandle = nullptr;

	return successful ? FileActionResult::Successful : FileActionResult::FileCloseFailure;
#endif
}

BF::ErrorCode BF::File::Remove(const char* filePath)
{
	int removeResult = FileRemoveA(filePath);
	ErrorCode errorCode = ConvertErrorCode(removeResult);

	return errorCode;
}

BF::ErrorCode BF::File::Remove(const wchar_t* filePath)
{
	int removeResult = FileRemoveW(filePath);
	ErrorCode errorCode = ConvertErrorCode(removeResult);

	return errorCode;
}

BF::ErrorCode BF::File::Rename(const char* oldName, const char* newName)
{
	int renameResult = FileRenameA(oldName, newName);
	ErrorCode errorCode = ConvertErrorCode(renameResult);

	return errorCode;
}

BF::ErrorCode BF::File::Rename(const wchar_t* oldName, const wchar_t* newName)
{
	int renameResult = FileRenameW(oldName, newName);
	bool wasSuccesful = renameResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::FileActionResult BF::File::Copy(const char* sourceFilePath, const char* destinationFilePath)
{
	if (!sourceFilePath || !destinationFilePath)
	{
		return FileActionResult::EmptyPath;
	}
#if defined (OSUnix)
	FILE* fileSource = fopen(sourceFilePath, FileReadMode);
	FILE* fileDestination = fopen(destinationFilePath, FileWriteMode);
	bool fileOpenSuccesful = fileSource && fileDestination;

	const size_t swapBufferSize = 2048;
	Byte swapBuffer[swapBufferSize];

	if (!fileOpenSuccesful)
	{
		return FileActionResult::FileOpenFailure;
	}

	while (!feof(fileSource))
	{
		size_t readBytes = fread(swapBuffer, sizeof(char), swapBufferSize, fileSource);
		size_t writtenBytes = fwrite(swapBuffer, sizeof(char), readBytes, fileDestination);
	}

	fclose(fileSource);
	fclose(fileDestination);
#elif defined(OSWindows)
	bool succesfull = CopyFileA(sourceFilePath, destinationFilePath, false);

	if (!succesfull)
	{
		return FileActionResult::FileCopyFailure;
	}
#endif

	return FileActionResult::Successful;
}

BF::FileActionResult BF::File::Copy(const wchar_t* sourceFilePath, const wchar_t* destinationFilePath)
{
	if (!sourceFilePath || !destinationFilePath)
	{
		return FileActionResult::EmptyPath;
	}

#if defined (OSUnix)
	char sourceFilePathA[PathMaxSize];
	char destinationFilePathA[PathMaxSize];

	Text::Copy(sourceFilePathA, sourceFilePath, PathMaxSize);
	Text::Copy(destinationFilePathA, destinationFilePath, PathMaxSize);

	return File::Copy(sourceFilePathA, destinationFilePathA);
#elif defined(OSWindows)
	bool succesfull = CopyFileW(sourceFilePath, destinationFilePath, false);

	if (!succesfull)
	{
		return FileActionResult::FileCopyFailure;
	}

	return FileActionResult::Successful;
#endif	
}

BF::ErrorCode BF::File::DirectoryCreate(const char* directoryName)
{
	int creationResult = FileDirectoryCreateA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::DirectoryCreate(const wchar_t* directoryName)
{
	int creationResult = FileDirectoryCreateW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryGet(char* workingDirectory, size_t workingDirectorySize)
{
	char* workingDirectoryResult = WorkingDirectoryCurrentA(workingDirectory, workingDirectorySize);
	bool wasSuccesful = workingDirectoryResult != nullptr;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryGet(wchar_t* workingDirectory, size_t workingDirectorySize)
{
	wchar_t* workingDirectoryResult = WorkingDirectoryCurrentW(workingDirectory, workingDirectorySize);
	bool wasSuccesful = workingDirectoryResult != nullptr;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryChange(const char* directoryName)
{
	int creationResult = WorkingDirectoryChangeA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryChange(const wchar_t* directoryName)
{
	int creationResult = WorkingDirectoryChangeW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::DirectoryDelete(const char* directoryName)
{
	int creationResult = FileRemoveA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::DirectoryDelete(const wchar_t* directoryName)
{
	int creationResult = FileRemoveW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::FileActionResult BF::File::ReadFromDisk(unsigned char** outPutBuffer, size_t& outPutBufferSize, const bool addTerminatorByte)
{	
#if defined(OSUnix)
	fseek(FileMarker, 0, SEEK_END); // Jump to end of file
	outPutBufferSize = ftell(FileMarker); // Get current 'data-cursor' position

	if (!outPutBufferSize) // If no bytes in file, exit.
	{
		return FileActionResult::FileEmpty;
	}

	rewind(FileMarker); // Jump to the begining of the file

	if (addTerminatorByte)
	{
		++outPutBufferSize;
	}

	unsigned char* dataBuffer = (unsigned char*)malloc(outPutBufferSize * sizeof(unsigned char));

	if (!dataBuffer) // If malloc failed
	{
		return BF::FileActionResult::OutOfMemory;
	}

	*outPutBuffer = dataBuffer;

	if (addTerminatorByte)
	{
		dataBuffer[outPutBufferSize - 1] = '\0';
		--outPutBufferSize;
	}

	size_t readBytes = fread(dataBuffer, 1u, outPutBufferSize, FileMarker);
	size_t overAllocatedBytes = outPutBufferSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.	

	assert(outPutBufferSize == readBytes);

	return FileActionResult::Successful;
#elif defined(OSWindows)
	const DWORD fileSize = GetFileSize(FileHandle, nullptr);
	DWORD numberOfBytesRead = 0;
	OVERLAPPED* overlapped = nullptr;
	//LARGE_INTEGER size;
	//bool succesSize = GetFileSizeEx(FileHandle, &size);
	size_t allocationSize = fileSize;

	if (addTerminatorByte)
	{
		++allocationSize;
	}

	unsigned char* buffer = Memory::Allocate<unsigned char>(allocationSize);

	if (!buffer)
	{
		return FileActionResult::OutOfMemory;
	}

	bool sucessful = ReadFile
	(
		FileHandle, // file
		buffer, // input
		fileSize, // Shall read
		&numberOfBytesRead, // Has read
		overlapped
	);

	if (!sucessful)
	{
		return FileActionResult::FileReadFailure;
	}

	buffer[allocationSize - 1] = '\0';

	(*outPutBuffer) = buffer;
	outPutBufferSize = numberOfBytesRead;

	return FileActionResult::Successful;
#endif	
}

void BF::File::PathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName)
{
	const size_t index = Text::FindLast(currnetPath, PathMaxSize, '/');
	const bool found = index != -1;

	if (found)
	{
		size_t copyedBytes = Text::Copy(targetPath, currnetPath, index + 1);

		Text::Copy(targetPath + copyedBytes, newFileName, 260 - copyedBytes);
	}
}

void BF::File::FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize)
{
	wchar_t folderPathW[PathMaxSize];
	size_t writtenBytes = Text::Copy(folderPathW, folderPath, PathMaxSize);

#if defined(OSUnix)		
	DIR* directory = opendir(folderPath);

	if (directory)
	{
		struct dirent* directoryInfo = nullptr;

		while (directoryInfo = readdir(directory))
		{
			++listSize;
		}

		rewinddir(directory);

		(*list) = (wchar_t**)malloc(listSize * sizeof(wchar_t*));

		for (size_t index = 0; directoryInfo = readdir(directory); index++)
		{
			bool isFile = directoryInfo->d_type == DT_REG || true;

			if (isFile)
			{
				const char* fileName = directoryInfo->d_name;
				size_t length = Text::Length(fileName);
				wchar_t* newString = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
				wchar_t** target = &(*list)[index];				

				if (!newString)
				{
					return; // Error: OutOfMemory
				}

				(*target) = newString;
				size_t writtenBytes = Text::Copy(*target, fileName, PathMaxSize);
			}
		}

		closedir(directory);
	}
#elif defined(OSWindows)
	WIN32_FIND_DATA dataCursour;
	HANDLE hFind = 0;

	Memory::Set(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	hFind = FindFirstFile(folderPathW, &dataCursour); 	// "/*.*";

	bool foundData = hFind != INVALID_HANDLE_VALUE;

	if (!foundData)
	{
		return;
	}

	++listSize;

	for (; FindNextFile(hFind, &dataCursour); listSize++);

	Memory::Set(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	(*list) = Memory::Allocate<wchar_t*>(listSize);

	hFind = FindFirstFile(folderPathW, &dataCursour); // Expected "." Folder
	size_t fileIndex = 0;

	do
	{
		const size_t length = Text::Length(dataCursour.cFileName);
		const wchar_t* filePathSource = dataCursour.cFileName;
		wchar_t* newString = Memory::Allocate<wchar_t>((length + 1) * sizeof(wchar_t));
	
		if (!newString)
		{
			return; // Error: OutOfMemory
		}	
	
		Text::Copy(newString, filePathSource, length);

		(*list)[fileIndex] = newString;

		fileIndex++;
	}
	while (FindNextFile(hFind, &dataCursour));

	FindClose(hFind);	
#endif
}

void BF::File::FilesInFolder(const wchar_t* folderPath, wchar_t*** list, size_t& listSize)
{
	
}

bool BF::File::DoesFileExist(const char* filePath)
{
	FILE* file = FileOpenA(filePath, "rb"); 

	if (file)
	{
		fclose(file);

		return true;
	}

	return false;
}

bool BF::File::DoesFileExist(const wchar_t* filePath)
{
	FILE* file = FileOpenW(filePath, L"rb");

	if(file)
	{
		fclose(file);

		return true;
	}

	return false;
}