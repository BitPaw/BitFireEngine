#include "RenderObject.h"


RenderObject::RenderObject() : RenderObject("[N/A]",nullptr)
{

}

RenderObject::RenderObject(const char* name, Mesh* mesh)
{
    Name = name;

    if (mesh == nullptr)
    {
        _mesh = new Mesh();
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

void RenderObject::SetName(const char* name)
{
    Name = name;
}