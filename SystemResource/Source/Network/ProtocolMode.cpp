#include "ProtocolMode.h"

#define ProtocolInvalid -1
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

BF::ProtocolMode BF::ConvertProtocolMode(unsigned int protocolMode)
{
	switch (protocolMode)
	{      
        case ProtocolHOPOPTS:
            return BF::ProtocolMode::HOPOPTS;

        case ProtocolICMP:
            return BF::ProtocolMode::ICMP;

        case ProtocolIGMP:
            return BF::ProtocolMode::IGMP;

        case ProtocolGGP:
            return BF::ProtocolMode::GGP;

        case ProtocolIPV4:
            return BF::ProtocolMode::IPV4;

        case ProtocolST:
            return BF::ProtocolMode::ST;

        case ProtocolTCP:
            return BF::ProtocolMode::TCP;

        case ProtocolCBT:
            return BF::ProtocolMode::CBT;

        case ProtocolEGP:
            return BF::ProtocolMode::EGP;

        case ProtocolIGP:
            return BF::ProtocolMode::IGP;

        case ProtocolPUP:
            return BF::ProtocolMode::PUP;

        case ProtocolUDP:
            return BF::ProtocolMode::UDP;

        case ProtocolIDP:
            return BF::ProtocolMode::IDP;

        case ProtocolRDP:
            return BF::ProtocolMode::RDP;

        case ProtocolIPV6:
            return BF::ProtocolMode::IPV6;

        case ProtocolROUTING:
            return BF::ProtocolMode::ROUTING;

        case ProtocolFRAGMENT:
            return BF::ProtocolMode::FRAGMENT;

        case ProtocolESP:
            return BF::ProtocolMode::ESP;

        case ProtocolAH:
            return BF::ProtocolMode::AH;

        case ProtocolICMPV6:
            return BF::ProtocolMode::ICMPV6;

        case ProtocolNONE:
            return BF::ProtocolMode::NONE;

        case ProtocolDSTOPTS:
            return BF::ProtocolMode::DSTOPTS;

        case ProtocolND:
            return BF::ProtocolMode::ND;

        case ProtocolICLFXBM:
            return BF::ProtocolMode::ICLFXBM;

        case ProtocolPIM:
            return BF::ProtocolMode::PIM;

        case ProtocolPGM:
            return BF::ProtocolMode::PGM;

        case ProtocolL2TP:
            return BF::ProtocolMode::L2TP;

        case ProtocolSCTP:
            return BF::ProtocolMode::SCTP;

        case ProtocolRAW:
            return BF::ProtocolMode::RAW;

        case ProtocolMAX:
            return BF::ProtocolMode::MAX;

        case ProtocolWindowsRAW:
            return BF::ProtocolMode::WindowsRAW;

        case ProtocolWindowsIPSEC:
            return BF::ProtocolMode::WindowsIPSEC;

        case ProtocolWindowsIPSECOFFLOAD:
            return BF::ProtocolMode::WindowsIPSECOFFLOAD;

        case ProtocolWindowsWNV:
            return BF::ProtocolMode::WindowsWNV;

        case ProtocolWindowsMAX:
            return BF::ProtocolMode::WindowsMAX;

        default:
            return BF::ProtocolMode::Invalid;
	}
}

unsigned int BF::ConvertProtocolMode(ProtocolMode protocolMode)
{
    switch (protocolMode)
    {
        default:
        case BF::ProtocolMode::Invalid:
            return ProtocolInvalid;

        case BF::ProtocolMode::HOPOPTS:
            return ProtocolHOPOPTS;

        case BF::ProtocolMode::ICMP:
            return ProtocolICMP;

        case BF::ProtocolMode::IGMP:
            return ProtocolIGMP;

        case BF::ProtocolMode::GGP:
            return ProtocolGGP;

        case BF::ProtocolMode::IPV4:
            return ProtocolIPV4;

        case BF::ProtocolMode::ST:
            return ProtocolST;

        case BF::ProtocolMode::TCP:
            return ProtocolTCP;

        case BF::ProtocolMode::CBT:
            return ProtocolCBT;

        case BF::ProtocolMode::EGP:
            return ProtocolEGP;

        case BF::ProtocolMode::IGP:
            return ProtocolIGP;

        case BF::ProtocolMode::PUP:
            return ProtocolPUP;

        case BF::ProtocolMode::UDP:
            return ProtocolUDP;

        case BF::ProtocolMode::IDP:
            return ProtocolIDP;

        case BF::ProtocolMode::RDP:
            return ProtocolRDP;

        case BF::ProtocolMode::IPV6:
            return ProtocolIPV6;

        case BF::ProtocolMode::ROUTING:
            return ProtocolROUTING;

        case BF::ProtocolMode::FRAGMENT:
            return ProtocolFRAGMENT;

        case BF::ProtocolMode::ESP:
            return ProtocolESP;

        case BF::ProtocolMode::AH:
            return ProtocolAH;

        case BF::ProtocolMode::ICMPV6:
            return ProtocolICMPV6;

        case BF::ProtocolMode::NONE:
            return ProtocolNONE;

        case BF::ProtocolMode::DSTOPTS:
            return ProtocolDSTOPTS;

        case BF::ProtocolMode::ND:
            return ProtocolND;

        case BF::ProtocolMode::ICLFXBM:
            return ProtocolICLFXBM;

        case BF::ProtocolMode::PIM:
            return ProtocolPIM;

        case BF::ProtocolMode::PGM:
            return ProtocolPGM;

        case BF::ProtocolMode::L2TP:
            return ProtocolL2TP;

        case BF::ProtocolMode::SCTP:
            return ProtocolSCTP;

        case BF::ProtocolMode::RAW:
            return ProtocolRAW;

        case BF::ProtocolMode::MAX:
            return ProtocolMAX;

        case BF::ProtocolMode::WindowsRAW:
            return ProtocolWindowsRAW;

        case BF::ProtocolMode::WindowsIPSEC:
            return ProtocolWindowsIPSEC;

        case BF::ProtocolMode::WindowsIPSECOFFLOAD:
            return ProtocolWindowsIPSECOFFLOAD;

        case BF::ProtocolMode::WindowsWNV:
            return ProtocolWindowsWNV;

        case BF::ProtocolMode::WindowsMAX:
            return ProtocolWindowsMAX;
    }
}