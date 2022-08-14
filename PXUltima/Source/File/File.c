#include "File.h"

#include <Text/Text.h>
#include <Memory/Memory.h>

#include <stdarg.h>
#include <fcntl.h>


#define FileReadMode "rb"
#define FileReadModeW L"rb"

#define FileWriteMode "wb"
#define FileWriteModeW L"wb"

#define FileReadWriteMode "rwb"
#define FileReadWriteModeW L"rwb"

#define FileCachingModeDefault 0 //POSIX_FADV_NORMAL


#if defined(OSUnix)
#include <sys/mman.h>
#include <sys/stat.h>

#define OSFileOpenA fopen
#define OSFileOpenW(string, mode) FileOpenA((const char*)string, (const char*)mode)
#define OSFileRemoveA remove
#define OSFileRemoveW(string) remove((const char*)string)
#define OSFileRenameA rename
#define OSFileRenameW(oldName, newName) rename((const char*)oldName, (const char*)newName)
#define OSFileDirectoryCreateA(string) mkdir(string, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#define OSFileDirectoryCreateW(string) FileDirectoryCreateA((const char*)string)
#define OSWorkingDirectoryCurrentA getcwd
#define OSWorkingDirectoryCurrentW(string, size) (wchar_t*)WorkingDirectoryCurrentA((char*)string, size)
#define OSWorkingDirectoryChangeA chdir
#define OSWorkingDirectoryChangeW(string) WorkingDirectoryChangeA((const char*)string)

#define PipeOpen popen
#define PipeOpenW(wchar, mode) popen((char*)wchar, (const char*) mode) // TODO: instable
#define PipeClose pclose


#define FileCachingModeSequentialScan 2 // POSIX_FADV_SEQUENTIAL
#define FileCachingModeRandomAccess  1 // POSIX_FADV_RANDOM
#define FileCachingModeWillNeed 3 // POSIX_FADV_WILLNEED
#define FileCachingModeDontNeed 4 // POSIX_FADV_DONTNEED
#define FileCachingModeNoReuse 5 // POSIX_FADV_NOREUSE


#elif defined(OSWindows)
#include <io.h>

#define OSFileOpenA fopen
#define OSFileOpenW _wfopen
#define OSFileRemoveA remove
#define OSFileRemoveW _wremove
#define OSFileRenameA rename
#define OSFileRenameW _wrename
#define OSFileDirectoryCreateA _mkdir
#define OSFileDirectoryCreateW _wmkdir
#define OSWorkingDirectoryCurrentA _getcwd
#define OSWorkingDirectoryCurrentW _wgetcwd
#define OSWorkingDirectoryChangeA _chdir
#define OSWorkingDirectoryChangeW _wchdir


// From WinBase.h
#define FileCachingModeWriteThrough      0x80000000 // FILE_FLAG_WRITE_THROUGH
#define FileCachingModeOverLapped        0x40000000
#define FileCachingModeNoBuffering       0x20000000 // FILE_FLAG_NO_BUFFERING
#define FileCachingModeRandomAccess      0x10000000 // FILE_FLAG_RANDOM_ACCESS
#define FileCachingModeSequentialScan    0x08000000 // FILE_FLAG_SEQUENTIAL_SCAN
#define FileCachingModeDeleteOnClose     0x04000000
#define FileCachingModeBackUpSemantics   0x02000000
#define FileCachingModePOSIXSemantics    0x01000000
#define FileCachingModeSessionAware      0x00800000
#define FileCachingModeOpenReparsePoint  0x00200000
#define FileCachingModeOpenNoRecall      0x00100000
#define FileCachingModeFirstPipeInstance 0x00080000

#define PipeOpen _popen
#define PipeOpenW _wpopen
#define PipeClose _pclose

// WinNT.h
// FILE_ATTRIBUTE_TEMPORARY

#endif



void FilePathSplittA(const char* fullPath, size_t fullPathMaxSize, char* drive, size_t driveMaxSize, char* directory, size_t directoryMaxSize, char* fileName, size_t fileNameMaxSize, char* extension, size_t extensionMaxSize)
{
#if defined(OSUnix)
	char directoryNameCache[PathMaxSize];
	char baseNameCache[FileNameMaxSize];

	TextCopyA(fullPath, FileNameMaxSize, directoryNameCache, FileNameMaxSize);
	TextCopyA(fullPath, FileNameMaxSize, baseNameCache, FileNameMaxSize);

	char* dirNameResult = dirname(directoryNameCache);
	char* baseNameResult = basename(baseNameCache);

	size_t directoryLength = TextCopyA(dirNameResult, DirectoryMaxSize, directory, DirectoryMaxSize);
	size_t fileNameLength = TextCopyA(baseNameResult, FileNameMaxSize, fileName, FileNameMaxSize);

	for(size_t i = fileNameLength - 1; i > 0; --i)
	{
		const unsigned char isDot = fileName[i] == '.';

		if(isDot)
		{
			TextCopyA(fileName + i + 1, ExtensionMaxSize - i, extension, extensionMaxSize);
			break;
		}
	}
#elif defined(OSWindows)
	char fileNameCache[FileNameMaxSize];

	_splitpath_s
	(
		fullPath,
		drive, driveMaxSize,
		directory, directoryMaxSize,
		fileName, fileNameMaxSize,
		extension, extensionMaxSize
	);

	for(size_t i = 0; fileName[i] != '\0'; i++)
	{
		const unsigned char isDot = fileName[i] == '.';

		if(isDot)
		{
			TextCopyA(extension + i, extensionMaxSize, fileNameCache, FileNameMaxSize);
			TextCopyA(fileNameCache, FileNameMaxSize, extension, extensionMaxSize);
			break;
		}
	}
#endif
}

void FilePathSplittW(const wchar_t* fullPath, size_t fullPathMaxSize, wchar_t* drive, size_t driveMaxSize, wchar_t* directory, size_t directoryMaxSize, wchar_t* fileName, size_t fileNameMaxSize, wchar_t* extension, size_t extensionMaxSize)
{
#if defined(OSUnix)
	char fullPathA[PathMaxSize];
	char driveA[DriveMaxSize];
	char directoryA[DirectoryMaxSize];
	char fileNameA[FileNameMaxSize];
	char extensionA[ExtensionMaxSize];

	TextCopyWA(fullPath, PathMaxSize, fullPathA, PathMaxSize);

	Splitt
	(
		fullPathA,
		driveA,
		directoryA,
		fileNameA,
		extensionA
	);

	TextCopyAW(driveA, DriveMaxSize, drive, DriveMaxSize);
	TextCopyAW(directoryA, DirectoryMaxSize, directory, DirectoryMaxSize);
	TextCopyAW(fileNameA, FileNameMaxSize, fileName, FileNameMaxSize);
	TextCopyAW(extensionA, ExtensionMaxSize, extension, ExtensionMaxSize);
#elif defined(OSWindows)
	wchar_t extensionCache[FileNameMaxSize];

	_wsplitpath_s
	(
		fullPath,
		drive, driveMaxSize,
		directory, directoryMaxSize,
		fileName, fileNameMaxSize,
		extension, extensionMaxSize
	);

	for(size_t i = 0; extension[i] != '\0'; i++)
	{
		const unsigned char isDot = extension[i] == '.';

		if(isDot)
		{
			TextCopyW(extension + i + 1, extensionMaxSize, extensionCache, FileNameMaxSize);
			TextCopyW(extensionCache, FileNameMaxSize, extension, extensionMaxSize);
			break;
		}
	}
#endif
}

void FilePathExtensionGetA(const char* filePath, const size_t filePathSize, char* extension, const size_t extensionSizeMax)
{
	const size_t index = TextFindLastA(filePath, filePathSize, '.');
	const unsigned char hasExtension = index != TextIndexNotFound;

	if(!hasExtension)
	{
		TextClearA(extension, extensionSizeMax);
		return;
	}

	TextCopyA(filePath + index, filePathSize - index, extension, extensionSizeMax);
}

void FilePathExtensionGetW(const wchar_t* filePath, const size_t filePathSize, wchar_t* extension, const size_t extensionSizeMax)
{
	const size_t index = TextFindLastW(filePath, filePathSize, '.');
	const unsigned char hasExtension = index != TextIndexNotFound;

	if(!hasExtension)
	{
		TextClearW(extension, extensionSizeMax);
		return;
	}

	TextCopyW(filePath + index + 1, filePathSize - index, extension, extensionSizeMax);
}

FileCachingMode ConvertToFileCachingMode(const unsigned int value)
{
	return FileCachingDefault;
}

unsigned int ConvertFromFileCachingMode(const FileCachingMode fileCachingMode)
{
	switch(fileCachingMode)
	{
		default:
		case FileCachingDefault:
			return FileCachingModeDefault;

		case FileCachingRandom:
			return FileCachingModeRandomAccess;

		case FileCachingSequential:
			return FileCachingModeSequentialScan;

			// case BF::FileCachingMode::Temporary:
			//     break;

			// case BF::FileCachingMode::UseOnce:
			//     break;

			// case BF::FileCachingMode::NoBuffering:
			//     return FileCachingModeNoBuffering;

			// case BF::FileCachingMode::NeedLater:
			//     return FileCachingModeDontNeed;

			// case BF::FileCachingMode::DontNeedNow:
			//     return FileCachingModeNoReuse;
	}
}

void FileConstruct(File* file)
{
	MemorySet(file, sizeof(File), 0);
}

void FileDestruct(File* file)
{
	switch(file->_fileLocation)
	{
		case FileLocationMappedFromDisk:
			FileUnmapFromVirtualMemory(file);
			break;

		case FileLocationMappedVirtual:
			MemoryVirtualRelease(file->Data, file->DataSize);
			break;

		case  FileLocationCachedFromDisk:
			MemoryRelease(file->Data, file->DataSize);
			break;

		case FileLocationLinked:
			FileClose(file);
			break;
	}
}

ActionResult FileOpenA(File* file, const char* filePath, const MemoryProtectionMode fileOpenMode, FileCachingMode fileCachingMode)
{
#if defined(OSUnix)
	const char* readMode = 0u;

	switch(fileOpenMode)
	{
		case MemoryReadOnly:
			readMode = FileReadMode;
			break;

		case MemoryWriteOnly:
			readMode = FileWriteMode;
			break;
	}

	assert(readMode != 0);

	// Use this somewhere here
	// int posix_fadvise(int fd, off_t offset, off_t len, int advice);
	// int posix_fadvise64(int fd, off_t offset, off_t len, int advice);

	file->FileHandle = fopen(filePath, readMode);

	return file->FileHandle ? ResultSuccessful : ResultFileOpenFailure;

#elif defined(OSWindows)
	wchar_t filePathW[PathMaxSize];

	TextCopyAW(filePath, PathMaxSize, filePathW, PathMaxSize);

	return FileOpenW(file, filePathW, fileOpenMode, fileCachingMode);
#endif
}

ActionResult FileOpenW(File* file, const wchar_t* filePath, const MemoryProtectionMode fileOpenMode, FileCachingMode fileCachingMode)
{

#if defined(OSUnix)
	char filePathA[PathMaxSize];

	TextCopyWA(filePath, PathMaxSize, filePathA, PathMaxSize);

	const ActionResult openResult = Open(filePathA, fileOpenMode);
	const unsigned char successful = openResult == ResultSuccessful;

	if(!successful)
	{
		return openResult;
	}

	return ResultSuccessful;
#elif defined(OSWindows)
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;
	//SECURITY_ATTRIBUTES securityAttributes = 0;
	DWORD dwCreationDisposition = 0;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = 0;

	switch(fileOpenMode)
	{
		case MemoryReadOnly:
		{
			dwShareMode = FILE_SHARE_READ;
			dwCreationDisposition = OPEN_EXISTING;
			dwDesiredAccess = GENERIC_READ;
			break;
		}
		case MemoryWriteOnly:
		{
			dwShareMode = FILE_SHARE_WRITE;
			dwCreationDisposition = CREATE_ALWAYS;
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			break;
		}
		case MemoryReadAndWrite:
		{
			dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
			dwCreationDisposition = CREATE_ALWAYS;
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			break;
		}
	}

	dwFlagsAndAttributes |= ConvertFromFileCachingMode(fileCachingMode);

	file->FileHandle = CreateFileW
	(
		filePath,
		dwDesiredAccess,
		dwShareMode,
		0,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);

	{
		const unsigned char successful = file->FileHandle != INVALID_HANDLE_VALUE;

		if(!successful)
		{
			switch(fileOpenMode)
			{
				case MemoryReadOnly:
					return ResultFileNotFound;

				case MemoryWriteOnly:
					return ResultFileCreateFailure;
			}
			/*
			const ErrorCode error = GetCurrentError();

			switch(error)
			{
				case ErrorCode::NoSuchFileOrDirectory:
					return ResultFileNotFound;

				default:
					return ResultFileOpenFailure;
			}*/
		}
	}

	// Get a FILE* from file HANDLE
	{
		int osHandleMode = 0;
		const char* fdOpenMode = 0;

		switch(fileOpenMode)
		{
			case MemoryReadOnly:
			{
				osHandleMode = _O_RDONLY;
				fdOpenMode = FileReadMode;
				break;
			}
			case  MemoryWriteOnly:
			{
				osHandleMode = _O_RDWR;//_O_WRONLY;
				fdOpenMode = FileWriteMode;
				break;
			}
			case  MemoryReadAndWrite:
			{
				osHandleMode = _O_RDWR;
				fdOpenMode = FileWriteMode;
				break;
			}
		}

		const int nHandle = _open_osfhandle((intptr_t)file->FileHandle, osHandleMode);
		const unsigned char sucessful = nHandle != -1;

		if(sucessful)
		{
			FILE* fp = _fdopen(nHandle, fdOpenMode);
			const unsigned char result = fp;

			if(result)
			{
				file->FileHandleCStyle = fp;
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

	file->_fileLocation = FileLocationLinked;

	return ResultSuccessful;
#endif
}

ActionResult FileClose(File* file)
{
#if defined(OSUnix)
	const int closeResult = fclose(file->FileHandle);

	switch(closeResult)
	{
		case 0:
			return ResultSuccessful;

		default:
			return ResultFileCloseFailure;
	}
#elif defined(OSWindows)
	if(file->FileHandleCStyle)
	{
		_fclose_nolock(file->FileHandleCStyle);

		file->FileHandleCStyle = 0;
		file->FileHandle = 0;
	}

	if(file->FileHandle)
	{
		const unsigned char successful = CloseHandle(file->FileHandle);

		file->FileHandle = 0;

		return successful ? ResultSuccessful : ResultFileCloseFailure;
	}

	return ResultSuccessful;
#endif
}

ActionResult FileMapToVirtualMemoryA(File* file, const char* filePath, const size_t fileSize, const MemoryProtectionMode protectionMode)
{

#if defined(OSUnix)
	size_t fileLength = 0;
	int accessType = PROT_READ;
	int flags = MAP_PRIVATE | MAP_POPULATE;
	int fileDescriptor = 0;
	off_t length = 0;

	// Open file
	{
		int openFlag = 0;

		switch(protectionMode)
		{
			case MemoryNoReadWrite:
				openFlag = 0;
				break;

			case MemoryReadOnly:
				openFlag = O_RDONLY;
				break;

			case MemoryWriteOnly:
				openFlag = O_WRONLY;
				break;

			case MemoryReadAndWrite:
				openFlag = O_RDWR;
				break;
		}

		const int fileDescriptor = open64(filePath, openFlag);
		const unsigned char sucessfulOpen = fileDescriptor;

		if(!sucessfulOpen)
		{
			return ResultFileOpenFailure;
		}

		file->IDMapping = fileDescriptor;
	}

	// Get file length
	{
		const size_t fileLength = lseek64(file->IDMapping, 0, SEEK_END);
		const unsigned char sucessful = fileLength > 0;

		if(!sucessful)
		{
			return ResultFileReadFailure;
		}

		file->DataSize = fileLength;
	}

	// Map data
	{
		const MemoryProtectionModeType protectionModeID = ConvertMemoryProtectionMode(protectionMode);
		const int flags = MAP_PRIVATE | MAP_POPULATE;
		const off_t offset = 0;

		const void* mappedData = mmap
		(
			0, // addressPrefered
			file->DataSize,
			protectionModeID,
			flags,
			file->IDMapping, // fileDescriptor
			offset
		);
		const unsigned char successfulMapping = mappedData;

		if(!successfulMapping)
		{
			return ResultFileMemoryMappingFailed;
		}

		file->Data = (unsigned char*)mappedData;
	}

	file->_fileLocation = FileLocationMappedFromDisk;

	close(file->IDMapping);

	file->IDMapping = 0;

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP %ls\n", Data, DataSize, filePath);
#endif

	return ResultSuccessful;

#elif defined(OSWindows)
	wchar_t filePathW[PathMaxSize];

	TextCopyAW(filePath, PathMaxSize, filePathW, PathMaxSize);

	const ActionResult fileActionResult = FileMapToVirtualMemoryW(file, filePathW, fileSize, protectionMode);

	return fileActionResult;
#endif
}

ActionResult FileMapToVirtualMemoryW(File* file, const wchar_t* filePath, const size_t fileSize, const MemoryProtectionMode protectionMode)
{
#if defined(OSUnix)
	char filePathA[PathMaxSize];

	TextCopyWA(filePath, PathMaxSize, filePathA, PathMaxSize);

	return MapToVirtualMemory(filePathA, protectionMode);

#elif defined(OSWindows)

	// Open file
	{
		const ActionResult openResult = FileOpenW(file, filePath, protectionMode, FileCachingSequential);
		const unsigned char openSuccess = openResult == ResultSuccessful;

		if(!openSuccess)
		{
			return openResult; //openResult;
		}
	}



	// Create mapping
	{
		SECURITY_ATTRIBUTES	fileMappingAttributes;
		DWORD				flProtect = 0;
		DWORD				dwMaximumSizeHigh = 0;
		DWORD				dwMaximumSizeLow = 0; // Problem if file is 0 Length
		wchar_t* name = filePath;

		switch (protectionMode)
		{
		case MemoryReadOnly:
		{
			LARGE_INTEGER largeInt;

			const unsigned char sizeResult = GetFileSizeEx(file->FileHandle, &largeInt);

			dwMaximumSizeHigh = 0;
			dwMaximumSizeLow = 0;

			file->DataSize = largeInt.QuadPart;
			break;
		}
		case MemoryWriteOnly:
		{
			dwMaximumSizeHigh = 0;
			dwMaximumSizeLow = fileSize;

			file->DataSize = fileSize;

			break;
		}
		case MemoryReadAndWrite:
		{
			break;
		}

		default:
			break;
		}

		file->MemoryMode = protectionMode;

		switch(protectionMode)
		{
			case MemoryNoReadWrite:
				flProtect = PAGE_NOACCESS;
				break;

			case MemoryReadOnly:
				flProtect = PAGE_READONLY;
				break;

			case MemoryWriteOnly:
				flProtect = PAGE_READWRITE; // PAGE_WRITECOPY
				break;

			case MemoryReadAndWrite:
				flProtect = PAGE_READWRITE;
				break;
		}

		const HANDLE fileMappingHandleResult = CreateFileMappingW
		(
			file->FileHandle,
			0,
			flProtect,
			dwMaximumSizeHigh,
			dwMaximumSizeLow,
			name
		);
		const unsigned char successful = fileMappingHandleResult;

		if(!successful)
		{
			DWORD x = GetLastError();

			return ResultFileMemoryMappingFailed;
		}

		file->IDMapping = fileMappingHandleResult;
	}

	{
		DWORD desiredAccess = 0;
		DWORD fileOffsetHigh = 0;
		DWORD fileOffsetLow = 0;
		size_t numberOfBytesToMap = 0;
		void* baseAddressTarget = 0;
		DWORD  numaNodePreferred = NUMA_NO_PREFERRED_NODE;

		switch(protectionMode)
		{
			case MemoryReadOnly:
				desiredAccess = FILE_MAP_READ;
				break;

			case MemoryWriteOnly:
				desiredAccess = FILE_MAP_WRITE;
				break;

			case MemoryReadAndWrite:
				desiredAccess = FILE_MAP_ALL_ACCESS;
				break;
		}

		void* fileMapped = MapViewOfFileExNuma
		(
			file->IDMapping,
			desiredAccess,
			fileOffsetHigh,
			fileOffsetLow,
			numberOfBytesToMap,
			baseAddressTarget,
			numaNodePreferred
		);

		file->Data = fileMapped;

		MemoryVirtualPrefetch(fileMapped, file->DataSize);
	}

#endif

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP %ls\n", Data, DataSize, filePath);
#endif

	file->_fileLocation = FileLocationMappedFromDisk;

	return ResultSuccessful;
}

ActionResult FileMapToVirtualMemory(File* file, const size_t size, const MemoryProtectionMode protectionMode)
{
	const void* data = MemoryVirtualAllocate(size, protectionMode);
	const unsigned char successful = data;

	if(!successful)
	{
		return ResultOutOfMemory;
	}

	file->_fileLocation = FileLocationMappedVirtual;
	file->Data = data;
	file->DataSize = size;

	return ResultSuccessful;
}

ActionResult FileUnmapFromVirtualMemory(File* file)
{
	// Write pending data
	unsigned char isWriteMapped = 0;

	switch(file->MemoryMode)
	{
		default:
		case MemoryInvalid:
		case MemoryNoReadWrite:
		case MemoryReadOnly:
			isWriteMapped = 0;
			break;

		case MemoryWriteOnly:
		case MemoryReadAndWrite:
			isWriteMapped = 1;
			break;
	}


#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP-Release\n", Data, DataSize);
#endif

#if defined(OSUnix)
	const int result = munmap(file->Data, file->DataSize);
	const unsigned char sucessful = result != -1;

	if(!sucessful)
	{
		const ActionResult errorCode = GetCurrentError(); // Not quite well

		return ResultFileMemoryMappingFailed;
	}

	file->Data = 0;
	file->DataSize = 0;

	return ResultSuccessful;

#elif defined(OSWindows)

	// Write pending data
	{
		if(isWriteMapped)
		{
			const BOOL flushSuccessful = FlushViewOfFile(file->Data, file->DataCursor);

			printf("");
		}
	}

	{
		const unsigned char unmappingSucessful = UnmapViewOfFile(file->Data);

		if(!unmappingSucessful)
		{
			//const ErrorCode error = GetCurrentError();

			return ResultInvalid; // TODO: fix this
		}

		file->Data = 0;
	}

	{
		const unsigned char closeMappingSucessful = CloseHandle(file->IDMapping);

		if(!closeMappingSucessful)
		{
			return ResultInvalid; // TODO: fix this
		}

		file->IDMapping = 0;
	}

	// Close
	{

		if(isWriteMapped)
		{
			//fseek();

			LARGE_INTEGER largeInteger;

			largeInteger.QuadPart = file->DataCursor;

			const BOOL setSuccessful = SetFilePointerEx(file->FileHandle, largeInteger, 0, FILE_BEGIN);

			const BOOL endSuccessful = SetEndOfFile(file->FileHandle);

			printf("");
		}

		const ActionResult closeFile = FileClose(file);
		const unsigned char sucessful = ResultSuccessful == closeFile;

		if(!sucessful)
		{

		}

		file->FileHandle = 0;
	}

	return ResultSuccessful;
#endif
}

unsigned char FileDoesExistA(const char* filePath)
{
	return 0;
}

unsigned char FileDoesExistW(const wchar_t* filePath)
{
	return 0;
}

ActionResult FileRemoveA(const char* filePath)
{
	int removeResult = OSFileRemoveA(filePath);
	//ErrorCode errorCode = ConvertErrorCode(removeResult);

	return ResultInvalid;
}

ActionResult FileRemoveW(const wchar_t* filePath)
{
	int removeResult = OSFileRemoveW(filePath);
	//ErrorCode errorCode = ConvertErrorCode(removeResult);

	return ResultInvalid;
}

ActionResult FileRenameA(const char* oldName, const char* newName)
{
	int renameResult = OSFileRenameA(oldName, newName);
	//ErrorCode errorCode = ConvertErrorCode(renameResult);

	return ResultInvalid;
}

ActionResult FileRenameW(const wchar_t* oldName, const wchar_t* newName)
{
	int renameResult = OSFileRenameW(oldName, newName);
	const unsigned char wasSuccesful = renameResult == 0;

	if(!wasSuccesful)
	{
		return ResultInvalid;// GetCurrentError();
	}

	return ResultSuccessful;
}

ActionResult FileCopyA(const char* sourceFilePath, const char* destinationFilePath)
{
	if(!sourceFilePath || !destinationFilePath)
	{
		return ResultEmptyPath;
	}
#if defined (OSUnix)
	FILE* fileSource = fopen(sourceFilePath, FileReadMode);
	FILE* fileDestination = fopen(destinationFilePath, FileWriteMode);
	const unsigned char fileOpenSuccesful = fileSource && fileDestination;

	const size_t swapBufferSize = 2048;
	unsigned char swapBuffer[swapBufferSize];

	if(!fileOpenSuccesful)
	{
		return ResultFileOpenFailure;
	}

	while(!feof(fileSource))
	{
		size_t readBytes = fread(swapBuffer, sizeof(char), swapBufferSize, fileSource);
		size_t writtenBytes = fwrite(swapBuffer, sizeof(char), readBytes, fileDestination);
	}

	fclose(fileSource);
	fclose(fileDestination);
#elif defined(OSWindows)
	unsigned char succesfull = CopyFileA(sourceFilePath, destinationFilePath, 0);

	if(!succesfull)
	{
		return ResultFileCopyFailure;
	}
#endif

	return ResultSuccessful;
}

ActionResult FileCopyW(const wchar_t* sourceFilePath, const wchar_t* destinationFilePath)
{
	if(!sourceFilePath || !destinationFilePath)
	{
		return ResultEmptyPath;
	}

#if defined (OSUnix)
	char sourceFilePathA[PathMaxSize];
	char destinationFilePathA[PathMaxSize];

	TextCopyWA(sourceFilePath, PathMaxSize, sourceFilePathA, PathMaxSize);
	TextCopyWA(destinationFilePath, PathMaxSize, destinationFilePathA, PathMaxSize);

	return FileCopy(sourceFilePathA, destinationFilePathA);
#elif defined(OSWindows)
	const unsigned char succesfull = CopyFileW(sourceFilePath, destinationFilePath, 0);

	if(!succesfull)
	{
		return ResultFileCopyFailure;
	}

	return ResultSuccessful;
#endif
}

void FilePathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName)
{
	const size_t index = TextFindLastW(currnetPath, PathMaxSize, '/');
	const unsigned char found = index != -1;

	if(found)
	{
		const size_t copyedBytes = TextCopyW(currnetPath, index + 1, targetPath, index + 1);
		const size_t toCopy = PathMaxSize - copyedBytes;

		TextCopyW(newFileName, toCopy, targetPath + copyedBytes, toCopy);
	}
}

ActionResult DirectoryCreateA(const char* directoryName)
{
	const int creationResult = OSFileDirectoryCreateA(directoryName);
	const unsigned char wasSuccesful = creationResult == 0;

	if(!wasSuccesful)
	{
		return ResultInvalid; //GetCurrentError();
	}

	return ResultSuccessful;
}

ActionResult DirectoryCreateW(const wchar_t* directoryName)
{
	const int creationResult = OSFileDirectoryCreateW(directoryName);
	const unsigned char wasSuccesful = creationResult == 0;

	if(!wasSuccesful)
	{
		return ResultInvalid; //GetCurrentError();
	}

	return ResultSuccessful;
}

ActionResult WorkingDirectoryChange(const char* directoryName)
{
	return ResultInvalid;
}

ActionResult WorkingDirectoryGetA(char* workingDirectory, size_t workingDirectorySize)
{
	char* workingDirectoryResult = OSWorkingDirectoryCurrentA(workingDirectory, workingDirectorySize);
	const unsigned char  wasSuccesful = workingDirectoryResult;

	if(!wasSuccesful)
	{
		return ResultInvalid; //GetCurrentError();
	}

	return ResultSuccessful;
}

ActionResult WorkingDirectoryGetW(wchar_t* workingDirectory, size_t workingDirectorySize)
{
	wchar_t* workingDirectoryResult = OSWorkingDirectoryCurrentW(workingDirectory, workingDirectorySize);
	const unsigned char  wasSuccesful = workingDirectoryResult;

	if(!wasSuccesful)
	{
		return ResultInvalid; //GetCurrentError();
	}

	return ResultSuccessful;
}

ActionResult WorkingDirectoryChangeW(const wchar_t* directoryName)
{
	return ResultInvalid;
}

ActionResult DirectoryDeleteA(const char* directoryName)
{
	return ResultInvalid;
}

ActionResult DirectoryDeleteW(const wchar_t* directoryName)
{
	return ResultInvalid;
}

ActionResult DirectoryFilesInFolderA(const char* folderPath, wchar_t*** list, size_t* listSize)
{
	return ResultInvalid;
}

ActionResult DirectoryFilesInFolderW(const wchar_t* folderPath, wchar_t*** list, size_t* listSize)
{
	return ResultInvalid;
}


/*

ActionResult FileWorkingDirectoryChangeA(const char* directoryName)
{
	int creationResult = WorkingDirectoryChangeA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

ActionResult FileWorkingDirectoryChangeW(const wchar_t* directoryName)
{
	int creationResult = WorkingDirectoryChangeW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

ActionResult FileDirectoryDeleteA(const char* directoryName)
{
	int creationResult = FileRemoveA(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

ActionResult FileDirectoryDeleteW(const wchar_t* directoryName)
{
	int creationResult = FileRemoveW(directoryName);
	bool wasSuccesful = creationResult == 0;

	if (!wasSuccesful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
}

ActionResult FileMapToVirtualMemoryA(const char* filePath, const MemoryProtectionMode protectionMode)
{
}

ActionResult FileMapToVirtualMemoryW(const wchar_t* filePath, const MemoryProtectionMode protectionMode)
{

}

ActionResult FileMapToVirtualMemory(const size_t size, const MemoryProtectionMode protectionMode)
{

}

ActionResult FileUnmapFromVirtualMemory()
{

}

ActionResult FileReadFromDisk(const char* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;

	// Open file
	{
		const ActionResult result = file.Open(filePath, FileOpenMode::Read, FileCachingMode::Sequential);
		const bool sucessful = result == ResultSuccessful;

		if(!sucessful)
		{
			return result;
		}
	}

	// Read
	{
		const ActionResult result = file.ReadFromDisk(&Data, DataSize, addNullTerminator);
		const bool sucessful = result == ResultSuccessful;

		if(!sucessful)
		{
			file.Close();
			return result;
		}
	}

	// Close
	{
		const ActionResult result = file.Close();
		const bool sucessful = result == ResultSuccessful;

		if(!sucessful)
		{
			return result;
		}
	}

	_fileLocation = FileLocation::CachedFromDisk;

	return ResultSuccessful;
}

ActionResult FileReadFromDisk(const wchar_t* filePath, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	ActionResult result = file.Open(filePath, FileOpenMode::Read, FileCachingMode::Sequential);

	if(result != ResultSuccessful)
	{
		return result;
	}

	result = file.ReadFromDisk(&Data, DataSize, addNullTerminator);

	if(result != ResultSuccessful)
	{
		file.Close();
		return result;
	}

	result = file.Close();

	if(result != ResultSuccessful)
	{
		return result;
	}

	_fileLocation = FileLocation::CachedFromDisk;

	return ResultSuccessful;
}

ActionResult FileReadFromDisk(FILE* file, Byte__** targetBuffer, size_t& bufferSize, bool addNullTerminator)
{
	fseek(file, 0, SEEK_END); // Jump to end of file
	bufferSize = ftell(file); // Get current 'data-cursor' position

	if(!bufferSize) // If no bytes in file, exit.
	{
		return ResultFileEmpty;
	}

	rewind(file); // Jump to the begining of the file

	if(addNullTerminator)
	{
		++bufferSize;
	}

	Byte__* dataBuffer = Memory::Allocate<Byte__>(bufferSize);

	if(!dataBuffer) // If malloc failed
	{
		return ResultOutOfMemory;
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

	return ResultSuccessful;
}

ActionResult FileReadFromDisk(const wchar_t* filePath, Byte__** targetBuffer, size_t& bufferSize, bool addNullTerminator, FilePersistence filePersistence)
{
	File file;
	ActionResult result = file.Open(filePath, FileOpenMode::Read);

	if(result != ResultSuccessful)
	{
		return result;
	}

	//result = ReadFromDisk(file.FileMarker, targetBuffer, bufferSize, addNullTerminator);

	file.ReadFromDisk(targetBuffer, bufferSize, addNullTerminator);

	result = file.Close();

	return ResultSuccessful;
}

ActionResult FileWriteToDisk(const bool value)
{
	return WriteToDisk(&value, sizeof(bool));
}

ActionResult FileWriteToDisk(const char value)
{
	return WriteToDisk(&value, sizeof(char));
}

ActionResult FileWriteToDisk(const unsigned char value)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

ActionResult FileWriteToDisk(const short value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

ActionResult FileWriteToDisk(const unsigned short value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

ActionResult FileWriteToDisk(const int value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

ActionResult FileWriteToDisk(const unsigned int value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

ActionResult FileWriteToDisk(const char* string, const size_t length)
{
	return WriteToDisk(string, length);
}

ActionResult FileWriteToDisk(const unsigned char* string, const size_t length)
{
	return WriteToDisk(string, length);
}

ActionResult FileWriteToDisk(const unsigned long long& value, const Endian endian)
{
	return WriteToDisk(&value, sizeof(unsigned char));
}

ActionResult FileWriteToDisk(const void* value, const size_t length)
{
#if defined(OSUnix)
FILE* fileHandle = FileHandle;
#elif defined(OSWindows)
FILE* fileHandle = FileHandleCStyle;
#endif

	const size_t writtenSize = fwrite(value, sizeof(Byte__), length, fileHandle);

	if(writtenSize > 0)
	{
		return ResultSuccessful;
	}
	else
	{
		return ResultWriteFailure;
	}
}

ActionResult FileWriteToDisk(const char* format, ...)
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
		return ResultWriteFailure;
	}

	return ResultSuccessful;
}

ActionResult FileWriteIntoFile(const void* data, const size_t dataSize)
{
#if defined(OSUnix)
	size_t writtenBytes = fwrite(data, sizeof(char), dataSize, FileHandle);
#elif defined(OSWindows)
	DWORD writtenBytes = 0;
	const bool successful = WriteFile(FileHandle, data, dataSize, &writtenBytes, nullptr);
#endif

	return ActionResult();
}

ActionResult FileWriteToDisk(const char* filePath, FilePersistence filePersistence)
{
	File file;
	ActionResult fileActionResult = file.Open(filePath, FileOpenMode::Write);

	if(fileActionResult != ResultSuccessful)
	{
		return fileActionResult;
	}

	WriteIntoFile(Data, DataSize);

	fileActionResult = file.Close();

	return ResultSuccessful;
}

ActionResult FileWriteToDisk(const wchar_t* filePath, FilePersistence filePersistence)
{
	File file;

	{
		const ActionResult fileActionResult = file.Open(filePath, FileOpenMode::Write);
		const bool sucessful = fileActionResult == ResultSuccessful;

		if(!sucessful)
		{
			return fileActionResult;
		}
	}

#if defined(OSUnix)
	size_t writtenBytes = fwrite(Data, sizeof(char), DataCursorPosition, file.FileHandle);
#elif defined(OSWindows)
	DWORD writtenBytes = 0;
	const bool successful = WriteFile(file.FileHandle, Data, DataCursor, &writtenBytes, nullptr);
#endif

	{
		const ActionResult closeResult = file.Close();
		const bool sucessful = closeResult == ResultSuccessful;

		if(!sucessful)
		{
			return closeResult;
		}
	}

	return ResultSuccessful;
}

ActionResult FileReadFromDisk(unsigned char** outPutBuffer, size_t& outPutBufferSize, const bool addTerminatorByte)
{
#if defined(OSUnix)
	fseek(FileHandle, 0, SEEK_END); // Jump to end of file
	outPutBufferSize = ftell(FileHandle); // Get current 'data-cursor' position

	if (!outPutBufferSize) // If no bytes in file, exit.
	{
		return ResultFileEmpty;
	}

	rewind(FileHandle); // Jump to the begining of the file

	if (addTerminatorByte)
	{
		++outPutBufferSize;
	}

	unsigned char* dataBuffer = Memory::Allocate<unsigned char>(outPutBufferSize);

	if (!dataBuffer) // If malloc failed
	{
		return ResultOutOfMemory;
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

	return ResultSuccessful;
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
		return ResultOutOfMemory;
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
		return ResultFileReadFailure;
	}

	buffer[allocationSize - 1] = '\0';

	(*outPutBuffer) = buffer;
	outPutBufferSize = numberOfBytesRead;

	return ResultSuccessful;
#endif
}

void FilePathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName)
{
	const size_t index = TextFindLastW(currnetPath, PathMaxSize, '/');
	const bool found = index != -1;

	if (found)
	{
		const size_t copyedBytes = TextCopyW(currnetPath, index + 1, targetPath, index + 1);
		const size_t toCopy = PathMaxSize - copyedBytes;

		TextCopyW(newFileName, toCopy, targetPath + copyedBytes, toCopy);
	}
}

void FileFilesInFolder(const char* folderPath, wchar_t*** list, size_t& listSize)
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
	size_t writtenBytes = TextCopyAW(folderPath, PathMaxSize, folderPathW, PathMaxSize);

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

	MemorySet(&dataCursour, 0, sizeof(WIN32_FIND_DATA));

	(*list) = Memory::Allocate<wchar_t*>(listSize);

	hFind = FindFirstFile(folderPathW, &dataCursour); // Expected "." Folder
	size_t fileIndex = 0;

	do
	{
		const size_t length = TextLengthW(dataCursour.cFileName);
		const wchar_t* filePathSource = dataCursour.cFileName;
		wchar_t* newString = Memory::Allocate<wchar_t>(length + 1);

		if (!newString)
		{
			return; // Error: OutOfMemory
		}

		TextCopyW(filePathSource, length, newString, length);

		(*list)[fileIndex] = newString;

		fileIndex++;
	}
	while (FindNextFile(hFind, &dataCursour));

	FindClose(hFind);
#endif
}

void FileFilesInFolder(const wchar_t* folderPath, wchar_t*** list, size_t& listSize)
{

}

unsigned char FileDoesExistA(const char* filePath)
{
	FILE* file = OSFileOpenA(filePath, "rb");

	if (file)
	{
		fclose(file);

		return 1;
	}

	return 0;
}

unsigned char FileDoesExistW(const wchar_t* filePath)
{
#if defined(OSUnix)
    char filePathA[PathMaxSize];

    Text::Copy(filePath, PathMaxSize, filePathA, PathMaxSize);

    return DoesFileExist(filePathA);

#elif defined(OSWindows)
	FILE* file = OSFileOpenW(filePath, L"rb");

	if(file)
	{
		fclose(file);

		return 1;
	}
#endif // defined

	return 0;
}*/

