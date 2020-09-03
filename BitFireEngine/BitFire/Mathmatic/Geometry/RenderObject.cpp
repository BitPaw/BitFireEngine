#include "RenderObject.h"

RenderObject::RenderObject() : RenderObject(nullptr)
{

}

RenderObject::RenderObject(Mesh* mesh)
{
    if (mesh == nullptr)
    {
        mesh = new Mesh();
    }
    else
    {
        _mesh = mesh;
    }
}

RenderObject::~RenderObject()
{
    delete _mesh;
}
/*
Mesh RenderObject::GetRenderMesh()
{
   // Mesh mesh(this);

    return mesh;
}*/
