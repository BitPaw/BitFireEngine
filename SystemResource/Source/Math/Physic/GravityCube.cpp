#include "GravityCube.h"

bool BF::GravityCube::IsColliding(Vector2<float> position)
{
    return false;
}

bool BF::GravityCube::IsColliding(Vector3<float> position)
{
    float x = IgnoreAxis.X ? INFINITY : position.X;
    float y = IgnoreAxis.Y ? INFINITY : position.Y;
    float z = IgnoreAxis.Z ? INFINITY : position.Z;

    return IsPointInObject(x, y, z);
}
