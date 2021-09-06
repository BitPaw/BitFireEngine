#include "Resource.h"
#include <string>

BF::Resource::Resource()
{
	ID = ResourceIDUndefined;

	strcpy(Name, "<Unnamed>");
	strcpy(FilePath, "<Internal Origin>");
}
