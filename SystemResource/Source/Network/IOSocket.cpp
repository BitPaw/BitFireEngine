#include "IOSocket.h"
#include <stdio.h>
#include <string.h>

#include "SocketActionResult.h"

char BF::IOSocket::IsCurrentlyUsed()
{
    return ID != -1;
}

BF::IOSocket::IOSocket()
{
    ID = -1;
    Port = -1;
    IPMode = IPVersion::IPVersionInvalid;

    Callback = 0;
    CommunicationThread = 0;

    memset(BufferMessage, 0, SocketBufferSize);
    memset(&AdressIPv4, 0, sizeof(struct sockaddr_in));

#ifdef OSUnix
    memset(&socket->AdressIPv6, 0, sizeof(socket->AdressIPv6));
#elif defined(OSWindows)
    memset(&AdressIPv6, 0, sizeof(AdressIPv6));
#endif
}

BF::SocketActionResult BF::IOSocket::SetupAdress(IPVersion ipVersion, const char* ip, unsigned short port)
{  
    int adressFamily = GetAdressFamily(ipVersion);
    const unsigned char socketType = SOCK_STREAM;

    IPMode = ipVersion;
    Port = port;

    switch (ipVersion)
    {
        case IPVersion::IPVersion4:
        {
            memset(&AdressIPv4, 0, sizeof(AdressIPv4));
            AdressIPv4.sin_family = adressFamily;
            AdressIPv4.sin_addr.s_addr = ip == 0 ? htonl((u_long) ip) : inet_addr(ip);
            AdressIPv4.sin_port = htons(port);
            break;
        }

        case IPVersion::IPVersion6:
        {
#ifdef OSUnix
            struct addrinfo adressIPv6RAW;
            struct addrinfo* adressIPv6Result = &AdressIPv6;
            struct addrinfo** adressIPv6HintPointer = &adressIPv6Adress;
#elif defined(OSWindows)
            ADDRINFO adressIPv6RAW;
            ADDRINFO* adressIPv6Result = &AdressIPv6;
            ADDRINFO** adressIPv6HintPointer = &adressIPv6Result;
#endif

            char portString[10];
            int result;

            sprintf_s(portString, "%i", port);
            memset(&adressIPv6RAW, 0, sizeof(ADDRINFO));
  
            adressIPv6RAW.ai_family = adressFamily; //    AF_INET / AF_INET6:
            adressIPv6RAW.ai_socktype = socketType;
            adressIPv6RAW.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
            adressIPv6RAW.ai_protocol = IPPROTO_TCP;

            result = getaddrinfo(ip, portString, &adressIPv6RAW, adressIPv6HintPointer);

            AdressIPv6 = *adressIPv6Result;

            switch (result)
            {
                case 0:
                    return SocketActionResult::Successful;

                case EAI_AGAIN: 	// A temporary failure in name resolution occurred.
                {
                    break;
                }
                case EAI_BADFLAGS: // An invalid value was provided for the ai_flags member of the pHints parameter.
                {
                    break;
                }
                case EAI_FAIL: // A nonrecoverable failure in name resolution occurred.
                {
                    break;
                }
                case EAI_FAMILY: // The ai_family member of the pHints parameter is not supported.
                {
                    break;
                }
                case EAI_MEMORY: // A memory allocation failure occurred.
                {
                    break;
                }
                case EAI_NONAME: // The name does not resolve for the supplied parameters or the pNodeName and pServiceName parameters were not provided.
                {
                    break;
                }
                case EAI_SERVICE: // The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter.
                {
                    break;
                }
                case EAI_SOCKTYPE: // The ai_socktype member of the pHints parameter is not supported.
                {
                    break;
                }
            }

            break;
        }
    }

    return SocketActionResult::Successful; // Delete this
}

BF::SocketActionResult BF::IOSocket::Open(IPVersion ipVersion, unsigned short port)
{    
#ifdef OSWindows
    SocketActionResult errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketActionResult::Successful)
    {
        return errorCode;
    }
#endif 

    SetupAdress(ipVersion, 0, port);

    // Create Socket
    {
        int adressFamily;
        int streamType;
        int protocol;

        switch (IPMode)
        {
            default:
            case IPVersion::IPVersion4:
            {
                adressFamily = AdressIPv4.sin_family;
                streamType = SOCK_STREAM;
                protocol = 0;
                break;
            }
            case IPVersion::IPVersion6:
            {
#ifdef OSUnix
                adressFamily = serverSocket->AdressIPv6.ai_family;
                streamType = serverSocket->AdressIPv6.ai_socktype;
                protocol = serverSocket->AdressIPv6.ai_protocol;
#elif defined(OSWindows)
                adressFamily = AdressIPv6.ai_family;
                streamType = AdressIPv6.ai_socktype;
                protocol = AdressIPv6.ai_protocol;
#endif

                break;
            }
        }

        ID = socket(adressFamily, streamType, protocol);

        if (ID == -1)
        {
            return SocketActionResult::SocketCreationFailure;
        }
    }

    // Set Socket Options
    {
        const int level = SOL_SOCKET;

#ifdef OSUnix
        const int optionName = SO_REUSEADDR;      // Do not use SO_REUSEADDR, else the port can be hacked. SO_REUSEPORT
#elif defined(OSWindows)
        const int optionName = SO_EXCLUSIVEADDRUSE;
#endif
        const char opval = 1;
        int optionsocketResult = setsockopt(ID, level, optionName, &opval, sizeof(opval));

        if (optionsocketResult == 1)
        {
            return SocketActionResult::SocketOptionFailure;
        }
    }
       
    // Bind Socket
    {
        int bindingResult = -1;
        switch (ipVersion)
        {
            case IPVersion::IPVersion4:
            {
                bindingResult = bind(ID, (const sockaddr*) &AdressIPv4, sizeof(AdressIPv4));
                break;
            }

            case IPVersion::IPVersion6:
            {
#ifdef OSUnix
                bindingResult = bind(serverSocket->ID, serverSocket->AdressIPv6.ai_addr, serverSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
                bindingResult = bind(ID, AdressIPv6.ai_addr, AdressIPv6.ai_addrlen);
#endif


                break;
            }
        }

        if (bindingResult == -1)
        {
            return SocketActionResult::SocketBindingFailure;
        }
    }

    // Listen
    {
        int maximalClientsWaitingInQueue = 10;
        int listeningResult = listen(ID, maximalClientsWaitingInQueue);

        if (listeningResult == -1)
        {
            return SocketActionResult::SocketListeningFailure;
        }
    }

    if (Callback)
    {
        Callback->OnConnectionListening(ID);
    }

    return SocketActionResult::Successful;
}

void BF::IOSocket::Close()
{
    char isSocketUsed = IsCurrentlyUsed();

    if (!isSocketUsed)
    {
        return;
    }

#ifdef OSWindows
    shutdown(ID, SD_SEND);
    closesocket(ID);
#elif defined(OSUnix)
    close(socket->ID);
#endif     

    if (Callback)
    {
        Callback->OnConnectionTerminated(ID);
    }

    ID = -1;
}

void BF::IOSocket::AwaitConnection(IOSocket& clientSocket)
{
    switch (IPMode)
    {
        case IPVersion::IPVersion4:
        {
            const int adressDataLength = sizeof(clientSocket.AdressIPv4);
            clientSocket.ID = accept(ID, (sockaddr*)&clientSocket.AdressIPv4, (int*)&adressDataLength);
            break;
        }

        case IPVersion::IPVersion6:
        {
#ifdef OSUnix
            clientSocket->ID = accept(serverSocket->ID, clientSocket->AdressIPv6.ai_addr, clientSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
            memset(&clientSocket.AdressIPv6, 0, sizeof(ADDRINFO));
            clientSocket.ID = accept(ID, (sockaddr*)&clientSocket.AdressIPv6.ai_addr, (int*)&AdressIPv6.ai_addrlen);
#endif
            break;
        }
    }
}

BF::SocketActionResult BF::IOSocket::Connect(IOSocket& serverSocket, const  char* ipAdress, unsigned short port)
{
#ifdef OSWindows
    SocketActionResult errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketActionResult::Successful)
    {
        return errorCode;
    }
#endif  

    SetupAdress(AnalyseIPVersion(ipAdress) ,ipAdress, port);

    // Create Socket
    {
        int adressFamily;
        int streamType;
        int protocol;       

        switch (IPMode)
        {
            case IPVersion::IPVersion4:
            {
                adressFamily = AdressIPv4.sin_family;
                streamType = SOCK_STREAM;
                protocol = 0;
                break;                
            }   
            case IPVersion::IPVersion6:
            {
#ifdef OSUnix
                adressFamily = clientSocket->AdressIPv6.ai_family;
                streamType = clientSocket->AdressIPv6.ai_socktype;
                protocol = clientSocket->AdressIPv6.ai_protocol;
#elif defined(OSWindows)
                adressFamily = AdressIPv6.ai_family;
                streamType = AdressIPv6.ai_socktype;
                protocol = AdressIPv6.ai_protocol;
#endif

                break;
            }
            default:
            {
                return SocketActionResult::SocketCreationFailure;
            }
        }

        ID = socket(adressFamily, streamType, protocol);

        if (ID == -1)
        {
            return SocketActionResult::SocketCreationFailure;
        }
    }

    // Connect
    {     
        SetupAdress(IPMode, ipAdress, port);

        switch (IPMode)
        {
            case IPVersion::IPVersion4:
            {
                serverSocket.ID = connect(ID, (const sockaddr*) &AdressIPv4, sizeof(AdressIPv4));
                break;
            }

            case IPVersion::IPVersion6:
            {
#ifdef OSUnix
                serverSocket.ID = connect(clientSocket->ID, clientSocket->AdressIPv6.ai_addr, clientSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
                serverSocket.ID = connect(ID, AdressIPv6.ai_addr, AdressIPv6.ai_addrlen);
#endif

                break;
            }
        }

        if (serverSocket.ID == -1)
        {
            return SocketActionResult::SocketConnectionFailure;
        }
    }

    if (Callback)
    {
        Callback->OnConnectionEstablished(ID);
    }

    return SocketActionResult::Successful;
}

BF::SocketActionResult BF::IOSocket::Receive()
{
    unsigned int byteRead = 0;

    memset(BufferMessage, 0, SocketBufferSize);

#ifdef OSUnix
    byteRead = read(ID, BufferMessage, SocketBufferSize - 1);
#elif defined(OSWindows)
    byteRead = recv(ID, BufferMessage, SocketBufferSize - 1, 0);
#endif

    switch (byteRead)
    {
        case (unsigned int)-1:
            return SocketActionResult::SocketRecieveFailure;

        case 0:// endOfFile
        {
            Close();

            return SocketActionResult::SocketRecieveConnectionClosed;
        }  
        default:
        {
            if (Callback)
            {
                Callback->OnMessageReceive(ID, BufferMessage, byteRead);
            }

            return SocketActionResult::Successful;
        }          
    }
}

BF::SocketActionResult BF::IOSocket::Send(const char* message, size_t messageLength)
{
    unsigned int writtenBytes = 0;

    if (messageLength == 0)
    {
        return SocketActionResult::Successful; // Do not send anything if the message is empty
    }

    if (Callback)
    {
        Callback->OnMessageSend(ID, message, messageLength);
    }

#ifdef OSUnix
    writtenBytes = write(ID, message, messageLength);
#elif defined(OSWindows)
    writtenBytes = send(ID, message, messageLength, 0);
#endif  

    switch (writtenBytes)
    {
        case (unsigned int)-1:
            return SocketActionResult::SocketSendFailure;

        default:
            return SocketActionResult::Successful;
    }   
}

int BF::IOSocket::GetAdressFamily(IPVersion ipVersion)
{
    switch (ipVersion)
    {
        case IPVersion::IPVersion4:
            return AF_INET;

        case IPVersion::IPVersion6:
            return AF_INET6;

        default:
            return -1;
    }

    return PF_UNSPEC;
}

#ifdef OSWindows
BF::SocketActionResult BF::IOSocket::WindowsSocketAgentStartup()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int result = -1;

    memset(&wsaData, 0, sizeof(WSADATA));

    result = WSAStartup(wVersionRequested, &wsaData);

    switch (result)
    {
        case WSASYSNOTREADY:
            return SocketActionResult::SubSystemNotReady;

        case WSAVERNOTSUPPORTED:
            return SocketActionResult::VersionNotSupported;

        case WSAEINPROGRESS:
            return SocketActionResult::BlockedByOtherOperation;

        case WSAEPROCLIM:
            return SocketActionResult::LimitReached;

        case WSAEFAULT:
            return SocketActionResult::InvalidParameter;

        case 0:
        default:
            return SocketActionResult::Successful;
    }
}
BF::SocketActionResult BF::IOSocket::WindowsSocketAgentShutdown()
{
    int result = WSACleanup();

    switch (result)
    {
        case WSANOTINITIALISED:
        {
            return SocketActionResult::SubSystemNotInitialised;
        }
        case WSAENETDOWN:
        {
            return SocketActionResult::SubSystemNetworkFailed;
        }
        case WSAEINPROGRESS:
        {
            return SocketActionResult::SocketIsBlocking;
        }   
        case 0:
        default:
            return SocketActionResult::Successful;
    }
}
#endif