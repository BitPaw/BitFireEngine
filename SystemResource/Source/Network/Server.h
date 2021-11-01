#pragma once

#include "Client.h"
#include "IOSocket.h"

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
        Server();

     

        SocketActionResult Start(IPVersion ipVersion, unsigned short port);
        void Stop();
        void KickClient(int socketID);
        Client* WaitForClient();
        Client* GetClientViaID(int socketID);
        SocketActionResult SendToClient(int clientID, char* message);
        SocketActionResult BroadcastToClients(char* message);
        void RegisterClient(Client* client);
        void UnRegisterClient(Client* client);
    };
}