#include "ResourceInfo.h"

#include <Text/Text.h>

BF::ResourceInfo::ResourceInfo()
{
	NameChange("<Unnamed>");
	FilePathChange("<Internal Origin>");
}

void BF::ResourceInfo::NameChange(const char* name)
{
	TextCopyAW(name, ResourceNameSize, Name, ResourceNameSize);
}

void BF::ResourceInfo::NameChange(const wchar_t* name)
{
	TextCopyW(name, ResourceNameSize, Name, ResourceNameSize);
}

void BF::ResourceInfo::FilePathChange(const char* filePath)
{
	TextCopyAW(filePath, ResourceFilePathSize, FilePath, ResourceFilePathSize);
}

void BF::ResourceInfo::FilePathChange(const wchar_t* filePath)
{
	TextCopyW(filePath, ResourceFilePathSize, FilePath, ResourceFilePathSize);
}