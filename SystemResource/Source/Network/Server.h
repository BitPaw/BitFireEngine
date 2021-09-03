#ifndef ServerIncluded
#define ServerIncluded

#include "Client.h"
#include "IOSocket.h"

namespace BF
{
    class Server
    {
        public:
        IOSocket Socket;

        Client* ClientList;
        unsigned int NumberOfConnectedClients;
        unsigned int NumberOfMaximalClients;

        private:
        Client* GetNextClient();

        public:
        Server();

        char Start(IPVersion ipVersion, unsigned short port);
        void Stop();
        void KickClient(int socketID);
        Client* WaitForClient();
        Client* GetClientViaID(int socketID);
        SocketError SendToClient(int clientID, char* message);
        SocketError BroadcastToClients(char* message);
        void RegisterClient(Client* client);
        void UnRegisterClient(Client* client);
    };
}
#endif
