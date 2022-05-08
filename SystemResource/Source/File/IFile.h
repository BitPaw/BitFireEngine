#pragma once

#include <cstdio>

#include "FileOpenMode.hpp"
#include "FileActionResult.hpp"
#include "FileCachingMode.h"

#define FileReadMode "rb"
#define FileReadModeW L"rb"

#define FileWriteMode "wb"
#define FileWriteModeW L"wb"

namespace BF
{
	struct IFile
	{
		public:
		FILE* FileMarker = nullptr;

		virtual FileActionResult Open(const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default) = 0;
		virtual FileActionResult Open(const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode = FileCachingMode::Default) = 0;
		virtual FileActionResult Close() = 0;
	};
}
