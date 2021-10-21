#pragma once

#include "../../../SystemRender/Source/RenderMode.h"

namespace BF
{
	struct MeshStructure
	{
		public:
		bool Original;

		//---<Vertex Data>-----------------------
		unsigned int VertexBufferID; // VBO
		size_t VertexDataSize;
		float* VertexData;

		size_t VertexDataBlockListSize;
		unsigned int VertexDataBlockList[4];
		unsigned int VertexDataBlockFullSize;
		//---------------------------------------

		//---<Index Data>------------------------
		unsigned int IndexBufferID; // IBO
		size_t IndexDataSize;
		unsigned int* IndexData;

		RenderMode RenderType;
		//---------------------------------------

		MeshStructure();
		~MeshStructure();

		void Allocate(size_t vertecDataSize, size_t indexDataSize);
		void DeAllocate();

		void MeshLink(MeshStructure& mesh);

		void PrintData();
	};
}