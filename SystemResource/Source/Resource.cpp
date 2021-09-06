#include "Resource.h"
#include <string>

BF::Resource::Resource()
{
	ID = ResourceIDUnused;

	strcpy(Name, "<Unnamed>");
	strcpy(FilePath, "<Internal Origin>");
}
