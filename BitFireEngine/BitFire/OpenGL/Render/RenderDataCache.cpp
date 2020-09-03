#include "RenderDataCache.h"

RenderDataCache::RenderDataCache(unsigned int bufferSize)
{
	LoadedObjects = 0;

	VertexData.AllocateSpace(bufferSize);
	IndexData.AllocateSpace(bufferSize);
}