#include "SBPClient.h"

#include <Network/Protocol/SBP/SBPData.h>
#include <Hardware/Memory/Memory.h>
#include <Text/Text.h>
#include <OS/User.h>

ResponseID BF::SBPClient::_counter = 0;

ThreadFunctionReturnType BF::SBPClient::SendFileThread(void* data)
{
	return ThreadFunctionReturnType();
}

void BF::SBPClient::PackageRecieve(const SBPData& data)
{

}

void BF::SBPClient::PackageDeploy(const SBPData& data)
{
	const size_t bufferSize = 2048u;
	Byte buffer[bufferSize];

	ByteStream stream(buffer, bufferSize);

	stream.Write("°°", 2u);
	stream.Write(data.Command.Data, 4u);
	stream.Write(data.SourceID, Endian::Little);
	stream.Write(data.TargetID, Endian::Little);
	stream.Write(data.ID, Endian::Little);
	stream.Write(data.DataSize, Endian::Little);
	stream.Write(data.Data, data.DataSize);

	_client.Send(buffer, stream.DataCursorPosition);
}

ResponseID BF::SBPClient::PackageDeploy(const unsigned int source, const unsigned int target, PackageBuilderFunction packageBuilderFunction)
{
	const ResponseID responseID = ResponseIDGenerate();

	SBPData data;

	data.SourceID = source;
	data.TargetID = target;
	data.ID = responseID;
	
	char buffer[512]{ 0 };
	size_t bufferSize = 0;

	packageBuilderFunction(data, buffer);

	ResponseData responseData;

	responseData.Time = 0;
	responseData.State = ResponseDataStateWaiting;
	responseData.Data = nullptr;

	_responseLookup.Add(data.ID, responseData);

	PackageDeploy(data);

	return responseID;
}

void BF::SBPClient::PackageCreateIAM(SBPData& data, void* payloadBuffer)
{
	const size_t nameSizeMAX = 256u;
	wchar_t name[nameSizeMAX]{0};
	size_t nameSize = 0;

	const bool read = User::Name(name, nameSizeMAX, nameSize);

	nameSize *= 2; // wchars are 2 Bytes long

	Memory::Copy(payloadBuffer, name, nameSize);

	data.Command.Value = SBPIDIAM;
	data.DataSize = nameSize;
	data.Data = payloadBuffer;
}

ResponseID BF::SBPClient::ResponseIDGenerate()
{
	return ++_counter;
}

BF::SBPClient::SBPClient()
{
	PackageRecieveCallBack = nullptr;
}

void BF::SBPClient::ConnectToServer(const char* ip, const unsigned short port)
{
	const SocketActionResult connectResult = _client.ConnectToServer(ip, port);
	const bool sucessful = connectResult == SocketActionResult::Successful;

	if(!sucessful)
	{
		return;
	}

	PackageDeploy(SourceMe, TargetServer, PackageCreateIAM);
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
	SendFileThreadData* sendFileThreadData = new SendFileThreadData();

	Text::Copy(filePath, PathMaxSize, sendFileThreadData->FilePath, PathMaxSize);

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