#include "Adler32.h"

BF::Adler32::Adler32()
{
    Value = 0;
    IsValid = false;
}

BF::Adler32::Adler32(unsigned int value)
{
    Value = value;
    IsValid = false;
}

unsigned int BF::Adler32::Check(unsigned char* data, size_t length)
{
    const size_t adlerModolo = 65521u;
    size_t a = 1;
    size_t b = 0;

    for (size_t index = 0; index < length; ++index)
    {
        a = (a + data[index]) % adlerModolo;
        b = (b + a) % adlerModolo;
    }

    return (b << 16) | a;
}

unsigned int BF::Adler32::Create(size_t adler, const unsigned char* data, size_t length)
{
    size_t s1 = adler & 0xffffu;
    size_t s2 = (adler >> 16u) & 0xffffu;

    while (length != 0u)
    {
        /*at least 5552 sums can be done before the sums overflow, saving a lot of module divisions*/
        size_t amount = length > 5552u ? 5552u : length;
        length -= amount;

        for (size_t i = 0; i != amount; ++i)
        {
            s1 += (*data++);
            s2 += s1;
        }

        s1 %= 65521u;
        s2 %= 65521u;
    }

    return (s2 << 16u) | s1;
}