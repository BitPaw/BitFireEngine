#include "Math.h"

int BF::Math::Ceiling(double value)
{
	int integerValue = static_cast<int>(value);
	double checkValue = static_cast<double>(integerValue);
	bool isSameValue = checkValue == value;

	integerValue += (1 * isSameValue);

	return integerValue;
}

int BF::Math::Floor(double value)
{
	return static_cast<int>(value);
}