#include "Resource.h"
#include <string>

BF::Resource::Resource()
{
	ID = -1;

	strcpy(Name, "<Unnamed>");
	strcpy(FilePath, "<Internal Origin>");
}
