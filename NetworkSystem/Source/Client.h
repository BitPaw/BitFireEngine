#ifndef ClientIncluded
#define ClientIncluded

#include "IOSocket.h"
#include "Thread.h"

namespace BF
{
    class Client : IOSocket
    {
        public:
        char* IP;
        IOSocket Socket;

        int ConnectedServerID;
        IOSocket ConnectedServerData;

        Thread CommunicationThread;

        Client();
        char ConnectToServer(char* ip, unsigned short port);
        void SendCommand();
        void Disconnect();
    }; 
}

#endif