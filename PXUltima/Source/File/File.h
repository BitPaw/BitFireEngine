#ifndef FileInclude
#define FileInclude

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include <dirent.h>

#include <OS/OSVersion.h>
#include <Memory/Memory.h>
#include <Error/ActionResult.h>
#include <File/Endian.h>

#define FileLineBufferSize 2048




#if defined(OSUnix)
#define PathMaxSize 260
#define DriveMaxSize 3
#define DirectoryMaxSize 256
#define FileNameMaxSize 256
#define ExtensionMaxSize 256
#elif defined(OSWindows)
#define PathMaxSize 260 // _MAX_PATH
#define DriveMaxSize 3 //_MAX_DRIVE
#define DirectoryMaxSize 256//_MAX_DIR
#define FileNameMaxSize 256 //_MAX_FNAME
#define ExtensionMaxSize 256 //_MAX_EXT
#endif

#if defined(OSUnix)

#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <libgen.h>

#define FileHandleType FILE*
#define FileMappingID int

#elif defined(OSWindows)

#include <windows.h>

#define FileHandleType HANDLE
#define FileMappingID HANDLE

#endif


#ifdef __cplusplus
extern "C"
{
#endif
	typedef enum FileLocation_
	{
		FileLocationInvalid,
		FileLocationMappedVirtual, // Used 'VirtalAlloc()' / 'mmap()'
		FileLocationMappedFromDisk, // Used 'FileView()' / 'fmap()'
		FileLocationCachedFromDisk, // When the file is cached into an internal buffer
		FileLocationLinked // Used existing file with 'fopen()'
	}
	FileLocation;

	typedef enum FilePersistence_
	{
		Permanent,
		Tempoary
	}
	FilePersistence;

	typedef enum FileCachingMode_
	{
		FileCachingDefault,

		FileCachingRandom,  // Access data in a random order.
		FileCachingSequential, // Data sequentially from lower offsets to higher offsets.
		FileCachingTemporary, // File will not be saves to drive.
		FileCachingUseOnce, // Access the specified data once and then not reuse it again.

		// Windows only
		FileCachingWriteThrough,
		FileCachingNoBuffering, // No OS Caching, direct to Harddrive if supprted

		// UNIX only
		FileCachingNeedLater, // Data is not needed right now. "For later"[near future].
		FileCachingDontNeedNow // Data will not be cached. "I dont need it yet"
	}
	FileCachingMode;

	/*
	typedef struct FilePath_
	{
		wchar_t Path[PathMaxSize];
		wchar_t Drive[DriveMaxSize];
		wchar_t Directory[DirectoryMaxSize];
		wchar_t FileName[FileNameMaxSize];
		wchar_t Extension[ExtensionMaxSize];
	}
	FilePath;*/



	typedef struct File_
	{
		unsigned char* Data;
		size_t DataSize;
		size_t DataCursor;

		FileLocation _fileLocation; // Where the is stored, used as indicator how to clean up.

		FileHandleType FileHandle; // Only used if file is used directly

		FileMappingID IDMapping; // Only used while mapping a file

#if defined(OSWindows)
		FILE* FileHandleCStyle; // Used for writing only, usage of fprintf()
#endif
		MemoryProtectionMode MemoryMode;
	}
	File;



	static FileCachingMode ConvertToFileCachingMode(const unsigned int value);
	static unsigned int ConvertFromFileCachingMode(const FileCachingMode fileCachingMode);


	extern void FileConstruct(File* file);
	extern void FileDestruct(File* file);


	//---<Open>------------------------------------------------------------
	extern ActionResult FileOpenA(File* file, const char* filePath, const MemoryProtectionMode fileOpenMode, FileCachingMode fileCachingMode);
	extern ActionResult FileOpenW(File* file, const wchar_t* filePath, const MemoryProtectionMode fileOpenMode, FileCachingMode fileCachingMode);
	//---------------------------------------------------------------------

	//---<Close>-----------------------------------------------------------
	extern ActionResult FileClose(File* file);
	//---------------------------------------------------------------------

	//---<Mapping>---------------------------------------------------------
	extern ActionResult FileMapToVirtualMemoryA(File* file, const char* filePath, const size_t fileSize, const MemoryProtectionMode protectionMode);
	extern ActionResult FileMapToVirtualMemoryW(File* file, const wchar_t* filePath, const size_t fileSize, const MemoryProtectionMode protectionMode);
	extern ActionResult FileMapToVirtualMemory(File* file, const size_t size, const MemoryProtectionMode protectionMode);
	extern ActionResult FileUnmapFromVirtualMemory(File* file);
	//---------------------------------------------------------------------

	//---<Read>------------------------------------------------------------
	/*extern ActionResult ReadFromDisk(File* file, unsigned char** outPutBuffer, size_t* outPutBufferSize, const unsigned char addTerminatorByte);
	extern ActionResult ReadFromDisk(File* file, const char* filePath, const unsigned char addNullTerminator, const FilePersistence filePersistence);
	extern 	ActionResult ReadFromDisk(File* file, const wchar_t* filePath, const unsigned char addNullTerminator, const FilePersistence filePersistence);

	extern ActionResult ReadFromDisk(FILE* file, unsigned char** targetBuffer, size_t* bufferSize, const unsigned char addNullTerminator);
	extern ActionResult ReadFromDisk
	(
		const wchar_t* filePath,
		unsigned char** targetBuffer,
		size_t* bufferSize,
		const unsigned char addNullTerminator,
		FilePersistence filePersistence
	);*/
	//---------------------------------------------------------------------

	//---<Write>-----------------------------------------------------------
	/*extern ActionResult WriteToDiskC(File* file, const char value);
	extern ActionResult WriteToDiskCU(File* file, const unsigned char value);
	extern ActionResult WriteToDiskS(File* file, const short value, const Endian endian);
	extern ActionResult WriteToDiskSU(File* file, const unsigned short value, const Endian endian);
	extern ActionResult WriteToDiskI(File* file, const int value, const  Endian endian);
	extern ActionResult WriteToDiskIU(File* file, const unsigned int value, const Endian endian);
	extern ActionResult WriteToDiskLL(File* file, const long long value, const Endian endian);
	extern ActionResult WriteToDiskLLU(File* file, const unsigned long long value, const Endian endian);
	extern ActionResult WriteToDiskD(File* file, const void* value, const size_t length);
	extern ActionResult WriteToDisk(File* file, const char* format, ...);*/

	//ActionResult WriteIntoFile(const void* data, const size_t dataSize);
	//ActionResult WriteToDisk(const char* filePath, FilePersistence filePersistence);
	//ActionResult WriteToDisk(const wchar_t* filePath, FilePersistence filePersistence);
	//---------------------------------------------------------------------



	//---<Utility>---------------------------------------------------------
	extern unsigned char FileDoesExistA(const char* filePath);
	extern unsigned char FileDoesExistW(const wchar_t* filePath);

	extern ActionResult FileRemoveA(const char* filePath);
	extern ActionResult FileRemoveW(const wchar_t* filePath);
	extern ActionResult FileRenameA(const char* oldName, const char* newName);
	extern ActionResult FileRenameW(const wchar_t* oldName, const wchar_t* newName);
	extern ActionResult FileCopyA(const char* sourceFilePath, const char* destinationFilePath);
	extern ActionResult FileCopyW(const wchar_t* sourceFilePath, const wchar_t* destinationFilePath);

	extern void FilePathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName);
	//---------------------------------------------------------------------

	//---<Directory>-------------------------------------------------------
	extern ActionResult DirectoryCreateA(const char* directoryName);
	extern ActionResult DirectoryCreateW(const wchar_t* directoryName);
	extern ActionResult WorkingDirectoryChange(const char* directoryName);
	extern ActionResult WorkingDirectoryGetA(char* workingDirectory, size_t workingDirectorySize);
	extern ActionResult WorkingDirectoryGetW(wchar_t* workingDirectory, size_t workingDirectorySize);
	extern ActionResult WorkingDirectoryChangeW(const wchar_t* directoryName);
	extern ActionResult DirectoryDeleteA(const char* directoryName);
	extern ActionResult DirectoryDeleteW(const wchar_t* directoryName);
	extern ActionResult DirectoryFilesInFolderA(const char* folderPath, wchar_t*** list, size_t* listSize);
	extern ActionResult DirectoryFilesInFolderW(const wchar_t* folderPath, wchar_t*** list, size_t* listSize);
	//---------------------------------------------------------------------



	extern void FilePathSplittA
	(
		const char* fullPath, size_t fullPathMaxSize,
		char* drive, size_t driveMaxSize,
		char* directory, size_t directoryMaxSize,
		char* fileName, size_t fileNameMaxSize,
		char* extension, size_t extensionMaxSize
	);

	extern void FilePathSplittW
	(
		const wchar_t* fullPath, size_t fullPathMaxSize,
		wchar_t* drive, size_t driveMaxSize,
		wchar_t* directory, size_t directoryMaxSize,
		wchar_t* fileName, size_t fileNameMaxSize,
		wchar_t* extension, size_t extensionMaxSize
	);

	extern void FilePathExtensionGetA(const char* filePath, const size_t filePathSize, char* extension, const size_t extensionSizeMax);
	extern void FilePathExtensionGetW(const wchar_t* filePath, const size_t filePathSize, wchar_t* extension, const size_t extensionSizeMax);

#ifdef __cplusplus
}
#endif

#endif
