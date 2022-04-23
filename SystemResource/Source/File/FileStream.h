#pragma once

#include "FileActionResult.hpp"
#include "ByteStream.h"
#include "IFile.h"
#include <cstdlib>
#include "FilePersistence.hpp"
#include "FileLocation.h"

#include <Windows.h>

namespace BF
{
	class FileStream : public ByteStream
	{	
		private:
		FileLocation _fileLocation;
		HANDLE _fileHandle;
		HANDLE _fileMappingHandle;

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