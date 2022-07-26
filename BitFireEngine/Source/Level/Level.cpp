#include "Level.h"

bool BF::Level::IsLevelFile(const wchar_t* filePath)
{
	return false;
}

ActionResult BF::Level::Load(const wchar_t* filePath)
{
	return ActionResult();
}

size_t BF::Level::FullSizeInMemory()
{
	return sizeof(*this);
}