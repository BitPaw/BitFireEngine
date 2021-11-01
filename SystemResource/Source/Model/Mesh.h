#pragma once

#include "MeshRenderInfo.h"
#include "MeshStructure.h"
#include "../../../SystemRender/Source/RenderMode.h"

namespace BF
{
	struct Mesh
	{
		public:
		MeshStructure Structure;
		MeshRenderInfo RenderInfo;	
	};
}