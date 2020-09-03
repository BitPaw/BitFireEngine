#include "Shape.h"

Shape::Shape(const unsigned int cornerPoints, const unsigned int drawOrderSteps)
{
	CornerPoints = cornerPoints;
	DrawOrderSteps = drawOrderSteps;
}

void Shape::CalculateDrawOrder()
{
	return;

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
}

unsigned int Shape::GetCornerPointsAmout()
{ 
	return CornerPoints; 
}

unsigned int Shape::GetDrawOrderStepsAmout()
{ 
	return DrawOrderSteps; 
}

std::vector<unsigned int>* Shape::GetDrawOrderSteps()
{
	return &DrawOrder;
}
