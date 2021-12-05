#include "Server.h"
#include "SocketActionResult.h"
#include "../Async/Thread.h"

#include <stdio.h>
#include <stdlib.h>
#include <cassert>

BF::Server::Server()
{
    ClientList = 0;
    NumberOfConnectedClients = 0;
    NumberOfMaximalClients = 10;
    EventCallBackServer = nullptr;

    ClientList = new Client[NumberOfMaximalClients];
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
    }

    ClientList = movedMemory;

    return GetNextClient();
}

BF::SocketActionResult BF::Server::Start(unsigned short port)
{
    SocketActionResult socketActionResult = Open(port);

    if (socketActionResult != SocketActionResult::Successful)
    {
        return socketActionResult;
    }         

    CommunicationThread.Create(Server::ClientListeningThread, this);    

    return SocketActionResult::Successful;
}

void BF::Server::Stop()
{
    Close();
}

void BF::Server::KickClient(int socketID)
{
    Client* client = GetClientViaID(socketID);

    client->Disconnect();
}

BF::Client* BF::Server::WaitForClient()
{
    Client* client = GetNextClient();
    
    assert(client);

    client->AdressInfo.ai_family = AdressInfo.ai_family;
    client->AdressInfo.ai_socktype = AdressInfo.ai_socktype;

    AwaitConnection(*client);
      
    if(!client->IsCurrentlyUsed())
    {
        return nullptr;
    }
    
    return client;
}

BF::Client* BF::Server::GetClientViaID(int socketID)
{
    for (unsigned int i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];
        int clientSocketID = client->ID;
        char foundTarget = clientSocketID == socketID;

        if (foundTarget)
        {
            return client;
        }
    }

    return 0;
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
    Server* server = (Server*)data;

    while (server->IsCurrentlyUsed())
    {
        Client* client = server->WaitForClient();

        if (client)
        {
            client->EventCallBackSocket = server->EventCallBackSocket;

            server->NumberOfConnectedClients++;

            if (server->EventCallBackServer)
            {
                server->EventCallBackServer->OnClientConnected(*client);
            }

            client->CommunicationThread.Create(Client::CommunicationFunctionAsync, client);

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
    }

    return 0;
}