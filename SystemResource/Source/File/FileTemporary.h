#pragma once

#include "FileActionResult.hpp"
#include "IFile.h"

namespace BF
{
	// Temporary file that will not be saved to the HardDrive.
	// May be faster than a file but is not peristend!
	struct FileTemporary : public IFile
	{
		public:
		FILE* FileMarker;

		FileActionResult Open(const char* filePath, FileOpenMode fileOpenMode);
		FileActionResult Open(const wchar_t* filePath, FileOpenMode fileOpenMode);

		FileActionResult Close();
	};

	typedef FileTemporary Pipe;
}