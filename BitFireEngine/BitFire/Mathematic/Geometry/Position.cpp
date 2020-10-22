#include "Position.h"

BF::Position::Position() : Position(0, 0, 0)
{

}

BF::Position::Position(BF::Point point) : BF::Position(point.X, point.Y, 0)
{

}

BF::Position::Position(const float x, const float y) : Position(x, y, 0)
{

}

BF::Position::Position(const float x, const float y, const float z) : Point(x, y)
{
	Z = z;
}

void BF::Position::Change(Position point)
{
	//X = abs(X - point.X);
	//Y = abs(Y - point.Y);
	//Z = abs(Z - point.Z);
}

void BF::Position::Change(const float x, const float y, const float z)
{
	X = x;
	Y = y;
	Z = z;
}
