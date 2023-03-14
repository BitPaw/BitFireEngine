#ifndef STEPInclude
#define STEPInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// (St)andard (E)xchange (P)roduct Data (ISO 10303-2xx)
	typedef struct STEP_
	{
		unsigned int __dummy__;
	}
	STEP;

	PXPublic PXActionResult STEPParse(STEP* step, const void* data, const PXSize dataSize, PXSize* dataRead);	

#ifdef __cplusplus
}
#endif

#endif