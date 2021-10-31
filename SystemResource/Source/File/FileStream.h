#pragma once

#include "FileActionResult.hpp"
#include "ByteStream.h"
#include "IFile.h"
#include <cstdlib>
#include "FilePersistence.hpp"

namespace BF
{
	class FileStream : public ByteStream
	{	
		public:
		FileStream();
		FileStream(size_t dataSize);
		~FileStream();

		FileActionResult ReadFromDisk(const char* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
		FileActionResult ReadFromDisk(const wchar_t* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
		static FileActionResult ReadFromDisk(FILE* file, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator = false);
		static FileActionResult ReadFromDisk
		(
			const char* filePath,
			Byte** targetBuffer, 
			size_t& bufferSize, 
			bool addNullTerminator = false,
			FilePersistence filePersistence = FilePersistence::Permanent
		);
		
		FileActionResult WriteToDisk(const char* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
		FileActionResult WriteToDisk(const wchar_t* filePath, FilePersistence filePersistence = FilePersistence::Permanent);
	};
}