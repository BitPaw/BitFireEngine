#include "GravityField.h"

BF::GravityField::GravityField() : Collider(ColliderType::Gravity)
{
	IgnoreAxisX = false;
	IgnoreAxisY = false;
	IgnoreAxisZ = false;
}

void BF::GravityField::IgnoreAxis(bool x, bool y, bool z)
{
	IgnoreAxisX = x;
	IgnoreAxisY = y;
	IgnoreAxisZ = z;
}