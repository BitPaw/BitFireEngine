#pragma once

struct MeshIndexData
{
public:
	int VertexPositionID;
	int TexturePointID;
	int NormalVectorID;

	MeshIndexData();
	MeshIndexData(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID);
};