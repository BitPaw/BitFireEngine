#include "Shape.h"

Shape::Shape(const unsigned int cornerPoints)
{
	CornerPoints = cornerPoints;
}


/*
unsigned int counter = CornerPoints;
	unsigned int vertexOffset = 0;

	DrawOrder.push_back(0);
	DrawOrder.push_back(1);
	DrawOrder.push_back(2);

	if (CornerPoints > 3)
	{
		do
		{
			DrawOrder.push_back(0 + vertexOffset);
			DrawOrder.push_back(1 + vertexOffset);
			DrawOrder.push_back(2 + vertexOffset);
			DrawOrder.push_back(2 + vertexOffset);
			DrawOrder.push_back(3 + vertexOffset);
			DrawOrder.push_back(0 + vertexOffset);

			counter -= 1;
		}
		while (counter > 0);
	}
*/