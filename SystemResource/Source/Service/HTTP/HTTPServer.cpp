#include "HTTPServer.h"
#include <string>

void BF::HTTPServer::MessageParse(const char* message)
{
	

}

void BF::HTTPServer::OnClientConnected(Client& client)
{
}

void BF::HTTPServer::OnClientDisconnected(Client& client)
{
}

void BF::HTTPServer::OnClientAcceptFailure()
{
}

void BF::HTTPServer::OnSocketCreating(const IPAdressInfo& adressInfo, bool& use)
{
}

void BF::HTTPServer::OnSocketCreated(const IPAdressInfo& adressInfo, bool& use)
{
}

void BF::HTTPServer::OnMessageSend(IOSocketMessage socketMessage)
{
}

void BF::HTTPServer::OnMessageReceive(IOSocketMessage socketMessage)
{
	bool isGet = memcmp("GET / HTTP/1.1", socketMessage.Message, 14) == 0;

	const char* response =
		"HTTP/1.1 200 OK\r\n\r\n"
		"<html>"
		"<head>"
		"<title>An Example Page</title>"
		"</head>"
		"<body>"
		"<p>Hello World, this is a very simple HTML document.</p>"
		"</body>"
		"</html>";

	if (isGet)
	{
		this->SendMessageToClient(socketMessage.SocketID, (char*)response, 147);
		this->KickClient(socketMessage.SocketID);
	}

	//MessageParse(socketMessage.Message);
}

void BF::HTTPServer::OnConnectionListening(const IPAdressInfo& adressInfo)
{
}

void BF::HTTPServer::OnConnectionLinked(const IPAdressInfo& adressInfo)
{
}

void BF::HTTPServer::OnConnectionEstablished(const IPAdressInfo& adressInfo)
{
}

void BF::HTTPServer::OnConnectionTerminated(const IPAdressInfo& adressInfo)
{
}
