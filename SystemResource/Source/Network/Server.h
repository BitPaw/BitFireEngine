#pragma once

#include "Client.h"
#include "IOSocket.h"
#include "IServerListener.h"
#include "SocketActionResult.h"

#include "../Async/Thread.h"
#include "../Async/AsyncLock.h"

namespace BF
{
    class Server
    {
        private:
        Client* GetNextClient();
        AsyncLock _clientListLock;

        public:
        IServerListener* EventCallBackServer;
        ISocketListener* EventCallBackSocket; // Gets attached to all clients

        //---<InputSterams>
        Client* ClientList;
        size_t NumberOfConnectedClients;
        size_t NumberOfMaximalClients;
        //-----------------------------------

        //---<Ouput>
        size_t SocketListSize;
        IOSocket* SocketList;
        //-----------------------------------

        Server();
        ~Server();

        SocketActionResult Start(unsigned short port);
        void Stop();
        void KickClient(int socketID);
        Client* GetClientViaID(int socketID);

        void RegisterClient(IOSocket* client);

        SocketActionResult SendMessageToClient(int clientID, char* message, size_t messageLength);
        SocketActionResult SendFileToClient(int clientID, const char* filePath);
        SocketActionResult SendFileToClient(int clientID, const wchar_t* filePath);

        SocketActionResult BroadcastMessageToClients(char* message, size_t messageLength);
        SocketActionResult BroadcastFileToClients(const char* filePath);

        static ThreadFunctionReturnType ClientListeningThread(void* server);
    };
}