#pragma once

namespace BF
{
    enum class IPVersion
    {
        IPVersionInvalid,
        IPVersionUnknownDomain,

        IPVersion4,
        IPVersion6
    };

    IPVersion AnalyseIPVersion(const char* ip);
    char IsValidIP(const char* ipAdress);
    char IsValidIPv4(const char* ipv4Adress);
    char IsValidIPv6(const char* ipv6Adress);
}