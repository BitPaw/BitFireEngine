#pragma once

#include <GL/glew.h>

#include "../../Utility/List.hpp"

#include "RenderInformation.h"

namespace BF
{
	class RenderDataCache
	{
	private:		
		List<RenderInformation> _renderInformationCache;
	
		unsigned int _renderObjectCounter = 0;

		void Update(RenderInformation* renderInformation);

	public:		
		RenderInformation* GetRenderInformation(Model* renderModel);

		

		RenderDataCache();

		void DrawAll();	
		void UpdateDataLink(Model* renderModel);
	};
}