#include "Level.h"

bool BF::Level::IsLevelFile(const wchar_t* filePath)
{
	return false;
}

PXActionResult BF::Level::Load(const wchar_t* filePath)
{
	return PXActionInvalid;
}

size_t BF::Level::FullSizeInMemory()
{
	return sizeof(*this);
}