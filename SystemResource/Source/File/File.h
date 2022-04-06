#pragma once

#include <cstdlib>
#include <cstdio>
#include <cwchar>
#include <cassert>

#include "IFile.h"
#include "FileCachingMode.h"

#include <ErrorCode.h>
#include <OS/OSDefine.h>
#include <File/FileActionResult.hpp>

#define FileLineBufferSize 2048



#ifndef Byte
#define Byte unsigned char
#endif

#if defined(OSUnix)
#define PathMaxSize 260
#define DriveMaxSize 3
#define DirectoryMaxSize 256
#define FileNameMaxSize 256
#define ExtensionMaxSize 256
#define FileHandleType FILE*

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
#define PathMaxSize _MAX_PATH
#define DriveMaxSize _MAX_DRIVE
#define DirectoryMaxSize _MAX_DIR
#define FileNameMaxSize _MAX_FNAME
#define ExtensionMaxSize _MAX_EXT
#define FileHandleType HANDLE

#include <direct.h>
#include <Windows.h>
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
#endif

namespace BF
{
	struct File : public IFile
	{
		private:
		FileActionResult CheckFile();

		public:	
		FileHandleType FileHandle;

		wchar_t Path[PathMaxSize];
		wchar_t Drive[DriveMaxSize];
		wchar_t Directory[DirectoryMaxSize];
		wchar_t FileName[FileNameMaxSize];
		wchar_t Extension[ExtensionMaxSize];

		File();
		File(const char* filePath);		
		File(const wchar_t* filePath);


		bool DoesFileExist();
		static bool DoesFileExist(const char* filePath);
		static bool DoesFileExist(const wchar_t* filePath);

		FileActionResult Open(const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default);
		static FileActionResult Open(FileHandleType& fileHandle, const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default);
		FileActionResult Open(const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default);
		static FileActionResult Open(FileHandleType& fileHandle, const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default);

		FileActionResult Close();
		static FileActionResult Close(FileHandleType& fileHandle);

		FileActionResult ReadFromDisk(unsigned char** outPutBuffer, size_t& outPutBufferSize, const bool addTerminatorByte = false);


		// Directory



		//---<Utility>--
	

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
		

		static FileActionResult Copy(const char* sourceFilePath, const char* destinationFilePath);
		static FileActionResult Copy(const wchar_t* sourceFilePath, const wchar_t* destinationFilePath);

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
		static void FilesInFolder(const wchar_t* folderPath, wchar_t*** list, size_t& listSize);

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