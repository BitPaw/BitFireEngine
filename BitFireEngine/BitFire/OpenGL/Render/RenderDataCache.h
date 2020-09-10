#pragma once

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

		RenderInformation* GetRenderInformation(RenderModel* renderModel);

		void Update(RenderInformation* renderInformation);

	public:		

		VertexDataCache VertexData;
		IndexDataCache IndexData;

		RenderDataCache(unsigned int bufferSize);
	
		void UpdateDataLink(RenderModel* renderModel);
	};
}