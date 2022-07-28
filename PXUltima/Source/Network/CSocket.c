#include "CSocket.h"

#include <Memory/Memory.h>
#include <Event/Event.h>


#define ProtocolInvalid (unsigned int)-1
#define ProtocolHOPOPTS 0
#define ProtocolICMP 1
#define ProtocolIGMP 2
#define ProtocolGGP 3
#define ProtocolIPV4 4
#define ProtocolST 5
#define ProtocolTCP 6
#define ProtocolCBT 7
#define ProtocolEGP 8
#define ProtocolIGP 9
#define ProtocolPUP 12
#define ProtocolUDP 17
#define ProtocolIDP 22
#define ProtocolRDP 27
#define ProtocolIPV6 41
#define ProtocolROUTING 43
#define ProtocolFRAGMENT 44
#define ProtocolESP 50
#define ProtocolAH 51
#define ProtocolICMPV6 58
#define ProtocolNONE 59
#define ProtocolDSTOPTS 60
#define ProtocolND 77
#define ProtocolICLFXBM 78
#define ProtocolPIM 103
#define ProtocolPGM 113
#define ProtocolL2TP 115
#define ProtocolSCTP 132
#define ProtocolRAW 255
#define ProtocolMAX 256
#define ProtocolWindowsRAW 257
#define ProtocolWindowsIPSEC 258
#define ProtocolWindowsIPSECOFFLOAD 259
#define ProtocolWindowsWNV 260
#define ProtocolWindowsMAX 261






#define IPAF_UNSPEC 0 // Unspecified
#define IPAF_LOCAL 1 // Local to host (pipes and file-domain). 
#define IPAF_UNIX IPAF_LOCAL // POSIX name for IPAF_LOCAL. 
#define IPAF_FILE IPAF_LOCAL // Another non-standard name for IPAF_LOCAL. 
#define IPAF_INET 2 // IP protocol family. 
#define IPAF_AX25 3 // Amateur Radio AX.25. 
#define IPAF_IMPLINK 3 // arpanet imp addresses
#define IPAF_IPX 4 // Novell Internet Protocol. 
#define IPAF_PUP 4 // pup protocols: e.g. BSP
#define IPAF_APPLETALK 5 // Appletalk DDP. 
#define IPAF_CHAOS 5 // mit CHAOS protocols
#define IPAF_NETROM 6 // Amateur radio NetROM. 
#define IPAF_NS 6 // XEROX NS protocols
#define IPAF_IPX IPAF_NS // IPX protocols: IPX, SPX, etc.
#define IPAF_BRIDGE 7 // Multiprotocol bridge. 
#define IPAF_ISO 7 // ISO protocols
#define IPAF_OSI IPAF_ISO // OSI is ISO
#define IPAF_ATMPVC 8 // ATM PVCs. 
#define IPAF_ECMA 8 // european computer manufacturers
#define IPAF_X25 9 // Reserved for X.25 project. 
#define IPAF_DATAKIT 9 // datakit protocols
#define IPAF_INET6 10 // IP version 6. 
#define IPAF_CCITT 10 // CCITT protocols, X.25 etc
#define IPAF_ROSE 11 // Amateur Radio X.25 PLP. 
#define IPAF_SNA 11 // IBM SNA
#define IPAF_DECnet 12 // Reserved for DECnet project. 
#define IPAF_DECnet 12 // DECnet
#define IPAF_NETBEUI 13 // Reserved for 802.2LLC project. 
#define IPAF_DLI 13 // Direct data link interface
#define IPAF_SECURITY 14 // Security callback pseudo AF. 
#define IPAF_LAT 14 // LAT
#define IPAF_KEY 15 // IPAF_KEY key management API. 
#define IPAF_HYLINK 15 // NSC Hyperchannel
#define IPAF_NETLINK 16
#define IPAF_APPLETALK 16 // AppleTalk
#define IPAF_ROUTE IPAF_NETLINK // Alias to emulate 4.4BSD. 
#define IPAF_PACKET 17 // Packet family. 
#define IPAF_NETBIOS 17 // NetBios-style addresses
#define IPAF_ASH 18 // Ash. 
#define IPAF_VOICEVIEW 18 // VoiceView
#define IPAF_ECONET 19 // Acorn Econet. 
#define IPAF_FIREFOX 19 // Protocols from Firefox
#define IPAF_ATMSVC 20 // ATM SVCs. 
#define IPAF_UNKNOWN1 20 // Somebody is using this!
#define IPAF_RDS 21 // RDS sockets. 
#define IPAF_BAN 21 // Banyan
#define IPAF_SNA 22 // Linux SNA Project 
#define IPAF_ATM 22 // Native ATM Services
#define IPAF_IRDA 23 // IRDA sockets. 
#define IPAF_INET6 23 // Internetwork Version 6
#define IPAF_PPPOX 24 // PPPoX sockets. 
#define IPAF_CLUSTER 24 // Microsoft Wolfpack
#define IPAF_WANPIPE 25 // Wanpipe API sockets. 
#define IPAF_12844 25 // IEEE 1284.4 WG AF
#define IPAF_LLC 26 // Linux LLC. 
#define IPAF_IRDA 26 // IrDA
#define IPAF_IB 27 // Native InfiniBand address. 
#define IPAF_MPLS 28 // MPLS. 
#define IPAF_NETDES 28 // Network Designers OSI & gateway
#define IPAF_CAN 29 // Controller Area Network. 
#define IPAF_TIPC 30 // TIPC sockets. 
#define IPAF_BLUETOOTH 31 // Bluetooth sockets. 
#define IPAF_IUCV 32 // IUCV sockets. 
#define IPAF_RXRPC 33 // RxRPC sockets. 
#define IPAF_ISDN 34 // mISDN sockets. 
#define IPAF_PHONET 35 // Phonet sockets. 
#define IPAF_IEEE802154 36 // IEEE 802.15.4 sockets. 
#define IPAF_CAIF 37 // CAIF sockets. 
#define IPAF_ALG 38 // Algorithm sockets. 
#define IPAF_NFC 39 // NFC sockets. 
#define IPAF_VSOCK 40 // vSockets. 
#define IPAF_KCM 41 // Kernel Connection Multiplexor. 
#define IPAF_QIPCRTR 42 // Qualcomm IPC Router. 
#define IPAF_SMC 43 // SMC sockets. 
#define IPAF_XDP 44 // XDP sockets. 
#define IPAF_MAX 45 // For now.. 

#define IPAF_TCNPROCESS   29
#define IPAF_TCNMESSAGE   30
#define IPAF_ICLFXBM      31
#define IPAF_BTH          32              // Bluetooth RFCOMM/L2CAP protocols
#define IPAF_LINK         33
#define IPAF_HYPERV       34
#define IPAF_MAX          35

#define IPAF_Invalid 0xFF










#if defined(OSWindows)
#define EAI_ADDRFAMILY WSAHOST_NOT_FOUND
#endif


#ifdef OSUnix
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define AdressInfoType struct addrinfo
#elif defined(OSWindows)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#define AdressInfoType ADDRINFOA
#endif

#define SOCK_Invalid 0xFF 


ProtocolMode ConvertToProtocolMode(const unsigned int protocolMode)
{
    switch(protocolMode)
    {
        case ProtocolHOPOPTS:
            return ProtocolModeHOPOPTS;

        case ProtocolICMP:
            return ProtocolModeICMP;

        case ProtocolIGMP:
            return ProtocolModeIGMP;

        case ProtocolGGP:
            return ProtocolModeGGP;

        case ProtocolIPV4:
            return ProtocolModeIPV4;

        case ProtocolST:
            return ProtocolModeST;

        case ProtocolTCP:
            return ProtocolModeTCP;

        case ProtocolCBT:
            return ProtocolModeCBT;

        case ProtocolEGP:
            return ProtocolModeEGP;

        case ProtocolIGP:
            return ProtocolModeIGP;

        case ProtocolPUP:
            return ProtocolModePUP;

        case ProtocolUDP:
            return ProtocolModeUDP;

        case ProtocolIDP:
            return ProtocolModeIDP;

        case ProtocolRDP:
            return ProtocolModeRDP;

        case ProtocolIPV6:
            return ProtocolModeIPV6;

        case ProtocolROUTING:
            return ProtocolModeROUTING;

        case ProtocolFRAGMENT:
            return ProtocolModeFRAGMENT;

        case ProtocolESP:
            return ProtocolModeESP;

        case ProtocolAH:
            return ProtocolModeAH;

        case ProtocolICMPV6:
            return ProtocolModeICMPV6;

        case ProtocolNONE:
            return ProtocolModeNONE;

        case ProtocolDSTOPTS:
            return ProtocolModeDSTOPTS;

        case ProtocolND:
            return ProtocolModeND;

        case ProtocolICLFXBM:
            return ProtocolModeICLFXBM;

        case ProtocolPIM:
            return ProtocolModePIM;

        case ProtocolPGM:
            return ProtocolModePGM;

        case ProtocolL2TP:
            return ProtocolModeL2TP;

        case ProtocolSCTP:
            return ProtocolModeSCTP;

        case ProtocolRAW:
            return ProtocolModeRAW;

        case ProtocolMAX:
            return ProtocolModeMAX;

        case ProtocolWindowsRAW:
            return ProtocolModeWindowsRAW;

        case ProtocolWindowsIPSEC:
            return ProtocolModeWindowsIPSEC;

        case ProtocolWindowsIPSECOFFLOAD:
            return ProtocolModeWindowsIPSECOFFLOAD;

        case ProtocolWindowsWNV:
            return ProtocolModeWindowsWNV;

        case ProtocolWindowsMAX:
            return ProtocolModeWindowsMAX;

        default:
            return ProtocolModeInvalid;
    }
}

unsigned int ConvertFromProtocolMode(const ProtocolMode protocolMode)
{
    switch(protocolMode)
    {
        default:
        case ProtocolModeInvalid:
            return ProtocolInvalid;

        case ProtocolModeHOPOPTS:
            return ProtocolHOPOPTS;

        case ProtocolModeICMP:
            return ProtocolICMP;

        case ProtocolModeIGMP:
            return ProtocolIGMP;

        case ProtocolModeGGP:
            return ProtocolGGP;

        case ProtocolModeIPV4:
            return ProtocolIPV4;

        case ProtocolModeST:
            return ProtocolST;

        case ProtocolModeTCP:
            return ProtocolTCP;

        case ProtocolModeCBT:
            return ProtocolCBT;

        case ProtocolModeEGP:
            return ProtocolEGP;

        case ProtocolModeIGP:
            return ProtocolIGP;

        case ProtocolModePUP:
            return ProtocolPUP;

        case ProtocolModeUDP:
            return ProtocolUDP;

        case ProtocolModeIDP:
            return ProtocolIDP;

        case ProtocolModeRDP:
            return ProtocolRDP;

        case ProtocolModeIPV6:
            return ProtocolIPV6;

        case ProtocolModeROUTING:
            return ProtocolROUTING;

        case ProtocolModeFRAGMENT:
            return ProtocolFRAGMENT;

        case ProtocolModeESP:
            return ProtocolESP;

        case ProtocolModeAH:
            return ProtocolAH;

        case ProtocolModeICMPV6:
            return ProtocolICMPV6;

        case ProtocolModeNONE:
            return ProtocolNONE;

        case ProtocolModeDSTOPTS:
            return ProtocolDSTOPTS;

        case ProtocolModeND:
            return ProtocolND;

        case ProtocolModeICLFXBM:
            return ProtocolICLFXBM;

        case ProtocolModePIM:
            return ProtocolPIM;

        case ProtocolModePGM:
            return ProtocolPGM;

        case ProtocolModeL2TP:
            return ProtocolL2TP;

        case ProtocolModeSCTP:
            return ProtocolSCTP;

        case ProtocolModeRAW:
            return ProtocolRAW;

        case ProtocolModeMAX:
            return ProtocolMAX;

        case ProtocolModeWindowsRAW:
            return ProtocolWindowsRAW;

        case ProtocolModeWindowsIPSEC:
            return ProtocolWindowsIPSEC;

        case ProtocolModeWindowsIPSECOFFLOAD:
            return ProtocolWindowsIPSECOFFLOAD;

        case ProtocolModeWindowsWNV:
            return ProtocolWindowsWNV;

        case ProtocolModeWindowsMAX:
            return ProtocolWindowsMAX;
    }
}

CSocketType ConvertToSocketType(unsigned int socketType)
{
    switch(socketType)
    {
        case SOCK_STREAM:
            return CSocketTypeStream;

        case SOCK_DGRAM:
            return CSocketTypeDatagram;

        case SOCK_RAW:
            return CSocketTypeRaw;

        case SOCK_RDM:
            return CSocketTypeRDM;

        case SOCK_SEQPACKET:
            return CSocketTypeSeqPacket;

        default:
            return CSocketTypeInvalid;
    }
}

unsigned int ConvertFromSocketType(CSocketType socketType)
{
    switch(socketType)
    {
        default:
        case CSocketTypeInvalid:
            return SOCK_Invalid;

        case CSocketTypeStream:
            return SOCK_STREAM;

        case CSocketTypeDatagram:
            return SOCK_DGRAM;

        case CSocketTypeRaw:
            return SOCK_RAW;

        case CSocketTypeRDM:
            return SOCK_RDM;

        case CSocketTypeSeqPacket:
            return SOCK_SEQPACKET;
    }
}

IPAdressFamily ConvertToIPAdressFamily(const unsigned int ipMode)
{
    switch(ipMode)
    {
        case IPAF_UNSPEC: return IPAdressFamilyUnspecified;
        case IPAF_UNIX: return IPAdressFamilyUNIX;
        case IPAF_INET: return IPAdressFamilyINET;
        case IPAF_IMPLINK: return IPAdressFamilyIMPLINK;
        case IPAF_PUP: return IPAdressFamilyPUP;
        case IPAF_CHAOS: return IPAdressFamilyCHAOS;
        case IPAF_NS: return IPAdressFamilyNS;
            //case IPAF_IPX: return IPAdressFamilyIPX;
        case IPAF_ISO: return IPAdressFamilyISO;
            //case IPAF_OSI: return IPAdressFamilyOSI;
        case IPAF_ECMA: return IPAdressFamilyECMA;
        case IPAF_DATAKIT: return IPAdressFamilyDATAKIT;
        case IPAF_CCITT: return IPAdressFamilyCCITT;
        case IPAF_SNA: return IPAdressFamilySNA;
        case IPAF_DECnet: return IPAdressFamilyDECnet;
        case IPAF_DLI: return IPAdressFamilyDLI;
        case IPAF_LAT: return IPAdressFamilyLAT;
        case IPAF_HYLINK: return IPAdressFamilyHYLINK;
        case IPAF_APPLETALK: return IPAdressFamilyAPPLETALK;
        case IPAF_NETBIOS: return IPAdressFamilyNETBIOS;
        case IPAF_VOICEVIEW: return IPAdressFamilyVOICEVIEW;
        case IPAF_FIREFOX: return IPAdressFamilyFIREFOX;
        case IPAF_UNKNOWN1: return IPAdressFamilyUNKNOWN1;
        case IPAF_BAN: return IPAdressFamilyBAN;
            //case IPAF_ATM: return IPAdressFamilyATM;
        case IPAF_INET6: return IPAdressFamilyINET6;
        case IPAF_CLUSTER: return IPAdressFamilyCLUSTER;
        case IPAF_12844: return IPAdressFamilyIEEE12844;
        case IPAF_IRDA: return IPAdressFamilyIRDA;
        case IPAF_NETDES: return IPAdressFamilyNETDES;

        default:
            return IPAdressFamilyInvalid;
    }
}

unsigned int ConvertFromIPAdressFamily(const IPAdressFamily ipMode)
{
    switch(ipMode)
    {
        default:
        case IPAdressFamilyInvalid:
            return IPAF_Invalid;

        case IPAdressFamilyUnspecified:
            return IPAF_UNSPEC;

        case IPAdressFamilyUNIX:
            return IPAF_UNIX;

        case IPAdressFamilyINET:
            return IPAF_INET;

        case IPAdressFamilyIMPLINK:
            return IPAF_IMPLINK;

        case IPAdressFamilyPUP:
            return IPAF_PUP;

        case IPAdressFamilyCHAOS:
            return IPAF_CHAOS;

        case IPAdressFamilyNS:
            return IPAF_NS;

        case IPAdressFamilyIPX:
            return IPAF_IPX;

        case IPAdressFamilyISO:
            return IPAF_ISO;

        case IPAdressFamilyOSI:
            return IPAF_OSI;

        case IPAdressFamilyECMA:
            return IPAF_ECMA;

        case IPAdressFamilyDATAKIT:
            return IPAF_DATAKIT;

        case IPAdressFamilyCCITT:
            return IPAF_CCITT;

        case IPAdressFamilySNA:
            return IPAF_SNA;

        case IPAdressFamilyDECnet:
            return IPAF_DECnet;

        case IPAdressFamilyDLI:
            return IPAF_DLI;

        case IPAdressFamilyLAT:
            return IPAF_LAT;

        case IPAdressFamilyHYLINK:
            return IPAF_HYLINK;

        case IPAdressFamilyAPPLETALK:
            return IPAF_APPLETALK;

        case IPAdressFamilyNETBIOS:
            return IPAF_NETBIOS;

        case IPAdressFamilyVOICEVIEW:
            return IPAF_VOICEVIEW;

        case IPAdressFamilyFIREFOX:
            return IPAF_FIREFOX;

        case IPAdressFamilyUNKNOWN1:
            return IPAF_UNKNOWN1;

        case IPAdressFamilyBAN:
            return IPAF_BAN;

        case IPAdressFamilyATM:
            return IPAF_ATM;

        case IPAdressFamilyINET6:
            return IPAF_INET6;

        case IPAdressFamilyCLUSTER:
            return IPAF_CLUSTER;

        case IPAdressFamilyIEEE12844:
            return IPAF_12844;

        case IPAdressFamilyIRDA:
            return IPAF_IRDA;

        case IPAdressFamilyNETDES:
            return IPAF_NETDES;

        case IPAdressFamilyMAX:
            return IPAF_MAX;

        case IPAdressFamilyLINK:
            return IPAF_LINK;

        case IPAdressFamilyHYPERV:
            return IPAF_HYPERV;

        case IPAdressFamilyBTH:
            return IPAF_BTH;

        case IPAdressFamilyTCNPROCESS:
            return IPAF_TCNPROCESS;

        case IPAdressFamilyTCNMESSAGE:
            return IPAF_TCNMESSAGE;

        case IPAdressFamilyICLFXBM:
            return IPAF_ICLFXBM;
    }
}

void CSocketConstruct(CSocket* cSocket)
{
    MemorySet(cSocket, sizeof(CSocket), 0);
}

void CSocketDestruct(CSocket* cSocket)
{
}

ActionResult CSocketCreate
(
    CSocket* cSocket,
    const IPAdressFamily adressFamily,
    const CSocketType socketType,
    const ProtocolMode protocolMode
)
{
    const int ipAdressFamilyID = ConvertFromIPAdressFamily(adressFamily);
    const int socketTypeID = ConvertFromSocketType(socketType);
    const int protocolModeID = ConvertFromProtocolMode(protocolMode);

#if defined(OSWindows)
    {
        const ActionResult permissionGranted = WindowsSocketAgentStartup();
        const unsigned char sucessful = ResultSuccessful == permissionGranted;

        if(!sucessful)
        {
            return permissionGranted;
        }
    }
#endif 

    {
        const size_t socketIDResult = socket(ipAdressFamilyID, socketTypeID, protocolModeID);
        const unsigned char wasSucessful = socketIDResult != -1;

        if(!wasSucessful)
        {
            return SocketCreationFailure;
        }

        cSocket->ID = socketIDResult;
    }

    cSocket->Family = adressFamily;
    cSocket->Protocol = protocolMode;
    cSocket->Type = socketType;


    return ResultSuccessful;
}

ActionResult CSocketConnect(CSocket* cSocket)
{
    const int serverSocketID = connect(cSocket->ID, (struct sockaddr*)cSocket->IP, cSocket->IPSize);
    const unsigned char connected = serverSocketID != -1;

    if(!connected)
    {
        return SocketConnectionFailure;
    }

    return ResultSuccessful;
}

ActionResult CSocketSetupAdress
(
    CSocket* cSocketList,
    const size_t cSocketListSizeMax,
    size_t* cSocketListSize,
    char* ip, // null for any ipAdress
    unsigned short port, // -1 for no port
    IPAdressFamily ipMode,
    CSocketType socketType,
    ProtocolMode protocolMode
)
{
    char portNumberString[30];
    char* portNumberStringAdress = 0;
    AdressInfoType adressHints;
    AdressInfoType* adressResult = 0;
    // ADRRINFOW?

#if defined(OSWindows)
    {
        const ActionResult wsaResult = WindowsSocketAgentStartup();
        const unsigned char sucessful = wsaResult == ResultSuccessful;

        if(!sucessful)
        {
            return wsaResult;
        }
    }
#endif 

    if(port != -1)
    {
        sprintf(portNumberString, "%i", port);
        portNumberStringAdress = portNumberString;
    }

    adressHints.ai_flags = AI_PASSIVE;    // For wildcard IP address (AI_NUMERICHOST | AI_PASSIVE;)
    adressHints.ai_family = ConvertIPAdressFamily(ipMode);
    adressHints.ai_socktype = ConvertSocketType(socketType); // Datagram socket
    adressHints.ai_protocol = ConvertProtocolMode(protocolMode);
    adressHints.ai_addrlen = 0;
    adressHints.ai_canonname = 0;
    adressHints.ai_addr = 0;
    adressHints.ai_next = 0;

    int adressInfoResult = getaddrinfo(ip, portNumberString, &adressHints, &adressResult);

    switch(adressInfoResult)
    {
        case 0:
            break; // OK - Sucess

        case EAI_ADDRFAMILY:
            return HostHasNoNetworkAddresses;

        case EAI_AGAIN:
            return NameServerReturnedTemporaryFailureIndication;

        case EAI_BADFLAGS:
            return SocketFlagsInvalid;

        case EAI_FAIL:
            return NameServerReturnedPermanentFailureIndication;

        case EAI_FAMILY:
            return RequestedAddressFamilyNotSupported;

        case EAI_MEMORY:
            return OutOfMemory;

            // case EAI_NODATA:
             //    return SocketActionResultHostExistsButHasNoData;

             //case EAI_NONAME:
               //  return SocketActionResultIPOrPortNotKnown;

        case EAI_SERVICE:
            return RequestedServiceNotAvailableForSocket;

        case EAI_SOCKTYPE:
            return SocketTypeNotSupported;

#if defined(OSWindows)
        case WSANOTINITIALISED:
            return WindowsSocketSystemNotInitialized;
#endif
        default:
            // case EAI_SYSTEM:
        {
            // ErrorCode error = GetCurrentError();

            break;
        }
    }

    size_t index = 0;

    for(AdressInfoType* adressInfo = adressResult; adressInfo; adressInfo = adressInfo->ai_next)
    {
        CSocket* csocket = &cSocketList[index++];
        struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)adressInfo->ai_addr;
        const char* result = 0;

        MemorySet(csocket->IP, IPv6LengthMax, 0);

        result = inet_ntop(adressInfo->ai_family, &ipv6->sin6_addr, csocket->IP, IPv6LengthMax);

        switch(adressInfo->ai_family)
        {
            case AF_INET:
            {
                csocket->Port = ntohs((((struct sockaddr_in*)adressInfo->ai_addr)->sin_port));
                break;
            }
            case AF_INET6:
            {
                csocket->Port = ntohs((((struct sockaddr_in6*)adressInfo->ai_addr)->sin6_port));
                break;
            }
            default:
            {
                csocket->Port = 0;
                break;
            }
        }

        csocket->Protocol = ConvertProtocolMode(adressInfo->ai_protocol);
        csocket->Family = ConvertIPAdressFamily(adressInfo->ai_family);
        csocket->Type = ConvertSocketType(adressInfo->ai_socktype);

        csocket->IPSize = adressInfo->ai_addrlen;
        MemoryCopy(adressInfo->ai_addr, adressInfo->ai_addrlen, csocket->IP, IPv6LengthMax);
    }

    *cSocketListSize = index;

    AdressInfoDelete(adressResult);

    return ResultSuccessful;
}

unsigned char CSocketIsCurrentlyUsed(CSocket* cSocket)
{
    return cSocket->ID != -1;
}

void CSocketClose(CSocket* cSocket)
{
    // If not used, we cant close.
    {
        const unsigned char isSocketUsed = CSocketIsCurrentlyUsed(cSocket);

        if(!isSocketUsed)
        {
            return;
        }
    }

#ifdef OSWindows
    shutdown(cSocket->ID, SD_SEND);
    closesocket(cSocket->ID);
#elif defined(OSUnix)
    close(cSocket->ID);
#endif   

    InvokeEvent(cSocket->ConnectionTerminatedCallback, cSocket);

    cSocket->ID = SocketIDOffline;
}

ActionResult CSocketBind(CSocket* cSocket)
{
    const int bindingResult = bind(cSocket->ID, (struct sockaddr*)cSocket->IP, cSocket->IPSize);
    const unsigned char sucessful = bindingResult == 0; //-1

    if(!sucessful)
    {
        return SocketBindingFailure;
    }

    return ResultSuccessful;
}

ActionResult CSocketOptionsSet(CSocket* cSocket)
{
    if(cSocket->ID != -1)
    {
        return;
    }

    const int level = SOL_SOCKET;

    const int optionName =
#if defined(OSUnix)
        SO_REUSEADDR;      // Do not use SO_REUSEADDR, else the port can be hacked. SO_REUSEPORT
#elif defined(OSWindows)
        SO_EXCLUSIVEADDRUSE;
#endif
    const char opval = 1;
    const int optionsocketResult = setsockopt(cSocket->ID, level, optionName, &opval, sizeof(opval));
    const unsigned char sucessful = optionsocketResult == 0;

    if(!sucessful)
    {
        return SocketOptionFailure;
    }

    return ResultSuccessful;
}

ActionResult CSocketListen(CSocket* cSocket)
{
    const int maximalClientsWaitingInQueue = 10;
    const int listeningResult = listen(cSocket->ID, maximalClientsWaitingInQueue);
    const unsigned char sucessful = listeningResult == 0;

    if(listeningResult == -1)
    {
        return SocketListeningFailure;
    }

    return ResultSuccessful;
}

ActionResult CSocketAccept(CSocket* server, CSocket* client)
{
    client->IPSize = IPv6LengthMax; // Needed for accept(), means 'length i can use'. 0 means "I canot perform"
    client->ID = accept
    (
        server->ID,
        (struct sockaddr*)client->IP,
#if defined(OSUnix)
        (socklen_t*)&client->IPSize
#elif defined(OSWindows)
        (int*)&client->IPSize
#endif        
    );

    const unsigned char sucessful = client->ID != -1;

    if(!sucessful)
    {
        return SocketBindingFailure;
    }

    return ResultSuccessful;
}

ActionResult CSocketSend(CSocket* cSocket, const void* inputBuffer, const size_t inputBufferSize, size_t* inputBytesWritten)
{
    // Check if socket is active and ready to send
    {
        const unsigned char isReady = CSocketIsCurrentlyUsed(cSocket);

        if(!isReady)
        {
            return SocketIsNotConnected;
        }
    }

    // Do we even send anything? If not, quit
    {
        const unsigned char hasDataToSend = inputBuffer && inputBufferSize > 0; // if NULL or 0 Bytes, return

        if(!hasDataToSend)
        {
            return ResultSuccessful; // Do not send anything if the message is empty
        }
    }

    InvokeEvent(cSocket->MessageSendCallback, cSocket->ID, inputBuffer, inputBufferSize);

#if SocketDebug
    printf("[#][Socket][Send] You >>> <%zi> %li Bytes\n", cSocket->ID, inputBufferSize);
#endif  

    // Send data
    {
        const char* data = (const char*)inputBuffer;

        const int writtenBytes =
#if defined(OSUnix)
            write(cSocket->ID, data, inputBufferSize);
#elif defined(OSWindows)
            send(cSocket->ID, data, inputBufferSize, 0);
#endif 
        const unsigned char sucessfulSend = writtenBytes != -1;

        if(!sucessfulSend)
        {
            return SocketSendFailure;
        }

        *inputBytesWritten = writtenBytes;
    }

    return ResultSuccessful;
}

ActionResult CSocketReceive(CSocket* cSocket, const void* outputBuffer, const size_t outputBufferSize, size_t* outputBytesWritten)
{
    // I did not read any data yet
    *outputBytesWritten = 0;

    // Check if socket is active and ready to send
    {
        const unsigned char isReady = IsCurrentlyUsed();

        if(!isReady)
        {
            return SocketIsNotConnected;
        }
    }

    // Read data
    {
        char* data = (char*)outputBuffer;
        int length = outputBufferSize;

        //StateChange(SocketStateDataReceiving);

        const unsigned int byteRead =
#if defined(OSUnix)
            read(cSocket->ID, data, length);
#elif defined(OSWindows)
            recv(cSocket->ID, data, length, 0);
#endif

        // StateChange(SocketStateIDLE);

        switch(byteRead)
        {
            case (unsigned int)-1:
                return SocketRecieveFailure;

            case 0:// endOfFile
            {
                CSocketClose(cSocket);

                return SocketRecieveConnectionClosed;
            }
            default:
            {
                *outputBytesWritten = byteRead;

#if SocketDebug
                printf("[#][Socket][Read] You <<< <%li> %i Bytes\n", cSocket->ID, byteRead);
#endif

                InvokeEvent(cSocket->MessageReceiveCallback, cSocket->ID, outputBuffer, byteRead);
            }
        }
    }
    return ResultSuccessful;
}

#if defined(OSWindows)
ActionResult WindowsSocketAgentStartup()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    MemorySet(&wsaData, sizeof(WSADATA), 0);
    const int result = WSAStartup(wVersionRequested, &wsaData);

    switch(result)
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
            return ResultSuccessful;
    }
}

ActionResult WindowsSocketAgentShutdown()
{
    int result = WSACleanup();

    switch(result)
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
            return ResultSuccessful;
    }
}
#endif