#include "FLAC.h"

BF::FileActionResult BF::FLAC::Load(const wchar_t* filePath)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::FLAC::Save(const wchar_t* filePath)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::FLAC::ConvertTo(Sound& sound)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::FLAC::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}