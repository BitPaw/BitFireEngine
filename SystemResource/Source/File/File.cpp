#include "File.h"

#include "../Container/AsciiString.h"
#include "../OSDefine.h"

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cwchar>
#include <direct.h>

#if defined(OSUnix)
#define FileRemoveA remove 
#define FileRemoveW wremove 
#define FileRenameA rename 
#define FileRenameW wrename
#define FileDirectoryCreate(string) mkdir(string, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#define FileDirectoryCreateW wmkdir
#define WorkingDirectoryCurrentA getcwd
#define WorkingDirectoryCurrentW wgetcwd
#define WorkingDirectoryChangeA chdir
#define WorkingDirectoryChangeW wchdir
#elif defined(OSWindows)
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

BF::FileActionResult BF::File::Open(const char* filePath, FileOpenMode fileOpenMode)
{
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

	FileMarker = fopen(filePath, readMode);

	return FileMarker ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
}

BF::FileActionResult BF::File::Open(const wchar_t* filePath, FileOpenMode fileOpenMode)
{
	const wchar_t* readMode = nullptr;

	switch (fileOpenMode)
	{
		case BF::FileOpenMode::Read:
			readMode = FileReadModeW;
			break;

		case BF::FileOpenMode::Write:
			readMode = FileWriteModeW;
			break;
	}

	assert(readMode != nullptr);

	FileMarker = _wfopen(filePath, readMode);

	return FileMarker ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
}

BF::FileActionResult BF::File::Close()
{
	int closeResult = fclose(FileMarker);

	switch (closeResult)
	{
		case 0:
			return FileActionResult::Successful;

		default:
			return FileActionResult::FileCloseFailure;
	}
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
	wchar_t nameW[_MAX_FNAME];
	size_t changedCharacters = 0;

	mbstowcs_s(&changedCharacters, nameW, _MAX_FNAME - 1, name, _MAX_FNAME - 1);

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

	wchar_t filePathW[_MAX_PATH];
	size_t changedCharacters = 0;

	mbstowcs_s(&changedCharacters, filePathW, _MAX_PATH-1, filePath, _MAX_PATH-1);

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

	lstrcpyW(Path, filePath);

	_wsplitpath_s
	(
		filePath,
		Drive, _MAX_DRIVE,
		Directory, _MAX_DIR,
		FileName, _MAX_FNAME,
		Extension, _MAX_EXT
	);

	if (Extension[0] != '\0')
	{
		wchar_t buffer[_MAX_EXT];

		memcpy(buffer, Extension, _MAX_EXT);
		memset(Extension, 0, _MAX_EXT);
		lstrcpyW(Extension, buffer + 1);
	}

	
	// Fix stuff
	//AsciiString fileName(Extension);
	//AsciiString extension(Extension);

	//extension.Remove('.');
	//fileName.Remove('/');
}

void BF::File::FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize)
{
	wchar_t folderPathW[_MAX_PATH];
	size_t writtenBytes = mbstowcs(folderPathW, folderPath, _MAX_PATH);	

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
				size_t length = strlen(fileName);				
				wchar_t* newString = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
				wchar_t** target = &(*list)[index];				

				if (!newString)
				{
					return; // Error: OutOfMemory
				}

				(*target) = newString;
				size_t writtenBytes = mbstowcs(*target, fileName, 255);
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
		size_t length = wcslen(dataCursour.cFileName);
		wchar_t* filePathSource = dataCursour.cFileName;		
		wchar_t* newString = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
	
		if (!newString)
		{
			return; // Error: OutOfMemory
		}	
	
		memcpy(newString, filePathSource, sizeof(wchar_t) * length);
		newString[length] = L'\0';

		(*list)[fileIndex] = newString;

		fileIndex++;
	}
	while (FindNextFile(hFind, &dataCursour));

	FindClose(hFind);
	
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

bool BF::File::ExtensionEquals(const char* extension)
{
	wchar_t extensionW[_MAX_EXT];
	size_t changedCharacters = 0;

	mbstowcs_s(&changedCharacters, extensionW, _MAX_EXT, extension, _MAX_EXT);

	return ExtensionEquals(extensionW);
}

bool BF::File::ExtensionEquals(const wchar_t* extension)
{
	return lstrcmpiW(Extension, extension) == 0;
}
