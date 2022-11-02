#include "Collider.h"

BF::Collider::Collider(ColliderType type)
{
	Type = type;
    OnCollisionCallBack = nullptr;
}

bool BF::Collider::IsInBoundingBox(PXVector3F ancerPosition, PXVector3F ancerSize, PXVector3F targetPosition, PXVector3F targetSize)
{
    bool IsPointInObject = 0;/*;Cube::IsPointInObject
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
    );*/

    return IsPointInObject;
}
