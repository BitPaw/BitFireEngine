#pragma once



#include <math.h>
#include <cstdlib>
#include <ctime>

#include "Interpolate.h"

namespace BF
{
	class Math
	{
	private:
		static bool _timerSet;

	public:
		// Pi, Archimedes' constant or Ludolph's number
		const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923;

		// e, Napier's constant, or Euler's number
		const float e = 2.71828182845904523536028747135266249;

		// Plastic constant
		const float p = 1.32471795724474602596090885447809734;

		// Feigenbaum constant
		const float a = 2.50290787509589282228390287321821578;

		// gravitational constant. 6.673×10^-11 N m2 kg^-2
		const float g = 0.00000000006673;

		// All in m/s^2
		const float GravityOnVenus = 8.87;
		const float GravityOnEarth = 9.807;
		const float GravityOnMoon = 1.62;
		const float GravityOnMars = 3.711;

		float Power(float base, float exponent)
		{
			return powf(base, exponent);
		}

		float Root(float value, float rootOf)
		{
			return 0;
		}

		float Pythagoras(float a, float b)
		{
			return Root(Power(a, 2) + Power(b, 2), 2);
		}

		float NewtonGravitation(float massA, float massB, float distance)
		{
			return g * ((massA * massB) / (Power(distance, 2)));
		}

		// Rounds x upward, returning the smallest integral value that is not less than x.
		static int Ceiling(double value);

		// Rounds x downward, returning the largest integral value that is not greater than x.
		static int Floor(double value);

		static int RandomeNumber();
	};
}