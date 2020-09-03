#pragma once

#include "../RenderModel.h"
#include "../../Mathematic/Geometry/Shape/Triangle.h"

class TriangleModel : public BF::RenderModel
{
public:
	Triangle Shape;

	TriangleModel();
};