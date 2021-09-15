#include "UIImage.h"

void BF::UIImage::SetBorder(const int borderSize)
{
	const int border = 1;
	const float borderOffset = border - borderSize;

	const float vertexPointData[36] =
	{
		// Normal
		-border, -border, 0,
		-border, border, 0,
		border, -border, 0,
		border, border, 0,

		-borderOffset, -borderOffset, 0,
		-borderOffset, borderOffset, 0,
		borderOffset, -borderOffset, 0,
		borderOffset, borderOffset, 0,


		-border,-borderSize,0,
		borderOffset,-border,0,
		border,borderOffset,0,
		borderSize,border,0
	};

	const int vertexTextureData[24] =
	{
		0,0,
		0,1,
		1,0,
		1,1,

		borderSize, borderSize,
		borderSize, borderOffset,
		borderOffset, borderSize,
		borderOffset, borderOffset,

		0,0,
		0,1,
		1,0,
		1,1,
	};

	//const unsigned int indexData[4 * 5];
	


	//RenderInformation.VertexData.ReSize(8*(3+2+3+4));
	//RenderInformation.IndexData.ReSize(4*5);

	unsigned int* indexData = &RenderInformation.IndexData[0];
}
