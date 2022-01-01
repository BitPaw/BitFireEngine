#include "Resource.h"
#include <string.h>
#include "OSDefine.h"

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
#if defined(OSUnix)
strncpy(Name, name, ResourceNameSize);
#elif  defined(OSWindows)
strncpy_s(Name, name, ResourceNameSize);
#endif
}

void BF::Resource::FilePathChange(const char* filePath)
{
#if defined(OSUnix)
	strncpy(FilePath, filePath, ResourceNameSize);
#elif  defined(OSWindows)
	strncpy_s(FilePath, filePath, ResourceNameSize);
#endif
}