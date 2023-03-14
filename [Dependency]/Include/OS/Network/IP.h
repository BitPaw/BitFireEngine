#ifndef IPInclude
#define IPInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum IPVersion_
    {
        IPVersionInvalid,
        IPVersionUnknownDomain,
        IPVersion4,
        IPVersion6
    }
    IPVersion;

    IPVersion AnalyseIPVersion(const char* ip);
    PXPublic unsigned char IsValidIP(const char* ipAdress);
    /*
  Check if the given IPv4 is Valid

  Returns the following:
  0 - Valid IPv4
  1 - Nullpointer as Parameter
  2 - Invalid Character (only 0-9 or .)
  3 - Octet too large (>255)
  4 - Too long (>15)
  5 - Too many Octets (more that 4)
*/
    PXPublic unsigned char IPv4CheckIfValid(const char* ipv4Adress);
    PXPublic unsigned char IPv6CheckIfValid(const char* ipv6Adress);

#ifdef __cplusplus
}
#endif

#endif

