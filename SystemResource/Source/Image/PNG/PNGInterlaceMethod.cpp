#include "PNGInterlaceMethod.h"

BF::PNGInterlaceMethod BF::ConvertPNGInterlaceMethod(unsigned char interlaceMethod)
{
	switch (interlaceMethod)
	{
		case 0u: 
			return PNGInterlaceMethod::NoInterlace;

		case 1u:
			return PNGInterlaceMethod::ADAM7Interlace;

		default:
			return PNGInterlaceMethod::Invalid;
	}

	return PNGInterlaceMethod();
}

unsigned char BF::ConvertPNGInterlaceMethod(PNGInterlaceMethod interlaceMethod)
{
	switch (interlaceMethod)
	{
		default:
		case BF::PNGInterlaceMethod::Invalid:
			return -1;

		case BF::PNGInterlaceMethod::NoInterlace:
			return 0u;

		case BF::PNGInterlaceMethod::ADAM7Interlace:
			return 1u;
	}
}