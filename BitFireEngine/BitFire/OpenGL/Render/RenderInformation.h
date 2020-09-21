#pragma once

#include "../../Graphics/RenderModel.h"

struct RenderInformation
{
public:
	BF::RenderModel* Model;
	unsigned int RenderID;
	bool ShouldItBeRendered;

	unsigned int VertexDataPosition;
	unsigned int VertexDataLength;

	unsigned int IndiceIndex;
	unsigned int IndiceIndexLength;

	unsigned int IndexOffset;

	RenderInformation();
};