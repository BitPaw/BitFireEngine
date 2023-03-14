#ifndef DirectXINCLUDE
#define DirectXINCLUDE

#include <Format/Type.h>

#if OSUnix
// UNIX has no DirectX support
typedef unsigned int  IDirect3D9; // Dummy value
#define MAX_DEVICE_IDENTIFIER_STRING 32
#elif OSWindows
#include <d3d9.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct DirectXContext_
	{
		IDirect3D9* ContextD9;

		char Driver[MAX_DEVICE_IDENTIFIER_STRING];
		char Description[MAX_DEVICE_IDENTIFIER_STRING];
		char DeviceName[32];
	}
	DirectXContext;

	PXPublic void DirectXContextConstruct(DirectXContext* const directXContext);
	PXPublic void DirectXContextDestruct(DirectXContext* const directXContext);

	PXPublic void DirectXContextCreate(DirectXContext* const directXContext);

#ifdef __cplusplus
}
#endif

#endif
