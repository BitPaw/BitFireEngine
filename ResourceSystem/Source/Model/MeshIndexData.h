#pragma once

namespace BF
{
	struct MeshIndexData
	{
		public:
		unsigned int VertexPositionID;
		unsigned int TexturePointID;
		unsigned int NormalVectorID;

		MeshIndexData();
		MeshIndexData(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID);

		void Set(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID);
	};
}