#include "OBJElement.h"

#include <Text/Text.h>

BF::OBJElement::OBJElement()
{
	TextCopyA("[N/A]", 5, Name, OBJElementNameLength);

	Smoothing = 0;
	MaterialInfo = nullptr;
	MaterialInfoSize = 0;
}

void BF::OBJElement::Allocate(size_t vertexSize, size_t texturePointSize, size_t normalPointSize, size_t vertexParameterSize, size_t faceElementSize)
{
	VertexPositionList.ReSize(vertexSize);
	TextureCoordinateList.ReSize(texturePointSize);
	VertexNormalPositionList.ReSize(normalPointSize);
	VertexParameterList.ReSize(vertexParameterSize);
	FaceElementList.ReSize(faceElementSize);
}
