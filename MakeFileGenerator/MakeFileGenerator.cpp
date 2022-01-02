//-----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS 1
//-----------------------------------------------------------------------------

#if defined(__linux__)
	#define OSUnix
	
	#define _MAX_PATH 260
	#define _MAX_DRIVE 3
	#define _MAX_DIR 256
	#define _MAX_FNAME 256
	#define _MAX_EXT 256
#elif defined(WIN32)
	#define OSWindows
#endif

//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <filesystem> // C++17 is needed

namespace fs = std::filesystem;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
const char* filePathExport = "__Export__";
const char* filePathTemp = "__Temp__";
const char* filePathLibName = "ExportLib";
const char* filePathObjectListCache = "_ObjectListCache";
FILE* _currentFile;
FILE* _objectFileList;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void WriteFileHeader();
void WriteLibary();
void WriteCompileFile(const char* fileName, const char* fileNameFull);
void DetectFiles(const char* directory);
void DetectRequiredIncludesInFile(const char* fileName);


#if defined(OSUnix)
#include <libgen.h>
void _splitpath(const char* fullPath, char* drive, char* directory, char* fileName, char* extension);

void _splitpath
(
	const char* fullPath,
	char* drive,
	char* directory,
	char* fileName,
	char* extension
)
{
	char directoryNameCache[_MAX_DIR];
	char baseNameCache[_MAX_FNAME];

	strcpy(baseNameCache, fullPath);

	char* dirNameResult = dirname(directoryNameCache);
	char* baseNameResult = basename(baseNameCache);

	strcpy(directory, dirNameResult);
	strcpy(fileName, baseNameResult);

	for (int i = 0; fileName[i] != '\0'; i++)
	{
		bool isDot = fileName[i] == '.';

		if (isDot)
		{
			strcpy(extension, fileName + i);

			fileName[i] = '\0';
			break;
		}

	}

};
#endif

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int main(int numberOfParameters, char** parammeterList)
{
	/*
	switch (numberOfParameters)
	{
		default:
			break;
	}*/

	_currentFile = nullptr;
	_objectFileList = nullptr;

	const char* fileNameMakeFile = "MakeFile_BFE.mk";

	// remove file if already eist

	printf("[i] Removing file if it exists.\n");

	// Open current File
	remove(fileNameMakeFile);
	_currentFile = fopen(fileNameMakeFile, "wb");

	remove(filePathObjectListCache);
	_objectFileList = fopen(filePathObjectListCache, "wb");

	if (!_currentFile)
	{
		printf("[x] Error: Creating file failed!\n");

		return EXIT_FAILURE;
	}

	printf("[>] Creating file. <%s>\n", fileNameMakeFile);

	WriteFileHeader();

	

	// Loop all directorys
	char tmp[_MAX_PATH];
	//getcwd(tmp, 256);
	auto currenPath = std::filesystem::current_path();

#if defined(OSUnix)
	strcpy(tmp, currenPath.c_str());
#elif defined(OSWindows)
	wcstombs(tmp, currenPath.c_str(), _MAX_PATH);
#endif

	char* directoryCurrent = tmp;
	char drive[_MAX_DRIVE];
	char directory[_MAX_DIR];
	char fileName[_MAX_FNAME];
	char extension[_MAX_EXT];
	
	printf("[>] Looking for files in diretory <%s>\n", directoryCurrent);

	_splitpath
	(
		directoryCurrent,
		drive,
		directory,
		fileName,
		extension
	);
	
	printf("[i] Found directory <%s>\n", directory);

	// Loop all files in current Dir
	DetectFiles(directory);




	WriteLibary();

	fprintf(_currentFile, "#########################################\n");

	printf("[i] FINISHED!\n");

	// Close current File
	int closingResult = fclose(_currentFile);

	int closingResultA = fclose(_objectFileList);

	if (closingResult == 0)
	{
		// OK
		printf("[i] Closing file. <%s>\n", fileNameMakeFile);
	}
	else
	{
		printf("[x] Errorwhile closing file. <%s>\n", fileNameMakeFile);		
	}

	_currentFile = nullptr;	
}



void DetectFiles(const char* directory)
{
	for (const auto& entry : fs::directory_iterator(directory))
	{
		char pathA[_MAX_PATH];
		char fileName[_MAX_FNAME];
		auto pathW = entry.path().c_str();				
		bool isDirectory = entry.is_directory();
		bool isFile = entry.is_regular_file();

#if defined(OSUnix)
	strcpy(pathA, pathW);
#elif defined(OSWindows)
	wcstombs(pathA, pathW, _MAX_PATH);
#endif		

		if (isDirectory)
		{
			printf("[i] DETECTED: Directory <%s> ----\\/\n", pathA);
			DetectFiles(pathA);
		}

		if (isFile)
		{
			printf("[i] DETECTED: File <%s>", pathA);

			char drive[_MAX_DRIVE];
			char directory[_MAX_DIR];
			char fileName[_MAX_FNAME];
			char extension[_MAX_EXT];

			_splitpath
			(
				pathA,
				drive,
				directory,
				fileName,
				extension
			);

			bool isHeader = strcmp(extension, ".h") == 0;
			bool isCOmpilabbleHeader = strcmp(extension, ".hpp") == 0;
			bool isCodeFileC = strcmp(extension, ".c") == 0;
			bool isCodeFileCpp = strcmp(extension, ".cpp") == 0;
			bool canCompile = isCOmpilabbleHeader || isCodeFileC || isCodeFileCpp;

			if (canCompile)
			{
				printf(" [OK]\n");

				WriteCompileFile(fileName, pathA);			
			}				
			else
			{
				printf(" [IGNORED]\n");
			}
		}	
	}
}

void WriteFileHeader()
{
	fprintf
	(
		_currentFile,
		"#######################################\n"
		"# MakeFile Generator - BitFire Engine #\n"
		"#######################################\n"
		"#---Variables---#\n"
		"Compiler = g++\n"
		"DirExport = \"%s\"\n"
		"DirTemp = \"%s\"\n\n",
		filePathExport,
		filePathTemp
	);

	fprintf
	(
		_currentFile,
		"all: folders $(DirExport)/%s\n\n"
		"folders: \n"
		"\t-mkdir $(DirExport)\n"
		"\t-mkdir $(DirTemp)\n",
		filePathLibName,
		filePathExport,
		filePathTemp
	);
}

void WriteLibary()
{
	char buffer[2048];

	fclose(_objectFileList);
	_objectFileList = fopen(filePathObjectListCache, "rb");

	fprintf(_currentFile, "#-------------------------------------------------------------------------------------------------\n");
	
	fprintf(_currentFile, "$(DirExport)/%s: ", filePathLibName);

	fseek(_objectFileList, 0, 0);
	while (fgets(buffer, 2048, _objectFileList))
	{
		size_t length = strlen(buffer);

		buffer[length - 1] = '\0';

		fprintf(_currentFile, "%s ", buffer);
	}

	fprintf(_currentFile, "\n\tar rcs $(DirExport)/%s.lib ", filePathLibName);
	
	fseek(_objectFileList, 0, 0);
	while (fgets(buffer, 2048, _objectFileList))
	{
		size_t length = strlen(buffer);

		buffer[length - 1] = '\0';

		fprintf(_currentFile, "%s ", buffer);
	}

	fprintf(_currentFile, "\n#-------------------------------------------------------------------------------------------------\n");
}

void WriteCompileFile(const char* fileName, const char* fileNameFull)
{
	fprintf(_currentFile, "#-------------------------------------------------------------------------------------------------\n");
	fprintf(_currentFile, "$(DirTemp)/%s.o: %s", fileName, fileNameFull);
	
	// Insert needed files

	fprintf(_currentFile, "\n");

	fprintf
	(

		_currentFile,
		"\t@echo \"[#] Compiling file %s\"\n"
		"\t-$(Compiler) -c \"%s\" -o $(DirTemp)/%s.o\n",
		fileNameFull,
		fileNameFull,
		fileName
	);

	fprintf(_objectFileList, "$(DirTemp)/%s.o\n", fileName);
}

void DetectRequiredIncludesInFile(const char* fileName)
{

}