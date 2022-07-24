#include "IOSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IOSocketMessage.h"

#include <Event/Event.h>

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
    State = SocketState::NotInitialised;

    EventCallBackSocket = 0;
}

BF::IOSocket::~IOSocket()
{
    //Close();
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

void BF::IOSocket::StateChange(const SocketState socketState)
{
    State = socketState;
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

BF::SocketActionResult BF::IOSocket::Send(const void* inputBuffer, const size_t inputBufferSize)
{
    // Check if socket is active and ready to send
    {
        const bool isReady = IsCurrentlyUsed();

        if(!isReady)
        {
            return SocketActionResult::SocketIsNotConnected;
        }
    }

    // Do we even send anything? If not, quit
    {
        const bool hasDataToSend = inputBuffer && inputBufferSize > 0; // if NULL or 0 Bytes, return

        if(!hasDataToSend)
        {
            return SocketActionResult::Successful; // Do not send anything if the message is empty
        }
    }

    // Call recievers before sending
    {
        if(EventCallBackSocket)
        {
            IOSocketMessage socketMessage(AdressInfo.SocketID, (unsigned char*)inputBuffer, inputBufferSize);

            EventCallBackSocket->OnMessageSend(socketMessage);
        }
    }

#if SocketDebug
    printf("[#][Socket][Send] You >>> <%zi> %li Bytes\n", AdressInfo.SocketID, inputBufferSize);
#endif

    // Send data
    {
        const char* data = (const char*)inputBuffer;

        const unsigned int writtenBytes =
#if defined(OSUnix)
        write(AdressInfo.SocketID, data, inputBufferSize);
#elif defined(OSWindows)
        send(AdressInfo.SocketID, data, inputBufferSize, 0);
#endif 
        const bool sucessfulSend = writtenBytes != -1;

        if(!sucessfulSend)
        {
            return SocketActionResult::SocketSendFailure;
        }     
    }

    return SocketActionResult::Successful;
}

BF::SocketActionResult BF::IOSocket::Receive(void* outputBuffer, const size_t outputBufferSizeMax, size_t& outputBufferSizeWritten)
{    
    // I did not read any data yet
    outputBufferSizeWritten = 0; 

    // Check if socket is active and ready to send
    {
        const bool isReady = IsCurrentlyUsed();

        if(!isReady)
        {
            return SocketActionResult::SocketIsNotConnected;
        }
    }

    // Is output valid
    {
        const bool canWriteOutput = outputBuffer && outputBufferSizeMax > 0;

        if(!canWriteOutput)
        {
            return SocketActionResult::OuputBufferTooSmal;
        }
    }

    // Read data
    {
        char* data = (char*)outputBuffer;
        int length = outputBufferSizeMax;

        StateChange(SocketState::DataReceiving);

        const unsigned int byteRead =
#if defined(OSUnix)
        read(AdressInfo.SocketID, data, length);
#elif defined(OSWindows)
        recv(AdressInfo.SocketID, data, length, 0);
#endif

        StateChange(SocketState::IDLE);

        switch(byteRead)
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
                outputBufferSizeWritten = byteRead;

#if SocketDebug
                printf("[#][Socket][Read] You <<< <%li> %i Bytes\n", AdressInfo.SocketID, byteRead);
#endif

                if(EventCallBackSocket)
                {
                    IOSocketMessage socketMessage(AdressInfo.SocketID, (unsigned char*)data, byteRead);

                    EventCallBackSocket->OnMessageReceive(socketMessage);
                }
            }
        }
    }

    return SocketActionResult::Successful;
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