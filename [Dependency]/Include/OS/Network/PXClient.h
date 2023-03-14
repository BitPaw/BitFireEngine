#ifndef PXClientInclude
#define PXClientInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <OS/Network/PXSocket.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXClient_ PXClient;

	typedef void (*ConnectedToServerEvent)(const PXClient* client);

	typedef struct PXClient_
	{
		PXSocket SocketPXClient;
		PXSocket SocketConnectedServer;

		PXSocketEventListener EventListener;

		ConnectedToServerEvent ConnectedToServerCallback;

		void* Owner;
	}
	PXClient;

	PXPublic PXActionResult PXClientConstruct(PXClient* const pxClient);
	PXPublic PXActionResult PXClientDestruct(PXClient* const pxClient);

	PXPublic PXActionResult PXClientConnectToServer(PXClient* const client, const char* ip, unsigned short port, const void* threadObject, const ThreadFunction threadFunction);
	PXPublic PXActionResult PXClientDisconnectFromServer(PXClient* const client);

	PXPublic PXThreadResult CommunicationFunctionAsync(void* ioSocket);

#ifdef __cplusplus
}
#endif

#endif