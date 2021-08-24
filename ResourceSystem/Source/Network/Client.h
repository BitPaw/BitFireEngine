#ifndef ClientIncluded
#define ClientIncluded

#include "IOSocket.h"
#include "../Async/Thread.h"

namespace BF
{
    class Client
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