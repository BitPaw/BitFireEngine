#ifndef XMLINCLUDE
#define XMLINCLUDE

#include <OS/Error/PXActionResult.h>
#include <Format/Type.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum XMLSymbol_
	{
		XMLSymbolInvalid,

		XMLSymbolUnkown,

		XMLSymbolTagOpenBegin, // <xxxx...
		XMLSymbolTagOpenFull, // <xxxxx>...

		XMLSymbolTagCloseCurrent, // .../>
		XMLSymbolTagCloseFull, // </>

		XMLSymbolAttribute,

		XMLSymbolRawData
	}
	XMLSymbol;

	PXPublic XMLSymbol XMLPeekLine(const char* const text, const PXSize textSize);

	PXPublic PXActionResult XMLFileCompile(PXDataStream* const inputStream, PXDataStream* const outputStream);

#ifdef __cplusplus
}
#endif

#endif