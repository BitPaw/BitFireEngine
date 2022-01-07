#include "Resource.h"

BF::Resource::Resource()
{
	ID = ResourceIDUndefined;
}

void BF::Resource::MarkAsLoading(const StringUnicode* name, const StringUnicode* filePath)
{
	ID = ResourceIDLoading;
}