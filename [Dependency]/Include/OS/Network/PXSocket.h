#ifndef PXSocketInclude
#define PXSocketInclude

#include <OS/System/OSVersion.h>

#if OSUnix
#ifndef _XOPEN_SOURCE
    // Needed for some reason, as without the "netdb.h" does not get included properly
    // Some say that there a flags that disable the code.
    // This statement here.. counters this.
    #define _XOPEN_SOURCE 600
#endif // _XOPEN_SOURCE
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct addrinfo AdressInfoType; //#define AdressInfoType (struct addrinfo)
#define AdressInfoDelete freeaddrinfo
#elif OSWindows

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1u
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#define AdressInfoType ADDRINFOA
#define AdressInfoDelete FreeAddrInfoA
#endif

//-----------------------------------------------

#include <Format/Type.h>

#include <OS/Thread/PXThread.h>
#include <OS/Error/PXActionResult.h>

typedef PXSize PXSocketID;
#define SocketDebug 1
#define SocketIDOffline -1
#define IPv6LengthMax 65

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum IPAdressFamily_
	{
		IPAdressFamilyInvalid,
		IPAdressFamilyUnspecified, // unspecified
		IPAdressFamilyUNIX, // local to host (pipes, portals)
		IPAdressFamilyINET, // internetwork: UDP, TCP, etc.
		IPAdressFamilyIMPLINK, // arpanet imp addresses
		IPAdressFamilyPUP, // pup protocols: e.g. BSP
		IPAdressFamilyCHAOS, // mit CHAOS protocols
		IPAdressFamilyNS, // XEROX NS protocols
		IPAdressFamilyIPX, // IPX protocols: IPX, SPX, etc.
		IPAdressFamilyISO, // ISO protocols
		IPAdressFamilyOSI, // OSI is ISO
		IPAdressFamilyECMA, // european computer manufacturers
		IPAdressFamilyDATAKIT, // datakit protocols
		IPAdressFamilyCCITT, // CCITT protocols, X.25 etc
		IPAdressFamilySNA, // IBM SNA
		IPAdressFamilyDECnet, // DECnet
		IPAdressFamilyDLI, // Direct data link interface
		IPAdressFamilyLAT, // LAT
		IPAdressFamilyHYLINK, // NSC Hyperchannel
		IPAdressFamilyAPPLETALK, // AppleTalk
		IPAdressFamilyNETBIOS, // NetBios-style addresses
		IPAdressFamilyVOICEVIEW, // VoiceView
		IPAdressFamilyFIREFOX, // Protocols from Firefox
		IPAdressFamilyUNKNOWN1, // Somebody is using this!
		IPAdressFamilyBAN, // Banyan
		IPAdressFamilyATM, // Native ATM Services
		IPAdressFamilyINET6, // Internetwork Version 6
		IPAdressFamilyCLUSTER, // Microsoft Wolfpack
		IPAdressFamilyIEEE12844, // IEEE 1284.4 WG AF
		IPAdressFamilyIRDA, // IrDA
		IPAdressFamilyNETDES, // Network Designers OSI & gateway
		IPAdressFamilyMAX, // depends
		IPAdressFamilyLINK,
		IPAdressFamilyHYPERV,
		IPAdressFamilyBTH, // Bluetooth RFCOMM/L2CAP protocols
		IPAdressFamilyTCNPROCESS,
		IPAdressFamilyTCNMESSAGE,
		IPAdressFamilyICLFXBM
	}
	IPAdressFamily;

	typedef enum PXSocketType_
	{
		PXSocketTypeInvalid,
		PXSocketTypeStream,// stream socket */
		PXSocketTypeDatagram, // datagram socket */
		PXSocketTypeRaw, // raw-protocol interface */
		PXSocketTypeRDM, // reliably-delivered message */
		PXSocketTypeSeqPacket // sequenced packet stream */
	}
	PXSocketType;

	typedef enum ProtocolMode_
	{
		ProtocolModeInvalid,
		ProtocolModeHOPOPTS,  // IPv6 Hop-by-Hop options
		ProtocolModeICMP,
		ProtocolModeIGMP,
		ProtocolModeGGP,
		ProtocolModeIPV4,
		ProtocolModeST,
		ProtocolModeTCP,
		ProtocolModeCBT,
		ProtocolModeEGP,
		ProtocolModeIGP,
		ProtocolModePUP,
		ProtocolModeUDP,
		ProtocolModeIDP,
		ProtocolModeRDP,
		ProtocolModeIPV6, // IPv6 header
		ProtocolModeROUTING, // IPv6 Routing header
		ProtocolModeFRAGMENT, // IPv6 fragmentation header
		ProtocolModeESP, // encapsulating security payload
		ProtocolModeAH, // authentication header
		ProtocolModeICMPV6, // ICMPv6
		ProtocolModeNONE, // IPv6 no next header
		ProtocolModeDSTOPTS, // IPv6 Destination options
		ProtocolModeND,
		ProtocolModeICLFXBM,
		ProtocolModePIM,
		ProtocolModePGM,
		ProtocolModeL2TP,
		ProtocolModeSCTP,
		ProtocolModeRAW,
		ProtocolModeMAX,
		//
		//  These are reserved for private use by Windows.
		//
		ProtocolModeWindowsRAW,
		ProtocolModeWindowsIPSEC,
		ProtocolModeWindowsIPSECOFFLOAD,
		ProtocolModeWindowsWNV,
		ProtocolModeWindowsMAX
	}
	ProtocolMode;

	typedef enum PXSocketState_
	{
		SocketNotInitialised,

		SocketIDLE, // Waiting for action, currently doing nothing
		SocketEventPolling, // Polling for events on multible sockets
		SocketOffline,

		// PXClient only
		SocketConnecting,
		SocketConnected,
		SocketDataReceiving,
		SocketDataSending,
		SocketFileReceiving,
		SocketFileSending,

		// PXServer only
	}
	PXSocketState;

	typedef struct PXSocket_ PXSocket;

	typedef void (*PXSocketCreatingEvent)(const PXSocket* const pxSocket, unsigned char* use);
	typedef void (*PXSocketCreatedEvent)(const PXSocket* const pxSocket);

	typedef void (*PXSocketDataSendEvent)(const PXSocket* const pxSocket, const void* message, const PXSize messageSize);
	typedef void (*PXSocketDataReceiveEvent)(const PXSocket* const pxSocket, const void* const message, const PXSize messageSize);

	// PXServer Only
	typedef void (*PXSocketListeningEvent)(const PXSocket* const pxSocket);
	typedef void (*PXSocketLinkedEvent)(const PXSocket* const pxSocket);

	// PXClient Only
	typedef void (*PXSocketConnectionEstablishedEvent)(const PXSocket* const pxSocket);
	typedef void (*PXSocketConnectionTerminatedEvent)(const PXSocket* const pxSocket);

	typedef void (*PXClientConnectedEvent)(const PXSocket* serverSocket, const PXSocket* clientSocket);
	typedef void (*PXClientDisconnectedEvent)(const PXSocket* serverSocket, const PXSocket* clientSocket);
	typedef void (*PXClientAcceptFailureEvent)(const PXSocket* serverSocket);

	typedef struct PXSocketEventListener_
	{
		//---<Event CallBack>---------
		PXSocketCreatingEvent SocketCreatingCallback;
		PXSocketCreatedEvent SocketCreatedCallback;

		PXSocketDataSendEvent MessageSendCallback;
		PXSocketDataReceiveEvent MessageReceiveCallback;

		// PXServer Only
		PXSocketListeningEvent ConnectionListeningCallback;
		PXSocketLinkedEvent ConnectionLinkedCallback;

		// PXClient Only
		PXSocketConnectionEstablishedEvent ConnectionEstablishedCallback;
		PXSocketConnectionTerminatedEvent ConnectionTerminatedCallback;
		//----------------------------
	}
	PXSocketEventListener;


	typedef struct PXSocket_
	{
		PXSocketState State;

		// Connection Info
		PXSocketID ID;
		ProtocolMode Protocol;
		IPAdressFamily Family;
		PXSocketType Type;
		char IP[IPv6LengthMax];
		PXSize IPSize;
		unsigned short Port;


		void* Owner;

		//----------------------------
		PXSize SocketPollingReadListSize;
		PXSocketID* SocketPollingReadList;

		//---<CPrivate IO>------------
		PXThread CommunicationThread;
		//----------------------------

		PXSocketEventListener EventList;
	}
	PXSocket;

	typedef struct PXSocketAdressSetupInfo_
	{
		const char* const IP; // null for any ipAdress
		unsigned short Port; // -1 for no port
		IPAdressFamily IPMode;
		PXSocketType SocketType;
		ProtocolMode ProtocolMode;
	}
	PXSocketAdressSetupInfo;


	PXPrivate ProtocolMode ConvertToProtocolMode(const unsigned int protocolMode);
	PXPrivate unsigned int ConvertFromProtocolMode(const ProtocolMode protocolMode);

	PXPrivate PXSocketType ConvertToSocketType(const unsigned int socketType);
	PXPrivate unsigned int ConvertFromSocketType(const PXSocketType socketType);

	PXPrivate IPAdressFamily ConvertToIPAdressFamily(const unsigned int ipMode);
	PXPrivate unsigned int ConvertFromIPAdressFamily(const IPAdressFamily ipMode);


	PXPublic void PXSocketConstruct(PXSocket* const pxSocket);
	PXPublic void PXSocketDestruct(PXSocket* const pxSocket);

	PXPublic PXActionResult PXSocketCreate
	(
		PXSocket* const pxSocket,
		const IPAdressFamily adressFamily,
		const PXSocketType socketType,
		const ProtocolMode protocolMode
	);

	PXPublic PXActionResult PXSocketConnect(PXSocket* const pxSocket);

	PXPublic PXActionResult PXSocketSetupAdress
	(
		PXSocket* const pxSocketList,
		const PXSize PXSocketListSizeMax,
		PXSize* PXSocketListSize,
		PXSocketAdressSetupInfo* const pxSocketAdressSetupInfo,
		const PXSize pxSocketAdressSetupInfoSize
	);

	PXPublic PXBool PXSocketIsCurrentlyUsed(PXSocket* const pxSocket);
	PXPublic void PXSocketClose(PXSocket* const pxSocket);

	PXPublic void PXSocketStateChange(PXSocket* const pxSocket, const PXSocketState socketState);

	PXPublic void PXSocketEventPull(PXSocket* const pxSocket, void* const buffer, const PXSize bufferSize);
	PXPublic void PXSocketEventReadRegister(PXSocket* const pxSocket, const PXSocketID socketID);
	PXPublic void PXSocketEventReadUnregister(PXSocket* const pxSocket, const PXSocketID socketID);

	PXPublic void PXSocketReadPendingHandle(PXSocket* const pxSocket, const PXSocketID socketID);

	PXPublic PXActionResult PXSocketBind(PXSocket* const pxSocket);
	PXPublic PXActionResult PXSocketOptionsSet(PXSocket* const pxSocket);
	PXPublic PXActionResult PXSocketListen(PXSocket* const pxSocket);
	PXPublic PXActionResult PXSocketAccept(PXSocket* server, PXSocket* client);

	PXPublic PXActionResult PXSocketSend(PXSocket* const pxSocket, const void* inputBuffer, const PXSize inputBufferSize, PXSize* inputBytesWritten);
	PXPublic PXActionResult PXSocketReceive(PXSocket* const pxSocket, const void* outputBuffer, const PXSize outputBufferSize, PXSize* outputBytesWritten);

#if OSWindows
	PXPrivate PXActionResult WindowsSocketAgentStartup(void);
	PXPrivate PXActionResult WindowsSocketAgentShutdown(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
