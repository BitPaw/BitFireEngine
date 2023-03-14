#ifndef PLYInclude
#define PLYInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct PLY_
	{
		unsigned int __dummy__;
	}
	PLY;

	PXPublic PXActionResult PLYParse(PLY* ply, const void* data, const PXSize dataSize, PXSize* dataRead);

#ifdef __cplusplus
}
#endif

#endif