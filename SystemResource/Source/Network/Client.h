#pragma once

#include "IOSocket.h"
#include "../Async/Thread.h"
#include "IClientListener.hpp"

#define IPSize 60

namespace BF
{
    class Client : public IOSocket
    {
        public:
        IPAdressInfo ConnectedServerInfo;

        IClientListener* EventCallBackClient;

        Client();

        SocketActionResult ConnectToServer(const char* ip, unsigned short port);
        void Disconnect();

        static ThreadFunctionReturnType CommunicationFunctionAsync(void* ioSocket);
    }; 
}