#pragma once

#include "IOSocket.h"
#include "IClientListener.hpp"

#include <Async/Thread.h>

#define IPSize 60

namespace BF
{
    class Client : public IOSocket
    {
        public:
        IPAdressInfo ConnectedServerInfo;

        IClientListener* EventCallBackClient;

        Client();

        SocketActionResult ConnectToServer(const char* ip, unsigned short port, const void* threadObject, const ThreadFunction threadFunction);

        static ThreadFunctionReturnType CommunicationFunctionAsync(void* ioSocket);
    }; 
}