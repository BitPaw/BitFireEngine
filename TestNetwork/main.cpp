
#include "../SystemResource/Source/Network/Server.h"
#include "../SystemResource/Source/Network/Client.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace BF;

const char* _client = "Client";
const char* _server = "Server";


struct MainSt : public ISocketListener
{
	const char* stringAdress = 0;

	void OnConnectionLinked(int socketID)
	{
		printf("[%s][%i] Connection Linked.\n", stringAdress, socketID);
	}

	void OnConnectionListening(int socketID)
	{
		printf("[%s][%i] Connection Listening...\n", stringAdress, socketID);
	}

	void OnConnectionEstablished(int socketID)
	{
		printf("[%s][%i] Connection Established.\n", stringAdress, socketID);
	}

	void OnConnectionTerminated(int socketID)
	{
		printf("[%s][%i] Connection Terminated.\n", stringAdress, socketID);
	}

	void OnMessageSend(int socketID, const char* message, size_t messageLengh)
	{
		printf("[%s][%i] Message Send : %s (%i Byte)\n", stringAdress, socketID, message, messageLengh);
	}

	void OnMessageReceive(int socketID, const char* message, size_t messageLengh)
	{
		printf("[%s][%i] Message Received : %s (%i Byte)\n", stringAdress, socketID, message, messageLengh);
	}
};

int main()
{
	MainSt serverCallBack;
	MainSt clientCallBack;

	Server server;

	serverCallBack.stringAdress = _server;
	server.Callback = &serverCallBack;

	
	SocketActionResult serverCreateResult = server.Start(IPVersion::IPVersion6, 25565);



	Client client;
	clientCallBack.stringAdress = _client;
	client.Callback = &clientCallBack;

	
	unsigned int counter = 0;
	char buffer[30];

	Sleep(100);

	SocketActionResult socketActionResult = client.ConnectToServer("::1", 25565);

	while (counter < 10000 && socketActionResult == SocketActionResult::Successful)
	{
		sprintf_s(buffer,30,"Hello x%i", ++counter);

		client.Write(buffer);

		//Sleep(250);
	}

	client.Disconnect();

	server.Stop();

	return 0;
}