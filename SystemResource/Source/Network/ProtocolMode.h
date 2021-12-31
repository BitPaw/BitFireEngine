#pragma once

namespace BF
{
	enum class ProtocolMode
	{
        Invalid,

        HOPOPTS,  // IPv6 Hop-by-Hop options
        ICMP,
        IGMP,
        GGP,
        IPV4,
        ST,
        TCP,
        CBT,
        EGP,
        IGP,
        PUP,
        UDP,
        IDP,
        RDP,
        IPV6, // IPv6 header
        ROUTING, // IPv6 Routing header
        FRAGMENT, // IPv6 fragmentation header
        ESP, // encapsulating security payload
        AH, // authentication header
        ICMPV6, // ICMPv6
        NONE, // IPv6 no next header
        DSTOPTS, // IPv6 Destination options
        ND,
        ICLFXBM,
        PIM,
        PGM,
        L2TP,
        SCTP,
        RAW,
        MAX,
        //
        //  These are reserved for internal use by Windows.
        //
        WindowsRAW,
        WindowsIPSEC,
        WindowsIPSECOFFLOAD,
        WindowsWNV,
        WindowsMAX
	};

	ProtocolMode ConvertProtocolMode(unsigned int protocolMode);
	unsigned int ConvertProtocolMode(ProtocolMode protocolMode);
}