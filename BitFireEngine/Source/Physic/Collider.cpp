#include "Collider.h"

#include <Math/Geometry/Form/Cube.h>

BF::Collider::Collider(ColliderType type)
{
	Type = type;
    OnCollisionCallBack = nullptr;
}

bool BF::Collider::IsInBoundingBox(Vector3<float> ancerPosition, Vector3<float> ancerSize, Vector3<float> targetPosition, Vector3<float> targetSize)
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
