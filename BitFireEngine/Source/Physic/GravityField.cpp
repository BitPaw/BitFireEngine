#include "GravityField.h"

BF::GravityField::GravityField() : Collider(ColliderType::Gravity)
{
	PullForce = 0;
}