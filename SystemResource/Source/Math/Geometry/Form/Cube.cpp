#include "Cube.h"
#include <string.h>
#include <cmath>

BF::Cube::Cube()
{
	float vertexData[] =
	{
		 1,  1,  1,
		-1,  1,  1,
		 1, -1,  1,
		-1, -1,  1,
		 1,  1, -1,
		-1,  1, -1,
		 1, -1, -1,
		-1, -1, -1,
	};

	unsigned int indexList[] =
	{
		0,1,3,2, // Left OK
		6,7,5,4, // Right  OK
		4,5,1,0, // Top OK
		2,3,7,6, // Bot OK
		0,2,6,4, // Front OK
		5,7,3,1 // Back OK
	};
	
	memcpy(VertexList, vertexData, VertexListSize * sizeof(float));
	memcpy(IndexList, indexList, IndexListSize * sizeof(unsigned int));
}

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

bool IsInLinar(float min, float max, float targetMin, float tagetMax)
{
	return (min - tagetMax) <= targetMin && (targetMin + tagetMax) <= (min+max);
}

bool BF::Cube::IsPointInObject
(
	float ancerPositionX,
	float ancerPositionY,
	float ancerPositionZ,
	float ancerSizeX, 
	float ancerSizeY,
	float ancerSizeZ,
	float targetPositionX, 
	float targetPositionY,
	float targetPositionZ,
	float targetSizeX,
	float targetSizeY,
	float targetSizeZ
)
{
	bool isInX = targetSizeX == INFINITY || IsInLinar(ancerPositionX, ancerSizeX, targetPositionX, targetSizeX);
	bool isInY = targetSizeY == INFINITY || IsInLinar(ancerPositionY, ancerSizeY, targetPositionY, targetSizeY);
	bool isInZ = targetSizeZ == INFINITY || IsInLinar(ancerPositionZ, ancerSizeZ, targetPositionZ, targetSizeZ);

	return isInX && isInY && isInZ;
}
