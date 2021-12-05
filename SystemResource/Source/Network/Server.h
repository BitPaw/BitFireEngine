#pragma once

#include "Client.h"
#include "IOSocket.h"
#include "IServerListener.h"
#include "SocketActionResult.h"

#include "../Async/Thread.h"

namespace BF
{
    class Server : public IOSocket
    {
        private:
        Client* GetNextClient();
        Thread _clientListeningThread;     

        public:
        IServerListener* EventCallBackServer;
        Client* ClientList;
        unsigned int NumberOfConnectedClients;
        unsigned int NumberOfMaximalClients;

        Server();

        SocketActionResult Start(unsigned short port);
        void Stop();
        void KickClient(int socketID);
        Client* WaitForClient();
        Client* GetClientViaID(int socketID);

        SocketActionResult SendMessageToClient(int clientID, char* message, size_t messageLength);
        SocketActionResult SendFileToClient(int clientID, const char* filePath);

        SocketActionResult BroadcastMessageToClients(char* message, size_t messageLength);
        SocketActionResult BroadcastFileToClients(const char* filePath);

        static ThreadFunctionReturnType ClientListeningThread(void* server);
    };
}