#include "IOSocket.h"
#include <stdio.h>
#include <string.h>


char BF::IOSocket::IsCurrentlyUsed()
{
    return ID != -1;
}

BF::IOSocket::IOSocket()
{
    ID = -1;
    Port = -1;
    IPMode = IPVersion::IPVersionInvalid;

    OnMessage = 0;
    OnConnected = 0;
    OnDisconnected = 0;

    memset(Message, 0, SocketBufferSize);
    memset(&AdressIPv4, 0, sizeof(struct sockaddr_in));

#ifdef OSUnix
    memset(&socket->AdressIPv6, 0, sizeof(socket->AdressIPv6));
#elif defined(OSWindows)
    memset(&AdressIPv6, 0, sizeof(AdressIPv6));
#endif
}

char BF::IOSocket::SetupAdress(IPVersion ipVersion, char* ip, unsigned short port)
{  
    int adressFamily = GetAdressFamily(ipVersion);

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
            struct addrinfo adressIPv6Hint;
            struct addrinfo* adressIPv6Adress = &connectionSocket->AdressIPv6;
            struct addrinfo** adressIPv6HintPointer = &adressIPv6Adress;
#elif defined(OSWindows)
            ADDRINFO adressIPv6Hint;
            ADDRINFO* adressIPv6Result = &AdressIPv6;
            ADDRINFO** adressIPv6HintPointer = &adressIPv6Result;
#endif

            char portString[10];
            int result;

            sprintf(portString, "%i", port);
            memset(&adressIPv6Hint, 0, sizeof(adressIPv6Hint));
  
            adressIPv6Hint.ai_family = adressFamily; //    AF_INET / AF_INET6:
            adressIPv6Hint.ai_socktype = SOCK_STREAM;
            adressIPv6Hint.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
            adressIPv6Hint.ai_protocol = IPPROTO_TCP;

            result = getaddrinfo(ip, portString, &adressIPv6Hint, adressIPv6HintPointer);

#ifdef OSUnix
            connectionSocket->AdressIPv6 = **adressIPv6HintPointer;
#endif

            switch (result)
            {
                case 0:
                    return SocketNoError;

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

    return SocketNoError; // Delete this
}

SocketError BF::IOSocket::Open(IPVersion ipVersion, unsigned short port)
{    
#ifdef OSWindows
    SocketError errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketNoError)
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
            return SocketCreationFailure;
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
            return SocketOptionFailure;
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
            return SocketBindingFailure;
        }
    }

    // Listen
    {
        int maximalClientsWaitingInQueue = 10;
        int listeningResult = listen(ID, maximalClientsWaitingInQueue);

        if (listeningResult == -1)
        {
            return SocketListeningFailure;
        }
    }

    return SocketNoError;
}

void BF::IOSocket::Close()
{
    char isSocketUsed = IsCurrentlyUsed();
    char hasOnDisconnectCallBack = OnDisconnected != 0;

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

    if (hasOnDisconnectCallBack)
    {
        OnDisconnected(ID);
    }
}

void BF::IOSocket::AwaitConnection(IOSocket* clientSocket)
{
    switch (IPMode)
    {
        case IPVersion::IPVersion4:
        {
            const int adressDataLength = sizeof(clientSocket->AdressIPv4);
            clientSocket->ID = accept(ID, (sockaddr*)&clientSocket->AdressIPv4, (int*)&adressDataLength);
            break;
        }

        case IPVersion::IPVersion6:
        {
#ifdef OSUnix
            clientSocket->ID = accept(serverSocket->ID, clientSocket->AdressIPv6.ai_addr, clientSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
            memset(&clientSocket->AdressIPv6, 0, sizeof(ADDRINFO));
            clientSocket->ID = accept(ID, (sockaddr*)&clientSocket->AdressIPv6.ai_addr, (int*)AdressIPv6.ai_addrlen);
#endif
            break;
        }
    }
}

SocketError BF::IOSocket::Connect(IOSocket* serverSocket, char* ipAdress, unsigned short port)
{
#ifdef OSWindows
    SocketError errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketNoError)
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
                return SocketCreationFailure;
            }
        }

        ID = socket(adressFamily, streamType, protocol);

        if (ID == -1)
        {
            return SocketCreationFailure;
        }
    }

    // Connect
    {     
        SetupAdress(IPMode, ipAdress, port);

        switch (IPMode)
        {
            case IPVersion::IPVersion4:
            {
                serverSocket->ID = connect(ID, (const sockaddr*) &AdressIPv4, sizeof(AdressIPv4));
                break;
            }

            case IPVersion::IPVersion6:
            {
#ifdef OSUnix
                serverSocket->ID = connect(clientSocket->ID, clientSocket->AdressIPv6.ai_addr, clientSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
                serverSocket->ID = connect(ID, AdressIPv6.ai_addr, AdressIPv6.ai_addrlen);
#endif

                break;
            }
        }

        if (serverSocket->ID == -1)
        {
            return SocketConnectionFailure;
        }
    }

    return SocketNoError;
}

SocketError BF::IOSocket::Read()
{
    unsigned int byteRead = 0;

    memset(Message, 0, SocketBufferSize);

#ifdef OSUnix
    byteRead = read(socket->ID, &socket->Message[0], SocketBufferSize - 1);
#elif defined(OSWindows)
    byteRead = recv(ID, &Message[0], SocketBufferSize - 1, 0);
#endif

    if (byteRead == -1)
    {
        return SocketRecieveFailure;
    }

    if (byteRead == 0) // endOfFile
    {
        return SocketRecieveConnectionClosed;
    }

    return SocketNoError;
}

SocketError BF::IOSocket::Write(char* message)
{
    int messageLengh = 0;
    unsigned int writtenBytes = 0;

    while (message[messageLengh++] != '\0') { }

   // memcpy(&message[messageLengh - 1], "\r\n\0", 3 * sizeof(char)); // Add line ending.

    //essageLengh += 2; // add cause of new length.

    if (messageLengh == 0)
    {
        return SocketNoError; // Just send nothing if the message is empty
    }

#ifdef OSUnix
    writtenBytes = write(socket->ID, message, messageLengh);
#elif defined(OSWindows)
    writtenBytes = send(ID, message, messageLengh, 0);
#endif  

    if (writtenBytes == -1)
    {        
        return SocketSendFailure;
    }

    return SocketNoError;
}

#ifdef OSUnix
void* SocketReadAsync(IOSocket* socket)
#elif defined(OSWindows)
unsigned long BF::IOSocket::ReadAsync()
#endif
{
    // Send & Recieve <Permanent Loop>!
    while (1)
    {
        SocketError errorCode = Read();
        char* message = &Message[0];

        if (errorCode == SocketNoError)
        {
            char hasCallBack = OnMessage != 0;

            if (hasCallBack)
            {
                OnMessage(ID, message);
            }
        }
        else
        {
            break;
        }
    }

    Close();

    return 0;
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
SocketError BF::IOSocket::WindowsSocketAgentStartup()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int result = -1;

    memset(&wsaData, 0, sizeof(WSADATA));

    result = WSAStartup(wVersionRequested, &wsaData);

    switch (result)
    {
        case WSASYSNOTREADY:
            return SubSystemNotReady;

        case WSAVERNOTSUPPORTED:
            return VersionNotSupported;

        case WSAEINPROGRESS:
            return BlockedByOtherOperation;

        case WSAEPROCLIM:
            return LimitReached;

        case WSAEFAULT:
            return InvalidParameter;

        case 0:
        default:
            return SocketNoError;
    }
}
int BF::IOSocket::WindowsSocketAgentShutdown()
{
    int result = WSACleanup();

    switch (result)
    {
        case WSANOTINITIALISED:
        {
            return SubSystemNotInitialised;
        }
        case WSAENETDOWN:
        {
            return SubSystemNetworkFailed;
        }
        case WSAEINPROGRESS:
        {
            return SocketIsBlocking;
        }   
        case 0:
        default:
            return SocketNoError;
    }
}
#endif