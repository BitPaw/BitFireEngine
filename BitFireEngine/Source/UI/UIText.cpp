#include "UIText.h"
#include "../../../SystemResource/Source/Font/FNT/FNT.h"
#include "../../../SystemResource/Source/Math/Interpolate.h"

void BF::UIText::Setup(AsciiString& text, Font& font, float x, float y)
{
	AncerPosition.Set(x, y);
	Width = 0;
	Height = 0;
	RenderInformation.RenderType = RenderMode::Square;

	strcpy(Name, "<Internal Text>");

	MeshList.ReSize(1); // textSize

	Mesh& mesh = MeshList[0];
	mesh.NormalPointList.ReSize(1);
	mesh.NormalPointList[0].Set(0, 0, -1);
	mesh.MeshMaterial = new Material();

	strcpy(mesh.Name, "<Text-Mesh>");
	strcpy(mesh.MeshMaterial->Name, "<Text Content>");	
	strcpy(mesh.MeshMaterial->TextureFilePath, "<Internal>");

	SetFont(font);
	SetText(text);
	SetTextPosition(x, y);
}

BF::UIText::UIText(const char* text, Font& font, float x, float y)
{
	AsciiString asciiText(text);

	Setup(asciiText, font, x, y);
}

BF::UIText::UIText(AsciiString& text, Font& font, float x, float y)
{
	Setup(text, font, x, y);
}

void BF::UIText::SetFont(Font& font)
{
	_font = &font;
}

void BF::UIText::SetTextPosition(float x, float y)
{
	float offset = 1;

	x = Interpolate::Liniar(-Width* offset, Width* offset, -1, 1, x);
	y = Interpolate::Liniar(-Height* offset, Height* offset, -1, 1, y);

	 MoveTo(x- Width, y- Height, 0);
}

void BF::UIText::SetText(const char* text)
{
	AsciiString asciiText(text);

	SetText(asciiText);
}

void BF::UIText::SetText(AsciiString& text)
{	
	if (_font == nullptr)
	{
		return;
	}

	if(_font->CharacterSize == 0)
	{
		return;
	}

	ID = ResourceIDLoading;

	AsciiString currentText(TextContent);

	FNT& bitmapFont = *((FNT*)(_font->BitMapFont));

	bool hasTextChanged = !currentText.Compare(text) || true;
	bool isDifferentSize = (currentText.Size() != text.Size()) || true;

	strcpy(TextContent, &text[0]);

	Mesh& mesh = MeshList[0];
	unsigned int textSize = strlen(TextContent);//currentText.Size();
	unsigned int amountOfVertices = 4 * textSize;
	mesh.MeshMaterial->Texture = _font->Texture;

	if (!hasTextChanged)
	{
		return; // Text has not changed. No update needed
	}

	if (isDifferentSize)
	{
		mesh.VertexList.DeleteAll();
		mesh.TexturePointList.DeleteAll();
		mesh.IndexList.DeleteAll();

		mesh.VertexList.ReSize(amountOfVertices);
		mesh.TexturePointList.ReSize(amountOfVertices);
		mesh.IndexList.ReSize(amountOfVertices);
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
		char character = TextContent[i];

		if (character == '\0')
		{
			break;
		}

		FNTCharacter* fntCharacter = bitmapFont.GetCharacterPosition(character);

		Vector2<float> xPos;
		Vector2<float> charSize;
		Vector2<float> interpulatedTexturePointXY;
		Vector2<float> interpulatedTexturePoinWidthHeight;

		if (fntCharacter == nullptr)
		{
			xPos.Set(0, 0);
			charSize.Set(50, 75);
			interpulatedTexturePointXY.Set(0, 0);
			interpulatedTexturePoinWidthHeight.Set(1, 1);
		}
		else
		{
			xPos.Set
			(
				fntCharacter->Position[0], 
				fntCharacter->Position[1]			
			);

			charSize.Set
			(				
				fntCharacter->Size[0],
				fntCharacter->Size[1]
			);
			
			interpulatedTexturePointXY.Set
			(
				Interpolate::Normalize(0, 512, fntCharacter->Position[0]),
				Interpolate::Normalize(0, 512, fntCharacter->Position[1])
			);

			interpulatedTexturePoinWidthHeight.Set
			(
				Interpolate::Normalize(0, 512, fntCharacter->Size[0]),
				Interpolate::Normalize(0, 512, fntCharacter->Size[1])
			);
		}

		Rectangle objectPosition
		(
			// Start-Position + ((CharOffset + (Size) + LastPos) * fontSize)
			AncerPosition.X + fontSize * lastPosition,
			AncerPosition.Y + fontSize,
			AncerPosition.X + fontSize * (charSize.X + lastPosition),
			AncerPosition.Y + fontSize * (charSize.Y)
		);

		Rectangle texturePosition
		(
			interpulatedTexturePointXY.X,  // LeftUnder
			interpulatedTexturePointXY.Y, // Right Under
			interpulatedTexturePointXY.X + interpulatedTexturePoinWidthHeight.X, // RightUpepr
			interpulatedTexturePoinWidthHeight.Y + interpulatedTexturePointXY.Y  // Left Upper
		);

		lastPosition += charSize.X + characterSpacingOffset;// +(fntCharacter->XAdvance);

		if (character == ' ')
		{
			lastPosition += characterSpacingOffset * 10;
		}

		//---[Calculate Max-Width and Max-Height]--
		Width += lastPosition;

		if (Height < charSize.Y)
		{
			Height = charSize.Y;
		}
		//-------------------------------------

		// Vertex data (no change do to not pointer?)
		float z = 0;

		mesh.IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh.VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointA.X, objectPosition.PointA.Y, z);
		mesh.TexturePointList[textureIndex++].Set(texturePosition.PointD);// 00

		mesh.IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh.VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointB.X, objectPosition.PointB.Y, z);
		mesh.TexturePointList[textureIndex++].Set(texturePosition.PointC);

		mesh.IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh.VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointC.X, objectPosition.PointC.Y, z);
		mesh.TexturePointList[textureIndex++].Set(texturePosition.PointB); // 11

		mesh.IndexList[faceIndex++].Set(vertexIndex, textureIndex, 0);
		mesh.VertexList[vertexIndex++].CurrentPosition.Set(objectPosition.PointD.X, objectPosition.PointD.Y, z);
		mesh.TexturePointList[textureIndex++].Set(texturePosition.PointA);
	}

	UpdateGlobalMesh();

	ID = ResourceIDLoaded;
}

void BF::UIText::UpdateText()
{
	
}

void BF::UIText::PrintObjectData()
{
	Mesh& mesh = MeshList[0];

	unsigned int vertexIndex = 0;
	unsigned int textureIndex = 0;

	printf(" |   x   |   y   | width   | height  |\n");

	for (unsigned int i = 0; TextContent[i] != '\0'; i++)
	{
		/*
		Rectangle vertexRectangle
		(
			mesh.VertexList[vertexIndex++].CurrentPosition,
			mesh.VertexList[vertexIndex++].CurrentPosition,
			mesh.VertexList[vertexIndex++].CurrentPosition,
			mesh.VertexList[vertexIndex++].CurrentPosition
		);

		Rectangle textureRectangle
		(
			mesh.TexturePointList[textureIndex++],
			mesh.TexturePointList[textureIndex++],
			mesh.TexturePointList[textureIndex++],
			mesh.TexturePointList[textureIndex++]
		);

		printf("A| %5.1f | %5.1f | %1.5f | %1.5f | > Character <%c> %u/%u\n", vertexRectangle.PointA.X, vertexRectangle.PointA.Y, textureRectangle.PointA.X, textureRectangle.PointA.Y, TextContent[i], i, -1);
		printf("B| %5.1f | %5.1f | %1.5f | %1.5f |\n", vertexRectangle.PointB.X, vertexRectangle.PointB.Y, textureRectangle.PointB.X, textureRectangle.PointB.Y);
		printf("C| %5.1f | %5.1f | %1.5f | %1.5f |\n", vertexRectangle.PointC.X, vertexRectangle.PointC.Y, textureRectangle.PointC.X, textureRectangle.PointC.Y);
		printf("D| %5.1f | %5.1f | %1.5f | %1.5f |\n", vertexRectangle.PointD.X, vertexRectangle.PointD.Y, textureRectangle.PointD.X, textureRectangle.PointD.Y);
		printf(" | \n");*/
	}
}
