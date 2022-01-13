﻿#define _CRT_SECURE_NO_WARNINGS


#include "../SystemResource/Source/Network/Server.h"
#include "../SystemResource/Source/Network/Client.h"
#include "../SystemResource/Source/File/FileTemporary.h"
#include "../SystemResource/Source/File/Program.h"
#include "../SystemResource/Source/File/FileActionResult.hpp"
#include "../SystemResource/Source/File/File.h"
#include "../SystemResource/Source/Font/TTF/TTF.h"

#include "../SystemResource/Source/Network/SocketActionResult.h"
#include "../SystemResource/Source/File/FileStream.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace BF;

const char* _client = "Client";
const char* _server = "Server";

#include "commdlg.h"

#include "../SystemResource/Source/File/OpenFileDialog.h"
#include "../SystemResource/Source/Service/HTTP/HTTPServer.h"

struct MainSt : public ISocketListener, public IClientListener, public IServerListener, BF::ProgramExecuteResultListener
{
	const char* stringAdress = 0;

	void OnMessageSend(IOSocketMessage socketMessage)
	{
		//printf("[%s][%i] Message Send : %s (%i Byte)\n", stringAdress, socketID, message, messageLengh);
		printf("[%s][%i] Message Send : (%zi Byte)\n", stringAdress, socketMessage.SocketID, socketMessage.MessageSize);
	}

	void OnMessageReceive(IOSocketMessage socketMessage)
	{
		printf("[%s][%i] Message Received : %s (%zi Byte)\n", stringAdress, socketMessage.SocketID, socketMessage.Message, socketMessage.MessageSize);
	}

	// Geerbt über ProgramExecuteResultListener
	void OnProgramExecuted(bool succesful, intptr_t returnResult, ErrorCode errorCode)
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

	void OnConnectionListening(const IPAdressInfo& adressInfo)
	{
		printf("[%s][%i] Connection Listening...\n", stringAdress, adressInfo.SocketID);
	}
	void OnConnectionLinked(const IPAdressInfo& adressInfo)
	{
		printf("[%s][%i] Connection Linked.\n", stringAdress, adressInfo.SocketID);
	}
	void OnConnectionEstablished(const IPAdressInfo& adressInfo)
	{
		printf("[%s][%i] Connection Established.\n", stringAdress, adressInfo.SocketID);
	}
	void OnConnectionTerminated(const IPAdressInfo& adressInfo)
	{
		printf("[%s][%i] Connection Terminated.\n", stringAdress, adressInfo.SocketID);
	}		
};

struct ExeLis : BF::ProgramExecuteResultListener
{
	virtual void OnProgramExecuted(bool succesful, intptr_t returnResult, ErrorCode errorCode) override
	{
		printf("Sucess exe \n");
	}
};

int main(int amountOFParameters, char** parameter)
{
	printf("[i][Core] Working Directory <%s>\n", parameter[0]);

	




	MainSt serverCallBack;
	MainSt clientCallBack;
	ExeLis axeLis;
	


#if 0 // Server
	HTTPServer httpServer;

	httpServer.EventCallBackServer = &httpServer;
	httpServer.EventCallBackSocket = &httpServer;
	httpServer.Start(PortHTTP);

	while (true)
	{
	
	}
#endif

#if 0 // List all files
	wchar_t** list = nullptr;
	size_t listSite = 0;

	BF::File::FilesInFolder("N:/Schule/Studium/Semester/Semester 5/[VS] Verteilte Systeme/Aufgabe/ClusterWorker/Program/UserInterface/WorkFolder_Server/*.chunk", &list, listSite);
#endif 

#if 0 // Execute program
	FILE* fielQQ = 0;

	fielQQ = fopen("A:\\_Cache\\H E L L O.txt", "wb");

	printf("\n");

	{
		char bufA[260];
		char bufb[260];

		strncpy_s(bufb, "C:\\Users\\BitPaw\\Videos\\E\\Server.exe", 420);
		strncpy_s(bufA, "C:\\Users\\BitPaw\\Videos\\E\\PP.input", 420);

		const char* dummy = "A:\\_Cache\\DummyProgram.exe";

		const char* a = "0";
		const char* exe = "N:\\Schule\\Studium\\Semester\\Semester 5\\[VS] Verteilte Systeme\\Aufgabe\\ClusterWorker\\Program\\x64\\Release\\VSServerDelegatorPrimes.exe";

		const char* b = "N:\\Schule\\Studium\\Semester\\Semester 5\\[VS] Verteilte Systeme\\Aufgabe\\ClusterWorker\\Program\\x64\\Release\\_InputServer.txt";
		const char* parameter[2] = { a, b };
		const char** ww = (const char**)&parameter;

		BF::Program::Execute(dummy, "0 \"LigmaBallz\"", &axeLis);

		//	BF::Program::Execute(dummy, ww, 2, &axeLis);
	}
#endif // 0

#if 0 // Other
	Program::Execute
	(
		"N:/Schule/Studium/Semester/Semester 5/[VS] Verteilte Systeme/Aufgabe/ClusterWorker/Program/VSClient/DummyProgram.exe",
		nullptr,
		&serverCallBack
	);*/


	Program program;

	FileActionResult fileActionResult = program.Execute("DummyProgram.exe", 0, 0);

	//char fileNameBuffer[255];
	//OpenFileDialog::Open(fileNameBuffer);
		
	OPENFILENAMEA fileNameBuffer;

	memset(&fileNameBuffer, 0, sizeof(OPENFILENAMEA));

	bool hello = GetOpenFileNameA(&fileNameBuffer);
#endif


#if 0 // Write file
	BF::FileStream fs2(20480);

	for (int i = 0; i < 1000; ++i)
	{
		printf("%i\n", i);

		fs2.Write("a\n", 3u);
	}

	fs2.WriteToDisk("A:/_WorkSpace/out.result");
#endif // 0


#if 0// Dictionary
	BF::DictionaryStatic<char[4], BF::SocketActionResult, 20> dict;

	dict.Add();
#endif


#if 0 // TTF load
	BF::TTF ttf;
	ttf.Load("A:/_WorkSpace/BOOKOSI.TTF");
#endif 	

	Server server;

	serverCallBack.stringAdress = _server;
	server.EventCallBackServer = &serverCallBack;
	server.EventCallBackSocket = &serverCallBack;
	
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
		
	client.SendFile("N:/Cache/2021-11-28 03-02-47.mp4");
	/*
	while (counter < (int)-1 && socketActionResult == SocketActionResult::Successful)
	{
		size_t readSize = sprintf_s(buffer,50,"Hello x%i", ++counter);

		client.Send(buffer, readSize);

		Sleep(500);
	}*/

	client.Disconnect();

	server.Stop();

	return 0;
}