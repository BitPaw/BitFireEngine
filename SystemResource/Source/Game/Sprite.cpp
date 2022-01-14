#include "Sprite.h"
#include "../Math/Geometry/Shape/Rectangle.h"

BF::Sprite::Sprite()
{
    TextureScaleSet(1,1);
}

void BF::Sprite::TextureScaleSet(float x, float y)
{
    TextureScale[0] = x;
    TextureScale[1] = y;
}

void BF::Sprite::Set(float x, float y, float z, const char* name, const char* textureFilePath, Model* model)
{
    ShouldItBeRendered = true;

    MatrixModel.Move(x, y, z);
    NameChange(name);    

    MaterialListSize = 1;
    MaterialList = new Material();

    Material& material = MaterialList[0];
    Image* image = new Image();
    image->NameChange("<Used Sprite Texture>");
    image->FilePathChange(textureFilePath);
    image->ImageWrapSet(ImageWrap::StrechEdges);

    material.Texture = image;

    if (model)
    {
        ID = ResourceIDShared;
        SharedModel = model;
    }
}