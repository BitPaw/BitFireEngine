#include "GravityCube.h"

#include "../Geometry/Form/Cube.h"

#include <cassert>

bool BF::GravityCube::IsColliding(Vector2<float> position)
{
    return false;
}

bool BF::GravityCube::IsColliding(Vector3<float> position)
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
    assert(false);

    return true;
}