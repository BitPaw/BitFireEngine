#include "IPAdressInfo.h"

#include <string.h>

BF::IPAdressInfo::IPAdressInfo()
{
    SocketID = -1;

    for (size_t i = 0; i < IPv6LengthMax; i++)
    {
        IP[i] = 0;
        IPRawByte[i] = 0;
    }

    Port = 0;
    Protocol = ProtocolMode::Invalid;
    Family = IPAdressFamily::Invalid; 
    Type = SocketType::Invalid;  

    IPRawByteSize = 0;
}

BF::IPAdressInfo::IPAdressInfo(AdressInfoType& adressInfo)
{
    ConvertFrom(adressInfo);
}

void BF::IPAdressInfo::ConvertFrom(AdressInfoType& adressInfo)
{
    struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)adressInfo.ai_addr;
    const char* result = nullptr;

    memset(IP, 0, IPv6LengthMax);
    result = inet_ntop(adressInfo.ai_family, &ipv6->sin6_addr, IP, IPv6LengthMax);

    switch (adressInfo.ai_family)
    {
        case AF_INET:
        {
            Port = ntohs((((struct sockaddr_in*)adressInfo.ai_addr)->sin_port));
            break;
        }
        case AF_INET6:
        {
            Port = ntohs((((struct sockaddr_in6*)adressInfo.ai_addr)->sin6_port));
            break;
        }
        default:
        {
            Port = 0;
            break;
        }
    }

    Protocol = ConvertProtocolMode(adressInfo.ai_protocol);
    Family = ConvertIPAdressFamily(adressInfo.ai_family);
    Type = ConvertSocketType(adressInfo.ai_socktype);

    IPRawByteSize = adressInfo.ai_addrlen;
    memcpy(IPRawByte, adressInfo.ai_addr, adressInfo.ai_addrlen);
}

void BF::IPAdressInfo::ConvertTo(AdressInfoType& adressInfo)
{
    // TODO: implement
}

void BF::IPAdressInfo::IPFromBinaryFormat()
{
    const char* result = inet_ntop(ConvertIPAdressFamily(Family), IPRawByte, IP, IPv6LengthMax);
}

void BF::IPAdressInfo::IPToBinaryFormat()
{
    int result = inet_pton(ConvertIPAdressFamily(Family), IP, IPRawByte);
}