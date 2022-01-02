#pragma once

#include <cstdlib>

#include "IFile.h"
#include "../OSDefine.h"
#include "../File/FileActionResult.hpp"
#include "../ErrorCode.h"

#define FileLineBufferSize 255u

#if defined(OSUnix)
	#define _MAX_PATH 260
	#define _MAX_DRIVE 3
	#define _MAX_DIR 256
	#define _MAX_FNAME 256
	#define _MAX_EXT 256
#endif

namespace BF
{
	struct File : public IFile
	{
		private:
		FileActionResult CheckFile();

		public:	
		FILE* FileMarker;

		wchar_t Path[_MAX_PATH];
		wchar_t Drive[_MAX_DRIVE];
		wchar_t Directory[_MAX_DIR];
		wchar_t FileName[_MAX_FNAME];
		wchar_t Extension[_MAX_EXT];

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

		static void GetFileExtension(const char* filePath, const char* fileExtension);
	
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

		static void FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize);
	};
}