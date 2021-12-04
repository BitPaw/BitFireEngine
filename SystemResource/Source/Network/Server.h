#pragma once

#include "Client.h"
#include "IOSocket.h"
#include "IServerListener.h"

namespace BF
{
    class Server : public IOSocket
    {
        public:
        Client* ClientList;
        unsigned int NumberOfConnectedClients;
        unsigned int NumberOfMaximalClients;

        private:
        Client* GetNextClient();
        std::thread* _clientListeningThread;

        public:
        IServerListener* EventCallBackServer;

        Server();

        SocketActionResult Start(IPVersion ipVersion, unsigned short port);
        void Stop();
        void KickClient(int socketID);
        Client* WaitForClient();
        Client* GetClientViaID(int socketID);
        SocketActionResult SendToClient(int clientID, char* message, size_t messageLength);
        SocketActionResult SendFileToClient(int clientID, const char* filePath);
        SocketActionResult BroadcastToClients(char* message, size_t messageLength);
    };
}