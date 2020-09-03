#pragma once

#include "VertexDataCache.h"
#include "IndexDataCache.h"

class RenderDataCache
{
public:
	unsigned int LoadedObjects;

	VertexDataCache VertexData;
	IndexDataCache IndexData;

	RenderDataCache(unsigned int bufferSize);
};