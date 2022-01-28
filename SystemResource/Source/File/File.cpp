#include "File.h"

#include "../Container/AsciiString.h"
#include "../OSDefine.h"

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cwchar>

#if defined(OSUnix)
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#define FileRemoveA remove 
#define FileRemoveW(string) remove((const char*)string)
#define FileRenameA rename 
#define FileRenameW(oldName, newName) rename((const char*)oldName, (const char*)newName)
#define FileDirectoryCreateA(string) mkdir(string, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#define FileDirectoryCreateW(string) FileDirectoryCreateA((const char*)string)
#define WorkingDirectoryCurrentA getcwd
#define WorkingDirectoryCurrentW(string, size) (wchar_t*)WorkingDirectoryCurrentA((char*)string, size)
#define WorkingDirectoryChangeA chdir
#define WorkingDirectoryChangeW(string) WorkingDirectoryChangeA((const char*)string)
#elif defined(OSWindows)
#include <direct.h>
#define FileOpenA fopen
#define FileOpenW _wfopen
#define FileRemoveA remove 
#define FileRemoveW _wremove 
#define FileRenameA rename 
#define FileRenameW _wrename
#define FileDirectoryCreateA _mkdir
#define FileDirectoryCreateW _wmkdir
#define WorkingDirectoryCurrentA _getcwd
#define WorkingDirectoryCurrentW _wgetcwd
#define WorkingDirectoryChangeA _chdir
#define WorkingDirectoryChangeW _wchdir
#include <Windows.h>
#endif
#include "Text.h"

BF::FileActionResult BF::File::CheckFile()
{
	if (!DoesFileExist(Path))
	{
		return BF::FileActionResult::FileNotFound;
	}

	return BF::FileActionResult::Successful;
}

BF::File::File()
{
	SetFilePath((wchar_t*)nullptr);
}

BF::File::File(const char* filePath)
{
	SetFilePath(filePath);
}

BF::File::File(const wchar_t* filePath)
{
	SetFilePath(filePath);
}

BF::FileActionResult BF::File::Open(const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
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

	FileHandle = CreateFileA
	(
		filePath, 
		dwDesiredAccess,
		dwShareMode, 
		nullptr,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);

	bool successful = FileHandle != INVALID_HANDLE_VALUE;

	return successful ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
#endif
}

BF::FileActionResult BF::File::Open(const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
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

	FileHandle = CreateFileW
	(
		filePath,
		dwDesiredAccess,
		dwShareMode,
		nullptr,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);

	bool successful = FileHandle != INVALID_HANDLE_VALUE;

	return successful ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
#endif
}

BF::FileActionResult BF::File::Close()
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
	bool successful = CloseHandle(FileHandle);

	FileHandle = nullptr;
	
	return successful ? FileActionResult::Successful : FileActionResult::FileCloseFailure;
#endif
}

BF::ErrorCode BF::File::Remove()
{
	return BF::File::Remove(Path);
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

BF::ErrorCode BF::File::Rename(const char* name)
{
	wchar_t nameW[FileNameMaxSize];

	mbstowcs(nameW, name, FileNameMaxSize - 1);

	return File::Rename(Path, nameW);
}

BF::ErrorCode BF::File::Rename(const char* oldName, const char* newName)
{
	int renameResult = FileRenameA(oldName, newName);
	ErrorCode errorCode = ConvertErrorCode(renameResult);

	return errorCode;
}

BF::ErrorCode BF::File::Rename(const wchar_t* name)
{
	return File::Rename(Path, name);
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

BF::FileActionResult BF::File::Copy(const char* sourceFilePath, const char* destinationFilePath, char* swapBuffer, size_t swapBufferSize)
{
	if (!sourceFilePath || !destinationFilePath)
	{
		return FileActionResult::EmptyPath;
	}

	FILE* fileSource = fopen(sourceFilePath, FileReadMode);
	FILE* fileDestination = fopen(destinationFilePath, FileWriteMode);
	bool fileOpenSuccesful = fileSource && fileDestination;

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

	return FileActionResult::Successful;
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

void BF::File::SetFilePath(const char* filePath)
{
	if (!filePath)
	{
		SetFilePath((wchar_t*)nullptr);
		return;
	}

	wchar_t filePathW[PathMaxSize];

	Text::AsciiToUnicode(filePath, PathMaxSize, filePathW,PathMaxSize);

	SetFilePath(filePathW);
}

void BF::File::SetFilePath(const wchar_t* filePath)
{
	FileMarker = nullptr;

	if (filePath == nullptr)
	{
		Path[0] = '\0';
		Drive[0] = '\0';
		Directory[0] = '\0';
		FileName[0] = '\0';
		Extension[0] = '\0';
		return;
	}

	Text::Copy(Path, filePath, PathMaxSize);

	PathSplitt(filePath, Drive, Directory, FileName, Extension);
}

BF::FileActionResult BF::File::ReadFromDisk(unsigned char** outPutBuffer, size_t& outPutBufferSize, bool addTerminatorByte)
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

	unsigned char* buffer = (unsigned char*)malloc(sizeof(char) * allocationSize);

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

	memset(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	hFind = FindFirstFile(folderPathW, &dataCursour); 	// "/*.*";

	bool foundData = hFind != INVALID_HANDLE_VALUE;

	if (!foundData)
	{
		return;
	}

	++listSize;

	for (; FindNextFile(hFind, &dataCursour); listSize++);

	memset(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	(*list) = (wchar_t**)malloc(listSize * sizeof(wchar_t*));

	hFind = FindFirstFile(folderPathW, &dataCursour); // Expected "." Folder
	size_t fileIndex = 0;

	do
	{
		size_t length = Text::Length(dataCursour.cFileName);
		wchar_t* filePathSource = dataCursour.cFileName;		
		wchar_t* newString = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
	
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

void BF::File::PathSplitt(const char* fullPath, char* drive, char* directory, char* fileName, char* extension)
{
	PathSplitt
	(
		fullPath, PathMaxSize,
		drive, DriveMaxSize,
		directory, DirectoryMaxSize,
		fileName, FileNameMaxSize,
		extension, ExtensionMaxSize
	);
}

void BF::File::PathSplitt
(
	const char* fullPath, size_t fullPathMaxSize,
	char* drive, size_t driveMaxSize,
	char* directory, size_t directoryMaxSize,
	char* fileName, size_t fileNameMaxSize,
	char* extension, size_t extensionMaxSize
)
{
#if defined(OSUnix)
	char directoryNameCache[PathMaxSize];
	char baseNameCache[FileNameMaxSize];

	Text::Copy(directoryNameCache, fullPath, FileNameMaxSize);
	Text::Copy(baseNameCache, fullPath, FileNameMaxSize);

	char* dirNameResult = dirname(directoryNameCache);
	char* baseNameResult = basename(baseNameCache);

	size_t directoryLength = Text::Copy(directory, dirNameResult, DirectoryMaxSize);
	size_t fileNameLength = Text::Copy(fileName, baseNameResult, FileNameMaxSize);

	for (size_t i = fileNameLength - 1; i > 0; --i)
	{
		bool isDot = fileName[i] == '.';

		if (isDot)
		{
			Text::Copy(extension, fileName + i + 1, ExtensionMaxSize - i);
			break;
		}
	}
#elif defined(OSWindows)
	char fileNameCache[FileNameMaxSize];

	_splitpath_s
	(
		fullPath,
		drive, driveMaxSize,
		directory, directoryMaxSize,
		fileName, fileNameMaxSize,
		extension, extensionMaxSize
	);

	for (size_t i = 0; fileName[i] != '\0'; i++)
	{
		bool isDot = fileName[i] == '.';

		if (isDot)
		{			
			Text::Copy(fileNameCache, extension + i, FileNameMaxSize);
			Text::Copy(extension, fileNameCache, FileNameMaxSize);
			break;
		}
	}
#endif 
}

void BF::File::PathSplitt(const wchar_t* fullPath, wchar_t* drive, wchar_t* directory, wchar_t* fileName, wchar_t* extension)
{
	PathSplitt
	(
		fullPath, PathMaxSize,
		drive, DriveMaxSize,
		directory, DirectoryMaxSize,
		fileName, FileNameMaxSize,
		extension, ExtensionMaxSize
	);
}

void BF::File::PathSplitt(const wchar_t* fullPath, size_t fullPathMaxSize, wchar_t* drive, size_t driveMaxSize, wchar_t* directory, size_t directoryMaxSize, wchar_t* fileName, size_t fileNameMaxSize, wchar_t* extension, size_t extensionMaxSize)
{
#if defined(OSUnix)
	char fullPathA[PathMaxSize];
	char driveA[DriveMaxSize];
	char directoryA[DirectoryMaxSize];
	char fileNameA[FileNameMaxSize];
	char extensionA[ExtensionMaxSize];

	Text::Copy(fullPathA, fullPath, PathMaxSize);

	PathSplitt
	(
		fullPathA,
		driveA,
		directoryA,
		fileNameA,
		extensionA
	);

	Text::Copy(drive, driveA, DriveMaxSize);
	Text::Copy(directory, directoryA, DirectoryMaxSize);
	Text::Copy(fileName, fileNameA, FileNameMaxSize);
	Text::Copy(extension, extensionA, ExtensionMaxSize);
#elif defined(OSWindows)
	wchar_t extensionCache[FileNameMaxSize];

	_wsplitpath_s
	(
		fullPath,
		drive, driveMaxSize,
		directory, directoryMaxSize,
		fileName, fileNameMaxSize,
		extension, extensionMaxSize
	);

	for (size_t i = 0; extension[i] != '\0'; i++)
	{
		bool isDot = extension[i] == '.';

		if (isDot)
		{
			Text::Copy(extensionCache, extension + i + 1, FileNameMaxSize);
			Text::Copy(extension, extensionCache, FileNameMaxSize);
			break;
		}
	}
#endif 
}

bool BF::File::DoesFileExist()
{
	FileActionResult fileActionResult = Open(Path, FileOpenMode::Read);

	if (fileActionResult == FileActionResult::Successful)
	{
		Close();

		return true;
	}
	else
	{
		return false;
	}
}

bool BF::File::DoesFileExist(const char* filePath)
{
	FILE* file = fopen(filePath, "rb"); 

	if (file)
	{
		fclose(file);

		return true;
	}

	return false;
}

bool BF::File::DoesFileExist(const wchar_t* filePath)
{
	File file(filePath);
	
	return file.DoesFileExist();
}

void BF::File::GetFileExtension(const char* filePath, char* fileExtension)
{
	char dummyBuffer[PathMaxSize];

	PathSplitt(filePath, dummyBuffer, dummyBuffer, dummyBuffer, fileExtension);
}

bool BF::File::ExtensionEquals(const char* extension)
{
	return Text::CompareIgnoreCase(Extension, extension, ExtensionMaxSize);
}

bool BF::File::ExtensionEquals(const wchar_t* extension)
{
	return Text::CompareIgnoreCase(Extension, extension, ExtensionMaxSize);
}