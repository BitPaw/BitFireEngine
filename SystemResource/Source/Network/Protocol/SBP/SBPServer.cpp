#include "SBPServer.h"

#include <cstdio>
#include <File/ByteStream.h>

#include <Text/Text.h>
#include <Network/Protocol/SBP/SBPText.h>

void BF::SBPServer::Start(const unsigned short port)
{
	_server.EventCallBackSocket = this;

	_server.Start(port);
}

void BF::SBPServer::Stop()
{
	_server.Stop();
}

void BF::SBPServer::SendFile(const ClientID clientID, const char* text)
{
	File file;

	// Check if file exists
	{
		const FileActionResult fileActionResult = file.MapToVirtualMemory(text);
		const bool sucessful = fileActionResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return; // Dont have file
		}
	}

	// Ask for new data connection
	{
		const char id = ConnectionCreateReasonFile;

		SBPData data
		(
			SBPIDConnectionCreate,
			SourceMe,
			clientID,
			-1,
			1u,
			&id
		);

		const size_t bufferSizeMax = 2048;
		size_t bufferSize = 0;
		Byte buffer[bufferSizeMax];

		//SBPData::GenerateMessage(data, buffer, bufferSize, bufferSizeMax);




		//_server.SendMessageToClient(clientID, buffer, bufferSize);
	}

	// Create "i want to send" package



	//SBPIDConnectionCreate

	// Send pakgage

	// Wait for response


	/*
	for(size_t i = 0; i < _server.NumberOfConnectedClients; i++)
	{
		auto& client = _server.ClientList[i];

		client.SendFile(text);
	}	*/
}

size_t randomIDGenerator = 420;

const ResponseID BF::SBPServer::GenerateResponseID()
{
	return randomIDGenerator++;
}

bool BF::SBPServer::SendMessageWaitResponse(const ClientID clientID, const ResponseID responseID, const Byte* buffer, const size_t& bufferSize)
{
	_responseLookup.Add(responseID, nullptr);



	//_server.SendMessageToClient(clientID, buffer, bufferSize);

	/*
	// wait for message
	while(true)
	{
		_responseLookup.
	}*/


	return false;
}

void BF::SBPServer::SendTextToAll(const char* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };

	//CreateText(text, buffer, size, bufferSize);

	//_server.SendMessageToAll(buffer, size);
}

void BF::SBPServer::SendTextToAll(const wchar_t* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };
	
	//CreateText(text, buffer, size, bufferSize);

	//_server.SendMessageToAll(buffer, size);
}

void BF::SBPServer::SendTextToClient(const unsigned int clientID, const char* text)
{


	//CreateText(text, buffer, size, bufferSize);

	//_server.SendMessageToClient(clientID, buffer, size);
}

void BF::SBPServer::SendTextToClient(const unsigned int clientID, const wchar_t* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };

	//CreateText(text, buffer, size, bufferSize);

	//_server.SendMessageToClient(clientID, buffer, size);
}

void BF::SBPServer::OnSocketCreating(const IPAdressInfo& adressInfo, bool& use)
{
}

void BF::SBPServer::OnSocketCreated(const IPAdressInfo& adressInfo, bool& use)
{
}

void BF::SBPServer::OnMessageSend(IOSocketMessage socketMessage)
{


	printf("[SBP] OnMessageSend\n");
	//_inputQueue.Enqueue();
}

void BF::SBPServer::OnMessageReceive(IOSocketMessage socketMessage)
{
	printf("[SBP][Server] Message %zi Bytes from <%i>\n",socketMessage.MessageSize, socketMessage.SocketID);


	SBPData data;
	const size_t read = SBPData::PackageParse(data, socketMessage.Message, socketMessage.MessageSize);

	data.Print();

	if(read)
	{
		switch(data.Command)
		{
			case BF::SBPCommand::Custom:
				break;
			case BF::SBPCommand::Iam:
			{
				const size_t bufferSize = 1024u;
				size_t bufferActural = 0;
				Byte buffer[bufferSize]{0};			

				const size_t written = SBPData::PackageSerialize(buffer, bufferSize, SourceMe, TargetYou, SBPData::PackageCreateResponse, data.ID);

				printf("[SBP][Server] Sending response\n");

				_server.SendMessageToClient(socketMessage.SocketID, buffer, written);			

				break;
			}				
			case BF::SBPCommand::ConnectionCreate:
				break;
			case BF::SBPCommand::ConnectionInfo:
				break;
			case BF::SBPCommand::ConnectionQuit:
				break;
			case BF::SBPCommand::Text:
				break;
			case BF::SBPCommand::File:
				break;
			default:
				break;
		}
	}
}

void BF::SBPServer::OnConnectionListening(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Server][%li] Listening on IP:%s Port:%i\n", adressInfo.SocketID, adressInfo.IP, adressInfo.Port);
}

void BF::SBPServer::OnConnectionLinked(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Server] Linked \n");
}

void BF::SBPServer::OnConnectionEstablished(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Server] Established <%i>\n", adressInfo.SocketID);
}

void BF::SBPServer::OnConnectionTerminated(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Server] Terminated <%i>\n", adressInfo.SocketID);
}