#ifndef MathInclude
#define MathInclude

#include <stddef.h>

#define MathConstantPI 3.1415926535897932384626433832 	// Pi, Archimedes' constant or Ludolph's number
#define MathConstantE 2.71828182845904523536028747135266249
#define MathConstantP 1.32471795724474602596090885447809734
#define MathConstantA 2.50290787509589282228390287321821578
#define MathConstantGravity 0.00000000006673

#define GravityOnVenus 8.87
#define GravityOnEarth 9.807
#define GravityOnMoon 1.62
#define GravityOnMars 3.711


#define MathMinimum(a, b) (a <= b ? a : b)
#define MathMaximum(a, b) (a >= b ? a : b)
#define MathFloor(a) ((int)(a))
//#define MathCeiling(a)
#define MathAbsolute(a) (a < 0 ? -a : a)

// Limit v between minimum and maximum
#define MathLimit(v, min, max)  (min*(v <= min) + max*(v >= max) + v *((v > min) && (v < max)));

#ifdef __cplusplus
extern "C"
{
#endif
	extern int MathMinimumI(const int a, const int b);
	extern double MathMinimumD(const double a, const double b);

	extern int MathFloorI(const int a);
	extern int MathFloorD(const double a);

	extern size_t MathAbsoluteI(const int value);
	extern double MathAbsoluteD(const double value);


	extern char MathLimitC(const char value, const char minimum, const char maximum);
	extern unsigned char MathLimitCU(const unsigned char  value, const unsigned char  minimum, const unsigned char maximum);
	extern int MathLimitI(const int value, const int minimum, const int maximum);

	extern float MathFastInverseSqaureRoot(float number);
	extern double MathPower(double base, double exponent);
	extern double MathPowerOfTwo(double base);
	extern unsigned int MathPowerModulo(unsigned int base, unsigned int exponent, unsigned int modulo);
	extern double MathRoot(unsigned int rootNr, double value);
	extern double MathSquareRoot(double value);
	extern double MathCubicRoot(double value);
	extern double MathPythagoras(double a, double b);
	extern double MathPythagorasReverse(double c, double a);
	extern double MathLogarithmus(int base, double exponent);
	extern double MathLogarithmusBase2(double exponent);
	extern double MathLogarithmusBase10(double exponent);
	extern double MathNewtonGravitation(double massA, double massB, double distance);
	extern int MathCeiling(const double value);
	extern unsigned int MathRandomeNumber();
	extern double MathSinus(double value);
	extern double MathTangens(double value);
	extern double MathCosinus(double value);
	extern unsigned long MathFibonacci(unsigned long step);
	extern double MathRadiansToDegree(double radians);
	extern double MathDegreeToRadians(double degree);

#ifdef __cplusplus
}
#endif

#endif
