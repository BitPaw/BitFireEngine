#include "Math.h"

#include <math.h>

float MathFastInverseSqaureRoot(float number)
{
	const float threehalfs = 1.5f;
	float x2 = number * 0.5f;
	float y = number;
	long i;

	i = *(long*)&y; // Convert the Binary Value from a float to an long. No conversion! A 1:1 Bitcopy. IEEE 574 standard
	i = 0x5f3759df - (i >> 1); // .The bit shift Halfs i. AProximation of (1/root(y))
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	// last line can be repeatet for more acuratecy.

	return y;
}

double MathPower(double base, double exponent)
{
	return pow(base, exponent);
}

double MathPowerOfTwo(double base)
{
	return MathPower(base, 2);
}

unsigned int MathPowerModulo(unsigned int base, unsigned int exponent, unsigned int modulo)
{
	unsigned int result = 1;
	for(int i = 0; i < exponent; i++)
	{
		result *= base;
		result %= modulo;
	}
	return result;
}

double MathRoot(unsigned int rootNr, double value)
{
	switch(rootNr)
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

double MathSquareRoot(double value)
{
	return MathRoot(2, value);
}

double MathCubicRoot(double value)
{
	return MathRoot(3, value);
}

double MathPythagoras(double a, double b)
{
	return MathSquareRoot(MathPowerOfTwo(a) + MathPowerOfTwo(b));
}

double MathPythagorasReverse(double c, double a)
{
	return 0.0;
}

double MathLogarithmus(int base, double exponent)
{
#if defined(OSUnix)
	return 0; // TODO: not implemented?
#elif defined(OSWindows)
	return _dlog(exponent, base);
#endif	
}

double MathLogarithmusBase2(double exponent)
{
	return log2(exponent);
}

double MathLogarithmusBase10(double exponent)
{
	return log10(exponent);
}

double MathNewtonGravitation(double massA, double massB, double distance)
{
	return MathConstantGravity * ((massA * massB) / (MathPower(distance, 2)));
}

int MathCeiling(const double value)
{
	return 0;
}

unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned int MathRandomeNumber()
{
	unsigned long t;

	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}

double MathSinus(double value)
{
	return sin(value);
}

double MathTangens(double value)
{
	return tan(value);
}

double MathCosinus(double value)
{
	return cos(value);
}

unsigned long MathFibonacci(unsigned long step)
{
	double rootOfFive = MathSquareRoot(5);

	if(step < 2)
	{
		return step;
	}
	else
	{
		// (1 + W/5)^n - (1 - W/5)^n 
		// -------------------------
		//         2^n * W/5

		double a = MathPower(1 + rootOfFive, step);
		double b = MathPower(1 - rootOfFive, step);
		double c = MathPower(2, step) * rootOfFive;

		return ((a - b) / c);

		// return FibonacciRetardVersion(step -1) + FibonacciRetardVersion(step -2); Recusive version
	}
}

double MathRadiansToDegree(double radians)
{
	return radians * (180.0 / MathConstantPI);
}

double MathDegreeToRadians(double degree)
{
	return degree * (MathConstantPI / 180.0);
}