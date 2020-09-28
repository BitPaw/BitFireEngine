#pragma once

#include <GL/glew.h>

#include "VertexDataCache.h"
#include "IndexDataCache.h"
#include "RenderInformation.h"

namespace BF
{
	class RenderDataCache
	{
	private:		
		List<RenderInformation> _renderInformationCache;
		unsigned int _faceModelOffset = 0;
		unsigned int _renderObjectCounter = 0;

		

		void Update(RenderInformation* renderInformation);

	public:		
		unsigned int IndexBufferID;
		unsigned int VertexBufferID;

		VertexDataCache VertexData;
		IndexDataCache IndexData;

		RenderInformation* GetRenderInformation(RenderModel* renderModel);

		RenderDataCache(unsigned int bufferSize);
	
		void UpdateDataLink(RenderModel* renderModel);
	};
}