/*#include "Level.h"

#include <File/File.h>

BF::Level::Level()
{
	ID = -1;
}

bool BF::Level::IsLevelFile(const wchar_t* filePath)
{
	File file(filePath);

	return file.ExtensionEquals("lev");
}

ActionResult BF::Level::Load()
{
	return ResultSuccessful;
}

size_t BF::Level::FullSizeInMemory()
{
	return sizeof(*this);
}*/
