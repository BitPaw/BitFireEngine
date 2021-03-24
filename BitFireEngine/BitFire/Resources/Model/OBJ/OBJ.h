#pragma once

#include "OBJElement.h"
#include "MTL/MTL.h"

#include "../IModel.h"
#include "../../../OpenGL/Render/RenderMode.h"

namespace BF
{
	// [.OBJ] Wavefront - 3D model format
	struct OBJ// : public IModel
	{
		public:
		OBJ();

		AsciiString Name = "[N/A]";
		unsigned char VertexStructureSize;
		List<MTL> Materials;
		List<OBJElement> ElementList;
	};
}