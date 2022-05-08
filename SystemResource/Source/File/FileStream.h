#pragma once

#include "IFile.h"
#include "File.h"
#include "FileActionResult.hpp"
#include "FilePersistence.hpp"
#include "FileLocation.h"
#include "ByteStream.h"

#include <cstdlib>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#endif

namespace BF
{
	class FileStream : public ByteStream
	{
		private:
		FileLocation _fileLocation;
		FileHandleType _fileHandle;
		FileHandleType _fileMappingHandle;

		public:
		FileStream();
		FileStream(const size_t dataSize);
		~FileStream();

		FileActionResult ReadFromDisk(const char* filePath, bool addNullTerminator = false, FilePersistence filePersistence = FilePersistence::Permanent);
		FileActionResult ReadFromDisk(const wchar_t* filePath, bool addNullTerminator = false, FilePersistence filePersistence = FilePersistence::Permanent);


		FileActionResult MapToVirtualMemory(const char* filePath);
		FileActionResult MapToVirtualMemory(const wchar_t* filePath);
		FileActionResult UnmapFromVirtualMemory();

		static FileActionResult ReadFromDisk(FILE* file, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator = false);
		static FileActionResult ReadFromDisk
		(
			const wchar_t* filePath,
			Byte** targetBuffer,
			size_t& bufferSize,
			bool addNullTerminator = false,
			FilePersistence filePersistence = FilePersistence::Permanent
		);

		FileActionResult WriteToDisk(const char* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
		FileActionResult WriteToDisk(const wchar_t* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
	};
}
