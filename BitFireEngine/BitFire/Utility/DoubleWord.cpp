#include "DoubleWord.h"

BF::DoubleWord::DoubleWord()
{
    Set(0, 0, 0, 0);
}

BF::DoubleWord::DoubleWord(unsigned char byteA, unsigned char byteB, unsigned  char byteC, unsigned char byteD)
{
    Set(byteA, byteB, byteC, byteD);
}

void BF::DoubleWord::Set(unsigned char byteA, unsigned  char byteB, unsigned char byteC, unsigned  char byteD)
{
    ByteData[0] = byteA;
    ByteData[1] = byteB;
    ByteData[2] = byteC;
    ByteData[3] = byteD;
}

unsigned int BF::DoubleWord::ExtractInt(EndianType endianType)
{
    switch (endianType)
    {
        case EndianType::Big:
            return 
                (ByteData[0] << 24) |
                (ByteData[1] << 16) |
                (ByteData[2] << 8) |
                (ByteData[3]);

        default:
        case EndianType::Little:
            return 
                (ByteData[0]) |
                (ByteData[1] << 8) |
                (ByteData[2] << 16) |
                (ByteData[3] << 24);
    }
}

unsigned int BF::DoubleWord::InsertInt(EndianType endianType, unsigned int value)
{
    return 0;
}
