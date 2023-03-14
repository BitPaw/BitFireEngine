#ifndef SBPServerINCLUDE
#define SBPServerINCLUDE

#include <Format/Type.h>
#include <OS/Network/PXServer.h>
#include <Network/SBP/PXSBPPackageProcessor.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXSBPServer_
	{
		PXSBPPackageProcessor PackageProcessor;
		PXServer Server;
	}
	PXSBPServer;

	PXPublic void SBPServerConstruct(PXSBPServer* const sbpServer);
	PXPublic void SBPServerDestruct(PXSBPServer* const sbpServer);

	PXPublic PXActionResult SBPServerStart(PXSBPServer* const sbpServer, const unsigned short port);
	PXPublic PXActionResult SBPServerStop(PXSBPServer* const sbpServer);

	PXPublic PXActionResult SBPServerSendFileA(PXSBPServer* const sbpServer, const PXSocketID clientID, const char* text);
	//CPublic void SBPServerSendFile(const PXSocketID clientID, wchar_t* text);

	PXPublic const ResponseID SBPServerGenerateResponseID();
	PXPublic unsigned char SBPServerSendMessageWaitResponse
	(
		const PXSocketID clientID,
		const ResponseID responseID,
		const unsigned char* buffer,
		const PXSize* bufferSize
	);

	PXPublic void SBPServerSendTextToAll(const char* text);
	//CPublic void SBPServerSendTextToAll(const wchar_t* text);
	PXPublic void SBPServerSendTextToPXClient(const unsigned int clientID, const char* text);
	//CPublic void SBPServerSendTextToPXClient(const unsigned int clientID, const wchar_t* text);

#ifdef __cplusplus
}
#endif

#endif
