#include "Shape.h"

Shape::Shape(const unsigned int cornerPoints, const unsigned int drawOrderSteps)
{
	CornerPoints = cornerPoints;
	DrawOrderSteps = drawOrderSteps;
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
