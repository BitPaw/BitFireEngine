#include "File.h"

#include "../Container/AsciiString.h"
#include "../OSDefine.h"
#include <cassert>
#include <cstdlib>
#include <cwchar>

#if  defined(OSUnix)

#elif defined(OSWindows)
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
	FileMarker = nullptr;
}

BF::File::File(const char* filePath)
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

void BF::File::FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize)
{
#if  defined(OSUnix)

#elif defined(OSWindows)
	wchar_t folderPathW[MAX_PATH];
	WIN32_FIND_DATA dataCursour;
	HANDLE hFind = 0;
	size_t writtenBytes = mbstowcs(folderPathW, folderPath, MAX_PATH);

	memset(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	hFind = FindFirstFile(folderPathW, &dataCursour); 	// "/*.*";

	bool foundData = hFind != INVALID_HANDLE_VALUE;

	if (!foundData)
	{
		return;
	}

	listSize++;

	for (; FindNextFile(hFind, &dataCursour); listSize++);

	memset(&dataCursour, 0, sizeof(WIN32_FIND_DATA));


	(*list) = (wchar_t**)malloc(listSize * sizeof(wchar_t*));

	hFind = FindFirstFile(folderPathW, &dataCursour); // Expected "." Folder
	size_t fileIndex = 0;

	do
	{
		wchar_t* filePathDestination = 0;
		wchar_t* filePathSource = dataCursour.cFileName;
		size_t length = wcslen(filePathSource);

		(*list)[fileIndex] = (wchar_t*)calloc(length + 1, sizeof(wchar_t));

		filePathDestination = (*list)[fileIndex];

		wcsncpy(filePathDestination, filePathSource, length);

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