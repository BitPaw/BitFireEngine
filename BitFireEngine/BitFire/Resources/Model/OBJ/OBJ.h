#pragma once

#include "OBJElement.h"
#include "MTL/MTL.h"

#include "../../../OpenGL/Render/RenderMode.h"
#include "../Model.h"

namespace BF
{
	// [.OBJ] Wavefront - 3D model format
	struct OBJ
	{
		public:
		OBJ();

		AsciiString Name;
		unsigned char VertexStructureSize;
		List<MTL> Materials;
		List<OBJElement> ElementList;

		void Load(AsciiString& filePath);
		void Save(AsciiString& filePath);
		void Convert(Model& model);

		void PrintData();
	};
}