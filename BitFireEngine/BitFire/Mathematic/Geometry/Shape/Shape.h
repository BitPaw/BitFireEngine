#pragma once

#include <vector>

class Shape
{
protected:
	Shape(const unsigned int cornerPoints, const unsigned int drawOrderSteps);

	unsigned int CornerPoints;
	unsigned int DrawOrderSteps;
	std::vector<unsigned int> DrawOrder;

	void CalculateDrawOrder();

public:
	unsigned int GetCornerPointsAmout();
	unsigned int GetDrawOrderStepsAmout();
	std::vector<unsigned int>* GetDrawOrderSteps();

	virtual void Reset() = 0;
};