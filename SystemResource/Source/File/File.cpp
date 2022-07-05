#include "File.h"

#include <Text/Text.h>
#include <Hardware/Memory/Memory.h>

#include <stdarg.h>
#include <fcntl.h>

#if defined(OSUnix)
#include <sys/mman.h>
#include <sys/stat.h>
#elif defined(OSWindows)
#include <io.h>
#endif

BF::File::File()
{
	_fileLocation = FileLocation::Invalid;
	FileHandle = 0;

#if defined(OSWindows)
	FileHandleCStyle = nullptr;
	IDMapping = nullptr;
#endif
}

BF::File::~File()
{
	switch(_fileLocation)
	{
		case FileLocation::MappedFromDisk:
			UnmapFromVirtualMemory();
			break;

		case FileLocation::MappedVirtual:
			Memory::VirtualMemoryRelease(Data, DataSize);
			break;

		case  FileLocation::CachedFromDisk:
			Memory::Release(Data, DataSize);
			break;

		case FileLocation::Linked:
			Close();
			break;
	}
}

BF::FileActionResult BF::File::Open(const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
{
#if defined(OSUnix)
	const char* readMode = nullptr;

	switch(fileOpenMode)
	{
		case BF::FileOpenMode::Read:
			readMode = FileReadMode;
			break;

		case BF::FileOpenMode::Write:
			readMode = FileWriteMode;
			break;
	}

	assert(readMode != nullptr);

	// Use this somewhere here
	// int posix_fadvise(int fd, off_t offset, off_t len, int advice);
	// int posix_fadvise64(int fd, off_t offset, off_t len, int advice);

	FileHandle = fopen(filePath, readMode);

	return FileHandle ? FileActionResult::Successful : FileActionResult::FileOpenFailure;

#elif defined(OSWindows)
	wchar_t filePathW[PathMaxSize];

	Text::Copy(filePath, PathMaxSize, filePathW, PathMaxSize);

	return Open(filePathW, fileOpenMode, fileCachingMode);
#endif
}

BF::FileActionResult BF::File::Open(const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
{
#if defined(OSUnix)
	char filePathA[PathMaxSize];

	Text::Copy(filePath, PathMaxSize, filePathA, PathMaxSize);

    const FileActionResult openResult = Open(filePathA, fileOpenMode);
    const bool successful = openResult == FileActionResult::Successful;

    if(!successful)
    {
        return openResult;
    }

	return FileActionResult::Successful;
#elif defined(OSWindows)
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;
	//SECURITY_ATTRIBUTES securityAttributes = 0;
	DWORD dwCreationDisposition = 0;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = nullptr;

	switch(fileOpenMode)
	{
		case FileOpenMode::Read:
		{
			dwCreationDisposition = OPEN_EXISTING;
			dwDesiredAccess = GENERIC_READ;
			break;
		}
		case  FileOpenMode::Write:
		{
			dwCreationDisposition = CREATE_ALWAYS;
			dwDesiredAccess = GENERIC_WRITE;
			break;
		}
	}

	dwFlagsAndAttributes |= ConvertFileCachingMode(fileCachingMode);

	FileHandle = CreateFileW
	(
		filePath,
		dwDesiredAccess,
		dwShareMode,
		nullptr,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);

	{
		const bool successful = FileHandle != INVALID_HANDLE_VALUE;

		if(!successful)
		{
			switch(fileOpenMode)
			{
				case FileOpenMode::Read:
					return FileActionResult::FileNotFound;

				case FileOpenMode::Write:
					return FileActionResult::FileCreateFailure;
			}

			const ErrorCode error = GetCurrentError();

			switch(error)
			{
				case ErrorCode::NoSuchFileOrDirectory:
					return FileActionResult::FileNotFound;

				default:
					return FileActionResult::FileOpenFailure;
			}
		}
	}

	// Get a FILE* from file HANDLE
	{
		int osHandleMode = 0;
		const char* fdOpenMode = nullptr;

		switch(fileOpenMode)
		{
			case FileOpenMode::Read:
			{
				osHandleMode = _O_RDONLY;
				fdOpenMode = FileReadMode;
				break;
			}
			case  FileOpenMode::Write:
			{
				osHandleMode = _O_WRONLY;
				fdOpenMode = FileWriteMode;
				break;
			}
		}

		const int nHandle = _open_osfhandle((intptr_t)FileHandle, osHandleMode);
		const bool sucessful = nHandle != -1;

		if(sucessful)
		{
			FILE* fp = _fdopen(nHandle, fdOpenMode);
			const bool result = fp;

			if(result)
			{
				FileHandleCStyle = fp;
			}
			else
			{
				// handle?
			}
		}
		else
		{
			// handle?
		}
	}

	_fileLocation = FileLocation::Linked;

	return FileActionResult::Successful;
#endif
}

BF::FileActionResult BF::File::Close()
{
#if defined(OSUnix)
	int closeResult = fclose(FileHandle);

	switch(closeResult)
	{
		case 0:
			return FileActionResult::Successful;

		default:
			return FileActionResult::FileCloseFailure;
	}
#elif defined(OSWindows)
	if(FileHandleCStyle)
	{
		_fclose_nolock(FileHandleCStyle);

		FileHandleCStyle = nullptr;

		FileHandle = nullptr;
	}

	if(FileHandle)
	{
		bool successful = CloseHandle(FileHandle);

		FileHandle = nullptr;

		return successful ? FileActionResult::Successful : FileActionResult::FileCloseFailure;
	}

	return FileActionResult::Successful;
#endif
}

BF::ErrorCode BF::File::Remove(const char* filePath)
{
	int removeResult = FileRemoveA(filePath);
	ErrorCode errorCode = ConvertErrorCode(removeResult);

	return errorCode;
}

BF::ErrorCode BF::File::Remove(const wchar_t* filePath)
{
	int removeResult = FileRemoveW(filePath);
	ErrorCode errorCode = ConvertErrorCode(removeResult);

	return errorCode;
}

BF::ErrorCode BF::File::Rename(const char* oldName, const char* newName)
{
	int renameResult = FileRenameA(oldName, newName);
	ErrorCode errorCode = ConvertErrorCode(renameResult);

	return errorCode;
}

BF::ErrorCode BF::File::Rename(const wchar_t* oldName, const wchar_t* newName)
{
	int renameResult = FileRenameW(oldName, newName);
	bool wasSuccesful = renameResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::FileActionResult BF::File::Copy(const char* sourceFilePath, const char* destinationFilePath)
{
	if (!sourceFilePath || !destinationFilePath)
	{
		return FileActionResult::EmptyPath;
	}
#if defined (OSUnix)
	FILE* fileSource = fopen(sourceFilePath, FileReadMode);
	FILE* fileDestination = fopen(destinationFilePath, FileWriteMode);
	bool fileOpenSuccesful = fileSource && fileDestination;

	const size_t swapBufferSize = 2048;
	Byte swapBuffer[swapBufferSize];

	if (!fileOpenSuccesful)
	{
		return FileActionResult::FileOpenFailure;
	}

	while (!feof(fileSource))
	{
		size_t readBytes = fread(swapBuffer, sizeof(char), swapBufferSize, fileSource);
		size_t writtenBytes = fwrite(swapBuffer, sizeof(char), readBytes, fileDestination);
	}

	fclose(fileSource);
	fclose(fileDestination);
#elif defined(OSWindows)
	bool succesfull = CopyFileA(sourceFilePath, destinationFilePath, false);

	if (!succesfull)
	{
		return FileActionResult::FileCopyFailure;
	}
#endif

	return FileActionResult::Successful;
}

BF::FileActionResult BF::File::Copy(const wchar_t* sourceFilePath, const wchar_t* destinationFilePath)
{
	if (!sourceFilePath || !destinationFilePath)
	{
		return FileActionResult::EmptyPath;
	}

#if defined (OSUnix)
	char sourceFilePathA[PathMaxSize];
	char destinationFilePathA[PathMaxSize];

	Text::Copy(sourceFilePath, PathMaxSize, sourceFilePathA, PathMaxSize);
	Text::Copy(destinationFilePath, PathMaxSize, destinationFilePathA, PathMaxSize);

	return File::Copy(sourceFilePathA, destinationFilePathA);
#elif defined(OSWindows)
	bool succesfull = CopyFileW(sourceFilePath, destinationFilePath, false);

	if (!succesfull)
	{
		return FileActionResult::FileCopyFailure;
	}

	return FileActionResult::Successful;
#endif
}

BF::ErrorCode BF::File::DirectoryCreate(const char* directoryName)
{
	int creationResult = FileDirectoryCreateA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::DirectoryCreate(const wchar_t* directoryName)
{
	int creationResult = FileDirectoryCreateW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryGet(char* workingDirectory, size_t workingDirectorySize)
{
	char* workingDirectoryResult = WorkingDirectoryCurrentA(workingDirectory, workingDirectorySize);
	bool wasSuccesful = workingDirectoryResult != nullptr;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryGet(wchar_t* workingDirectory, size_t workingDirectorySize)
{
	wchar_t* workingDirectoryResult = WorkingDirectoryCurrentW(workingDirectory, workingDirectorySize);
	bool wasSuccesful = workingDirectoryResult != nullptr;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryChange(const char* directoryName)
{
	int creationResult = WorkingDirectoryChangeA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::WorkingDirectoryChange(const wchar_t* directoryName)
{
	int creationResult = WorkingDirectoryChangeW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::DirectoryDelete(const char* directoryName)
{
	int creationResult = FileRemoveA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::ErrorCode BF::File::DirectoryDelete(const wchar_t* directoryName)
{
	int creationResult = FileRemoveW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

BF::FileActionResult BF::File::MapToVirtualMemory(const char* filePath, const MemoryProtectionMode protectionMode)
{
#if defined(OSUnix)
    size_t fileLength = 0;
    int accessType = PROT_READ;
    int flags = MAP_PRIVATE | MAP_POPULATE;
    int fileDescriptor = 0;
    off64_t length = 0;

	// Open file
	{
		int openFlag = 0;

        switch(protectionMode)
		{
			case MemoryProtectionMode::NoReadWrite:
				openFlag = 0;
				break;

			case MemoryProtectionMode::ReadOnly:
				openFlag = O_RDONLY;
				break;

			case MemoryProtectionMode::WriteOnly:
				openFlag = O_WRONLY;
				break;

			case MemoryProtectionMode::ReadAndWrite:
				openFlag = O_RDWR;
				break;
		}

        const int fileDescriptor = open64(filePath, openFlag);
		const bool sucessfulOpen = fileDescriptor;

		if(!sucessfulOpen)
		{
			return FileActionResult::FileOpenFailure;
		}

		IDMapping = fileDescriptor;
	}

	// Get file length
	{
		const size_t fileLength = lseek64(IDMapping, 0, SEEK_END);
		const bool sucessful = fileLength > 0;

		if(!sucessful)
		{
			return FileActionResult::FileReadFailure;
		}

		DataSize = fileLength;
	}

	// Map data
	{
		const MemoryProtectionModeType protectionModeID = ConvertMemoryProtectionMode(protectionMode);
        const int flags = MAP_PRIVATE | MAP_POPULATE;
        const off_t offset = 0;

        const void* mappedData = mmap
        (
            nullptr, // addressPrefered
            DataSize,
            protectionModeID,
            flags,
            IDMapping, // fileDescriptor
            offset
        );
        const bool successfulMapping = mappedData;

		if(!successfulMapping)
		{
			return FileActionResult::FileMemoryMappingFailed;
		}

		Data = (Byte*)mappedData;
	}

	_fileLocation = FileLocation::MappedFromDisk;

	close(IDMapping);

	IDMapping = 0;

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP %ls\n", Data, DataSize, filePath);
#endif

	return FileActionResult::Successful;

#elif defined(OSWindows)
	wchar_t filePathW[PathMaxSize];

	Text::Copy(filePath, PathMaxSize, filePathW, PathMaxSize);

	const FileActionResult fileActionResult = MapToVirtualMemory(filePathW, protectionMode);

	return fileActionResult;
#endif
}

BF::FileActionResult BF::File::MapToVirtualMemory(const wchar_t* filePath, const MemoryProtectionMode protectionMode)
{
#if defined(OSUnix)
	char filePathA[PathMaxSize];

	Text::Copy(filePath, PathMaxSize, filePathA, PathMaxSize);

	return MapToVirtualMemory(filePathA, protectionMode);

#elif defined(OSWindows)

	// Open file
	{
		const FileActionResult openResult = Open(filePath, FileOpenMode::Read, FileCachingMode::Sequential);
		const bool openSuccess = openResult == FileActionResult::Successful;

		if(!openSuccess)
		{
			return openResult; //openResult;
		}
	}

	{
		LARGE_INTEGER largeInt{ 0 };

		const bool sizeResult = GetFileSizeEx(FileHandle, &largeInt);

		DataSize = largeInt.QuadPart;
	}

	// Create mapping
	{
		SECURITY_ATTRIBUTES	fileMappingAttributes{ 0 };
		DWORD				flProtect = 0;
		DWORD				dwMaximumSizeHigh = 0;
		DWORD				dwMaximumSizeLow = 0; // Problem if file is 0 Length
		wchar_t* name = nullptr;

		switch(protectionMode)
		{
			case MemoryProtectionMode::NoReadWrite:
				flProtect = PAGE_NOACCESS;
				break;

			case MemoryProtectionMode::ReadOnly:
				flProtect = PAGE_READONLY;
				break;

			case MemoryProtectionMode::WriteOnly:
				flProtect = PAGE_WRITECOPY;
				break;

			case MemoryProtectionMode::ReadAndWrite:
				flProtect = PAGE_READWRITE;
				break;
		}

		const HANDLE fileMappingHandleResult = CreateFileMappingW
		(
			FileHandle,
			nullptr,
			flProtect,
			dwMaximumSizeHigh,
			dwMaximumSizeLow,
			name
		);
		const bool successful = fileMappingHandleResult;

		if(!successful)
		{
			return FileActionResult::FileMemoryMappingFailed;
		}

		IDMapping = fileMappingHandleResult;
	}

	{
		DWORD desiredAccess = 0;
		DWORD fileOffsetHigh = 0;
		DWORD fileOffsetLow = 0;
		size_t numberOfBytesToMap = 0;
		void* baseAddressTarget = nullptr;
		DWORD  numaNodePreferred = NUMA_NO_PREFERRED_NODE;

		switch(protectionMode)
		{
			case MemoryProtectionMode::ReadOnly:
				desiredAccess = FILE_MAP_READ;
				break;

			case MemoryProtectionMode::WriteOnly:
				desiredAccess = FILE_MAP_WRITE;
				break;

			case MemoryProtectionMode::ReadAndWrite:
				desiredAccess = FILE_MAP_ALL_ACCESS;
				break;
		}

		void* fileMapped = MapViewOfFileExNuma
		(
			IDMapping,
			desiredAccess,
			fileOffsetHigh,
			fileOffsetLow,
			numberOfBytesToMap,
			baseAddressTarget,
			numaNodePreferred
		);

		Data = (Byte*)fileMapped;

		Memory::VirtualMemoryPrefetch(fileMapped, DataSize);
	}
#endif

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP %ls\n", Data, DataSize, filePath);
#endif

	_fileLocation = FileLocation::MappedFromDisk;

	return FileActionResult::Successful;
}

BF::FileActionResult BF::File::MapToVirtualMemory(const size_t size, const MemoryProtectionMode protectionMode)
{
	const void* data = Memory::VirtualMemoryAllocate(size, protectionMode);
	const bool successful = data;

	if(!successful)
	{
		return FileActionResult::Invalid;
	}

	_fileLocation = FileLocation::MappedVirtual;
	Data = (Byte*)data;
	DataSize = size;

	return FileActionResult::Successful;
}

BF::FileActionResult BF::File::UnmapFromVirtualMemory()
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP-Release\n", Data, DataSize);
#endif

#if defined(OSUnix)
	const int result = munmap(Data, DataSize);
	const bool sucessful = result != -1;

	if(!sucessful)
	{
		const ErrorCode errorCode = GetCurrentError(); // Not quite well

		return FileActionResult::FileMemoryMappingFailed;
	}

	Data = 0;
	DataSize = 0;

	return FileActionResult::Successful;

#elif defined(OSWindows)
	{
		const bool unmappingSucessful = UnmapViewOfFile(Data);

		if(!unmappingSucessful)
		{
			const ErrorCode error = GetCurrentError();

			return FileActionResult::Invalid; // TODO: fix this
		}

		Data = nullptr;
	}

	{
		const bool closeMappingSucessful = CloseHandle(IDMapping);

		if(!closeMappingSucessful)
		{
			return FileActionResult::Invalid; // TODO: fix this
		}

		IDMapping = 0;
	}

	const FileActionResult closeFile = Close();

	return closeFile;
#endif
}

BF::FileActionResult BF::File::ReadFromDisk(const char* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;

	// Open file
	{
		const FileActionResult result = file.Open(filePath, FileOpenMode::Read, FileCachingMode::Sequential);
		const bool sucessful = result == FileActionResult::Successful;

		if(!sucessful)
		{
			return result;
		}
	}

	// Read
	{
		const FileActionResult result = file.ReadFromDisk(&Data, DataSize, addNullTerminator);
		const bool sucessful = result == FileActionResult::Successful;

		if(!sucessful)
		{
			file.Close();
			return result;
		}
	}

	// Close
	{
		const FileActionResult result = file.Close();
		const bool sucessful = result == FileActionResult::Successful;

		if(!sucessful)
		{
			return result;
		}
	}

	_fileLocation = FileLocation::CachedFromDisk;

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::ReadFromDisk(const wchar_t* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read, FileCachingMode::Sequential);

	if(result != FileActionResult::Successful)
	{
		return result;
	}

	result = file.ReadFromDisk(&Data, DataSize, addNullTerminator);

	if(result != FileActionResult::Successful)
	{
		file.Close();
		return result;
	}

	result = file.Close();

	if(result != FileActionResult::Successful)
	{
		return result;
	}

	_fileLocation = FileLocation::CachedFromDisk;

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::ReadFromDisk(FILE* file, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator)
{
	fseek(file, 0, SEEK_END); // Jump to end of file
	bufferSize = ftell(file); // Get current 'data-cursor' position

	if(!bufferSize) // If no bytes in file, exit.
	{
		return FileActionResult::FileEmpty;
	}

	rewind(file); // Jump to the begining of the file

	if(addNullTerminator)
	{
		++bufferSize;
	}

	Byte* dataBuffer = Memory::Allocate<Byte>(bufferSize);

	if(!dataBuffer) // If malloc failed
	{
		return BF::FileActionResult::OutOfMemory;
	}

	*targetBuffer = dataBuffer;

	if(addNullTerminator)
	{
		dataBuffer[bufferSize - 1] = '\0';
		--bufferSize;
	}

	size_t readBytes = fread(dataBuffer, 1u, bufferSize, file);
	size_t overAllocatedBytes = bufferSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.

	assert(bufferSize == readBytes);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::File::ReadFromDisk(const wchar_t* filePath, Byte** targetBuffer, size_t& bufferSize, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	FileActionResult result = file.Open(filePath, FileOpenMode::Read);

	if(result != FileActionResult::Successful)
	{
		return result;
	}

	//result = ReadFromDisk(file.FileMarker, targetBuffer, bufferSize, addNullTerminator);

	file.ReadFromDisk(targetBuffer, bufferSize, addNullTerminator);

	result = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::WriteToDisk(const bool value)
{
	return WriteToDisk(&value, sizeof(bool));
}

BF::FileActionResult BF::File::WriteToDisk(const char value)
{
	return WriteToDisk(&value, sizeof(char));
}

BF::FileActionResult BF::File::WriteToDisk(const unsigned char value)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

BF::FileActionResult BF::File::WriteToDisk(const short value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

BF::FileActionResult BF::File::WriteToDisk(const unsigned short value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

BF::FileActionResult BF::File::WriteToDisk(const int value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

BF::FileActionResult BF::File::WriteToDisk(const unsigned int value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

BF::FileActionResult BF::File::WriteToDisk(const char* string, const size_t length)
{
	return WriteToDisk(string, length);
}

BF::FileActionResult BF::File::WriteToDisk(const unsigned char* string, const size_t length)
{
	return WriteToDisk(string, length);
}

BF::FileActionResult BF::File::WriteToDisk(const unsigned long long& value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

BF::FileActionResult BF::File::WriteToDisk(const void* value, const size_t length)
{
#if defined(OSUnix)
FILE* fileHandle = FileHandle;
#elif defined(OSWindows)
FILE* fileHandle = FileHandleCStyle;
#endif

	const size_t writtenSize = fwrite(value, sizeof(Byte), length, fileHandle);

	if(writtenSize > 0)
	{
		return FileActionResult::Successful;
	}
	else
	{
		return FileActionResult::WriteFailure;
	}
}

BF::FileActionResult BF::File::WriteToDisk(const char* format, ...)
{
#if defined(OSUnix)
    FILE* fileHandle = FileHandle;
#elif defined(OSWindows)
    FILE* fileHandle = FileHandleCStyle;
#endif

	va_list args;
	va_start(args, format);

	const int writtenBytes = vfprintf(fileHandle, format, args);
	const bool sucessful = writtenBytes >= 0;

	va_end(args);

	if(!sucessful)
	{
		return FileActionResult::WriteFailure;
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::File::WriteIntoFile(const void* data, const size_t dataSize)
{
#if defined(OSUnix)
	size_t writtenBytes = fwrite(data, sizeof(char), dataSize, FileHandle);
#elif defined(OSWindows)
	DWORD writtenBytes = 0;
	const bool successful = WriteFile(FileHandle, data, dataSize, &writtenBytes, nullptr);
#endif

	return FileActionResult();
}

BF::FileActionResult BF::File::WriteToDisk(const char* filePath, FilePersistence filePersistence)
{
	File file;
	FileActionResult fileActionResult = file.Open(filePath, FileOpenMode::Write);

	if(fileActionResult != FileActionResult::Successful)
	{
		return fileActionResult;
	}

	WriteIntoFile(Data, DataSize);

	fileActionResult = file.Close();

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::WriteToDisk(const wchar_t* filePath, FilePersistence filePersistence)
{
	File file;

	{
		const FileActionResult fileActionResult = file.Open(filePath, FileOpenMode::Write);
		const bool sucessful = fileActionResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileActionResult;
		}
	}

#if defined(OSUnix)
	size_t writtenBytes = fwrite(Data, sizeof(char), DataCursorPosition, file.FileHandle);
#elif defined(OSWindows)
	DWORD writtenBytes = 0;
	const bool successful = WriteFile(file.FileHandle, Data, DataCursorPosition, &writtenBytes, nullptr);
#endif

	{
		const FileActionResult closeResult = file.Close();
		const bool sucessful = closeResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return closeResult;
		}
	}

	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::File::ReadFromDisk(unsigned char** outPutBuffer, size_t& outPutBufferSize, const bool addTerminatorByte)
{
#if defined(OSUnix)
	fseek(FileHandle, 0, SEEK_END); // Jump to end of file
	outPutBufferSize = ftell(FileHandle); // Get current 'data-cursor' position

	if (!outPutBufferSize) // If no bytes in file, exit.
	{
		return FileActionResult::FileEmpty;
	}

	rewind(FileHandle); // Jump to the begining of the file

	if (addTerminatorByte)
	{
		++outPutBufferSize;
	}

	unsigned char* dataBuffer = Memory::Allocate<unsigned char>(outPutBufferSize);

	if (!dataBuffer) // If malloc failed
	{
		return BF::FileActionResult::OutOfMemory;
	}

	*outPutBuffer = dataBuffer;

	if (addTerminatorByte)
	{
		dataBuffer[outPutBufferSize - 1] = '\0';
		--outPutBufferSize;
	}

	size_t readBytes = fread(dataBuffer, 1u, outPutBufferSize, FileHandle);
	size_t overAllocatedBytes = outPutBufferSize - readBytes; // if overAllocatedBytes > 0 there was a reading error.

	assert(outPutBufferSize == readBytes);

	return FileActionResult::Successful;
#elif defined(OSWindows)
	const DWORD fileSize = GetFileSize(FileHandle, nullptr);
	DWORD numberOfBytesRead = 0;
	OVERLAPPED* overlapped = nullptr;
	//LARGE_INTEGER size;
	//bool succesSize = GetFileSizeEx(FileHandle, &size);
	size_t allocationSize = fileSize;

	if (addTerminatorByte)
	{
		++allocationSize;
	}

	unsigned char* buffer = Memory::Allocate<unsigned char>(allocationSize);

	if (!buffer)
	{
		return FileActionResult::OutOfMemory;
	}

	bool sucessful = ReadFile
	(
		FileHandle, // file
		buffer, // input
		fileSize, // Shall read
		&numberOfBytesRead, // Has read
		overlapped
	);

	if (!sucessful)
	{
		return FileActionResult::FileReadFailure;
	}

	buffer[allocationSize - 1] = '\0';

	(*outPutBuffer) = buffer;
	outPutBufferSize = numberOfBytesRead;

	return FileActionResult::Successful;
#endif
}

void BF::File::PathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName)
{
	const size_t index = Text::FindLast(currnetPath, PathMaxSize, '/');
	const bool found = index != -1;

	if (found)
	{
		const size_t copyedBytes = Text::Copy(currnetPath, index + 1, targetPath, index + 1);
		const size_t toCopy = PathMaxSize - copyedBytes;

		Text::Copy(newFileName, toCopy, targetPath + copyedBytes, toCopy);
	}
}

void BF::File::FilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize)
{
#if defined(OSUnix)
	DIR* directory = opendir(folderPath);

	if (directory)
	{
		struct dirent* directoryInfo = nullptr;

		while (directoryInfo = readdir(directory))
		{
			++listSize;
		}

		rewinddir(directory);

		(*list) = Memory::Allocate<wchar_t*>(listSize);

		for (size_t index = 0; directoryInfo = readdir(directory); index++)
		{
			const bool isFile = directoryInfo->d_type == DT_REG || true;

			if (isFile)
			{
				const char* fileName = directoryInfo->d_name;
				const size_t length = Text::Length(fileName);
				wchar_t* newString = Memory::Allocate<wchar_t>(length + 1);
				wchar_t** target = &(*list)[index];

				if (!newString)
				{
					return; // Error: OutOfMemory
				}

				(*target) = newString;
				size_t writtenBytes = Text::Copy(fileName, length, *target, length);
			}
		}

		closedir(directory);
	}
#elif defined(OSWindows)
	wchar_t folderPathW[PathMaxSize];
	size_t writtenBytes = Text::Copy(folderPath, PathMaxSize, folderPathW, PathMaxSize);

	WIN32_FIND_DATA dataCursour{0};
	HANDLE hFind = 0;

	//Memory::Set(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	hFind = FindFirstFile(folderPathW, &dataCursour); 	// "/*.*";

	bool foundData = hFind != INVALID_HANDLE_VALUE;

	if (!foundData)
	{
		return;
	}

	++listSize;

	for (; FindNextFile(hFind, &dataCursour); listSize++);

	Memory::Set(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	(*list) = Memory::Allocate<wchar_t*>(listSize);

	hFind = FindFirstFile(folderPathW, &dataCursour); // Expected "." Folder
	size_t fileIndex = 0;

	do
	{
		const size_t length = Text::Length(dataCursour.cFileName);
		const wchar_t* filePathSource = dataCursour.cFileName;
		wchar_t* newString = Memory::Allocate<wchar_t>(length + 1);

		if (!newString)
		{
			return; // Error: OutOfMemory
		}

		Text::Copy(filePathSource, length, newString, length);

		(*list)[fileIndex] = newString;

		fileIndex++;
	}
	while (FindNextFile(hFind, &dataCursour));

	FindClose(hFind);
#endif
}

void BF::File::FilesInFolder(const wchar_t* folderPath, wchar_t*** list, size_t& listSize)
{

}

bool BF::File::DoesFileExist(const char* filePath)
{
	FILE* file = FileOpenA(filePath, "rb");

	if (file)
	{
		fclose(file);

		return true;
	}

	return false;
}

bool BF::File::DoesFileExist(const wchar_t* filePath)
{
#if defined(OSUnix)
    char filePathA[PathMaxSize];

    Text::Copy(filePath, PathMaxSize, filePathA, PathMaxSize);

    return DoesFileExist(filePathA);

#elif defined(OSWindows)
	FILE* file = FileOpenW(filePath, L"rb");

	if(file)
	{
		fclose(file);

		return true;
	}
#endif // defined

	return false;
}
