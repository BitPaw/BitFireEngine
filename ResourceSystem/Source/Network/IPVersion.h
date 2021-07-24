#ifndef IPTypeIncluded
#define IPTypeIncluded

enum class IPVersion
{
    IPVersionInvalid,
    IPVersionUnknownDomain,

    IPVersion4,
    IPVersion6
};

IPVersion AnalyseIPVersion(char* ip);
char IsValidIP(char* ipAdress);
char IsValidIPv4(char* ipv4Adress);
char IsValidIPv6(char* ipv6Adress);

#endif