#include "IOSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IOSocketMessage.h"

#define SocketPackageIDFileBegin 'F'
#define SocketPackageIDFileEnd '/'

#if defined(OSWindows)
#define EAI_ADDRFAMILY WSAHOST_NOT_FOUND
#endif

#include <ErrorCode.h>
#include <Hardware/Memory/Memory.h>

bool BF::IOSocket::IsCurrentlyUsed()
{
    return AdressInfo.SocketID != -1;
}

BF::SocketActionResult BF::IOSocket::SetupAdress
(
    char* ip, 
    unsigned short port, 
    IPAdressFamily ipMode, 
    SocketType socketType, 
    ProtocolMode protocolMode,
    size_t& adressInfoListSize,
    IPAdressInfo** adressInfoList
)
{
    char portNumberString[30];
    char* portNumberStringAdress = nullptr;
    AdressInfoType adressHints { 0 };
    AdressInfoType* adressResult = nullptr;    
    // ADRRINFOW?

#if defined(OSWindows)
    {
        const SocketActionResult wsaResult = WindowsSocketAgentStartup();
        const bool sucessful = wsaResult == SocketActionResult::Successful;

        if(!sucessful)
        {
            return wsaResult;
        }
    }  
#endif 

    if (port != -1)
    {
        sprintf(portNumberString, "%i", port);
        portNumberStringAdress = portNumberString;
    }

    adressHints.ai_flags = AI_PASSIVE;    // For wildcard IP address (AI_NUMERICHOST | AI_PASSIVE;)
    adressHints.ai_family = ConvertIPAdressFamily(ipMode);
    adressHints.ai_socktype = ConvertSocketType(socketType); // Datagram socket
    adressHints.ai_protocol = ConvertProtocolMode(protocolMode);
    adressHints.ai_addrlen = 0;
    adressHints.ai_canonname = nullptr;
    adressHints.ai_addr = nullptr;
    adressHints.ai_next = nullptr;    

    int adressInfoResult = getaddrinfo(ip, portNumberString, &adressHints, &adressResult);
    
    switch (adressInfoResult)
    {
        case 0:
            break; // OK - Sucess

        case EAI_ADDRFAMILY:
            return SocketActionResult::HostHasNoNetworkAddresses;

        case EAI_AGAIN:
            return SocketActionResult::NameServerReturnedTemporaryFailureIndication;

        case EAI_BADFLAGS:
            return SocketActionResult::SocketFlagsInvalid;

        case EAI_FAIL:
            return SocketActionResult::NameServerReturnedPermanentFailureIndication;

        case EAI_FAMILY:
            return SocketActionResult::RequestedAddressFamilyNotSupported;

        case EAI_MEMORY:
            return SocketActionResult::OutOfMemory;

       // case EAI_NODATA:
        //    return SocketActionResult::HostExistsButHasNoData;

        //case EAI_NONAME:
          //  return SocketActionResult::IPOrPortNotKnown;

        case EAI_SERVICE:
            return SocketActionResult::RequestedServiceNotAvailableForSocket;

        case EAI_SOCKTYPE:
            return SocketActionResult::SocketTypeNotSupported;

#if defined(OSWindows)
        case WSANOTINITIALISED:
            return SocketActionResult::WindowsSocketSystemNotInitialized;
#endif
        default:
       // case EAI_SYSTEM:
        {
            ErrorCode error = GetCurrentError();

            break;
        }
    }

    for (AdressInfoType* adressInfo = adressResult; adressInfo ; adressInfo = adressInfo->ai_next)
    {
        ++adressInfoListSize;
    }

    // Allocate 
    (*adressInfoList) = new IPAdressInfo[adressInfoListSize];

    if (!(*adressInfoList))
    {
        AdressInfoDelete(adressResult);
        return SocketActionResult::OutOfMemory;
    }

    size_t index = 0;

    for (AdressInfoType* rp = adressResult; rp ; rp = rp->ai_next)
    {
        IPAdressInfo& adressInfo = (*adressInfoList)[index++];

        adressInfo.ConvertFrom(*rp);    
    }

    AdressInfoDelete(adressResult);

    return SocketActionResult::Successful;
}

BF::IOSocket::IOSocket()
{
    EventCallBackSocket = 0;
}

void BF::IOSocket::Close()
{
    char isSocketUsed = IsCurrentlyUsed();

    if (!isSocketUsed)
    {
        return;
    }

#ifdef OSWindows
    shutdown(AdressInfo.SocketID, SD_SEND);
    closesocket(AdressInfo.SocketID);
#elif defined(OSUnix)
    close(AdressInfo.SocketID);
#endif   

    if (EventCallBackSocket)
    {
        EventCallBackSocket->OnConnectionTerminated(AdressInfo);
    }

    AdressInfo.SocketID = SocketIDOffline;
}

BF::SocketActionResult BF::IOSocket::Create
(
    const IPAdressFamily adressFamily,
    const SocketType socketType,
    const ProtocolMode protocolMode,
    size_t& socketID
)
{
    const int ipAdressFamilyID = ConvertIPAdressFamily(adressFamily);
    const int socketTypeID = ConvertSocketType(socketType);
    const int protocolModeID = ConvertProtocolMode(protocolMode);

#if defined(OSWindows)
    {
        const SocketActionResult permissionGranted = WindowsSocketAgentStartup();
        const bool sucessful = permissionGranted == SocketActionResult::Successful;

        if(!sucessful)
        {
            return permissionGranted;
        }
    }  
#endif 

    const size_t socketIDResult = socket(ipAdressFamilyID, socketTypeID, protocolModeID);

    {
        const bool wasSucessful = socketIDResult != SocketIDOffline;

        if(!wasSucessful)
        {
            return SocketActionResult::SocketCreationFailure;
        }
    } 

    socketID = socketIDResult;

    return SocketActionResult::Successful;
}

BF::SocketActionResult BF::IOSocket::Receive(Byte* message, const size_t messageLength)
{
    unsigned int byteRead = 0;

    if (!IsCurrentlyUsed())
    {
        return SocketActionResult::SocketIsNotConnected;
    }

    // Read
    {
        char* data = (char*)message;

#if defined(OSUnix)
        byteRead = read(AdressInfo.SocketID, data, messageLength);
#elif defined(OSWindows)
        byteRead = recv(AdressInfo.SocketID, data, messageLength, 0);
#endif
    }

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
                IOSocketMessage socketMessage(AdressInfo.SocketID, message, byteRead);

                EventCallBackSocket->OnMessageReceive(socketMessage);
            }

            return SocketActionResult::Successful;
        }          
    }
}

BF::SocketActionResult BF::IOSocket::Send(const Byte* message, const size_t messageLength)
{
    unsigned int writtenBytes = 0;

    if (!IsCurrentlyUsed())
    {
        return SocketActionResult::SocketIsNotConnected;
    }

    if (messageLength == 0)
    {
        return SocketActionResult::Successful; // Do not send anything if the message is empty
    }

    if (EventCallBackSocket)
    {
        IOSocketMessage socketMessage(AdressInfo.SocketID, message, messageLength);

        EventCallBackSocket->OnMessageSend(socketMessage);
    }

    // Send into stream
    {
        const char* data = (const char*)message;

#if defined(OSUnix)
        writtenBytes = write(AdressInfo.SocketID, data, messageLength);
#elif defined(OSWindows)
        writtenBytes = send(AdressInfo.SocketID, data, messageLength, 0);
#endif 
    }
    
    switch (writtenBytes)
    {
        case (unsigned int)-1:
            return SocketActionResult::SocketSendFailure;

        default:
            return SocketActionResult::Successful;
    }   
}

BF::SocketActionResult BF::IOSocket::SendFile(const char* filePath, const size_t sendBufferSize)
{
    FILE* file = fopen(filePath, "rb");
    Byte buffer[2048];

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

#ifdef OSWindows
BF::SocketActionResult BF::IOSocket::WindowsSocketAgentStartup()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData{ 0 };
    const int result = WSAStartup(wVersionRequested, &wsaData);

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