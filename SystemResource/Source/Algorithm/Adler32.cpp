#include "Adler32.h"

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
