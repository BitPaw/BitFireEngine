#include "Cube.h"

BF::Cube::Cube()
{
	PositionA.Set(0, 0, 0);
	PositionB.Set(1, 0, 0);
	PositionC.Set(1, 0, 1);
	PositionD.Set(0, 0, 1);

	PositionE.Set(0, 1, 0);
	PositionF.Set(1, 1, 0);
	PositionG.Set(1, 1, 1);
	PositionH.Set(0, 1, 1);
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

BF::List<BF::Point<float>>* BF::Cube::DrawPointList()
{
	List<Point<float>>* drawPointList = new List<Point<float>>(8);

	(*drawPointList)[0].Set(PositionA);
	(*drawPointList)[1].Set(PositionB);
	(*drawPointList)[2].Set(PositionC);
	(*drawPointList)[3].Set(PositionD);


	(*drawPointList)[4].Set(PositionE);
	(*drawPointList)[5].Set(PositionF);
	(*drawPointList)[6].Set(PositionG);
	(*drawPointList)[7].Set(PositionH);

	return drawPointList;
}
