#ifndef SBPPXClientINCLUDE
#define SBPPXClientINCLUDE

#include <Format/Type.h>

#include <OS/Network/PXClient.h>
#include <OS/Thread/PXThread.h>

#include "SBPProtocol.h"
#include "PXSBPPackageProcessor.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXSBPClient_
	{
		// Private
		PXSBPPackageProcessor PackageProcessor;
		PXClient Client;

		// Public
		
	}
	PXSBPClient;

	PXPublic void PXSBPClientConstruct(PXSBPClient* const sbpPXClient);
	PXPublic void PXSBPClientDestruct(PXSBPClient* const sbpPXClient);

	// Sending a message via a socket, await a response.
	PXPublic SBPResult SendAndWaitResponse
	(
		PXSBPClient* const sbpPXClient,
		void* inputData,
		const PXSize inputDataSize,
		void* responseData,
		PXSize* responseDataSize,

		const unsigned int sourceID,
		const unsigned int targetID,
		const SBPPackageHeader* dataPackage
	);

	PXPublic PXActionResult SBPPXClientConnectToServer(PXSBPClient* const sbpPXClient, const char* ip, const unsigned short port);
//	void SBPPXClientConnectToServer(SBPPXClient* const sbpPXClient, const wchar_t* ip, const unsigned short port);
	PXPublic PXActionResult SBPPXClientDisconnectFromServer(PXSBPClient* const sbpPXClient);

	//PXPublic PXActionResult PXSBPClientSendPackage(PXSBPClient* const sbpPXClient, );

	void SBPPXClientRegisterMe();
	void SBPPXClientSendText(const char* text);
	void SBPPXClientSendFile(const char* filePath);

#ifdef __cplusplus
}
#endif

#endif
