#ifndef ServerInclude
#define ServerInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <Network/CSocket.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct Client_ Client;

	typedef void (*ClientConnectedEvent)(const CSocket* serverSocket, const CSocket* clientSocket);
	typedef void (*ClientDisconnectedEvent)(const CSocket* serverSocket, const CSocket* clientSocket);
	typedef void (*ClientAcceptFailureEvent)(const CSocket* serverSocket);

	typedef struct Server_
	{
		CSocket* ServerSocketList;
		size_t ServerSocketListSize;

		CSocket* ClientSocketList;
		size_t ClientSocketListSize;

		ClientConnectedEvent ClientConnectedCallback;
		ClientDisconnectedEvent ClientDisconnectedCallback;
		ClientAcceptFailureEvent ClientAcceptFailureCallback;
	}
	Server;

	extern void ServerConstruct(Server* server);
	extern void ServerDestruct(Server* server);

	extern ActionResult ServerStart(Server* server, const unsigned short port, const ProtocolMode protocolMode);
	extern ActionResult ServerStop(Server* server);
	extern ActionResult ServerKickClient(Server* server, const CSocketID socketID);
	extern CSocket* ServerGetClientViaID(Server* server, const CSocketID socketID);

	extern void ServerRegisterClient(Server* server, Client* client);

	//extern ActionResult ServerSendMessageToAll(Server* server, const unsigned char* data, const size_t dataSize);
//	extern ActionResult ServerSendMessageToClient(Server* server, const CSocketID clientID, const unsigned char* data, const size_t dataSize);

	//extern ActionResult ServerSendFileToClient(Server* server, int clientID, const char* filePath);
	//extern ActionResult ServerSendFileToClient(Server* server, int clientID, const wchar_t* filePath);

	//extern ActionResult ServerBroadcastMessageToClients(Server* server, char* message, size_t messageLength);
	//extern ActionResult ServerBroadcastFileToClients(Server* server, const char* filePath);

	static ThreadResult ServerClientListeningThread(void* server);

#ifdef __cplusplus
}
#endif

#endif