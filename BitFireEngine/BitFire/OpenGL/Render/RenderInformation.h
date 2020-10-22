#pragma once

#include "VertexDataCache.h"
#include "IndexDataCache.h"

#include "../../Resources/Model/Model.h"

namespace BF
{
	class RenderInformation
	{
	public:
		Model* Model;
		unsigned int RenderID;
		bool ShouldItBeRendered;

		unsigned int ShaderID;		

		unsigned int VertexDataPosition;
		unsigned int VertexDataLength;

		unsigned int IndiceIndex;
		unsigned int IndiceIndexLength;

		unsigned int IndexOffset;

		// Data
		unsigned int VertexArrayID = -1;

		unsigned int FaceModelOffset = 0;		

		unsigned int IndexBufferID = -1;
		unsigned int VertexBufferID = -1;

		VertexDataCache VertexData;
		IndexDataCache IndexData;

		RenderInformation();
	};
}