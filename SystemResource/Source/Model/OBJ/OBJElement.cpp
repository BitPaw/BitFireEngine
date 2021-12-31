#include "OBJElement.h"

BF::OBJElement::OBJElement()
{
	strcpy(Name, "[N/A]");

	Smoothing = 0;
	MaterialListIndex = -1;
}

void BF::OBJElement::Allocate(size_t vertexSize, size_t texturePointSize, size_t normalPointSize, size_t vertexParameterSize, size_t faceElementSize)
{
	VertexPositionList.ReSize(vertexSize);
	TextureCoordinateList.ReSize(texturePointSize);
	VertexNormalPositionList.ReSize(normalPointSize);
	VertexParameterList.ReSize(vertexParameterSize);
	FaceElementList.ReSize(faceElementSize);
}
