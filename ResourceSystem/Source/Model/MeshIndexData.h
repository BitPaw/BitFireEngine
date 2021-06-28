#pragma once

namespace BF
{
	struct MeshIndexData
	{
		public:
		int VertexPositionID;
		int TexturePointID;
		int NormalVectorID;

		MeshIndexData();
		MeshIndexData(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID);

		void Set(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID);
	};
}