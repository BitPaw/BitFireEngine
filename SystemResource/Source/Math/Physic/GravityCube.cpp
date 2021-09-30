#include "GravityCube.h"

bool BF::GravityCube::IsColliding(Vector2<float> position)
{
    return false;
}

bool BF::GravityCube::IsColliding(Vector3<float> position)
{
    float x = IgnoreAxisX ? INFINITY : position.X;
    float y = IgnoreAxisY ? INFINITY : position.Y;
    float z = IgnoreAxisZ ? INFINITY : position.Z;

    return IsPointInObject(x, y, z);
}
