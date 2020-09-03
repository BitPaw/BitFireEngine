#include "Position.h"

Position::Position() : Position(0, 0, 0)
{

}

Position::Position(Point point) : Position(point.X, point.Y, 0)
{
}

Position::Position(const float x, const float y) : Position(x, y, 0)
{

}

Position::Position(const float x, const float y, const float z) : Point(x, y)
{
	Z = z;
}
