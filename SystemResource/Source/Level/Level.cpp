#include "Level.h"
#include "../File/File.h"

BF::Level::Level()
{
	ID = -1;
}

bool BF::Level::IsLevelFile(const char* filePath)
{
	File file(filePath);
	AsciiString fileExtension(file.Extension);

	return fileExtension.CompareIgnoreCase("lev");
}