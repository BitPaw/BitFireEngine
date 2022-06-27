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

			targetSegment.ID = sourceSegment.ID;
			targetSegment.Size = sourceSegment.Size;
			targetSegment.TextureType = sourceSegment.TextureType;

			targetSegment.MaterialRangeSize = sourceSegment.MaterialRangeSize;
			targetSegment.MaterialRange = new SegmentMaterialRange[sourceSegment.MaterialRangeSize];

			for(size_t i = 0; i < sourceSegment.MaterialRangeSize; i++)
			{
				SegmentMaterialRange& segmentTarget = targetSegment.MaterialRange[i];
				SegmentMaterialRange& segmentSource = sourceSegment.MaterialRange[i];

				segmentTarget.ShaderID = segmentSource.ShaderID;
				segmentTarget.TextureID = segmentSource.TextureID;
				segmentTarget.Size = segmentSource.Size;
			}
		}
	}
}

void BF::Renderable::ShaderUse(const ShaderProgram& shaderProgram)
{
	ShaderUse(shaderProgram.ID);
}

void BF::Renderable::ShaderUse(const unsigned int shaderProgramID)
{
	for(size_t i = 0; i < ChunkListSize; i++)
	{
		RenderableChunk& renderableChunk = ChunkList[i];

		for(size_t j = 0; j < renderableChunk.SegmentListSize; j++)
		{
			RenderableSegment& renderableSegment = renderableChunk.SegmentList[j];

			for(size_t i = 0; i < renderableSegment.MaterialRangeSize; i++)
			{
				SegmentMaterialRange& SegmentMaterialRange = renderableSegment.MaterialRange[i];
								
				SegmentMaterialRange.ShaderID = shaderProgramID;
			}
		}
	}
}

void BF::Renderable::TextureUse(const unsigned int texturteID)
{
	for(size_t i = 0; i < ChunkListSize; i++)
	{
		RenderableChunk& renderableChunk = ChunkList[i];

		for(size_t j = 0; j < renderableChunk.SegmentListSize; j++)
		{
			RenderableSegment& renderableSegment = renderableChunk.SegmentList[j];

			for(size_t i = 0; i < renderableSegment.MaterialRangeSize; i++)
			{
				SegmentMaterialRange& SegmentMaterialRange = renderableSegment.MaterialRange[i];

				SegmentMaterialRange.TextureID = texturteID;
			}
		}
	}
}