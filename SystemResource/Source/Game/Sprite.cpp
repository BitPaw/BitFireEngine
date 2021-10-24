#include "Sprite.h"
#include "../Math/Geometry/Shape/Rectangle.h"

BF::Sprite::Sprite()
{

}

void BF::Sprite::Set(float x, float y, float z, const char* name, const char* textureFilePath, Model* model)
{
    ShouldItBeRendered = true;

    MatrixModel.Move(x, y, z);
    NameChange(name);    

    Texture.NameChange("<Used Sprite Texture>");
    Texture.FilePathChange(textureFilePath);

    if (model)
    {
        ID = ResourceIDShared;
        SharedModel = model;
    }
}