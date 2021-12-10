
#include "../SystemResource/Source/Network/Server.h"
#include "../SystemResource/Source/Network/Client.h"
#include "../SystemResource/Source/File/FileTemporary.h"
#include "../SystemResource/Source/File/Program.h"
#include "../SystemResource/Source/File/FileActionResult.hpp"
#include "../SystemResource/Source/File/File.h"
#include "../SystemResource/Source/Font/TTF/TTF.h"

#include "../SystemResource/Source/Network/SocketActionResult.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace BF;

const char* _client = "Client";
const char* _server = "Server";

#include "commdlg.h"

#include "../SystemResource/Source/File/OpenFileDialog.h"

struct MainSt : public ISocketListener, public IClientListener, public IServerListener, BF::ProgramExecuteResultListener
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

	void OnMessageSend(IOSocketMessage socketMessage)
	{
		//printf("[%s][%i] Message Send : %s (%i Byte)\n", stringAdress, socketID, message, messageLengh);
		printf("[%s][%i] Message Send : (%i Byte)\n", stringAdress, socketMessage.SocketID, socketMessage.MessageSize);
	}

	void OnMessageReceive(IOSocketMessage socketMessage)
	{
		printf("[%s][%i] Message Received : %s (%i Byte)\n", stringAdress, socketMessage.SocketID, socketMessage.Message, socketMessage.MessageSize);
	}

	// Geerbt über ProgramExecuteResultListener
	void OnProgramExecuted(bool succesful, size_t returnResult, ErrorCode errorCode)
	{
		printf("Heelp");
	}

	// Geerbt über ISocketListener
	void OnSocketCreating(const IPAdressInfo& adressInfo, bool& use)
	{
		printf("OnSocketCreate()\n");
	}
	void OnSocketCreated(const IPAdressInfo& adressInfo, bool& use)
	{
		printf("OnSocketCreated()\n");
	}


	void OnClientConnected(Client& client)
	{
		printf("OnClientConnected()\n");
	}

	void OnClientDisconnected(Client& client)
	{
		printf("OnClientDisconnected()\n");
	}

	void OnClientAcceptFailure()
	{
		printf("OnClientAcceptFailure()\n");
	}

	void OnConnectedToServer(IPAdressInfo& adressInfo)
	{
		printf("Connected to server\n");
	}
};

int main(int amountOFParameters, char** parameter)
{
	printf("[i][Core] Working Directory <%s>\n", parameter[0]);


	MainSt serverCallBack;
	MainSt clientCallBack;


	//BF::DictionaryStatic<char[4], BF::SocketActionResult, 20> dict;

	//dict.Add();


//	BF::TTF ttf;
//	ttf.Load("A:/_WorkSpace/BOOKOSI.TTF");

	/*
	Program::Execute
	(
		"N:/Schule/Studium/Semester/Semester 5/[VS] Verteilte Systeme/Aufgabe/ClusterWorker/Program/VSClient/DummyProgram.exe",
		nullptr,
		&serverCallBack
	);*/


	/*
	Program program;	

	FileActionResult fileActionResult = program.Execute("DummyProgram.exe", 0, 0);

	return 1;*/
	//char fileNameBuffer[255];
	//OpenFileDialog::Open(fileNameBuffer);

	/*
	OPENFILENAMEA fileNameBuffer;

	memset(&fileNameBuffer, 0, sizeof(OPENFILENAMEA));

	bool hello = GetOpenFileNameA(&fileNameBuffer);
	*/

	Server server;

	serverCallBack.stringAdress = _server;
	server.EventCallBackServer = &serverCallBack;

	
	SocketActionResult serverCreateResult = server.Start(25666);


	Client client;
	clientCallBack.stringAdress = _client;
	client.EventCallBackSocket = &clientCallBack;
	client.EventCallBackClient = &clientCallBack;
	
	unsigned int counter = 0;
	char buffer[50];

	
	/*
	while (true)
	{

	}*/

	Sleep(100);

	SocketActionResult socketActionResult = client.ConnectToServer("localhost", 25666);

	//client.Send("U\0\0\0\11BOOKOSI.TTF",17);
	//client.SendFile("A:/_WorkSpace/BOOKOSI.TTF");
		
	while (counter < (int)-1 && socketActionResult == SocketActionResult::Successful)
	{
		size_t readSize = sprintf_s(buffer,50,"Hello x%i", ++counter);

		client.Send(buffer, readSize);

		Sleep(500);
	}

	client.Disconnect();

	server.Stop();

	return 0;
}