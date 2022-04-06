#include "RenderableSegment.h"

BF::RenderableSegment::RenderableSegment()
{
	ID = -1;
	Size = 0;
	ShaderID = -1;
	TextureID = -1;

	TextureType = ImageType::TextureUnkown;
}
