#include "Renderable.h"

BF::Renderable::Renderable()
{
	DoRendering = true;

	ID = -1; 
	ChunkListSize = 0;
	ChunkList = nullptr;

	Parent = nullptr;

	Mode = RenderMode::Triangle;
}

void BF::Renderable::MeshShare(const Renderable& rendable)
{
	ID = rendable.ID;
	Mode = rendable.Mode;
	
	ChunkListSize = rendable.ChunkListSize;
	ChunkList = new RenderableChunk[ChunkListSize];

	for (size_t i = 0; i < ChunkListSize; i++)
	{
		const RenderableChunk& sourceChunk = rendable.ChunkList[i];
		RenderableChunk& targetChunk = ChunkList[i];
		const size_t segmentListSize = sourceChunk.SegmentListSize;

		targetChunk.ID = sourceChunk.ID;
		targetChunk.SegmentListSize = segmentListSize;
		targetChunk.SegmentList = new RenderableSegment[segmentListSize];
		
		for (size_t e = 0; e < segmentListSize; e++)
		{
			const RenderableSegment& sourceSegment = sourceChunk.SegmentList[i];
			RenderableSegment& targetSegment = targetChunk.SegmentList[i];

			targetSegment = sourceSegment;
		}
	}
}

void BF::Renderable::ShaderUse(const ShaderProgram& shaderProgram)
{
	if (ChunkList)
	{
		ChunkList[0].SegmentList[0].ShaderID = shaderProgram.ID;
	}

	//ShaderID = shaderProgram.ID;
}