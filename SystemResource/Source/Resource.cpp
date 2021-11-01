#include "Resource.h"
#include <string>

BF::Resource::Resource()
{
	ID = ResourceIDUndefined;

	NameChange("<Unnamed>");
	FilePathChange("<Internal Origin>");
}

void BF::Resource::MarkAsLoading(const char* name, const char* filePath)
{
	ID = ResourceIDLoading;

	NameChange(name);
	FilePathChange(filePath);
}

void BF::Resource::NameChange(const char* name)
{
	strncpy_s(Name, name, ResourceNameSize);
}

void BF::Resource::FilePathChange(const char* filePath)
{
	strncpy_s(FilePath, filePath, ResourceNameSize);
}