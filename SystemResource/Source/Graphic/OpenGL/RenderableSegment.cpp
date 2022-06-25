#include "RenderableSegment.h"

BF::RenderableSegment::RenderableSegment()
{
	ID = -1;
	Size = 0;

	MaterialRangeSize = 0;
	MaterialRange = nullptr;

	TextureType = ImageType::Texture2D;
}
