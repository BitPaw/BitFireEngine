#include "Text.h"

void BF::Text::CreateText(ASCIIString& text, FNT* font, float x, float y)
{
	_font = font;

	AncerPosition.Set(x,y);
	Width = 0;
	Height = 0;
	RenderInformation.RenderType = RenderMode::Square;

	MeshList.ReSize(1); // textSize

	Mesh* mesh = &MeshList[0];
	mesh->NormalPointList.ReSize(1);
	mesh->NormalPointList[0].Set(0, 0, -1);	

	SetText(text);
}

BF::Text::Text(ASCIIString& text, FNT* font)
{
	CreateText(text, font, 0, 0);
}

BF::Text::Text(ASCIIString& text, FNT* font, float x, float y)
{
	CreateText(text, font, x, y);
}

void BF::Text::SetTextPosition(float x, float y)
{
	float offset = 1;

	x = Interpolate::Liniar(-Width* offset, Width* offset, -1, 1, x);
	y = Interpolate::Liniar(-Height* offset, Height* offset, -1, 1, y);



	//x = Interpolate::Liniar(0, 1920 - 150, -1, 1, x) ;
	//y = Interpolate::Liniar(0, 1080 - 250, -1, 1, y) ;

	 MoveTo(x- Width, y- Height, 0);
}

void BF::Text::SetText(ASCIIString& text)
{
	bool hasTextChanged = !Content.Compare(text);
	bool isDifferentSize = Content.Size() != text.Size();

	Content.Copy(text);

	Mesh* mesh = &MeshList[0];
	unsigned int textSize = Content.Size();
	unsigned int amountOfVertices = 4 * textSize;

	if (!hasTextChanged)
	{
		return; // Text has not changed. No update needed
	}

	if (isDifferentSize)
	{	
		mesh->VertexList.DeleteAll();
		mesh->TexturePointList.DeleteAll();
		mesh->IndexList.DeleteAll();

		mesh->VertexList.ReSize(amountOfVertices);
		mesh->TexturePointList.ReSize(amountOfVertices);
		mesh->IndexList.ReSize(amountOfVertices);
	}

	// Put Data
	unsigned int vertexIndex = 0;
	unsigned int textureIndex = 0;
	unsigned int faceIndex = 0;
	unsigned int characterSpacingOffset = 1;
	float fontSize = 0.002;
	float lastPosition = 0;

	for (unsigned int i = 0; i < textSize; i++)
	{
		char character = Content[i];

		if (character == '\0')
		{
			break;
		}

		FNTCharacter* fntCharacter = _font->GetCharacterPosition(character);
		Point<float> xPos = fntCharacter->Position;

		Point<float> interpulatedTexturePointXY
		(
			Interpolate::Normalize(0, 512, fntCharacter->Position.X),
			Interpolate::Normalize(0, 512, fntCharacter->Position.Y)
		);

		Point<float> interpulatedTexturePoinWidthHeight
		(
			Interpolate::Normalize(0, 512, fntCharacter->Size.X),
			Interpolate::Normalize(0, 512, fntCharacter->Size.Y)
		);

		Rectangle objectPosition
		(
			// Start-Position + ((CharOffset + (Size) + LastPos) * fontSize)
			AncerPosition.X + ((-fntCharacter->Offset.X + lastPosition) * fontSize),
			AncerPosition.Y + (fntCharacter->Offset.Y * fontSize),
			AncerPosition.X + ((-fntCharacter->Offset.X + fntCharacter->Size.X + lastPosition) * fontSize),
			AncerPosition.Y + ((fntCharacter->Offset.Y + fntCharacter->Size.Y) * fontSize)
		);

		Rectangle texturePosition
		(
			interpulatedTexturePointXY.X,  // LeftUnder
			interpulatedTexturePointXY.Y, // Right Under
			interpulatedTexturePointXY.X + interpulatedTexturePoinWidthHeight.X, // RightUpepr
			interpulatedTexturePoinWidthHeight.Y + interpulatedTexturePointXY.Y  // Left Upper
		);

		lastPosition += fntCharacter->Size.X + characterSpacingOffset;// +(fntCharacter->XAdvance);

		if (character == ' ')
		{
			lastPosition += characterSpacingOffset * 10;
		}

		//---[Calculate Max-Width and Max-Height]--
		Width += lastPosition;

		if (Height < fntCharacter->Size.Y)
		{
			Height = fntCharacter->Size.Y;
		}
		//-------------------------------------

		// Vertex data (no change do to not pointer?)
		mesh->IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh->VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointA);
		mesh->TexturePointList[textureIndex++].Set(texturePosition.PointD);// 00

		mesh->IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh->VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointB);
		mesh->TexturePointList[textureIndex++].Set(texturePosition.PointC);

		mesh->IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh->VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointC);
		mesh->TexturePointList[textureIndex++].Set(texturePosition.PointB); // 11

		mesh->IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh->VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointD);
		mesh->TexturePointList[textureIndex++].Set(texturePosition.PointA);
	}

	UpdateGlobalMesh();
}

void BF::Text::UpdateText()
{
}

void BF::Text::PrintObjectData()
{
	Mesh* mesh = &MeshList[0];

	unsigned int vertexIndex = 0;
	unsigned int textureIndex = 0;

	printf(" |   x   |   y   | width   | height  |\n");

	for (unsigned int i = 0; i < Content.Size(); i++)
	{
		Rectangle vertexRectangle
		(
			mesh->VertexList[vertexIndex++].CurrentPosition,
			mesh->VertexList[vertexIndex++].CurrentPosition,
			mesh->VertexList[vertexIndex++].CurrentPosition,
			mesh->VertexList[vertexIndex++].CurrentPosition
		);

		Rectangle textureRectangle
		(
			mesh->TexturePointList[textureIndex++],
			mesh->TexturePointList[textureIndex++],
			mesh->TexturePointList[textureIndex++],
			mesh->TexturePointList[textureIndex++]
		);

		printf("A| %5.1f | %5.1f | %1.5f | %1.5f | > Character <%c> %u/%u\n", vertexRectangle.PointA.X, vertexRectangle.PointA.Y, textureRectangle.PointA.X, textureRectangle.PointA.Y, Content[i], i, Content.Size());
		printf("B| %5.1f | %5.1f | %1.5f | %1.5f |\n", vertexRectangle.PointB.X, vertexRectangle.PointB.Y, textureRectangle.PointB.X, textureRectangle.PointB.Y);
		printf("C| %5.1f | %5.1f | %1.5f | %1.5f |\n", vertexRectangle.PointC.X, vertexRectangle.PointC.Y, textureRectangle.PointC.X, textureRectangle.PointC.Y);
		printf("D| %5.1f | %5.1f | %1.5f | %1.5f |\n", vertexRectangle.PointD.X, vertexRectangle.PointD.Y, textureRectangle.PointD.X, textureRectangle.PointD.Y);
		printf(" | \n");
	}
}
