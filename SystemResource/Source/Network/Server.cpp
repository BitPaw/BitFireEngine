#include "Server.h"
#include "SocketActionResult.h"
#include "../Async/Thread.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <cassert>

BF::Server::Server()
{
    _clientListeningThread = nullptr;

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

BF::SocketActionResult BF::Server::Start(IPVersion ipVersion, unsigned short port)
{
    SocketActionResult socketActionResult = Open(ipVersion, port);

    if (socketActionResult != SocketActionResult::Successful)
    {
        return socketActionResult;
    }         

    CommunicationThread = new std::thread([](Server* server)
    {
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

                client->CommunicationThread = new std::thread([](Client* client, Server* server)
                {
                    while (client->IsCurrentlyUsed())
                    {
                        SocketActionResult socketActionResult = client->Receive();                                        

                    }

                    server->NumberOfConnectedClients--;                 

                    if (server->EventCallBackServer)
                    {
                        server->EventCallBackServer->OnClientDisconnected(*client);
                    }

                    client->Disconnect();

                }, client, server);               
            }
        }

    }, this);

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

BF::SocketActionResult BF::Server::SendToClient(int clientID, char* message, size_t messageLength)
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

BF::SocketActionResult BF::Server::BroadcastToClients(char* message, size_t messageLength)
{
    SocketActionResult errorCode = SocketActionResult::InvalidResult;

    for (size_t i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];

        if (client->IsCurrentlyUsed())
        {
            SocketActionResult currentCrrorCode = Send(message, messageLength);

            if (currentCrrorCode != SocketActionResult::Successful)
            {
                errorCode = currentCrrorCode;
            }
        }     
    }

    return errorCode;
}