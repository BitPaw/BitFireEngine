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
    ByteA = byteA;
    ByteB = byteB;
    ByteC = byteC;
    ByteD = byteD;
}

unsigned int BF::DoubleWord::ExtractInt(EndianType endianType)
{
    switch (endianType)
    {
        case BF::EndianType::Big:
            return (ByteA << 24) | (ByteB << 16) | (ByteC << 8) | (ByteD);

        default:
        case BF::EndianType::Little:
            return (ByteA) | (ByteB << 8) | (ByteC << 16) | (ByteD << 24);        
    }
}

unsigned int BF::DoubleWord::InsertInt(EndianType endianType, unsigned int value)
{
    return 0;
}
