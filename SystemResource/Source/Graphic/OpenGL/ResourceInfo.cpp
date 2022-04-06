#include "ResourceInfo.h"

#include <Text/Text.h>

BF::ResourceInfo::ResourceInfo()
{
	NameChange("<Unnamed>");
	FilePathChange("<Internal Origin>");
}

void BF::ResourceInfo::NameChange(const char* name)
{
	Text::Copy(Name, name, ResourceNameSize);
}

void BF::ResourceInfo::NameChange(const wchar_t* name)
{
	Text::Copy(Name, name, ResourceNameSize);
}

void BF::ResourceInfo::FilePathChange(const char* filePath)
{
	Text::Copy(FilePath, filePath, ResourceFilePathSize);
}

void BF::ResourceInfo::FilePathChange(const wchar_t* filePath)
{
	Text::Copy(FilePath, filePath, ResourceFilePathSize);
}
