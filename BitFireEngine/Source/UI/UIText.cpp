#include "UIText.h"

#include <File/Format/FNT/FNT.h>
#include <Math/Interpolate.h>
#include <Text/Text.h>

void BF::UIText::Setup(const wchar_t* text, CFont* font, float x, float y)
{
	AncerPosition.Set(x, y);
	Width = 0;
	Height = 0;

	//Text::Copy(Name, "<Internal Text>", ResourceNameSize);

	MeshListSize = 1;
	MeshList = new Mesh[1];

	Mesh& mesh = MeshList[0];
	//mesh.Structure.RenderType = RenderMode::Square;
	//mesh.Structure.RenderType = RenderMode::Square;

	//strcpy(mesh.Name, "<Text-Mesh>");
	//strcpy(mesh.FilePath, "<Internal>");

	FontSet(*font);
	TextSet(text);
	TextPositionSet(x, y);
}

BF::UIText::UIText()
{
	Setup(L"-----------------------", nullptr, 0, 0);
}

void BF::UIText::FontSet(CFont& font)
{
	_font = &font;
}

void BF::UIText::TextPositionSet(float x, float y)
{
	float offset = 1;

	x = Interpolate::Liniar(-Width* offset, Width* offset, -1, 1, x);
	y = Interpolate::Liniar(-Height* offset, Height* offset, -1, 1, y);

	//MatrixModel.MoveTo(x- Width, y- Height, 0);
}

void BF::UIText::TextSet(const char* text)
{
	if (!text)
	{
		return;
	}

	TextSizeCurrent = TextCopyAW(text, TextSizeMax, TextContent, TextSizeMax);
}

void BF::UIText::TextSet(const wchar_t* text)
{
	if (!text)
	{
		return;
	}

	TextSizeCurrent = TextCopyW(text, TextSizeMax, TextContent, TextSizeMax);
}

void BF::UIText::TextUpdate()
{
	FNT& bitmapFont = *((FNT*)(_font->BitMapFont));

#if 0 // Print font data
	bitmapFont.PrintData();
#endif
	/*

	bool hasTextChanged = true;// Text::Compare(TextContent);
	//bool isDifferentSize = true;// (currentText.Size() != text.Size()) || true;

	Mesh & mesh = MeshList[0];
	unsigned int textSize = TextSizeCurrent; //strlen(TextContent);//currentText.Size();

	MaterialListSize = 1;
	MaterialList = new Material();
	MaterialList->Texture = this->_font->Texture;

	Image& image = *MaterialList->Texture;

	mesh.RenderInfo.MaterialID = 0;

	//mesh.MeshMaterial->Texture = _font->Texture;
	bool isDifferentSize = (mesh.Structure.IndexDataSize / 4) < TextSizeCurrent;

	if (!hasTextChanged)
	{
		return; // Text has not changed. No update needed
	}

	if (isDifferentSize)
	{
		//mesh.VertexList.DeleteAll();
		//mesh.TexturePointList.DeleteAll();
	//	mesh.IndexList.DeleteAll();

		size_t indexDataSize = 4 * textSize;
		size_t amountOfVertices = indexDataSize * (3+3+4+2);

		mesh.Structure.Allocate(amountOfVertices, indexDataSize);



		//mesh.VertexList.ReSize(amountOfVertices);
		//mesh.TexturePointList.ReSize(amountOfVertices);
	//	mesh.IndexList.ReSize(amountOfVertices);
	}



	// Put Data
	unsigned int characterSpacingOffset = 1;
	float fontSize = 0.002;
	float lastPosition = 0;
	size_t vertexIndex = 0;

	// Fill IndexData
	{
		unsigned int* indexData = mesh.Structure.IndexData;
		size_t faceIndex = 0;

		for (size_t i = 0; i < mesh.Structure.IndexDataSize; i++)
		{
			indexData[faceIndex++] = i;
		}
	}

	for (size_t i = 0; (i < textSize) && (TextContent[i] != '\0'); i++)
	{
		const wchar_t character = TextContent[i];
		const FNTCharacter* fntCharacter = bitmapFont.GetCharacterPosition(character);
		float characterOffsetX = 0;
		float characterOffsetY = 0;
		Vector2<float> xPos;
		Vector2<float> charSize;
		Vector2<float> interpulatedTexturePointXY;
		Vector2<float> interpulatedTexturePoinWidthHeight;
		Rectangle objectPosition;
		Rectangle texturePosition;

		if (fntCharacter)
		{
			characterOffsetX = fntCharacter->Offset[0];
			characterOffsetY = fntCharacter->Offset[1];

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
				Interpolate::Normalize(0, image.Width, fntCharacter->Position[0]),
				Interpolate::Normalize(0, image.Height, fntCharacter->Position[1])
			);

			interpulatedTexturePoinWidthHeight.Set
			(
				Interpolate::Normalize(0, image.Width, fntCharacter->Size[0]),
				Interpolate::Normalize(0, image.Height, fntCharacter->Size[1])
			);


			objectPosition.Set
			(
				// Start-Position + ((CharOffset + (Size) + LastPos) * fontSize)
				AncerPosition.X + fontSize * (-characterOffsetX + lastPosition),
				AncerPosition.Y + fontSize * (-characterOffsetY),
				AncerPosition.X + fontSize * (-characterOffsetX + charSize.X + lastPosition),
				AncerPosition.Y + fontSize * (-characterOffsetY + charSize.Y)
			);

			texturePosition.Set
			(
				interpulatedTexturePointXY.X,  // LeftUnder
				interpulatedTexturePointXY.Y, // Right Under
				interpulatedTexturePointXY.X + interpulatedTexturePoinWidthHeight.X, // RightUpepr
				interpulatedTexturePoinWidthHeight.Y + interpulatedTexturePointXY.Y  // Left Upper
			);

		}
		else
		{
			xPos.Set(0, 0);
			charSize.Set(50, 75);
			interpulatedTexturePointXY.Set(0, 0);
			interpulatedTexturePoinWidthHeight.Set(1, 1);
		}

		lastPosition += charSize.X + (float)characterSpacingOffset;// +(fntCharacter->XAdvance);

		if (character == ' ')
		{
			lastPosition += (float)(characterSpacingOffset * 10);
		}

		//---[Calculate Max-Width and Max-Height]--
		Width += lastPosition;

		if (Height < charSize.Y)
		{
			Height = charSize.Y;
		}
		//-------------------------------------

		/*
		if (true)
		{
			continue;
		}* /

		// Flip Y Axis because the fileformat is like this
		{
			Vector2<float> positionUnswapped = texturePosition.Position;
			Vector2<float> sizeUnswapped = texturePosition.Size;

			float overflowOffset = 0.000f;

			texturePosition.Position.Set(positionUnswapped.X  + overflowOffset, sizeUnswapped.Y - overflowOffset);
			texturePosition.Size.Set(sizeUnswapped.X + overflowOffset,positionUnswapped.Y + overflowOffset);
		}

		// FillData
		{
			const Vector3<float> normal(0, 0, -1);
			const Vector4<float> color(1, 1, 1, 1);

			size_t textureIndex = 0;
			float* vertexData = mesh.Structure.VertexData;
			const float z = 0;

			vertexData[vertexIndex++] = objectPosition.Position.X; // (objectPosition.PointA.X, objectPosition.PointA.Y, z);
			vertexData[vertexIndex++] = objectPosition.Position.Y;
			vertexData[vertexIndex++] = z;
			vertexData[vertexIndex++] = normal.X;
			vertexData[vertexIndex++] = normal.Y;
			vertexData[vertexIndex++] = normal.Z;
			vertexData[vertexIndex++] = 1;
			vertexData[vertexIndex++] = 0;
			vertexData[vertexIndex++] = 0;
			vertexData[vertexIndex++] = color.W;
			vertexData[vertexIndex++] = texturePosition.Position.X;
			vertexData[vertexIndex++] = texturePosition.Position.Y; // texturePosition.PointD);// 00


			vertexData[vertexIndex++] = objectPosition.Size.X; //et(objectPosition.PointB.X, objectPosition.PointB.Y, z);
			vertexData[vertexIndex++] = objectPosition.Position.Y;
			vertexData[vertexIndex++] = z;
			vertexData[vertexIndex++] = normal.X;
			vertexData[vertexIndex++] = normal.Y;
			vertexData[vertexIndex++] = normal.Z;
			vertexData[vertexIndex++] = 1;
			vertexData[vertexIndex++] = 1;
			vertexData[vertexIndex++] = 0;
			vertexData[vertexIndex++] = color.W;
			vertexData[vertexIndex++] = texturePosition.Size.X;
			vertexData[vertexIndex++] = texturePosition.Position.Y; //t(texturePosition.PointC);


			vertexData[vertexIndex++] = objectPosition.Size.X; // (objectPosition.PointC.X, objectPosition.PointC.Y, z);
			vertexData[vertexIndex++] = objectPosition.Size.Y;
			vertexData[vertexIndex++] = z;
			vertexData[vertexIndex++] = normal.X;
			vertexData[vertexIndex++] = normal.Y;
			vertexData[vertexIndex++] = normal.Z;
			vertexData[vertexIndex++] = 0;
			vertexData[vertexIndex++] = color.Y;
			vertexData[vertexIndex++] = 0;
			vertexData[vertexIndex++] = color.W;
			vertexData[vertexIndex++] = texturePosition.Size.X;
			vertexData[vertexIndex++] = texturePosition.Size.Y; // (texturePosition.PointB); // 11


			vertexData[vertexIndex++] = objectPosition.Position.X; // t(objectPosition.PointD.X, objectPosition.PointD.Y, z);
			vertexData[vertexIndex++] = objectPosition.Size.Y;
			vertexData[vertexIndex++] = z;
			vertexData[vertexIndex++] = normal.X;
			vertexData[vertexIndex++] = normal.Y;
			vertexData[vertexIndex++] = normal.Z;
			vertexData[vertexIndex++] = 0;
			vertexData[vertexIndex++] = 0;
			vertexData[vertexIndex++] = color.Z;
			vertexData[vertexIndex++] = color.W;
			vertexData[vertexIndex++] = texturePosition.Position.X;
			vertexData[vertexIndex++] = texturePosition.Size.Y; // texturePosition.PointA);
		}
	}*/
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
