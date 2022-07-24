#include "Bash.h"

ActionResult BashExecuteA(const char* programPath, const unsigned char syncronous)
{
	/*
	Pipe pipe;
	FileActionResult result = pipe.Open(programPath, FileOpenMode::Read);
	size_t dataLength = 0;
	unsigned char* data = 0;

	if(result != FileActionResult::Successful)
	{
		return result;
	}

	result = File::ReadFromDisk(pipe.FileMarker, &data, dataLength, true);

	result = pipe.Close();

	printf("[PEx] %s\n", data);

	free(data);*/

	return ResultSuccessful;
}

ActionResult BashExecuteW(const wchar_t* programPath, const unsigned char syncronous)
{
	return ResultSuccessful;
}
