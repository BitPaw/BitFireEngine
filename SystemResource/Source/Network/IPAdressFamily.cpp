#include "IPAdressFamily.h"

#include "../OSDefine.h"

#if defined(OSUnix)
#elif defined(OSWindows)
#include <WinSock2.h>
#endif

#define AF_Invalid 0xFF

BF::IPAdressFamily BF::ConvertIPAdressFamily(unsigned int ipMode)
{
	switch (ipMode)
	{
		case AF_UNSPEC: return IPAdressFamily::Unspecified;		
		case AF_UNIX: return IPAdressFamily::UNIX;
		case AF_INET: return IPAdressFamily::INET;
		case AF_IMPLINK: return IPAdressFamily::IMPLINK;
		case AF_PUP: return IPAdressFamily::PUP;
		case AF_CHAOS: return IPAdressFamily::CHAOS;
		case AF_NS: return IPAdressFamily::NS;
		//case AF_IPX: return IPAdressFamily::IPX;
		case AF_ISO: return IPAdressFamily::ISO;
		//case AF_OSI: return IPAdressFamily::OSI;
		case AF_ECMA: return IPAdressFamily::ECMA;
		case AF_DATAKIT: return IPAdressFamily::DATAKIT;
		case AF_CCITT: return IPAdressFamily::CCITT;
		case AF_SNA: return IPAdressFamily::SNA;
		case AF_DECnet: return IPAdressFamily::DECnet;
		case AF_DLI: return IPAdressFamily::DLI;
		case AF_LAT: return IPAdressFamily::LAT;
		case AF_HYLINK: return IPAdressFamily::HYLINK;
		case AF_APPLETALK: return IPAdressFamily::APPLETALK;
		case AF_NETBIOS: return IPAdressFamily::NETBIOS;
		case AF_VOICEVIEW: return IPAdressFamily::VOICEVIEW;
		case AF_FIREFOX: return IPAdressFamily::FIREFOX;
		case AF_UNKNOWN1: return IPAdressFamily::UNKNOWN1;
		case AF_BAN: return IPAdressFamily::BAN;
		case AF_ATM: return IPAdressFamily::ATM;
		case AF_INET6: return IPAdressFamily::INET6;
		case AF_CLUSTER: return IPAdressFamily::CLUSTER;
		case AF_12844: return IPAdressFamily::IEEE12844;
		case AF_IRDA: return IPAdressFamily::IRDA;
		case AF_NETDES: return IPAdressFamily::NETDES;

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
			return AF_Invalid;
			
		case BF::IPAdressFamily::Unspecified:
			return AF_UNSPEC;
			
		case BF::IPAdressFamily::UNIX:
			return AF_UNIX;
			
		case BF::IPAdressFamily::INET:
			return AF_INET;
			
		case BF::IPAdressFamily::IMPLINK:
			return AF_IMPLINK;
			
		case BF::IPAdressFamily::PUP:
			return AF_PUP;
			
		case BF::IPAdressFamily::CHAOS:
			return AF_CHAOS;
			
		case BF::IPAdressFamily::NS:
			return AF_NS;
			
		case BF::IPAdressFamily::IPX:
			return AF_IPX;
			
		case BF::IPAdressFamily::ISO:
			return AF_ISO;
			
		case BF::IPAdressFamily::OSI:
			return AF_OSI;
			
		case BF::IPAdressFamily::ECMA:
			return AF_ECMA;
			
		case BF::IPAdressFamily::DATAKIT:
			return AF_DATAKIT;
			
		case BF::IPAdressFamily::CCITT:
			return AF_CCITT;
			
		case BF::IPAdressFamily::SNA:
			return AF_SNA;
			
		case BF::IPAdressFamily::DECnet:
			return AF_DECnet;
			
		case BF::IPAdressFamily::DLI:
			return AF_DLI;
			
		case BF::IPAdressFamily::LAT:
			return AF_LAT;
			
		case BF::IPAdressFamily::HYLINK:
			return AF_HYLINK;
			
		case BF::IPAdressFamily::APPLETALK:
			return AF_APPLETALK;
			
		case BF::IPAdressFamily::NETBIOS:
			return AF_NETBIOS;
			
		case BF::IPAdressFamily::VOICEVIEW:
			return AF_VOICEVIEW;
			
		case BF::IPAdressFamily::FIREFOX:
			return AF_FIREFOX;
			
		case BF::IPAdressFamily::UNKNOWN1:
			return AF_UNKNOWN1;
			
		case BF::IPAdressFamily::BAN:
			return AF_BAN;
			
		case BF::IPAdressFamily::ATM:
			return AF_ATM;
			
		case BF::IPAdressFamily::INET6:
			return AF_INET6;
			
		case BF::IPAdressFamily::CLUSTER:
			return AF_CLUSTER;
			
		case BF::IPAdressFamily::IEEE12844:
			return AF_12844;
			
		case BF::IPAdressFamily::IRDA:
			return AF_IRDA;
			
		case BF::IPAdressFamily::NETDES:
			return AF_NETDES;
			
		case BF::IPAdressFamily::MAX:
			return AF_MAX;
			
		case BF::IPAdressFamily::LINK:
			return AF_LINK;
			
		case BF::IPAdressFamily::HYPERV:
			return AF_HYPERV;
			
		case BF::IPAdressFamily::BTH:
			return AF_BTH;
			
		case BF::IPAdressFamily::TCNPROCESS:
			return AF_TCNPROCESS;
			
		case BF::IPAdressFamily::TCNMESSAGE:
			return AF_TCNMESSAGE;
			
		case BF::IPAdressFamily::ICLFXBM:
			return AF_ICLFXBM;
	}
}
