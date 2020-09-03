#include "Converter.h"

unsigned int Converter::ConvertHexadezimalToDezimal(unsigned char hex)
{
        switch (hex)
        {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;

        case 'a': 
        case 'A': return 10;
        case 'b': 
        case 'B': return 11;
        case 'c': 
        case 'C': return 12;
        case 'd':
        case 'D': return 13;
        case 'e': 
        case 'E': return 14;
        case 'f': 
        case 'F': return 15;
        }
   

        return -1;
}

unsigned int Converter::CovertByteToNumber(EndianType type, std::vector<unsigned char> bytes)
{
    unsigned int lenght = bytes.size();
    unsigned int value = 0;
    unsigned int rotation = 1;
    unsigned int dynNumber = 0;

    for (unsigned int i = 0; i < lenght; i++)
    {
        unsigned int byte;
        unsigned int bitShitftIndex;
        unsigned int bitShitftValue;

        if (type == EndianType::Big)
        {
            bitShitftIndex = i;
        }
        else
        {
            bitShitftIndex = lenght - i - 1;
        }       

        byte = bytes.at(bitShitftIndex);
        bitShitftIndex = 8 * (bitShitftIndex);

        value = value | byte << bitShitftIndex;
    }

    /*

    
           unsigned char byte = 

        dynNumber = bytes.at << (8 * (i + 1)

        //value = value << (8 * (i + 1));

        if (type == EndianType::Big)
        {
            value = value | bytes.at(i);
        }
        else
        {
            value = value | bytes.at((lenght - 1) - i);
        }
    
    */

    return value;
}

unsigned int Converter::ConvertTwoBytesToNumber(EndianType type, unsigned char byteA, unsigned char byteB)
{
    std::vector<unsigned char> bytes;

    bytes.reserve(2);

    bytes.push_back(byteA);
    bytes.push_back(byteB);

    unsigned int result = CovertByteToNumber(type, bytes);

    printf("%02x %02x = %u\n", byteA, byteB, result);

    return result;
}

unsigned int Converter::Convert4BytesToNumber(EndianType type, unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned char byteD)
{
    std::vector<unsigned char> bytes;

    bytes.reserve(4);

    bytes.push_back(byteA);
    bytes.push_back(byteB);
    bytes.push_back(byteC);
    bytes.push_back(byteD);

    unsigned int result = CovertByteToNumber(type, bytes);

    printf("%02x %02x %02x %02x = %u\n", byteA, byteB, byteC, byteD, result);

    return result;
}
