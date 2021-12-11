#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <cassert>

#include "../Async/Thread.h"
#include "SocketActionResult.h"
#include "ServerListeningThreadInfo.h"

BF::Server::Server()
{
    ClientList = 0;
    NumberOfConnectedClients = 0;
    NumberOfMaximalClients = 10;
    EventCallBackServer = nullptr;
    EventCallBackSocket = nullptr;

    ClientList = new Client[NumberOfMaximalClients];

    SocketListSize = 0;
    SocketList = nullptr;

    _clientListLock.Create();
}

BF::Server::~Server()
{
    delete[] ClientList;
    delete[] SocketList;
}

BF::Client* BF::Server::GetNextClient()
{
    for (unsigned int i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];
        char isUsed = client->IsCurrentlyUsed();

        if (!isUsed)
        {           
            return client;
        }
    }

    size_t riseAmount = 10;
    size_t newNumberOfMaximalClients = NumberOfMaximalClients + riseAmount;
    Client* movedMemory = (Client*)realloc(ClientList, newNumberOfMaximalClients * sizeof(Client));

    if (!movedMemory)
    {
        return nullptr; // No memory for another Client
    }

    for (size_t i = NumberOfMaximalClients; i < newNumberOfMaximalClients; i++)
    {
        movedMemory[i] = Client();
        ++NumberOfMaximalClients;
    }

    ClientList = movedMemory;

    return GetNextClient();
}

BF::SocketActionResult BF::Server::Start(unsigned short port)
{
    size_t adressInfoListSize = 0;
    IPAdressInfo* adressInfoList = nullptr;

    SocketActionResult adressResult = IOSocket::SetupAdress
    (
        nullptr, 
        port, 
        IPAdressFamily::Unspecified,
        SocketType::Stream, 
        ProtocolMode::TCP,
        adressInfoListSize,
        &adressInfoList
    );

    if (adressResult != SocketActionResult::Successful)
    {
        return adressResult;
    }

    SocketListSize = adressInfoListSize;
    SocketList = new IOSocket[SocketListSize];

    for (size_t i = 0; i < SocketListSize; i++)
    {
        IOSocket& ioSocket = SocketList[i];
        ioSocket.AdressInfo = adressInfoList[i];        

        ioSocket.EventCallBackSocket = EventCallBackSocket;

        // If some is there to ask, ask. He may want to say no.
        {
            bool createSocket = true;

            if (ioSocket.EventCallBackSocket)
            {
                ioSocket.EventCallBackSocket->OnSocketCreating(ioSocket.AdressInfo, createSocket); // createSocket may get changed from listener.
            }

            if (!createSocket)
            {
                continue; // Skip to next socket
            }
        }
      
        SocketActionResult socketCreateResult = IOSocket::Create(ioSocket.AdressInfo.Family, ioSocket.AdressInfo.Type, ioSocket.AdressInfo.Protocol, ioSocket.AdressInfo.SocketID);

        if (socketCreateResult != SocketActionResult::Successful)
        {
            return SocketActionResult::SocketCreationFailure;
        }

        // Set Socket Options
        {
            const int level = SOL_SOCKET;

            const int optionName =
#if defined(OSUnix)
                SO_REUSEADDR;      // Do not use SO_REUSEADDR, else the port can be hacked. SO_REUSEPORT
#elif defined(OSWindows)
                SO_EXCLUSIVEADDRUSE;
#endif
            const char opval = 1;
            int optionsocketResult = setsockopt(ioSocket.AdressInfo.SocketID, level, optionName, &opval, sizeof(opval));

            if (optionsocketResult == 1)
            {
                return SocketActionResult::SocketOptionFailure;
            }
        }

        // Bind Socket
        {
            int bindingResult = bind(ioSocket.AdressInfo.SocketID, (struct sockaddr*)ioSocket.AdressInfo.IPRawByte, ioSocket.AdressInfo.IPRawByteSize);

            if (bindingResult == -1)
            {
                return SocketActionResult::SocketBindingFailure;
            }
        }

        // Listen
        {
            int maximalClientsWaitingInQueue = 10;
            int listeningResult = listen(ioSocket.AdressInfo.SocketID, maximalClientsWaitingInQueue);

            if (listeningResult == -1)
            {
                return SocketActionResult::SocketListeningFailure;
            }
        }

        if (ioSocket.EventCallBackSocket)
        {
            ioSocket.EventCallBackSocket->OnConnectionListening(ioSocket.AdressInfo);
        }

        ServerListeningThreadInfo* serverListeningThreadInfo = new ServerListeningThreadInfo(&SocketList[i], this);

        ioSocket.CommunicationThread.Run(Server::ClientListeningThread, serverListeningThreadInfo);
    }       

    return SocketActionResult::Successful;
}

void BF::Server::Stop()
{
    for (size_t i = 0; i < SocketListSize; i++)
    {
        SocketList[i].Close();
    }
}

void BF::Server::KickClient(int socketID)
{
    Client* client = GetClientViaID(socketID);

    client->Disconnect();
}

BF::Client* BF::Server::GetClientViaID(int socketID)
{
    for (unsigned int i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];
        int clientSocketID = 0;// client->ID; //TODO
        char foundTarget = clientSocketID == socketID;

        if (foundTarget)
        {
            return client;
        }
    }

    return 0;
}

void BF::Server::RegisterClient(IOSocket* clientSocket)
{
    _clientListLock.Lock();
    Client* indexedClient = GetNextClient();
    _clientListLock.Release();

    indexedClient->EventCallBackSocket = clientSocket->EventCallBackSocket;
    indexedClient->AdressInfo = clientSocket->AdressInfo;

    NumberOfConnectedClients++;

    if (EventCallBackServer)
    {
        EventCallBackServer->OnClientConnected(*indexedClient);
    }

    indexedClient->CommunicationThread.Run(Client::CommunicationFunctionAsync, indexedClient);

    /*
    * ADD in this /\
    *
      server->NumberOfConnectedClients--;

        if (server->EventCallBackServer)
        {
            server->EventCallBackServer->OnClientDisconnected(*client);
        }


    */
}

BF::SocketActionResult BF::Server::SendMessageToClient(int clientID, char* message, size_t messageLength)
{
    Client* client = GetClientViaID(clientID);

    if (!client)
    {
        return SocketActionResult::NoClientWithThisID;
    }

    return client->Send(message, messageLength);
}

BF::SocketActionResult BF::Server::SendFileToClient(int clientID, const char* filePath)
{
    Client* client = GetClientViaID(clientID);

    if (!client)
    {
        return SocketActionResult::NoClientWithThisID;
    }        

    return client->SendFile(filePath);
}

BF::SocketActionResult BF::Server::BroadcastMessageToClients(char* message, size_t messageLength)
{
    SocketActionResult errorCode = SocketActionResult::InvalidResult;

    for (size_t i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];

        if (client->IsCurrentlyUsed())
        {
            SocketActionResult currentCrrorCode = client->Send(message, messageLength);

            if (currentCrrorCode != SocketActionResult::Successful)
            {
                errorCode = currentCrrorCode;
            }
        }     
    }

    return errorCode;
}

BF::SocketActionResult BF::Server::BroadcastFileToClients(const char* filePath)
{
    SocketActionResult socketActionResult = SocketActionResult::Successful;

    for (unsigned int i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];
        char isUsed = client->IsCurrentlyUsed();

        if (isUsed)
        {
            SocketActionResult currentResult = client->SendFile(filePath);

            if (socketActionResult != SocketActionResult::Successful)
            {
                socketActionResult = currentResult;
            }
        }
    }

    return socketActionResult;
}

ThreadFunctionReturnType BF::Server::ClientListeningThread(void* data)
{
    ServerListeningThreadInfo* serverListeningInfo = (ServerListeningThreadInfo*)data;
    Server* server = serverListeningInfo->ServerAdress;
    IOSocket* serverSocket = serverListeningInfo->ServerSocket;

    free(data); // there was a new, but we only need to get this here.

    while (serverSocket->IsCurrentlyUsed())
    {
        IOSocket clientSocket;     

        assert(server);
        assert(serverSocket);

        clientSocket.AdressInfo.IPRawByteSize = IPv6LengthMax; // Needed for accept(), means 'length i can use'. 0 means "I canot perform"

        clientSocket.AdressInfo.SocketID = accept
        (
            serverSocket->AdressInfo.SocketID,
            (struct sockaddr*)clientSocket.AdressInfo.IPRawByte,
            (int*)&clientSocket.AdressInfo.IPRawByteSize
        );

        bool sucessful = clientSocket.IsCurrentlyUsed();

        if (!sucessful)
        {
            if (server->EventCallBackServer)
            {
                server->EventCallBackServer->OnClientAcceptFailure();
                continue;
            }
        }

        clientSocket.EventCallBackSocket = serverSocket->EventCallBackSocket;

        server->RegisterClient(&clientSocket);
    }

    return 0;
}