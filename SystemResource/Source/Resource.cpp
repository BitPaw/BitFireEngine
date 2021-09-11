#include "Resource.h"
#include <string>

BF::Resource::Resource()
{
	ID = ResourceIDUndefined;

	strcpy(Name, "<Unnamed>");
	strcpy(FilePath, "<Internal Origin>");
}

void BF::Resource::MarkAsLoading(const char* name, const char* filePath)
{
	ID = ResourceIDLoading;

	strcpy_s(Name, ResourceNameSize , name);
	strcpy_s(FilePath, ResourceFilePathSize, filePath);
}
