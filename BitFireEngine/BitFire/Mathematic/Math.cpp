#include "Math.h"


#include <math.h>
#include <cstdlib>
#include <ctime>

#include "Interpolate.h"

bool BF::Math::_timerSet = false;


const float BF::Math::PI = 3.1415926535897932384626433832795028841971693993751058209749445923;
const float BF::Math::e = 2.71828182845904523536028747135266249;
const float BF::Math::p = 1.32471795724474602596090885447809734;
const float BF::Math::a = 2.50290787509589282228390287321821578;
const float BF::Math::g = 0.00000000006673;

const float BF::Math::GravityOnVenus = 8.87;
const float BF::Math::GravityOnEarth = 9.807;
const float BF::Math::GravityOnMoon = 1.62;
const float BF::Math::GravityOnMars = 3.711;


int BF::Math::Ceiling(double value)
{
	int integerValue = static_cast<int>(value);
	double checkValue = static_cast<double>(integerValue);
	bool isDifferentValue = checkValue != value;

	integerValue += (1 * isDifferentValue);

	return integerValue;
}

int BF::Math::Floor(double value)
{
	return static_cast<int>(value);
}

int BF::Math::Absolute(int value)
{
	return value < 0 ? -value : value;
}

float BF::Math::Absolute(float value)
{
	return value < 0 ? -value : value;
}

double BF::Math::Absolute(double value)
{
	return value < 0 ? -value : value;
}

unsigned int BF::Math::RandomeNumber()
{
	if (!_timerSet)
	{
		srand(time(nullptr));
		_timerSet = true;
	}

	return std::rand();
}

double BF::Math::Sinus(double value)
{
	return sin(value);
}

double BF::Math::Tangens(double value)
{
	return tan(value);
}

double BF::Math::Cosinus(double value)
{
	return cos(value);
}

unsigned long BF::Math::Fibonacci(unsigned long step)
{
	double rootOfFive = SquareRoot(5);

	if (step < 2)
	{
		return step;
	}
	else
	{
		// (1 + W/5)^n - (1 - W/5)^n 
		// -------------------------
		//         2^n * W/5

		double a = Power(1 + rootOfFive, step);
		double b = Power(1 - rootOfFive, step);
		double c = Power(2, step) * rootOfFive;
		
		return static_cast<unsigned long>((a - b) / c);

		// return FibonacciRetardVersion(step -1) + FibonacciRetardVersion(step -2); Recusive version
	}
}

float BF::Math::FastInverseSqaureRoot(float number)
{
	const float threehalfs = 1.5f;
	float x2 = number * 0.5f;
	float y = number;
	long i;

	i = *(long*) & y; // Convert the Binary Value from a float to an long. No conversion! A 1:1 Bitcopy. IEEE 574 standard
	i = 0x5f3759df - (i >> 1); // .The bit shift Halfs i. AProximation of (1/root(y))
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	// last line can be repeatet for more acuratecy.

	return y;
}

double BF::Math::Power(double base, double exponent)
{
	return pow(base, exponent);
}

double BF::Math::PowerOfTwo(double base)
{
	return Power(base, 2);
}

double BF::Math::Root(unsigned int rootNr, double value)
{
	switch (rootNr)
	{
		case 0:
			return 0;

		case 1:
			return 0;

		case 2:
			return sqrt(value);

		case 3:
			return cbrt(value);

		default:
			return 0;
	}
}

double BF::Math::SquareRoot(double value)
{
	return Root(2, value);
}

double BF::Math::CubicRoot(double value)
{
	return Root(3, value);
}

double BF::Math::Pythagoras(double a, double b)
{
	return SquareRoot(PowerOfTwo(a) + PowerOfTwo(b));
}

double BF::Math::PythagorasReverse(double biggestSide, double smalerSide)
{
	return SquareRoot(PowerOfTwo(biggestSide) - PowerOfTwo(smalerSide));
}

double BF::Math::NewtonGravitation(double massA, double massB, double distance)
{
	return g * ((massA * massB) / (Power(distance, 2)));
}