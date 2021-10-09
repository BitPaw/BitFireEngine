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
    ClientList = 0;
    NumberOfConnectedClients = 0;
    NumberOfMaximalClients = 10;

    ClientList = new Client[10];
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

    return 0;
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
                server->RegisterClient(client);

                client->Callback = server->Callback;

                client->CommunicationThread = new std::thread([](Client* client)
                {
                    while (client->IsCurrentlyUsed())
                    {
                        SocketActionResult socketActionResult = client->Read();


                    }

                }, client);               
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
      
    if(client->ID == -1)
    {
        return 0;
    }

    if (Callback)
    {
        Callback->OnConnectionLinked(ID);
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

BF::SocketActionResult BF::Server::SendToClient(int clientID, char* message)
{
    // Client LookUp
    Client* client = GetClientViaID(clientID);

    if (client == 0)
    {
        // Error: No client with this ID.
        return SocketActionResult::SocketSendFailure;
    }

    // Sent to Client;
    return Write(message);
}

BF::SocketActionResult BF::Server::BroadcastToClients(char* message)
{
    SocketActionResult errorCode = SocketActionResult::InvalidResult;

    for (size_t i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];

        if (client->ID != -1)
        {
            SocketActionResult currentCrrorCode = Write(message);

            if (currentCrrorCode != SocketActionResult::Successful)
            {
                errorCode = currentCrrorCode;
            }
        }     
    }

    return errorCode;
}

void BF::Server::RegisterClient(Client* client)
{
    NumberOfConnectedClients++;

   // server->ClientList = realloc(server->ClientList, ++server->NumberOfConnectedClients);

    //server->ClientList[server->NumberOfConnectedClients - 1] = *client;  
}

void BF::Server::UnRegisterClient(Client* client)
{
    NumberOfConnectedClients--;
}