#ifndef PXWebServerINCLUDE
#define PXWebServerINCLUDE

#include <OS/Error/PXActionResult.h>
#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXWebServer_
	{
		int x;
	}
	PXWebServer;

	PXPublic PXActionResult PXWebServerStart(PXWebServer* const pxWebServer);
	PXPublic PXActionResult PXWebServerStop(PXWebServer* const pxWebServer);


#ifdef __cplusplus
}
#endif

#endif