#include "Level.h"

bool BF::Level::IsLevelFile(const wchar_t* filePath)
{
	return false;
}

BF::FileActionResult BF::Level::Load(const wchar_t* filePath)
{
	return FileActionResult();
}

size_t BF::Level::FullSizeInMemory()
{
	return sizeof(*this);
}