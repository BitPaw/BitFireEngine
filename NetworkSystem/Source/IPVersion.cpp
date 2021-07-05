#include "IPVersion.h"

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
char IsValidIPv4(char* ipAdress)
{
    const unsigned char resultIPv4OK = 0;
    const unsigned char resultIPv4NullPointer = 1;
    const unsigned char resultIPv4InvalidCharacter = 2;
    const unsigned char resultIPv4OctetTooLarge = 3;
    const unsigned char resultIPv4InvalidLength = 4;
    const unsigned char resultIPv4InvalidOctetAmount = 5;

    const unsigned char expectedDots = 3;
    const unsigned char minimalSize = 7; // 0.0.0.0
    const unsigned char maximalSize = 15; //255.255.255.255

    unsigned int index = 0;
    unsigned int length = 0;
    unsigned int countedDots = 0;
    unsigned char hasValidLength = 0;
    unsigned char hasEnoghDots = 0;

    unsigned short octetValue = 0;

    if (ipAdress == 0)
    {
        return resultIPv4NullPointer;
    }

    for (; ipAdress[index] != '\0' && index < maximalSize; index++)
    {
        char character = ipAdress[index];
        char isDot = character == '.';
        char isValidCharacter = (character >= '0' && character <= '9') || character;

        if (!isValidCharacter)
        {
            return resultIPv4InvalidCharacter;
        }

        if (isDot)
        {
            countedDots++;
            octetValue = 0;
        }
        else
        {
            octetValue *= 10; // "Shft number to left" Example 12 -> 120
            octetValue += (character - '0'); // ASCII character to actual number.

            if (octetValue > 255) // Is in 8-Bit range? Can be 0-255 only
            {
                return resultIPv4OctetTooLarge;
            }
        }

        length++;
    }

    hasValidLength = length >= minimalSize && length <= maximalSize;
    hasEnoghDots = countedDots == expectedDots;

    if (!hasValidLength)
    {
        return resultIPv4InvalidLength;
    }

    if (!hasEnoghDots)
    {
        return resultIPv4InvalidOctetAmount;
    }

    return resultIPv4OK;
}

// todo : Comple this function.
char IsValidIPv6(char* ipAdress)
{
    const char validIPv6Adress = 0;
    const char invalidAmountOfSeperators = 1;
    
    const char seperator = ':';
    const int expectedAmountOfSeperators = 7;
    unsigned char seperatorCounter = 0;
    unsigned int lengh = 0;
    unsigned int maxLength = 32;
    unsigned int minLength = 2;


    for ( ; ipAdress[lengh] != '\0' && lengh <= maxLength; lengh++)
    {
        char character = ipAdress[lengh];
        char isSeperator = character == seperator;

        if (isSeperator)
        {
            if (++seperatorCounter > 7)
            {
                return invalidAmountOfSeperators;
            }
        }
    }

    return validIPv6Adress;
}

IPVersion AnalyseIPVersion(char* ip)
{
    IPVersion ipVersion = IPVersion::IPVersionInvalid;

    char containsDot = 0;
    char containsDoubleDot = 0;
    char containsHexadezimal = 0;
    char textChars = 0;
    char containsNumbers = 0;

    for (int index = 0; ip[index] != '\0'; index++)
    {
        char character = ip[index];
        char isNumber = character >= '0' && character <= '9';
        char isBetweenAToF = (character >= 'a' && character <= 'f') || (character >= 'A' && character <= 'F');     
        char isDot = character == '.';
        char isDoubleDot = character == ':';
        char isTextChars = !isNumber && !isBetweenAToF && !isDot && !isDoubleDot;

        if (isTextChars)
            textChars++;

        if (isNumber)  
            containsNumbers++;   

        if (isBetweenAToF) 
            containsHexadezimal++;

        if (isDot) 
            containsDot++;

        if (isDoubleDot)
            containsDoubleDot++;


        if (isDot)
        {
            return IPVersion::IPVersion4;
        }

        if (isDoubleDot)
        {
            return IPVersion::IPVersion6;
        }
    }

    if (containsNumbers && containsDot && !containsDoubleDot && !containsHexadezimal && !textChars)
    {
        return IPVersion::IPVersion4;
    }

    if (containsNumbers && containsDoubleDot && containsHexadezimal && !textChars && !containsDot)
    {
        return IPVersion::IPVersion6;
    }

    if (!containsDoubleDot)
    {
        return IPVersion::IPVersionUnknownDomain;
    }


    return IPVersion::IPVersionInvalid;
}

char IsValidIP(char* ipAdress)
{
    IPVersion ipVersion = AnalyseIPVersion(ipAdress);

    switch (ipVersion)
    {  
        case IPVersion::IPVersion4:
        {
            return IsValidIPv4(ipAdress) == 0;
        }
        case IPVersion::IPVersionUnknownDomain:
        {
            return 1;
        }
        case IPVersion::IPVersion6:
        {
            return IsValidIPv6(ipAdress) == 0;
        }

        default:
        case IPVersion::IPVersionInvalid:
        {
            return 0;
        }
    }
}
