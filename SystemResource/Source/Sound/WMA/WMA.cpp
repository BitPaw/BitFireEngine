#include "WMA.h"
#include "../../File/File.h"

BF::FileActionResult BF::WMA::Load(const char* filePath)
{
	File file(filePath);
	FileActionResult loadingResult = file.ReadFromDisk();

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