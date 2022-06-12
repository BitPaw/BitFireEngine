#pragma once

#include <cstdlib>
#include <cstdio>
#include <cwchar>
#include <cassert>

#include "IFile.h"
#include "FileActionResult.hpp"
#include "FileCachingMode.h"
#include "FileLocation.h"
#include "FilePath.h"
#include "ByteStream.h"

#include <ErrorCode.h>
#include <OS/OSDefine.h>
#include <File/FilePersistence.hpp>

#define FileLineBufferSize 2048

#if defined(OSUnix)

#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>

#define FileHandleType FILE*
#define FileMappingID int

#define FileOpenA fopen
#define FileOpenW(string, mode) FileOpenA((const char*)string, (const char*)mode)
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

#define FileHandleType HANDLE
#define FileMappingID HANDLE

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
	struct File : public ByteStream
	{
		protected:
		FileLocation _fileLocation; // Where the is stored, used as indicator how to clean up.

		public:	
		FileHandleType FileHandle; // Only used if file is used directly	

#if defined(OSWindows)
		FILE* FileHandleCStyle; // Used for writing only, usage of fprintf()
		FileMappingID IDMapping; // Only used while mapping a file
#endif
		
		File();
		~File();	

		//---<Open>------------------------------------------------------------
		FileActionResult Open(const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default);
		FileActionResult Open(const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default);
		//---------------------------------------------------------------------

		//---<Mapping>---------------------------------------------------------
		FileActionResult MapToVirtualMemory(const char* filePath);
		FileActionResult MapToVirtualMemory(const wchar_t* filePath);
		FileActionResult MapToVirtualMemory(const size_t size);
		FileActionResult UnmapFromVirtualMemory();
		//---------------------------------------------------------------------

		//---<Read>------------------------------------------------------------
		FileActionResult ReadFromDisk(unsigned char** outPutBuffer, size_t& outPutBufferSize, const bool addTerminatorByte = false);	
		FileActionResult ReadFromDisk(const char* filePath, bool addNullTerminator = false, FilePersistence filePersistence = FilePersistence::Permanent);
		FileActionResult ReadFromDisk(const wchar_t* filePath, bool addNullTerminator = false, FilePersistence filePersistence = FilePersistence::Permanent);
		static FileActionResult ReadFromDisk(FILE* file, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator = false);
		static FileActionResult ReadFromDisk
		(
			const wchar_t* filePath,
			Byte** targetBuffer,
			size_t& bufferSize,
			bool addNullTerminator = false,
			FilePersistence filePersistence = FilePersistence::Permanent
		);
		//---------------------------------------------------------------------

		//---<Write>-----------------------------------------------------------
		FileActionResult WriteToDisk(const bool value);
		FileActionResult WriteToDisk(const char value);
		FileActionResult WriteToDisk(const unsigned char value);
		FileActionResult WriteToDisk(const short value, const Endian endian);
		FileActionResult WriteToDisk(const unsigned short value, const Endian endian);
		FileActionResult WriteToDisk(const int value, const  Endian endian);
		FileActionResult WriteToDisk(const unsigned int value, const Endian endian);
		FileActionResult WriteToDisk(const char* string, const size_t length);
		FileActionResult WriteToDisk(const unsigned char* string, const size_t length);
		FileActionResult WriteToDisk(const unsigned long long& value, const Endian endian);
		FileActionResult WriteToDisk(const void* value, const size_t length);
		FileActionResult WriteToDisk(const char* format, ...);

		FileActionResult WriteIntoFile(const void* data, const size_t dataSize);
		FileActionResult WriteToDisk(const char* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
		FileActionResult WriteToDisk(const wchar_t* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
		//---------------------------------------------------------------------

		//---<Close>-----------------------------------------------------------
		FileActionResult Close();
		//---------------------------------------------------------------------

		//---<Utility>---------------------------------------------------------
		static bool DoesFileExist(const char* filePath);
		static bool DoesFileExist(const wchar_t* filePath);

		static ErrorCode Remove(const char* filePath);
		static ErrorCode Remove(const wchar_t* filePath);
		static ErrorCode Rename(const char* oldName, const char* newName);
		static ErrorCode Rename(const wchar_t* oldName, const wchar_t* newName);
		static FileActionResult Copy(const char* sourceFilePath, const char* destinationFilePath);
		static FileActionResult Copy(const wchar_t* sourceFilePath, const wchar_t* destinationFilePath);

		static void PathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName);
		//---------------------------------------------------------------------

		//---<Directory>-------------------------------------------------------
		static ErrorCode DirectoryCreate(const char* directoryName);
		static ErrorCode DirectoryCreate(const wchar_t* directoryName);
		static ErrorCode WorkingDirectoryChange(const char* directoryName);
		static ErrorCode WorkingDirectoryGet(char* workingDirectory, size_t workingDirectorySize);
		static ErrorCode WorkingDirectoryGet(wchar_t* workingDirectory, size_t workingDirectorySize);
		static ErrorCode WorkingDirectoryChange(const wchar_t* directoryName);
		static ErrorCode DirectoryDelete(const char* directoryName);
		static ErrorCode DirectoryDelete(const wchar_t* directoryName);
		static void FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize);
		static void FilesInFolder(const wchar_t* folderPath, wchar_t*** list, size_t& listSize);
		//---------------------------------------------------------------------	
	};
}