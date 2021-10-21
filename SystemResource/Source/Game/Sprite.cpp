#include "Sprite.h"

BF::Sprite::Sprite()
{

}

void BF::Sprite::Set(float x, float y, float z, const char* name, const char* textureFilePath, Model* model)
{
    ID = ResourceIDShared;
    ShouldItBeRendered = true;
    SharedModel = model;
    MatrixModel.Move(x, y, z);
    NameChange(name);    

    Texture.NameChange("<Used Sprite Texture>");
    Texture.FilePathChange(textureFilePath);
}