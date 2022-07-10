#include "Client.h"

#include <stdio.h>

#include "../ErrorCode.h"

BF::Client::Client()
{
    EventCallBackClient = 0;
}

BF::SocketActionResult BF::Client::ConnectToServer(const char* ip, unsigned short port, const void* threadObject, const ThreadFunction threadFunction)
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

    for(size_t i = 0; i < adressInfoListSize; ++i)
    {
        IPAdressInfo& adressInfo = adressInfoList[i];
        const SocketActionResult socketCreateResult = Create(adressInfo.Family, adressInfo.Type, adressInfo.Protocol, adressInfo.SocketID);
        const bool creationSuccesful = adressInfo.SocketID != -1;

        if(creationSuccesful)
        {
            const int serverSocketID = connect(adressInfo.SocketID, (struct sockaddr*)adressInfo.IPRawByte, adressInfo.IPRawByteSize);
            const bool connected = serverSocketID != -1;

            if(connected)
            {
                AdressInfo = adressInfo;

                if(EventCallBackSocket)
                {
                    EventCallBackSocket->OnConnectionEstablished(adressInfo);
                }

                CommunicationThread.Run(threadFunction, threadObject);

                wasSucessful = true;
                break;
            }
        }
    }

    if(!wasSucessful)
    {
        return SocketActionResult::SocketConnectionFailure;
    }

    return SocketActionResult::Successful;
}

ThreadFunctionReturnType BF::Client::CommunicationFunctionAsync(void* data)
{
    Client& client = *(Client*)data;

    while (client.IsCurrentlyUsed())
    {
        const size_t bufferSizeMax = 2048;
        size_t bufferSize = 0;
        Byte__ buffer[bufferSizeMax]{0};

        const SocketActionResult receiveingResult = client.Receive(buffer, bufferSizeMax, bufferSize);
        const bool sucessful = receiveingResult == SocketActionResult::Successful;

        if (!sucessful)
        {
           // client.Disconnect();
        }
    }  

    return 0;
}