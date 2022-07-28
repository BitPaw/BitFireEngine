#include "Client.h"

#include <Memory/Memory.h>
#include <Event/Event.h>

ActionResult ClientConnectToServer(Client* client, const char* ip, unsigned short port, const void* threadObject, const ThreadFunction threadFunction)
{
    IPAdressFamily ipAdressFamily = IPAdressFamilyUnspecified;
    CSocketType socketType = CSocketTypeStream;
    ProtocolMode protocolMode = ProtocolModeTCP;

    CSocket cSocketList[5];
    size_t cSocketListSizeMax = 5;
    size_t cSocketListSize = 0;

    MemorySet(cSocketList,sizeof(CSocket)* cSocketListSizeMax, 0);

    CSocketSetupAdress
    (
        cSocketList,
        cSocketListSizeMax,
        &cSocketListSize,
        (char*)ip,
        port,
        ipAdressFamily,
        socketType,
        protocolMode
    );

    unsigned char wasSucessful = 0;

    for (size_t i = 0; i < cSocketListSize; ++i)
    {
        CSocket* cSocket = &cSocketList[i];
        const ActionResult socketCreateResult = CSocketCreate(cSocket, cSocket->Family, cSocket->Type, cSocket->Protocol);
        const unsigned char creationSuccesful = ResultSuccessful == socketCreateResult;

        if (creationSuccesful)
        {
            const ActionResult connectResult = CSocketConnect(cSocket);
            const unsigned char connected = ResultSuccessful == connectResult;

            if (connected)
            {  
                InvokeEvent(cSocket->ConnectionEstablishedCallback, cSocket);          

                cSocket->CommunicationThread = ThreadRun(threadFunction, threadObject);

                wasSucessful = 1u;
                break; // Connect only once. If this is not here, we would connect more than once (with different protocol)
            }
        }
    }

    if (!wasSucessful)
    {
        return SocketConnectionFailure;
    }

    return ResultSuccessful;
}

#define ClientBufferSize 2048u

ThreadFunctionReturnType CommunicationFunctionAsync(void* cSocketAdress)
{
    CSocket* cSocket = (CSocket*)cSocketAdress;

    while (CSocketIsCurrentlyUsed(cSocket))
    {
        const size_t bufferSizeMax = 2048;
        size_t bufferSize = 0;
        unsigned char buffer[ClientBufferSize];

        MemorySet(buffer, sizeof(unsigned char) * ClientBufferSize, 0);

        const ActionResult receiveingResult = CSocketReceive(cSocket, buffer, bufferSizeMax, &bufferSize);
        const unsigned char sucessful = ResultSuccessful == receiveingResult;

        if (!sucessful)
        {
            CSocketDestruct(cSocket);
        }
    }

    return 0;
}