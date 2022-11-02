#include "GravityCube.h"

bool BF::GravityCube::IsColliding(PXVector2F* const  position)
{
    return false;
}

bool BF::GravityCube::IsColliding(PXVector3F* const position)
{
    /*
    bool IsPointInObject = Cube::IsPointInObject
    (
        BoundingBox.Position.X,
        BoundingBox.Position.Y,
        0,
        BoundingBox.Position.X - BoundingBox.Size.X,
        BoundingBox.Size.Y,
        0,
        position.X, 
        position.Y,
        INFINITY
    );*/
    //assert(false);

    return true;
}