//-----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS 1
//-----------------------------------------------------------------------------



#if defined(__linux__)
#define OSUnix
#include <limits>

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
#include <dirent.h>
#include <filesystem>

namespace fs = std::filesystem;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
FILE* _currentFile;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void DetectFiles(const char* directory);
void DetectRequiredIncludesInFile(const char* fileName);


#if defined(OSUnix)
#include <libgen.h>

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

						fileName[i] == '\0';
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

	const char* fileNameMakeFile = "MakeFile_BFE.mk";

	// remove file if already eist
	remove(fileNameMakeFile);
	printf("[i] Removing file if it exists.\n");

	// Open current File
	_currentFile = fopen(fileNameMakeFile, "wb");

	if (!_currentFile)
	{
		printf("[x] Error: Creating file failed!\n");

		return EXIT_FAILURE;
	}

	printf("[>] Creating file. <%s>\n", fileNameMakeFile);

	fprintf
	(
		_currentFile,
		"#######################################\n"
		"# MakeFile Generator - BitFire Engine #\n"
		"#######################################\n"
	);

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

	fprintf(_currentFile, "#########################################\n");

	printf("[i] FINISHED!\n");

	// Close current File
	int closingResult = fclose(_currentFile);

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

				const char* compileBuffer = "bin";

				fprintf(_currentFile, "#-------------------------------------------------------------------------------------------------\n");
				fprintf(_currentFile, "%s/%s.o: \"%s\"", compileBuffer, fileName, pathA);
				// Insert needed files
				
				fprintf(_currentFile,"\n");

				fprintf
				(
	
					_currentFile,					
					"\t@echo \"[#] Compiling file %s\"\n"
					"\tg++ -c \"%s\"\n",
					pathA,
					pathA
				);
			}				
			else
			{
				printf(" [IGNORED]\n");
			}
		}	
	}
}

void DetectRequiredIncludesInFile(const char* fileName)
{

}