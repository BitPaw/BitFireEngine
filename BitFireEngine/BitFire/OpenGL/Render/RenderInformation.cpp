#include "RenderInformation.h"

RenderInformation::RenderInformation()
{
	Model = nullptr;
	RenderID = -1;

	ShouldItBeRendered = false;

	VertexDataPosition = -1;
	VertexDataLength = -1;

	IndiceIndex = -1;
	IndiceIndexLength = -1;
}
