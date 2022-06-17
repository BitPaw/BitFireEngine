#include "FilePath.h"

#include <Text/Text.h>

#include <cstdlib>

#if defined(OSUnix)
#include <libgen.h> // dirname()
#elif defined(OSWindows)
#endif

BF::FilePath::FilePath()
{
	Path[0] = '\0';
	Drive[0] = '\0';
	Directory[0] = '\0';
	FileName[0] = '\0';
	Extension[0] = '\0';
}

BF::FilePath::FilePath(const char* filePath)
{
	Splitt(filePath);
}

BF::FilePath::FilePath(const wchar_t* filePath)
{
	Splitt(filePath);
}

void BF::FilePath::Splitt(const char* filePath)
{
	wchar_t filePathW[PathMaxSize];

	Text::Copy(filePath, PathMaxSize, filePathW, PathMaxSize);

	FilePath::Splitt
	(
		filePathW, PathMaxSize,
		Drive, DriveMaxSize,
		Directory, DirectoryMaxSize,
		FileName, FileNameMaxSize,
		Extension, ExtensionMaxSize
	);
}

void BF::FilePath::Splitt(const wchar_t* filePath)
{
	FilePath::Splitt
	(
		filePath, PathMaxSize,
		Drive, DriveMaxSize,
		Directory, DirectoryMaxSize,
		FileName, FileNameMaxSize,
		Extension, ExtensionMaxSize
	);
}

void BF::FilePath::Splitt(const char* fullPath, char* drive, char* directory, char* fileName, char* extension)
{
	Splitt
	(
		fullPath, PathMaxSize,
		drive, DriveMaxSize,
		directory, DirectoryMaxSize,
		fileName, FileNameMaxSize,
		extension, ExtensionMaxSize
	);
}

void BF::FilePath::Splitt(const char* fullPath, size_t fullPathMaxSize, char* drive, size_t driveMaxSize, char* directory, size_t directoryMaxSize, char* fileName, size_t fileNameMaxSize, char* extension, size_t extensionMaxSize)
{
#if defined(OSUnix)
	char directoryNameCache[PathMaxSize];
	char baseNameCache[FileNameMaxSize];

	Text::Copy(fullPath, FileNameMaxSize, directoryNameCache, FileNameMaxSize);
	Text::Copy(fullPath, FileNameMaxSize, baseNameCache, FileNameMaxSize);

	char* dirNameResult = dirname(directoryNameCache);
	char* baseNameResult = basename(baseNameCache);

	size_t directoryLength = Text::Copy(dirNameResult, DirectoryMaxSize, directory, DirectoryMaxSize);
	size_t fileNameLength = Text::Copy(baseNameResult, FileNameMaxSize, fileName, FileNameMaxSize);

	for(size_t i = fileNameLength - 1; i > 0; --i)
	{
		bool isDot = fileName[i] == '.';

		if(isDot)
		{
			Text::Copy(fileName + i + 1, ExtensionMaxSize - i, extension, extensionMaxSize);
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

	for(size_t i = 0; fileName[i] != '\0'; i++)
	{
		const bool isDot = fileName[i] == '.';

		if(isDot)
		{
			Text::Copy(extension + i, extensionMaxSize, fileNameCache, FileNameMaxSize);
			Text::Copy(fileNameCache, FileNameMaxSize, extension, extensionMaxSize);
			break;
		}
	}
#endif
}

void BF::FilePath::Splitt(const wchar_t* fullPath, wchar_t* drive, wchar_t* directory, wchar_t* fileName, wchar_t* extension)
{
	Splitt
	(
		fullPath, PathMaxSize,
		drive, DriveMaxSize,
		directory, DirectoryMaxSize,
		fileName, FileNameMaxSize,
		extension, ExtensionMaxSize
	);
}

void BF::FilePath::Splitt(const wchar_t* fullPath, size_t fullPathMaxSize, wchar_t* drive, size_t driveMaxSize, wchar_t* directory, size_t directoryMaxSize, wchar_t* fileName, size_t fileNameMaxSize, wchar_t* extension, size_t extensionMaxSize)
{
#if defined(OSUnix)
	char fullPathA[PathMaxSize];
	char driveA[DriveMaxSize];
	char directoryA[DirectoryMaxSize];
	char fileNameA[FileNameMaxSize];
	char extensionA[ExtensionMaxSize];

	Text::Copy(fullPath, PathMaxSize, fullPathA, PathMaxSize);

	Splitt
	(
		fullPathA,
		driveA,
		directoryA,
		fileNameA,
		extensionA
	);

	Text::Copy(driveA, DriveMaxSize, drive, DriveMaxSize);
	Text::Copy(directoryA, DirectoryMaxSize, directory, DirectoryMaxSize);
	Text::Copy(fileNameA, FileNameMaxSize, fileName, FileNameMaxSize);
	Text::Copy(extensionA, ExtensionMaxSize, extension, ExtensionMaxSize);
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

	for(size_t i = 0; extension[i] != '\0'; i++)
	{
		const bool isDot = extension[i] == '.';

		if(isDot)
		{
			Text::Copy(extension + i + 1, extensionMaxSize, extensionCache, FileNameMaxSize);
			Text::Copy(extensionCache, FileNameMaxSize, extension, extensionMaxSize);
			break;
		}
	}
#endif
}

void BF::FilePath::GetFileExtension(const char* filePath, char* fileExtension)
{
	char dummyBuffer[PathMaxSize];

	Splitt(filePath, dummyBuffer, dummyBuffer, dummyBuffer, fileExtension);
}

bool BF::FilePath::ExtensionEquals(const char* extension)
{
	return Text::CompareIgnoreCase(Extension, extension, ExtensionMaxSize);
}

bool BF::FilePath::ExtensionEquals(const wchar_t* extension)
{
	return Text::CompareIgnoreCase(Extension, extension, ExtensionMaxSize);
}
