#include "Client.h"

#include <stdio.h>

#include "../ErrorCode.h"

BF::Client::Client()
{
    EventCallBackClient = 0;
}

BF::SocketActionResult BF::Client::ConnectToServer(const char* ip, unsigned short port)
{
    IPAdressFamily ipAdressFamily = IPAdressFamily::Unspecified;
    SocketType socketType = SocketType::Stream;
    ProtocolMode protocolMode = ProtocolMode::TCP;

    size_t adressInfoListSize = 0;
    IPAdressInfo* adressInfoList = nullptr;

    SetupAdress
    (
        (char*)ip,
        port, 
        ipAdressFamily,
        socketType,
        protocolMode,
        adressInfoListSize,
        &adressInfoList
    );

    bool wasSucessful = false;

    for (size_t i = 0; i < adressInfoListSize; i++)
    {
        IPAdressInfo& adressInfo = adressInfoList[i];
        SocketActionResult socketCreateResult = Create(adressInfo.Family, adressInfo.Type, adressInfo.Protocol, adressInfo.SocketID);
        bool creationSuccesful = adressInfo.SocketID != -1;

        if (creationSuccesful)
        {
            int serverSocketID = connect(adressInfo.SocketID, (struct sockaddr*)adressInfo.IPRawByte, adressInfo.IPRawByteSize);
            bool connected = serverSocketID != -1;

            if (connected)
            {
                AdressInfo = adressInfo;

                if (EventCallBackSocket)
                {
                    EventCallBackSocket->OnConnectionEstablished(adressInfo.SocketID);

                    CommunicationThread.Run(Client::CommunicationFunctionAsync, this);
                }

                wasSucessful = true;
            }

            break;
        }
    }

    if (!wasSucessful)
    {
        return SocketActionResult::SocketCreationFailure;
    }

    return SocketActionResult::Successful;
}

void BF::Client::Disconnect()
{
	Close();
}

ThreadFunctionReturnType BF::Client::CommunicationFunctionAsync(void* data)
{
    Client& client = *(Client*)data;

    while (client.IsCurrentlyUsed())
    {
        SocketActionResult socketActionResult = client.Receive();

        if (socketActionResult != SocketActionResult::Successful)
        {
            client.Disconnect();
        }
    }  

    return 0;
}