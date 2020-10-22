#include "RenderInformation.h"

BF::RenderInformation::RenderInformation()
{
	Model = nullptr;
	RenderID = -1;
	ShouldItBeRendered = false;

	ShaderID = -1;

	VertexDataPosition = -1;
	VertexDataLength = -1;

	IndiceIndex = -1;
	IndiceIndexLength = -1;

	IndexOffset = -1;

	VertexArrayID = -1;

	IndexBufferID = -1;
	VertexBufferID = -1;

	FaceModelOffset = 0;
}
