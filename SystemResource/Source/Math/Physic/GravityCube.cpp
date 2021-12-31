#include "GravityCube.h"

#include "../Geometry/Form/Cube.h"

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

bool BF::GravityCube::IsColliding
(
    Vector3<float> ancerPosition,
    Vector3<float> ancerSize,
    Vector3<float> targetPosition,
    Vector3<float> targetSize
)
{
    bool IsPointInObject = Cube::IsPointInObject
    (
        ancerPosition.X,
        ancerPosition.Y,
        ancerPosition.Z,
        ancerSize.X,
        ancerSize.Y,
        ancerSize.Z,
        targetPosition.X,
        targetPosition.Y,
        targetPosition.Z,
        targetSize.X,
        targetSize.Y,
        targetSize.Z
    );

    return IsPointInObject;
}