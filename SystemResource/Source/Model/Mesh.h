#pragma once

#include "MeshRenderInfo.h"
#include "MeshStructure.h"
#include "../../../SystemRender/Source/RenderMode.h"

#define MeshNameLength 64

namespace BF
{
	struct Mesh
	{
		public:
		wchar_t Name[MeshNameLength];
		MeshStructure Structure;
		MeshRenderInfo RenderInfo;	
	};
}