#include "MeshIndexData.h"

BF::MeshIndexData::MeshIndexData() : MeshIndexData(0,0,0)
{
}

BF::MeshIndexData::MeshIndexData(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID)
{
	VertexPositionID = vertexPositionID;
	TexturePointID = texturePointID;
	NormalVectorID = normalVectorID;
}
