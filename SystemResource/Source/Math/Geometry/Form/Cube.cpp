#include "Cube.h"
#include <float.h>
#include <cmath>

float BF::Cube::Volume()
{
	return 0.0f;
}

float BF::Cube::SurfaceArea()
{
	return 0.0f;
}

float BF::Cube::Perimeter()
{
	return 0.0f;
}

bool BF::Cube::IsPointInObject(float x, float y, float z)
{
	if ((-1.0f <= x && x <= 1.0f) || x == INFINITY)
	{
		if ((-1.0f <= z && z <= 1.0f) || z == INFINITY)
		{
			if ((-1.0f <= y && y <= 1.0f) || y == INFINITY)
			{
				return true;
			}
		}
	}

	return false;
}
