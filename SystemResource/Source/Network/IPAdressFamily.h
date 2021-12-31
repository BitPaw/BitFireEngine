#pragma once

namespace BF
{
	enum class IPAdressFamily
	{
		Invalid,

		Unspecified, // unspecified
		UNIX, // local to host (pipes, portals)
		INET, // internetwork: UDP, TCP, etc.
		IMPLINK, // arpanet imp addresses
		PUP, // pup protocols: e.g. BSP
		CHAOS, // mit CHAOS protocols
		NS, // XEROX NS protocols
		IPX, // IPX protocols: IPX, SPX, etc.
		ISO, // ISO protocols
		OSI, // OSI is ISO
		ECMA, // european computer manufacturers
		DATAKIT, // datakit protocols
		CCITT, // CCITT protocols, X.25 etc
		SNA, // IBM SNA
		DECnet, // DECnet
		DLI, // Direct data link interface
		LAT, // LAT
		HYLINK, // NSC Hyperchannel
		APPLETALK, // AppleTalk
		NETBIOS, // NetBios-style addresses
		VOICEVIEW, // VoiceView
		FIREFOX, // Protocols from Firefox
		UNKNOWN1, // Somebody is using this!
		BAN, // Banyan
		ATM, // Native ATM Services
		INET6, // Internetwork Version 6
		CLUSTER, // Microsoft Wolfpack
		IEEE12844, // IEEE 1284.4 WG AF
		IRDA, // IrDA
		NETDES, // Network Designers OSI & gateway
		MAX, // depends
		LINK,
		HYPERV,
		BTH, // Bluetooth RFCOMM/L2CAP protocols
		TCNPROCESS,
		TCNMESSAGE,
		ICLFXBM
	};

	IPAdressFamily ConvertIPAdressFamily(unsigned int ipMode);
	unsigned int ConvertIPAdressFamily(IPAdressFamily ipMode);
}