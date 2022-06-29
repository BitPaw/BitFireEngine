#include "SBPServer.h"

#include <cstdio>
#include <File/ByteStream.h>

#include <Text/Text.h>
#include <Network/Protocol/SBP/SBPText.h>

void BF::SBPServer::CreateText(const char* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax)
{
	const size_t size = Text::Length(text) + 1; // length + nullbyte 

	SBPText sbpText(text);

	const SBPData sbpData
	(
		SBPIDText,
		SourceMe,
		TargetAll,
		-1,
		size + 1, // +string indicator
		&sbpText
	);

	SBPData::GenerateMessage(sbpData, buffer, bufferSize, bufferSizeMax);
}

void BF::SBPServer::CreateText(const wchar_t* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax)
{
	ByteStream byteStream(buffer, bufferSize);

	const SBPText sbpText(text);
	const size_t size = sbpText.SizeInBytes();

	const SBPData sbpData
	(
		SBPIDText,
		SourceMe,
		TargetAll,
		-1,
		size + 1, // +string indicator
		&sbpText
	);

	SBPData::GenerateMessage(sbpData, buffer, bufferSize, bufferSizeMax);
}

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

		SBPData::GenerateMessage(data, buffer, bufferSize, bufferSizeMax);




		_server.SendMessageToClient(clientID, buffer, bufferSize);
	}

	// Create "i want to send" package



	//SBPIDConnectionCreate

	// Send pakgage

	// Wait for response



	for(size_t i = 0; i < _server.NumberOfConnectedClients; i++)
	{
		auto& client = _server.ClientList[i];

		client.SendFile(text);
	}	
}

size_t randomIDGenerator = 420;

const ResponseID BF::SBPServer::GenerateResponseID()
{
	return randomIDGenerator++;
}

bool BF::SBPServer::SendMessageWaitResponse(const ClientID clientID, const ResponseID responseID, const Byte* buffer, const size_t& bufferSize)
{
	_responseLookup.Add(responseID, nullptr);



	_server.SendMessageToClient(clientID, buffer, bufferSize);

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

	CreateText(text, buffer, size, bufferSize);

	_server.SendMessageToAll(buffer, size);
}

void BF::SBPServer::SendTextToAll(const wchar_t* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };
	
	CreateText(text, buffer, size, bufferSize);

	_server.SendMessageToAll(buffer, size);
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

	CreateText(text, buffer, size, bufferSize);

	_server.SendMessageToClient(clientID, buffer, size);
}

void BF::SBPServer::OnSocketCreating(const IPAdressInfo& adressInfo, bool& use)
{
}

void BF::SBPServer::OnSocketCreated(const IPAdressInfo& adressInfo, bool& use)
{
}

void BF::SBPServer::OnMessageSend(IOSocketMessage socketMessage)
{


	printf("[SBP] ");
	//_inputQueue.Enqueue();
}

void BF::SBPServer::OnMessageReceive(IOSocketMessage socketMessage)
{
	SBPData data;

	PackageParse(data, socketMessage.Message, socketMessage.MessageSize);

	printf("[SBP] ");
}

void BF::SBPServer::OnConnectionListening(const IPAdressInfo& adressInfo)
{

}

void BF::SBPServer::OnConnectionLinked(const IPAdressInfo& adressInfo)
{
}

void BF::SBPServer::OnConnectionEstablished(const IPAdressInfo& adressInfo)
{
}

void BF::SBPServer::OnConnectionTerminated(const IPAdressInfo& adressInfo)
{
}

int BF::SBPServer::PackageParse(SBPData& data, const void* inputData, const size_t inputDataSize)
{
	// Check length
	{
		const size_t sizeMaximal = 512u;
		const size_t sizeMinimal = 20u;
		const bool isValidLength = inputDataSize >= sizeMinimal && inputDataSize <= sizeMaximal;

		if(!isValidLength)
		{
			return -1;
		}
	}

	{
		ByteStream dataStream((Byte*)inputData, inputDataSize);

		data.Clear();

		const bool validHeader = dataStream.ReadAndCompare("°°", 2u);
		dataStream.Read(data.Command.Data, 4u);
		dataStream.Read(data.SourceID, Endian::Little);
		dataStream.Read(data.TargetID, Endian::Little);
		dataStream.Read(data.ID, Endian::Little);
		dataStream.Read(data.DataSize, Endian::Little);

		data.Data = dataStream.CursorCurrentAdress();
	}

	return 0;
}
