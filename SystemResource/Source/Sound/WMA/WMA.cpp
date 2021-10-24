#include "WMA.h"
#include "../../File/FileStream.h"

BF::FileActionResult BF::WMA::Load(const char* filePath)
{
	FileStream file;
	FileActionResult loadingResult = file.ReadFromDisk(filePath);

	if (loadingResult != FileActionResult::Successful)
	{
		return loadingResult;
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WMA::Save(const char* filePath)
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