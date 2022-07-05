#include "SBPClient.h"

#include <Network/Protocol/SBP/SBPData.h>
#include <Hardware/Memory/Memory.h>
#include <Text/Text.h>
#include <OS/User.h>
#include <Time/Time.h>
#include <Time/StopWatch.h>

#define TimeOutLimit 5000u // 5s

BF::SBPClient::SBPClient()
{
	SubConnectionList = nullptr;
	SubConnectionListSize = 0;

	_client.EventCallBackSocket = this;
}

BF::SBPResult BF::SBPClient::SendAndWaitResponse
(
	void* inputData,
	const size_t inputDataSize,
	void* responseData,
	size_t& responseDataSize,
	const unsigned int sourceID,
	const unsigned int targetID,
	const PackageBuilderFunction packageBuilderFunction
)
{
	responseData = 0;
	responseDataSize = 0;

	const ResponseID responseID = _responseCache.Register();

	const size_t writtenBytes = SBPData::PackageSerialize(inputData, inputDataSize, SourceMe, TargetServer, packageBuilderFunction, responseID);

	// Send stuff
	{
		const SocketActionResult sendResult = _client.Send(inputData, writtenBytes);
		const bool sucessful = sendResult == SocketActionResult::Successful;

		if(!sucessful)
		{
			_responseCache.Remove(responseID);

			return SBPResult::PackageSendingFailure;
		}
	}

	{
		Time timestampStart;
		Time timestampCurrent;

		{
			ResponseCacheEntry responseCacheEntry;
			const ResponseCacheResult responseCacheResult = _responseCache.Find(responseID, responseCacheEntry);
			const bool isRegistered = responseCacheResult != ResponseCacheResult::NotRegistered;

			if(!isRegistered)
			{
				return SBPResult::PackageSendSucessfulButNoResponder;
			}
		}

		Time::Now(timestampStart);

		while(true) // Wait aslong as response is there
		{
			// Check if timeout
			{
				Time::Now(timestampCurrent);

				const size_t millisecondsDelta = Time::MillisecondsDelta(timestampStart, timestampCurrent);

				const bool isTimeout = millisecondsDelta > TimeOutLimit;

				if(isTimeout)
				{
					printf("[SBP] Package timed out!\n");

					_responseCache.Remove(responseID); // We assume that the message does not come anymore or is not needed

					return SBPResult::PackageTimeout;
				}
			}

			// Check if answered
			{
				ResponseCacheEntry responseCacheEntry;
				const ResponseCacheResult responseCacheResult = _responseCache.Find(responseID, responseCacheEntry);
				const bool isAnswered = responseCacheResult == ResponseCacheResult::Answered;

				if(isAnswered)
				{
					responseData = responseCacheEntry.Data;
					responseDataSize = responseCacheEntry.Length;

#if SocketDebug
					printf("[SBP] Package answered!\n");
#endif

					return SBPResult::PackageAnswered;
				}
			}
		}
	}

	return SBPResult::Invalid;
}

void BF::SBPClient::ConnectToServer(const char* ip, const unsigned short port)
{
	const SocketActionResult connectResult = _client.ConnectToServer(ip, port, this, ReciveDataThread);
	const bool sucessful = connectResult == SocketActionResult::Successful;

	if(!sucessful)
	{
		return;
	}

	char inputBuffer[2048]{ 0 };
	size_t inputBufferSize = 2024;
	char outputBuffer[2048]{ 0 };
	size_t outputBufferSize = 2024;

	StopWatch stopwatch;

	printf("[Benchmark] Package sending...\n");

	stopwatch.Start();

	const SBPResult result = SendAndWaitResponse
	(
		inputBuffer,
		inputBufferSize,
		outputBuffer,
		outputBufferSize,
		SourceMe,
		TargetServer,
		SBPData::PackageCreateIAM
	);

	double x = stopwatch.Stop();

	if(result == SBPResult::PackageAnswered)
	{
		printf("[Benchmark] Package answered! took %.2lfms", x*1000);
	}
}

void BF::SBPClient::ConnectToServer(const wchar_t* ip, const unsigned short port)
{

}

void BF::SBPClient::DisconnectFromServer()
{
	//_client.Disconnect();
}

void BF::SBPClient::RegisterMe()
{



}

void BF::SBPClient::SendText(const char* text)
{

}

void BF::SBPClient::SendFile(const char* filePath)
{
	/*
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
	}*/
}

void BF::SBPClient::OnSocketCreating(const IPAdressInfo& adressInfo, bool& use)
{
	printf("[SBP][Client] Createding <%zi> %s:%i\n", adressInfo.SocketID, adressInfo.IP, adressInfo.Port);
}

void BF::SBPClient::OnSocketCreated(const IPAdressInfo& adressInfo, bool& use)
{
	printf("[SBP][Client] Created <%zi> %s:%i\n", adressInfo.SocketID, adressInfo.IP, adressInfo.Port);
}

void BF::SBPClient::OnMessageSend(IOSocketMessage socketMessage)
{
#if SocketDebug
	printf("[SBP][Client] Send %zi Bytes to <%zi>\n", socketMessage.MessageSize, socketMessage.SocketID);
#endif
}

void BF::SBPClient::OnMessageReceive(IOSocketMessage socketMessage)
{
#if SocketDebug
	printf("[SBP][Client] Receive %zi Bytes from <%zi>\n", socketMessage.MessageSize, socketMessage.SocketID);
#endif
}

void BF::SBPClient::OnConnectionListening(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Client] OnConnectionListening\n");
}

void BF::SBPClient::OnConnectionLinked(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Client] OnConnectionLinked\n");
}

void BF::SBPClient::OnConnectionEstablished(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Client] OnConnectionEstablished\n");
}

void BF::SBPClient::OnConnectionTerminated(const IPAdressInfo& adressInfo)
{
	printf("[SBP][Client] OnConnectionTerminated\n");
}

ThreadFunctionReturnType BF::SBPClient::ReciveDataThread(void* sbpClientAdress)
{
	SBPClient& client = *(SBPClient*)sbpClientAdress;

	char buffer[1024]{ 0 };
	size_t bufferSizeMax = 1024;
	size_t bufferSize = 0;

	while(client._client.IsCurrentlyUsed())
	{
		SBPData data;

		// Get raw bytes
		const auto receiveingResult = client._client.Receive(buffer, bufferSizeMax, bufferSize);

		// Convert raw bytes into data object
		const size_t parsedBytes = SBPData::PackageParse(data, buffer, bufferSize);

		if(parsedBytes)
		{
#if SocketDebug
			printf("[SBP][Client] SBP detected %c%c%c%c\n", data.CommandID.A, data.CommandID.B, data.CommandID.C, data.CommandID.D);
#endif
			client._responseCache.Fill(data.ID, buffer, bufferSize);

			//_responseCache.;

			// Handle packaage
			switch(data.Command)
			{
				case SBPCommand::Iam:
				{
					wchar_t* name = (wchar_t*)data.Data;

					//printf("[SBP][I'am] %ls\n", name);

					//InvokeEvent(PackageIAMRecieveCallBack, name);

					break;
				}
				case SBPCommand::ConnectionCreate:
				{
					break;
				}
				case SBPCommand::ConnectionInfo:
				{
					break;
				}
				case SBPCommand::ConnectionQuit:
				{
					break;
				}
				case SBPCommand::Text:
				{
					break;
				}
				case SBPCommand::File:
				{
					break;
				}
				default:
				{
					//PackageRecieveCallBack(data);
					//return SBPResult::PackageDetectedCustom;
				}
			}
		}

		//return SBPResult::PackageDetectedRegistered;


		//if(!sucessful)
		//{
			// client.Disconnect();
		//}
	}

	return ThreadFunctionReturnValue;
}
