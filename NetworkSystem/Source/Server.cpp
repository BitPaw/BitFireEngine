#include "Server.h"
#include "Thread.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
        char isUsed = IsCurrentlyUsed();

        if (!isUsed)
        {
            return client;
        }
    }

    return 0;
}

char BF::Server::Start(IPVersion ipVersion, unsigned short port)
{
    SocketError errorCode = Open(ipVersion, port);
    
    return errorCode == SocketNoError;
}

void BF::Server::Stop()
{
    char isRunning = IsCurrentlyUsed();

    if (isRunning)
    {        
        Close();
    }
}

void BF::Server::KickClient(int socketID)
{
    Client* client = GetClientViaID(socketID);

    client->Disconnect();
}

BF::Client* BF::Server::WaitForClient()
{
    char hasCallBack = Socket.OnConnected != 0;
    Client* client = GetNextClient();
    
    AwaitConnection(&client->Socket);
      
    if(client->Socket.ID == -1)
    {
        return 0;
    }

    if (hasCallBack)
    {
        Socket.OnConnected(Socket.ID);
    }

    RegisterClient(client);
    
  //  ThreadCreate(&client->CommunicationThread, [](void* data) -> unsigned long { ReadAsync; }, &client->Socket);

    return client;
}

BF::Client* BF::Server::GetClientViaID(int socketID)
{
    for (unsigned int i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];
        int clientSocketID = client->Socket.ID;
        char foundTarget = clientSocketID == socketID;

        if (foundTarget)
        {
            return client;
        }
    }

    return 0;
}

SocketError BF::Server::SendToClient(int clientID, char* message)
{
    // Client LookUp
    Client* client = GetClientViaID(clientID);

    if (client == 0)
    {
        // Error: No client with this ID.
        return SocketSendFailure;
    }

    // Sent to Client;
    return Write(message);
}

SocketError BF::Server::BroadcastToClients(char* message)
{
    SocketError errorCode = SocketNoError;

    for (size_t i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];

        if (client->Socket.ID != -1)
        {
            SocketError currentCrrorCode = Write(message);

            if (currentCrrorCode != SocketNoError)
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