#include "Resource.h"

BF::Resource::Resource()
{
	ID = -1;
	LoadedToGPU = false;
	SharedCounter = 0;
	ShouldBeRendered = true;
}
