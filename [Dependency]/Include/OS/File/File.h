#ifndef FileINCLUDE
#define FileINCLUDE

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#include <Format/Type.h>
#include <OS/Memory/PXMemory.h>
#include <OS/Error/PXActionResult.h>

#if OSUnix

#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <libgen.h>
//#include <dirent.h>

typedef FILE* FileHandleType;
typedef int FileMappingID;

#elif OSWindows

#include <windows.h>
#include <direct.h>

typedef HANDLE FileHandleType;
typedef HANDLE FileMappingID;

#endif

#define FileLineBufferSize 2048

#if OSUnix
#define PathMaxSize 260
#define DriveMaxSize 3
#define DirectoryMaxSize 256
#define FileNameMaxSize 256
#define ExtensionMaxSize 256
#elif OSWindows
#define PathMaxSize 260 // _MAX_PATH
#define DriveMaxSize 3 //_MAX_DRIVE
#define DirectoryMaxSize 256//_MAX_DIR
#define FileNameMaxSize 256 //_MAX_FNAME
#define ExtensionMaxSize 256 //_MAX_EXT
#endif


#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum FileFormatExtension_
	{
		FileFormatInvalid,
		FileFormatUnkown,

		FileFormatA3DS,
		FileFormatAAC,
		FileFormatAVI,
		FileFormatBitMap,
		FileFormatCSS,
		FileFormatWindowsDynamicLinkedLibrary,
		FileFormatLinuxExecutableAndLinkable,
		FileFormatEML,
		FileFormatWindowsExecutable,
		FileFormatFimBox,
		FileFormatFLAC,
		FileFormatSpriteFont,
		FileFormatGIF,
		FileFormatHTML,
		FileFormatINI,
		FileFormatJPEG,
		FileFormatJSON,
		FileFormatM4A,
		FileFormatMIDI,
		FileFormatMP3,
		FileFormatMP4,
		FileFormatMSI,
		FileFormatMTL,
		FileFormatOBJ,
		FileFormatOGG,
		FileFormatPDF,
		FileFormatPHP,
		FileFormatPLY,
		FileFormatPNG,
		FileFormatQOI,
		FileFormatSTEP,
		FileFormatSTL,
		FileFormatSVG,
		FileFormatTGA,
		FileFormatTagImage,
		FileFormatTrueTypeFont,
		FileFormatVRML,
		FileFormatWave,
		FileFormatWEBM,
		FileFormatWEBP,
		FileFormatWMA,
		FileFormatXML,
		FileFormatYAML
	}
	FileFormatExtension;

	PXPublic FileFormatExtension FilePathExtensionDetectTryA(const char* const filePath, const PXSize filePathSize);
	PXPublic FileFormatExtension FilePathExtensionDetectTryW(const wchar_t* const filePath, const PXSize filePathSize);

	PXPublic FileFormatExtension FileExtensionDetectTryA(const char* const extension, const PXSize extensionSize);
	PXPublic FileFormatExtension FileExtensionDetectTryW(const wchar_t* const extension, const PXSize extensionSize);


	typedef struct PXFile_
	{
#if OSUnix
		int Context;
#elif OSWindows
		HANDLE Context;
#endif
	}
	PXFile;

	PXPublic void PXFileConstruct(PXFile* const pxFile);
	PXPublic void PXFileDestruct(PXFile* const pxFile);


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

	//---<Utility>---------------------------------------------------------
	PXPublic PXBool FileDoesExistA(const char* filePath);
	PXPublic PXBool FileDoesExistW(const wchar_t* filePath);

	PXPublic PXActionResult FileRemoveA(const char* filePath);
	PXPublic PXActionResult FileRemoveW(const wchar_t* filePath);
	PXPublic PXActionResult FileRenameA(const char* oldName, const char* newName);
	PXPublic PXActionResult FileRenameW(const wchar_t* oldName, const wchar_t* newName);
	PXPublic PXActionResult FileCopyA(const char* sourceFilePath, const char* destinationFilePath);
	PXPublic PXActionResult FileCopyW(const wchar_t* sourceFilePath, const wchar_t* destinationFilePath);

	PXPublic void FilePathSwapFile(const wchar_t* currnetPath, wchar_t* targetPath, const wchar_t* newFileName);
	PXPublic void FilePathSwapFileNameA(const PXTextASCII inputPath, PXTextASCII exportPath, const PXTextASCII fileName);
	PXPublic void FilePathSwapFileNameW(const PXTextUNICODE inputPath, PXTextUNICODE exportPath, const PXTextUNICODE fileName);
	PXPublic void FilePathSwapFileNameU(const PXTextUTF8 inputPath, PXTextUTF8 exportPath, const PXTextUTF8 fileName);

	PXPublic void FilePathSwapExtensionA(const PXTextASCII inputPath, PXTextASCII exportPath, const PXTextASCII fileExtension);
	PXPublic void FilePathSwapExtensionW(const PXTextUNICODE inputPath, PXTextUNICODE exportPath, const PXTextUNICODE fileExtension);
	PXPublic void FilePathSwapExtensionU(const PXTextUTF8 inputPath, PXTextUTF8 exportPath, const PXTextUTF8 fileExtension);
	//---------------------------------------------------------------------

	//---<Directory>-------------------------------------------------------
	PXPublic PXActionResult DirectoryCreateA(const char* directoryName);
	PXPublic PXActionResult DirectoryCreateW(const wchar_t* directoryName);
	PXPublic PXActionResult WorkingDirectoryChange(const char* directoryName);
	PXPublic PXActionResult WorkingDirectoryGetA(char* workingDirectory, PXSize workingDirectorySize);
	PXPublic PXActionResult WorkingDirectoryGetW(wchar_t* workingDirectory, PXSize workingDirectorySize);
	PXPublic PXActionResult WorkingDirectoryChangeW(const wchar_t* directoryName);
	PXPublic PXActionResult DirectoryDeleteA(const char* directoryName);
	PXPublic PXActionResult DirectoryDeleteW(const wchar_t* directoryName);
	PXPublic PXActionResult DirectoryFilesInFolderA(const char* folderPath, wchar_t*** list, PXSize* listSize);
	PXPublic PXActionResult DirectoryFilesInFolderW(const wchar_t* folderPath, wchar_t*** list, PXSize* listSize);
	//---------------------------------------------------------------------

	PXPublic PXActionResult PXFileNameA(PXFile* const pxFile, const PXTextASCII fileName, const PXSize fileNameSize, PXSize* const sizeWritten);
	PXPublic PXActionResult PXFileNameW(PXFile* const pxFile, const PXTextUNICODE fileName, const PXSize fileNameSize, PXSize* const sizeWritten);

	PXPublic void FilePathSplittA
	(
		const char* fullPath, PXSize fullPathMaxSize,
		char* drive, PXSize driveMaxSize,
		char* directory, PXSize directoryMaxSize,
		char* fileName, PXSize fileNameMaxSize,
		char* extension, PXSize extensionMaxSize
	);

	PXPublic void FilePathSplittW
	(
		const wchar_t* fullPath, PXSize fullPathMaxSize,
		wchar_t* drive, PXSize driveMaxSize,
		wchar_t* directory, PXSize directoryMaxSize,
		wchar_t* fileName, PXSize fileNameMaxSize,
		wchar_t* extension, PXSize extensionMaxSize
	);

	PXPublic void FilePathSplittPositionW
	(
		const wchar_t* fullPath, PXSize fullPathMaxSize,
		PXSize* drivePos, PXSize driveSize,
		PXSize* directory, PXSize directorySize,
		PXSize* fileName, PXSize fileNameSize,
		PXSize* extension, PXSize extensionSize
	);

	PXPublic PXSize FilePathExtensionGetA(const char* filePath, const PXSize filePathSize, char* extension, const PXSize extensionSizeMax);
	PXPublic PXSize FilePathExtensionGetW(const wchar_t* filePath, const PXSize filePathSize, wchar_t* extension, const PXSize extensionSizeMax);

#ifdef __cplusplus
}
#endif

#endif
