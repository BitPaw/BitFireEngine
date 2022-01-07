#pragma once

#include <cstdlib>

#include "IFile.h"
#include "../OSDefine.h"
#include "../File/FileActionResult.hpp"
#include "../ErrorCode.h"

#define FileLineBufferSize 2048

#if defined(OSUnix)
#define PathMaxSize 260
#define DriveMaxSize 3
#define DirectoryMaxSize 256
#define FileNameMaxSize 256
#define ExtensionMaxSize 256
#elif defined(OSWindows)
#define PathMaxSize _MAX_PATH
#define DriveMaxSize _MAX_DRIVE
#define DirectoryMaxSize _MAX_DIR
#define FileNameMaxSize _MAX_FNAME
#define ExtensionMaxSize _MAX_EXT
#endif

namespace BF
{
	struct File : public IFile
	{
		private:
		FileActionResult CheckFile();

		public:	
		FILE* FileMarker;

		wchar_t Path[PathMaxSize];
		wchar_t Drive[DriveMaxSize];
		wchar_t Directory[DirectoryMaxSize];
		wchar_t FileName[FileNameMaxSize];
		wchar_t Extension[ExtensionMaxSize];

		File();
		File(const char* filePath);		
		File(const wchar_t* filePath);

		FileActionResult Open(const char* filePath, FileOpenMode fileOpenMode);
		FileActionResult Open(const wchar_t* filePath, FileOpenMode fileOpenMode);

		FileActionResult Close();


		//---<Utility>--
		bool DoesFileExist();
		static bool DoesFileExist(const char* filePath);
		static bool DoesFileExist(const wchar_t* filePath);

		static void GetFileExtension(const char* filePath, char* fileExtension);
	
		bool ExtensionEquals(const char* extension);
		bool ExtensionEquals(const wchar_t* extension);

		ErrorCode Remove();
		static ErrorCode Remove(const char* filePath);
		static ErrorCode Remove(const wchar_t* filePath);

		ErrorCode Rename(const char* name);
		static ErrorCode Rename(const char* oldName, const char* newName);
		ErrorCode Rename(const wchar_t* name);
		static ErrorCode Rename(const wchar_t* oldName, const wchar_t* newName);
		

		static FileActionResult Copy(const char* sourceFilePath, const char* destinationFilePath, char* swapBuffer, size_t swapBufferSize);

		static ErrorCode DirectoryCreate(const char* directoryName);
		static ErrorCode DirectoryCreate(const wchar_t* directoryName);
		static ErrorCode WorkingDirectoryChange(const char* directoryName);
		static ErrorCode WorkingDirectoryGet(char* workingDirectory, size_t workingDirectorySize);
		static ErrorCode WorkingDirectoryGet(wchar_t* workingDirectory, size_t workingDirectorySize);
		static ErrorCode WorkingDirectoryChange(const wchar_t* directoryName);
		static ErrorCode DirectoryDelete(const char* directoryName);
		static ErrorCode DirectoryDelete(const wchar_t* directoryName);

		void SetFilePath(const char* filePath);
		void SetFilePath(const wchar_t* filePath);
		//---------------------------------------------------------------------

		static void PathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName);

		static void FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize);

		static void PathSplitt(const char* fullPath, char* drive, char* directory, char* fileName, char* extension);
		static void PathSplitt
		(
			const char* fullPath, size_t fullPathMaxSize,
			char* drive, size_t driveMaxSize,
			char* directory, size_t directoryMaxSize,
			char* fileName, size_t fileNameMaxSize,
			char* extension, size_t extensionMaxSize
		);

		static void PathSplitt(const wchar_t* fullPath, wchar_t* drive, wchar_t* directory, wchar_t* fileName, wchar_t* extension);
		static void PathSplitt
		(
			const wchar_t* fullPath, size_t fullPathMaxSize,
			wchar_t* drive, size_t driveMaxSize,
			wchar_t* directory, size_t directoryMaxSize,
			wchar_t* fileName, size_t fileNameMaxSize,
			wchar_t* extension, size_t extensionMaxSize
		);
	};
}