#include "WMA.h"
#include <File/FileStream.h>

BF::FileActionResult BF::WMA::Load(const wchar_t* filePath)
{
	FileStream file;
	FileActionResult loadingResult = file.ReadFromDisk(filePath);

	if (loadingResult != FileActionResult::Successful)
	{
		return loadingResult;
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WMA::Save(const wchar_t* filePath)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::WMA::ConvertTo(Sound& sound)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::WMA::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}