#include "Bash.h"
#include "FileTemporary.h"
#include "File.h"

BF::FileActionResult BF::Bash::Execute(const char* programPath, bool syncronous)
{
	Pipe pipe;
	FileActionResult result = pipe.Open(programPath, FileOpenMode::Read);
	size_t dataLength = 0;
	unsigned char* data = 0;

	if (result != FileActionResult::Successful)
	{
		return result;
	}

	result = File::ReadFromDisk(pipe.FileMarker, &data, dataLength, true);

	result = pipe.Close();

	printf("[PEx] %s\n", data);

	free(data);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::Bash::Execute(const wchar_t* programPath, bool syncronous)
{
	return FileActionResult::Successful;
}