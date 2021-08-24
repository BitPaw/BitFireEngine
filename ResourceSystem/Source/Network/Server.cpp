#include "Server.h"
#include "../Async/Thread.h"

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
        char isUsed = Socket.IsCurrentlyUsed();

        if (!isUsed)
        {
            return client;
        }
    }

    return 0;
}

char BF::Server::Start(IPVersion ipVersion, unsigned short port)
{
    SocketError errorCode = Socket.Open(ipVersion, port);
    
    return errorCode == SocketError::SocketNoError;
}

void BF::Server::Stop()
{
    char isRunning = Socket.IsCurrentlyUsed();

    if (isRunning)
    {        
        Socket.Close();
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
    
    Socket.AwaitConnection(&client->Socket);
      
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

BF::SocketError BF::Server::SendToClient(int clientID, char* message)
{
    // Client LookUp
    Client* client = GetClientViaID(clientID);

    if (client == 0)
    {
        // Error: No client with this ID.
        return SocketError::SocketSendFailure;
    }

    // Sent to Client;
    return Socket.Write(message);
}

BF::SocketError BF::Server::BroadcastToClients(char* message)
{
    SocketError errorCode = SocketError::SocketNoError;

    for (size_t i = 0; i < NumberOfMaximalClients; i++)
    {
        Client* client = &ClientList[i];

        if (client->Socket.ID != -1)
        {
            SocketError currentCrrorCode = Socket.Write(message);

            if (currentCrrorCode != SocketError::SocketNoError)
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