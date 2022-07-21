#ifndef SVGInclude
#define SVGInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct SVG_
	{
		unsigned int __dummy__;
	}
	SVG;

	extern ActionResult SVGParse(SVG* svg, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif