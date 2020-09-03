#include "MeshIndexData.h"

MeshIndexData::MeshIndexData() : MeshIndexData(0,0,0)
{
}

MeshIndexData::MeshIndexData(const unsigned int vertexPositionID, const unsigned int texturePointID, const unsigned int normalVectorID)
{
	VertexPositionID = vertexPositionID;
	TexturePointID = texturePointID;
	NormalVectorID = normalVectorID;
}
