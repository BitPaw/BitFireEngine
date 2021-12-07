#include "IOSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IOSocketMessage.h"

#include "../ErrorCode.h"

char BF::IOSocket::IsCurrentlyUsed()
{
    return ID != -1;
}

bool BF::IOSocket::GetIP(char* buffer, size_t bufferSize)
{
    const char* resolvedIP = inet_ntop(AdressInfo.ai_family, AdressInfo.ai_addr, buffer, bufferSize);;

    return resolvedIP;
}

bool BF::IOSocket::GetIPAndPort(char* ip, unsigned short& port)
{
    char sbuf[NI_MAXSERV];
    int returnCode = getnameinfo(AdressInfo.ai_addr, AdressInfo.ai_addrlen, ip, NI_MAXHOST, sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
    bool successful = returnCode == 0;

    port = atoi(sbuf);

    return successful;
}

BF::SocketActionResult BF::IOSocket::SetupAdress(char* ip, unsigned short port, IPAdressFamily ipMode, SocketType socketType, ProtocolMode protocolMode)
{
#if 0 // Use depricated soultion. Only works for IPv4
    hostent* host = gethostbyname(ip);
    char* uh = host->h_addr_list[0];
    size_t size = host->h_length;
    in_addr inaddr;

    memcpy(&inaddr, uh, size);

    char* resolvedIP = inet_ntoa(inaddr);

    strncpy(ip, resolvedIP, 120);
#else 
    char portNumberString[30];
    char* portNumberStringAdress = nullptr;
    ADDRINFOA adressHints;
    ADDRINFOA* adressResult = nullptr;    
    // ADRRINFOW?

    if (port != -1)
    {
        sprintf(portNumberString, "%i", port);
        portNumberStringAdress = portNumberString;
    }

    memset(&adressHints, 0, sizeof(ADDRINFOA));

    adressHints.ai_family = ConvertIPAdressFamily(ipMode);
    adressHints.ai_socktype = ConvertSocketType(socketType); // Datagram socket
    adressHints.ai_flags = AI_PASSIVE;    // For wildcard IP address
    adressHints.ai_protocol = 0;// ConvertProtocolMode(protocolMode);
    adressHints.ai_canonname = NULL;
    adressHints.ai_addr = NULL;
    adressHints.ai_next = NULL;
        
    /*
                adressIPv6RAW.ai_family = adressFamily; //    AF_INET / AF_INET6:
            adressIPv6RAW.ai_socktype = socketType;
            adressIPv6RAW.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
            adressIPv6RAW.ai_protocol = IPPROTO_TCP;
    */

    int adressInfoSuccessful = getaddrinfo(ip, portNumberString, &adressHints, &adressResult);

    char budder[INET6_ADDRSTRLEN];
    size_t bufferSize = INET6_ADDRSTRLEN;



    memcpy(&AdressInfo, adressResult, sizeof(AdressInfo));
    AdressInfo.ai_next = nullptr; 

    for (ADDRINFOA* rp = adressResult; rp != NULL; rp = rp->ai_next)
    {
        memset(budder, 0, INET6_ADDRSTRLEN);

        char ipbuffer[50];
        memset(ipbuffer, 0, 50);
        //memcpy(, );
        struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)rp->ai_addr;
        

        //getnameinfo();
        const char* resolvedIP = inet_ntop(rp->ai_family, &ipv6->sin6_addr, budder, bufferSize);

        printf("IPv%i : %s\n", rp->ai_family == AF_INET6 ? 6 : 4,resolvedIP);

        /*
        int sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

            // close(sfd);
    }

    FreeAddrInfoA(adressResult);

#endif   

    return SocketActionResult::Successful;
}

BF::IOSocket::IOSocket()
{
    ID = -1;
    Port = -1;

    EventCallBackSocket = 0;

    memset(BufferMessage, 0, SocketBufferSize);
    memset(&AdressInfo, 0, sizeof(AdressInfo));
}

void BF::IOSocket::Close()
{
    char isSocketUsed = IsCurrentlyUsed();

    if (!isSocketUsed)
    {
        return;
    }

    //CommunicationThread->detach();

    //delete CommunicationThread;
    //CommunicationThread = nullptr;

#ifdef OSWindows
    shutdown(ID, SD_SEND);
    closesocket(ID);
#elif defined(OSUnix)
    close(socket->ID);
#endif     

    if (EventCallBackSocket)
    {
        EventCallBackSocket->OnConnectionTerminated(ID);
    }

    ID = -1;
}

void BF::IOSocket::AwaitConnection(IOSocket& clientSocket)
{
    clientSocket.AdressInfo.ai_addrlen = 60;
    clientSocket.AdressInfo.ai_addr = (struct sockaddr*)malloc(60);

    clientSocket.ID = accept(ID, clientSocket.AdressInfo.ai_addr, (int*)&clientSocket.AdressInfo.ai_addrlen);

    bool sucessful = clientSocket.ID != -1;

    if (!sucessful)
    {
       ErrorCode errorCode = GetCurrentError();
    }
    else
    {
        if (EventCallBackSocket)
        {
            EventCallBackSocket->OnConnectionLinked(clientSocket.ID);
        }
    }  
}

BF::SocketActionResult BF::IOSocket::Open(unsigned short port, IPAdressFamily ipAdressFamily, SocketType socketType, ProtocolMode protocolMode)
{
#if defined(OSWindows)
    SocketActionResult errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketActionResult::Successful)
    {
        return errorCode;
    }
#endif 

    SetupAdress(nullptr, port, ipAdressFamily, socketType, protocolMode);

    //---<Create Socket>--------------------
    ID = socket(AdressInfo.ai_family, AdressInfo.ai_socktype, AdressInfo.ai_protocol);

    if (ID == -1)
    {
        return SocketActionResult::SocketCreationFailure;
    }
    //---------------------------------------

    // Set Socket Options
    {
        const int level = SOL_SOCKET;

        const int optionName =
#if defined(OSUnix)
            SO_REUSEADDR;      // Do not use SO_REUSEADDR, else the port can be hacked. SO_REUSEPORT
#elif defined(OSWindows)
            SO_EXCLUSIVEADDRUSE;
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
        int bindingResult = bind(ID, AdressInfo.ai_addr, AdressInfo.ai_addrlen);

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

    if (EventCallBackSocket)
    {
        EventCallBackSocket->OnConnectionListening(ID);
    }

    return SocketActionResult::Successful;
}

BF::SocketActionResult BF::IOSocket::Connect(IOSocket& serverSocket, const char* ipAdress, unsigned short port)
{
#ifdef OSWindows
    SocketActionResult errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketActionResult::Successful)
    {
        return errorCode;
    }
#endif  

    IPAdressFamily ipAdressFamily = IPAdressFamily::Unspecified;
    SocketType socketType = SocketType::Stream;
    ProtocolMode protocolMode = ProtocolMode::Any;

    SetupAdress((char*)ipAdress, port, ipAdressFamily, socketType, protocolMode);

    // Create Socket
    ID = socket(AdressInfo.ai_family, AdressInfo.ai_socktype, AdressInfo.ai_protocol);

    if (ID == -1)
    {
        return SocketActionResult::SocketCreationFailure;
    }

    // Connect
    {     
        serverSocket.ID = connect(ID, AdressInfo.ai_addr, AdressInfo.ai_addrlen);

        if (serverSocket.ID == -1)
        {
            BF::ErrorCode errorCode = GetCurrentError();

            return SocketActionResult::SocketConnectionFailure;
        }
    }

    if (EventCallBackSocket)
    {
        EventCallBackSocket->OnConnectionEstablished(ID);
    }

    return SocketActionResult::Successful;
}

BF::SocketActionResult BF::IOSocket::Receive()
{
    unsigned int byteRead = 0;

    memset(BufferMessage, 0, SocketBufferSize);

#if defined(OSUnix)
    byteRead = read(ID, BufferMessage, SocketBufferSize);
#elif defined(OSWindows)
    byteRead = recv(ID, BufferMessage, SocketBufferSize, 0);
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
            if (EventCallBackSocket)
            {
                IOSocketMessage socketMessage(ID, BufferMessage, byteRead);

                EventCallBackSocket->OnMessageReceive(socketMessage);
            }

            return SocketActionResult::Successful;
        }          
    }
}

BF::SocketActionResult BF::IOSocket::Send(const char* message, size_t messageLength)
{
    unsigned int writtenBytes = 0;

    memcpy(BufferMessage, message, messageLength);

    if (messageLength == 0)
    {
        return SocketActionResult::Successful; // Do not send anything if the message is empty
    }

    if (EventCallBackSocket)
    {
        IOSocketMessage socketMessage(ID, BufferMessage, messageLength);

        EventCallBackSocket->OnMessageSend(socketMessage);
    }

#if defined(OSUnix)
    writtenBytes = write(ID, BufferMessage, messageLength);
#elif defined(OSWindows)
    writtenBytes = send(ID, BufferMessage, messageLength, 0);
#endif  

    switch (writtenBytes)
    {
        case (unsigned int)-1:
            return SocketActionResult::SocketSendFailure;

        default:
            return SocketActionResult::Successful;
    }   
}

BF::SocketActionResult BF::IOSocket::SendFile(const char* filePath, size_t sendBufferSize)
{
    FILE* file = fopen(filePath, "rb");
    char buffer[2048];

    if (!file)
    {
        return SocketActionResult::FileNotFound;
    }

    size_t readSize = 0;

    do
    {
        readSize = fread(buffer, sizeof(char), sendBufferSize, file);
        Send(buffer, readSize);
    }
    while (readSize > 0);

    int closeResult = fclose(file);

    return closeResult == 0 ? SocketActionResult::Successful : SocketActionResult::InvalidResult;
}

int BF::IOSocket::GetAdressFamily(IPVersion ipVersion)
{
    switch (ipVersion)
    {
        default:
        case IPVersion::IPVersion4:
            return AF_INET;

        case IPVersion::IPVersion6:
            return AF_INET6;
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