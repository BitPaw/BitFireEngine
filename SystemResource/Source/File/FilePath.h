#pragma once

#include <OS/OSDefine.h>
#include <cstddef>

#if defined(OSUnix)
#define PathMaxSize 260
#define DriveMaxSize 3
#define DirectoryMaxSize 256
#define FileNameMaxSize 256
#define ExtensionMaxSize 256
#elif defined(OSWindows)
#define PathMaxSize 260 // _MAX_PATH
#define DriveMaxSize 3 //_MAX_DRIVE
#define DirectoryMaxSize 256//_MAX_DIR
#define FileNameMaxSize 256 //_MAX_FNAME
#define ExtensionMaxSize 256 //_MAX_EXT
#endif

namespace BF
{
	struct FilePath
	{
		public:
		wchar_t Path[PathMaxSize];
		wchar_t Drive[DriveMaxSize];
		wchar_t Directory[DirectoryMaxSize];
		wchar_t FileName[FileNameMaxSize];
		wchar_t Extension[ExtensionMaxSize];

		FilePath();
		FilePath(const char* filePath);
		FilePath(const wchar_t* filePath);

		void Splitt(const char* filePath);
		void Splitt(const wchar_t* filePath);

		static void Splitt(const char* fullPath, char* drive, char* directory, char* fileName, char* extension);
		static void Splitt
		(
			const char* fullPath, size_t fullPathMaxSize,
			char* drive, size_t driveMaxSize,
			char* directory, size_t directoryMaxSize,
			char* fileName, size_t fileNameMaxSize,
			char* extension, size_t extensionMaxSize
		);

		static void Splitt(const wchar_t* fullPath, wchar_t* drive, wchar_t* directory, wchar_t* fileName, wchar_t* extension);
		static void Splitt
		(
			const wchar_t* fullPath, size_t fullPathMaxSize,
			wchar_t* drive, size_t driveMaxSize,
			wchar_t* directory, size_t directoryMaxSize,
			wchar_t* fileName, size_t fileNameMaxSize,
			wchar_t* extension, size_t extensionMaxSize
		);

		static void GetFileExtension(const char* filePath, char* fileExtension);

		bool ExtensionEquals(const char* extension);
		bool ExtensionEquals(const wchar_t* extension);
	};
}
