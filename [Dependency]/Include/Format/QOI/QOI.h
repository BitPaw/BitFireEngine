#ifndef QOIInclude
#define QOIInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct QOI_
	{
		unsigned int __dummy__;
	}
	QOI;

	PXPublic PXActionResult QOIParse(QOI* qoi, const void* data, const PXSize dataSize, PXSize* dataRead);

#ifdef __cplusplus
}
#endif

#endif