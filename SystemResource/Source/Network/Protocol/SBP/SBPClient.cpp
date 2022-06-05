#include "SBPClient.h"

#include <Network/Protocol/SBP/SBPData.h>

void BF::SBPClient::ConnectToServer(const char* ip, const unsigned short port)
{
	const SocketActionResult connectResult = _client.ConnectToServer(ip, port);
	const bool sucessful = connectResult == SocketActionResult::Successful;

	if(!sucessful)
	{
		return;
	}

	SBPData data
	(
		SBPIDIAM,
		SourceMe,
		TargetServer,
		-1,
		0,
		nullptr
	);

	const size_t bufferSizeMax = 2048;
	size_t bufferSize = 0;
	Byte buffer[bufferSizeMax];

	SBPData::GenerateMessage(data, buffer, bufferSize, bufferSizeMax);

	_client.Send(buffer, bufferSize);
}

void BF::SBPClient::ConnectToServer(const wchar_t* ip, const unsigned short port)
{

}

void BF::SBPClient::DisconnectFromServer()
{
	_client.Disconnect();
}

void BF::SBPClient::RegisterMe()
{
	


}

void BF::SBPClient::SendText(const char* text)
{

}

void BF::SBPClient::SendFile(const char* filePath)
{
	const char* ip = _client.AdressInfo.IP;
	const unsigned short port = _client.AdressInfo.Port;
	Client client;

	{
		const SocketActionResult connectResult = client.ConnectToServer(ip, port);
		const bool sucessful = connectResult == SocketActionResult::Successful;

		if(!sucessful)
		{
			return; // No connection
		}
	}

	{
		SocketActionResult socketActionResult = client.SendFile(filePath);
		const bool sucessful = socketActionResult == SocketActionResult::Successful;

		if(!sucessful)
		{
			return; // File, something
		}
	}
}