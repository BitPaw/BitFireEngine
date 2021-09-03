#include "MeshIndexData.h"

BF::MeshIndexData::MeshIndexData()
{
	VertexPositionID = -1;
	TexturePointID = -1;
	NormalVectorID = -1;
}

BF::MeshIndexData::MeshIndexData(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID)
{
	Set(vertexPositionID, texturePointID, normalVectorID);
}

void BF::MeshIndexData::Set(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID)
{
	VertexPositionID = vertexPositionID;
	TexturePointID = texturePointID;
	NormalVectorID = normalVectorID;
}
