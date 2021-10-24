#pragma once

#include <cstdlib>

#include "IFile.h"
#include "../File/FileActionResult.hpp"

#define FileLineBufferSize 255u

namespace BF
{
	struct File : public IFile
	{
		private:
		FileActionResult CheckFile();

		public:	
		FILE* FileMarker;

		char Path[_MAX_PATH];
		char Drive[_MAX_DRIVE];
		char Directory[_MAX_DIR];
		char FileName[_MAX_FNAME];
		char Extension[_MAX_EXT];

		File();
		File(const char* filePath);		

		FileActionResult Open(const char* filePath, FileOpenMode fileOpenMode);
		FileActionResult Open(const wchar_t* filePath, FileOpenMode fileOpenMode);

		FileActionResult Close();


		//---<Utility>--
		bool DoesFileExist();
		static bool DoesFileExist(const char* filePath);
		static void GetFileExtension(const char* filePath, const char* fileExtension);
	

		bool Remove();
		static bool Remove(const char* filePath);
		bool ReName(const char* name);

		void SetFilePath(const char* filePath);
		//---------------------------------------------------------------------

		static void FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize);
	};
}