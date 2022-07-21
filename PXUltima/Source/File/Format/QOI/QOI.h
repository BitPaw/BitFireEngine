#ifndef QOIInclude
#define QOIInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct QOI_
	{
		unsigned int __dummy__;
	}
	QOI;

	extern ActionResult QOIParse(QOI* qoi, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif