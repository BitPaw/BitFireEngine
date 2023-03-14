#ifndef PXMathInclude
#define PXMathInclude

#include <Format/Type.h>

#define MathConstantPI 3.1415926535897932384626433832 	// Pi, Archimedes' constant or Ludolph's number
#define MathConstantE 2.71828182845904523536028747135266249
#define MathConstantP 1.32471795724474602596090885447809734
#define MathConstantA 2.50290787509589282228390287321821578
#define MathConstantGravity 0.00000000006673

#define GravityOnVenus 8.87
#define GravityOnEarth 9.807
#define GravityOnMoon 1.62
#define GravityOnMars 3.711

#define MathMinimum(a, b) ((a < b) * a + (a >= b) * b)
#define MathMaximum(a, b) ((a > b) * a + (a <= b) * b)
//#define MathLimit(x, low, high) (MathMinimum(MathMaximum(x, low), high)) 
#define MathLimit(x, low, high)  (low*(x <= low) + high*(x >= high) + x *((x > low) && (x < high)))

#define MathFloor(a) ((int)(a))
//#define MathCeiling(a)
#define MathAbsolute(a) (a * ((a >= 0) - (a < 0)))


#ifdef __cplusplus
extern "C"
{
#endif
	PXPublic int MathMinimumI(const int a, const int b);
	PXPublic PXSize MathMinimumIU(const PXSize a, const PXSize b);
	PXPublic double MathMinimumD(const double a, const double b);

	PXPublic int MathFloorI(const int a);
	PXPublic int MathFloorD(const double a);

	PXPublic PXSize MathAbsoluteI(const int value);
	PXPublic double MathAbsoluteD(const double value);


	PXPublic char MathLimitC(const char value, const char minimum, const char maximum);
	PXPublic unsigned char MathLimitCU(const unsigned char  value, const unsigned char  minimum, const unsigned char maximum);
	PXPublic int MathLimitI(const int value, const int minimum, const int maximum);
	PXPublic PXSize MathLimitIU(const PXSize value, const PXSize minimum, const PXSize maximum);

	PXPublic float MathFastInverseSqaureRoot(float number);
	PXPublic double MathPower(double base, double exponent);
	PXPublic double MathPowerOfTwo(double base);
	PXPublic unsigned int MathPowerModulo(unsigned int base, unsigned int exponent, unsigned int modulo);
	PXPublic double MathRoot(unsigned int rootNr, double value);
	PXPublic double MathSquareRoot(double value);
	PXPublic double MathCubicRoot(double value);
	PXPublic double MathPythagoras(double a, double b);
	PXPublic double MathPythagorasReverse(double c, double a);
	PXPublic double MathLogarithmus(int base, double exponent);
	PXPublic double MathLogarithmusBase2(double exponent);
	PXPublic double MathLogarithmusBase10(double exponent);
	PXPublic double MathNewtonGravitation(double massA, double massB, double distance);
	PXPublic int MathCeilingF(const float value);
	PXPublic int MathCeilingD(const double value);
	PXPublic unsigned int MathRandomeNumber();
	PXPublic double MathSinus(double value);
	PXPublic double MathTangens(double value);
	PXPublic double MathCosinus(double value);
	PXPublic unsigned long MathFibonacci(unsigned long step);
	PXPublic double MathRadiansToDegree(double radians);
	PXPublic double MathDegreeToRadians(double degree);

	PXPublic float MathLiniarF(const float yMinimum, const float yMaximum, const float xMinimum, const float xMaximum, const float xValue);
	PXPublic float MathNormalizeF(const float minimum, const float maximum, const float value);
	PXPublic unsigned int MathLiniarClampAsRGBColorF(const float minimum, const float maximum, const float value);

#ifdef __cplusplus
}
#endif

#endif
