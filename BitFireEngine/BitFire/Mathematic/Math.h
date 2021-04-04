#pragma once

#define PI 3.1415926535897932384626433832 	// Pi, Archimedes' constant or Ludolph's number

namespace BF
{
	class Math
	{
		private:
		static bool _timerSet;

		public:

		// e, Napier's constant, or Euler's number
		static const float e;

		// Plastic constant
		static const float p;

		// Feigenbaum constant
		static const float a;

		// gravitational constant. 6.673�10^-11 N m2 kg^-2
		static const float g;

		// All in m/s^2
		static const float GravityOnVenus;
		static const float GravityOnEarth;
		static const float GravityOnMoon;
		static const float GravityOnMars;

		static float FastInverseSqaureRoot(float number);
		
		static double Power(double base, double exponent);
		static double PowerOfTwo(double base);

		static double Root(unsigned int rootNr, double value);

		static double SquareRoot(double value);

		static double CubicRoot(double value);

		static double Pythagoras(double a, double b);
		static double PythagorasReverse(double c, double a);
		
		static double Logarithmus(int base, double exponent);
		static double LogarithmusBase2(double exponent);
		static double LogarithmusBase10(double exponent);

		static double NewtonGravitation(double massA, double massB, double distance);

		// Rounds x upward, returning the smallest integral value that is not less than x.
		static int Ceiling(double value);

		// Rounds x downward, returning the largest integral value that is not greater than x.
		static int Floor(double value);

		static int Absolute(int value);
		static float Absolute(float value);
		static double Absolute(double value);

		static unsigned int RandomeNumber();



		static double Sinus(double value);
		static double Tangens(double value);
		static double Cosinus(double value);
		static unsigned long Fibonacci(unsigned long step);


		static double RadiansToDegree(double radians);
		static double DegreeToRadians(double degree);
	};
}