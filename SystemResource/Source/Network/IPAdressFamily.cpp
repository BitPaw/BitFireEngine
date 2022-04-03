#include "IPAdressFamily.h"

#include <OS/OSDefine.h>

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

BF::IPAdressFamily BF::ConvertIPAdressFamily(unsigned int ipMode)
{
	switch (ipMode)
	{
		case IPAF_UNSPEC: return IPAdressFamily::Unspecified;		
		case IPAF_UNIX: return IPAdressFamily::UNIX;
		case IPAF_INET: return IPAdressFamily::INET;
		case IPAF_IMPLINK: return IPAdressFamily::IMPLINK;
		case IPAF_PUP: return IPAdressFamily::PUP;
		case IPAF_CHAOS: return IPAdressFamily::CHAOS;
		case IPAF_NS: return IPAdressFamily::NS;
		//case IPAF_IPX: return IPAdressFamily::IPX;
		case IPAF_ISO: return IPAdressFamily::ISO;
		//case IPAF_OSI: return IPAdressFamily::OSI;
		case IPAF_ECMA: return IPAdressFamily::ECMA;
		case IPAF_DATAKIT: return IPAdressFamily::DATAKIT;
		case IPAF_CCITT: return IPAdressFamily::CCITT;
		case IPAF_SNA: return IPAdressFamily::SNA;
		case IPAF_DECnet: return IPAdressFamily::DECnet;
		case IPAF_DLI: return IPAdressFamily::DLI;
		case IPAF_LAT: return IPAdressFamily::LAT;
		case IPAF_HYLINK: return IPAdressFamily::HYLINK;
		case IPAF_APPLETALK: return IPAdressFamily::APPLETALK;
		case IPAF_NETBIOS: return IPAdressFamily::NETBIOS;
		case IPAF_VOICEVIEW: return IPAdressFamily::VOICEVIEW;
		case IPAF_FIREFOX: return IPAdressFamily::FIREFOX;
		case IPAF_UNKNOWN1: return IPAdressFamily::UNKNOWN1;
		case IPAF_BAN: return IPAdressFamily::BAN;
		//case IPAF_ATM: return IPAdressFamily::ATM;
		case IPAF_INET6: return IPAdressFamily::INET6;
		case IPAF_CLUSTER: return IPAdressFamily::CLUSTER;
		case IPAF_12844: return IPAdressFamily::IEEE12844;
		case IPAF_IRDA: return IPAdressFamily::IRDA;
		case IPAF_NETDES: return IPAdressFamily::NETDES;

		default:
			return IPAdressFamily::Invalid;
	}
}

unsigned int BF::ConvertIPAdressFamily(IPAdressFamily ipMode)
{
	switch (ipMode)
	{
		default:
		case BF::IPAdressFamily::Invalid:
			return IPAF_Invalid;
			
		case BF::IPAdressFamily::Unspecified:
			return IPAF_UNSPEC;
			
		case BF::IPAdressFamily::UNIX:
			return IPAF_UNIX;
			
		case BF::IPAdressFamily::INET:
			return IPAF_INET;
			
		case BF::IPAdressFamily::IMPLINK:
			return IPAF_IMPLINK;
			
		case BF::IPAdressFamily::PUP:
			return IPAF_PUP;
			
		case BF::IPAdressFamily::CHAOS:
			return IPAF_CHAOS;
			
		case BF::IPAdressFamily::NS:
			return IPAF_NS;
			
		case BF::IPAdressFamily::IPX:
			return IPAF_IPX;
			
		case BF::IPAdressFamily::ISO:
			return IPAF_ISO;
			
		case BF::IPAdressFamily::OSI:
			return IPAF_OSI;
			
		case BF::IPAdressFamily::ECMA:
			return IPAF_ECMA;
			
		case BF::IPAdressFamily::DATAKIT:
			return IPAF_DATAKIT;
			
		case BF::IPAdressFamily::CCITT:
			return IPAF_CCITT;
			
		case BF::IPAdressFamily::SNA:
			return IPAF_SNA;
			
		case BF::IPAdressFamily::DECnet:
			return IPAF_DECnet;
			
		case BF::IPAdressFamily::DLI:
			return IPAF_DLI;
			
		case BF::IPAdressFamily::LAT:
			return IPAF_LAT;
			
		case BF::IPAdressFamily::HYLINK:
			return IPAF_HYLINK;
			
		case BF::IPAdressFamily::APPLETALK:
			return IPAF_APPLETALK;
			
		case BF::IPAdressFamily::NETBIOS:
			return IPAF_NETBIOS;
			
		case BF::IPAdressFamily::VOICEVIEW:
			return IPAF_VOICEVIEW;
			
		case BF::IPAdressFamily::FIREFOX:
			return IPAF_FIREFOX;
			
		case BF::IPAdressFamily::UNKNOWN1:
			return IPAF_UNKNOWN1;
			
		case BF::IPAdressFamily::BAN:
			return IPAF_BAN;
			
		case BF::IPAdressFamily::ATM:
			return IPAF_ATM;
			
		case BF::IPAdressFamily::INET6:
			return IPAF_INET6;
			
		case BF::IPAdressFamily::CLUSTER:
			return IPAF_CLUSTER;
			
		case BF::IPAdressFamily::IEEE12844:
			return IPAF_12844;
			
		case BF::IPAdressFamily::IRDA:
			return IPAF_IRDA;
			
		case BF::IPAdressFamily::NETDES:
			return IPAF_NETDES;
			
		case BF::IPAdressFamily::MAX:
			return IPAF_MAX;
			
		case BF::IPAdressFamily::LINK:
			return IPAF_LINK;
			
		case BF::IPAdressFamily::HYPERV:
			return IPAF_HYPERV;
			
		case BF::IPAdressFamily::BTH:
			return IPAF_BTH;
			
		case BF::IPAdressFamily::TCNPROCESS:
			return IPAF_TCNPROCESS;
			
		case BF::IPAdressFamily::TCNMESSAGE:
			return IPAF_TCNMESSAGE;
			
		case BF::IPAdressFamily::ICLFXBM:
			return IPAF_ICLFXBM;
	}
}
