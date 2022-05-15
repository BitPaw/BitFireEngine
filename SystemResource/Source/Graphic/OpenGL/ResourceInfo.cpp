#include "ResourceInfo.h"

#include <Text/Text.h>

BF::ResourceInfo::ResourceInfo()
{
	NameChange("<Unnamed>");
	FilePathChange("<Internal Origin>");
}

void BF::ResourceInfo::NameChange(const char* name)
{
	Text::Copy(name, ResourceNameSize, Name, ResourceNameSize);
}

void BF::ResourceInfo::NameChange(const wchar_t* name)
{
	Text::Copy(name, ResourceNameSize, Name, ResourceNameSize);
}

void BF::ResourceInfo::FilePathChange(const char* filePath)
{
	Text::Copy(filePath, ResourceFilePathSize, FilePath, ResourceFilePathSize);
}

void BF::ResourceInfo::FilePathChange(const wchar_t* filePath)
{
	Text::Copy(filePath, ResourceFilePathSize, FilePath, ResourceFilePathSize);
}